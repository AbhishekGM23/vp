/*
* Design a 8 bits shift register which rotates right random number of 
* times between 1 and 15 and then rotates left random number of times
* 1 and 15. Initial input can be considered. No subsequent inputs are
* given. Additional 1 bit can be used  for roattion
*/

#include <systemc.h>
#include <cstdlib>
#include <ctime>
#include <bitset>

// ================= DUT =================
SC_MODULE(shift_reg) {
    sc_in<bool> clk;
    sc_out<sc_uint<8>> out;

    sc_uint<8> reg;
    sc_uint<4> count;
    bool dir;   // 0 = right, 1 = left

    void process() {
        while (true) {
            wait();  // clock edge
            out.write(reg);

            // -------- RIGHT ROTATION --------
            dir = 0;
            count = (rand() % 15) + 1;

            cout << "\nRight rotations: " << count << endl;

            for (int i = 0; i < count; i++) {
                wait();
                

                if (dir == 0)
                    reg = (reg >> 1) | (sc_uint<8>(reg[0]) << 7);
                else
                    reg = (reg << 1) | sc_uint<8>(reg[7]);

                out.write(reg);
            }

            // -------- LEFT ROTATION --------
            dir = 1;
            count = (rand() % 15) + 1;

            cout << "Left rotations: " << count << endl;

            for (int i = 0; i < count; i++) {
                wait();

                if (dir == 0)
                    reg = (reg >> 1) | (sc_uint<8>(reg[0]) << 7);
                else
                    reg = (reg << 1) | sc_uint<8>(reg[7]);

                out.write(reg);
            }

            sc_stop(); // stop after one full cycle
        }
    }

    SC_CTOR(shift_reg) {
        SC_THREAD(process);
        sensitive << clk.pos();

        reg = 0b10110011;   // initial input
        srand(time(0));     // seed random generator
    }
};


// ================= DRIVER =================
SC_MODULE(driver) {
    sc_in<bool> clk;

    void drive() {
        while (true) {
            wait();
            cout << "\n@" << sc_time_stamp() << " Driver active" << endl;
        }
    }

    SC_CTOR(driver) {
        SC_THREAD(drive);
        sensitive << clk.pos();
    }
};


// ================= MONITOR =================
SC_MODULE(monitor) {
    sc_in<bool> clk;
    sc_in<sc_uint<8>> data_in;

    void observe() {
        while (true) {
            wait();
            std::bitset<8> b(data_in.read().to_uint());
           
            cout << "@" << sc_time_stamp()
                 << " Output: "
                 << b
                 << endl;
        }
    }

    SC_CTOR(monitor) {
        SC_THREAD(observe);
        sensitive << clk.pos();
    }
};


// ================= TESTBENCH =================
int sc_main(int argc, char* argv[]) {

    sc_clock clk("clk", 1, SC_NS);
    sc_signal<sc_uint<8>> data_sig;

    // Instantiate modules
    shift_reg dut("DUT");
    driver drv("DRIVER");
    monitor mon("MONITOR");

    // Connections
    dut.clk(clk);
    dut.out(data_sig);

    drv.clk(clk);

    mon.clk(clk);
    mon.data_in(data_sig);

    // Waveform dump
    sc_trace_file *tf = sc_create_vcd_trace_file("shift_reg");
    sc_trace(tf, clk, "clk");
    sc_trace(tf, data_sig, "output");

    // Run simulation
    sc_start(200, SC_NS);

    sc_close_vcd_trace_file(tf);

    return 0;
}













// #include <systemc.h>
// #include <cstdlib>
// #include <ctime>

// // ================= DUT =================
// SC_MODULE(siso)
// {
//     sc_out<sc_lv<8>> state;
//     sc_in<bool> clk;

//     sc_lv<8> temp;
//     int count;
//     bool dir; // 0 = right, 1 = left

//     void compute_siso()
//     {
//         // -------- RIGHT ROTATION --------
//         dir = 0;
//         count = (rand() % 15) + 1;

//         cout << "\nRight rotations: " << count << endl;

//         for (int i = 0; i < count; i++)
//         {
//             wait();

//             if (dir == 0)
//             {
//                 // right rotate
//                 sc_logic lsb = temp[0];
//                 temp = temp >> 1;
//                 temp[7] = lsb;
//             }

//             state.write(temp);
//         }

//         // -------- LEFT ROTATION --------
//         dir = 1;
//         count = (rand() % 15) + 1;

//         cout << "Left rotations: " << count << endl;

//         for (int i = 0; i < count; i++)
//         {
//             wait();

//             if (dir == 1)
//             {
//                 // left rotate
//                 sc_logic msb = temp[7];
//                 temp = temp << 1;
//                 temp[0] = msb;
//             }

//             state.write(temp);
//         }

//         sc_stop();
//     }

//     SC_CTOR(siso)
//     {
//         SC_THREAD(compute_siso);
//         sensitive << clk.pos();

//         temp = "10110011";   // initial input
//         srand(time(0));      // random seed
//     }
// };


// // ================= MONITOR =================
// SC_MODULE(monitor)
// {
//     sc_in<sc_lv<8>> state;
//     sc_in<bool> clk;

//     void mon()
//     {
//         cout << "@" << sc_time_stamp()
//              << " REG: " << state.read()
//              << endl;
//     }

//     SC_CTOR(monitor)
//     {
//         SC_METHOD(mon);
//         sensitive << clk.pos();
//     }
// };


// // ================= TESTBENCH =================
// int sc_main(int argc, char* argv[])
// {
//     sc_signal<sc_lv<8>> state_sig;
//     sc_clock clk("clk", 10, SC_NS);

//     siso dut("shift_reg");
//     monitor mon("monitor");

//     dut.state(state_sig);
//     dut.clk(clk);

//     mon.state(state_sig);
//     mon.clk(clk);

//     sc_start(200, SC_NS);

//     return 0;
// }