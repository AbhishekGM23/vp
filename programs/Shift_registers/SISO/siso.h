//siso.h
#include <systemc.h>
SC_MODULE(siso)
{
	sc_in<sc_logic> d;
	sc_out<sc_logic> r;
	sc_in<bool> clk;
		sc_lv<4> temp = "0000";
	void compute_siso()
	{
			
		r=temp[3];
		temp[3]=temp[2];
		temp[2]=temp[1];
		temp[1]=temp[0];
		temp[0]=d.read();
	}
	SC_CTOR(siso)
	{
		SC_METHOD(compute_siso);
		sensitive<<clk.pos();
	}
};


//Design a SysemC module which implements an
// 8 bit shift register where insertion 
//takes place at the fouth bit and the 
//third bit is dispossed. LSB is considered to be bit 1.

// #include <systemc.h>

// SC_MODULE(siso)
// {
//     sc_in<sc_logic> d;
//     sc_out<sc_logic> r;
//     sc_in<bool> clk;

//     sc_lv<8> temp;   // 8-bit register (PERSISTENT)

//     void compute_siso()
//     {
//         // Dispose 3rd bit → shift left from bit 4 to bit 3
//         temp[2] = temp[3];   // bit3 overwritten

//         // Shift higher bits
//         temp[3] = temp[4];
//         temp[4] = temp[5];
//         temp[5] = temp[6];
//         temp[6] = temp[7];

//         // Insert new data at 4th bit
//         temp[3] = d.read();

//         // Output MSB (bit 8)
//         r = temp[7];
// 		cout <<"\n" << "Temp = " << temp<< endl;
//     }

//     SC_CTOR(siso)
//     {
//         temp = "00000000";   // initialize
//         SC_METHOD(compute_siso);
//         sensitive << clk.pos();
//     }
// };