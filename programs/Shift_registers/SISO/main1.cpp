#include <systemc.h>

SC_MODULE(siso)
{
	sc_in<sc_logic> d;
	sc_out<sc_logic> r;
    sc_out<sc_lv<4>> state;   // ADD THIS
	sc_in<bool> clk;
	sc_lv<4> temp;
    
	void compute_siso()
	{
			state.write(temp);   // send internal register out
		r.write(temp[3]);
		temp[3]=temp[2];
		temp[2]=temp[1];
		temp[1]=temp[0];
		temp[0]=d.read();
	}
	SC_CTOR(siso)
	{
        temp ="0000";
		SC_METHOD(compute_siso);
		sensitive<<clk.pos();
	}
};


SC_MODULE(driver)
{
	sc_out<sc_logic> d;
	sc_in<bool> clk;

	void inputs()
	{
		wait();
		d = sc_logic_1;
		wait();
		d = sc_logic_0;
		wait();
		d = sc_logic_1;
		wait();
		d = sc_logic_0;
		wait();
        d = sc_logic_1;
		wait();
		d = sc_logic_0;
		wait();
		d = sc_logic_1;
		wait();
		d = sc_logic_0;
		wait();
		
	}
		SC_CTOR(driver)
		{
			SC_THREAD(inputs);
			sensitive <<clk.pos();
		}
	
};


SC_MODULE(monitor)
{
	sc_in<sc_logic> d,r;
	sc_in<sc_lv<4>> state;
	sc_in<bool> clk;

	void mon()
	{
            cout<<"@"<<sc_time_stamp()
            <<" Input D: "<<d.read()
            <<" Output Q: "<<r.read()
             << " REG: " << state.read()
            <<endl;
	}

	SC_CTOR(monitor)
	{
		SC_METHOD(mon);
		sensitive<<clk.pos();
	}
};




int sc_main(int argc, char* argv[])
{
	sc_signal<sc_logic> d,r;
	sc_signal<sc_lv<4>> reg_sig;
    sc_signal<sc_lv<4>> state_sig;
	sc_clock  testclk("testclock",10,SC_NS,0.5);
    d.write(SC_LOGIC_0);

	siso siso1("siso");
	driver drive("driver");
	monitor mon("monitor");

	siso1.d(d); siso1.r(r); siso1.clk(testclk); siso1.state(state_sig); 
	drive.d(d); drive.clk(testclk); 
	mon.d(d); mon.r(r); mon.clk(testclk);  mon.state(state_sig);
	// waveform

	sc_trace_file *Tf;
	Tf = sc_create_vcd_trace_file("traces");
	sc_trace(Tf, d, "d");
	sc_trace(Tf, r, "r");
	sc_trace(Tf,testclk,"testclk");
	
	sc_start(120, SC_NS);
	sc_close_vcd_trace_file(Tf);
	return 0; 
}




















