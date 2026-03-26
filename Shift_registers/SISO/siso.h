//siso.h
#include <systemc.h>
SC_MODULE(siso)
{
	sc_in<sc_logic> d;
	sc_out<sc_logic> r;
	sc_in<bool> clk;
		
	void compute_siso()
	{
		sc_lv<4> temp = "0000";	
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
