/*
* Design a SysemC module which implements an 8 bit
* shift register where insertion takes place at the
* fouth bit and the third bit is dispossed. LSB is
* considered to be bit 1.
*/

#include <systemc.h>

// ================= DUT =================
SC_MODULE(siso)
{
    sc_in<sc_logic> d;
    sc_out<sc_logic> r;
    sc_out<sc_lv<8>> reg_out;   // add this
    sc_in<bool> clk;

    sc_lv<8> temp = "00000000";   // changed to 8-bit

    void compute_siso()
    {
        sc_lv<8> old = temp; 
        reg_out.write(temp);
        r.write(old[7]);  // output MSB (bit 8)

        // shift + custom logic
        temp[0] = old[1];   // bit1 <- bit2
        temp[1] = old[2];   // bit2 <- bit3
        temp[2] = old[3];   // bit3 <- bit4 (bit3 discarded)
        temp[3] = d.read();  // bit4 <- input
        temp[4] = old[5];   // bit5 <- bit6
        temp[5] = old[6];   // bit6 <- bit7
        temp[6] = old[7];   // bit7 <- bit8
        temp[7] = old[0];   // bit8 hold
    }

    SC_CTOR(siso)
    {   
        temp = "00000000";
        SC_METHOD(compute_siso);
        sensitive << clk.pos();
    }
};

// ================= DRIVER =================
SC_MODULE(driver)
{
    sc_out<sc_logic> d;
    sc_in<bool> clk;

    void inputs()
    {
        d.write(SC_LOGIC_1);
        wait();

        d.write(SC_LOGIC_1); wait();
        d.write(SC_LOGIC_1); wait();
        d.write(SC_LOGIC_0); wait();
        d.write(SC_LOGIC_1); wait();
        d.write(SC_LOGIC_1); wait();
        d.write(SC_LOGIC_0); wait();
        d.write(SC_LOGIC_1); wait();
        d.write(SC_LOGIC_0); wait();
    }

    SC_CTOR(driver)
    {
        SC_THREAD(inputs);
        sensitive << clk.pos();
    }
};

// ================= MONITOR =================
SC_MODULE(monitor)
{
    sc_in<sc_logic> d, r;
    sc_in<sc_lv<8>> reg_sig;
    sc_in<bool> clk;

    void mon()
    {
        cout << sc_time_stamp()
             << " Input D: " << d.read()
             << " Output R: " << r.read()
             << " REG=" << reg_sig.read()
             << endl;
    }

    SC_CTOR(monitor)
    {
        SC_METHOD(mon);
        sensitive << clk.pos();
    }
};

// ================= MAIN =================
int sc_main(int argc, char* argv[])
{
    sc_signal<sc_logic> d, r;
    sc_signal<sc_lv<8>> reg_sig;
    sc_clock testclk("testclock", 10, SC_NS, 0.5);

    siso siso1("siso");
    driver drive("driver");
    monitor mon("monitor");

    siso1.d(d); siso1.r(r); siso1.clk(testclk); siso1.reg_out(reg_sig);
    drive.d(d); drive.clk(testclk);
    mon.d(d); mon.r(r); mon.clk(testclk); mon.reg_sig(reg_sig);

    // waveform
    sc_trace_file *Tf;
    Tf = sc_create_vcd_trace_file("traces");

    sc_trace(Tf, d, "d");
    sc_trace(Tf, r, "r");
    sc_trace(Tf, testclk, "clk");
    
    d.write(SC_LOGIC_0);
    sc_start(160, SC_NS);

    sc_close_vcd_trace_file(Tf);
    return 0;
}