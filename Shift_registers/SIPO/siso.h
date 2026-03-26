//siso.h
#include <systemc.h>
SC_MODULE(siso)
{
	sc_in<bool> d;
	sc_out<bool> q0,q1,q2,q3;
	sc_in<bool> clk;
	
	
	void compute_siso()
	{	
		q3.write(q2.read());
		q2.write(q1.read());
		q1.write(q0.read());
		q0.write(d.read());
		
	}
	SC_CTOR(siso)
	{
		SC_METHOD(compute_siso);
		sensitive<<clk.pos();
	}
};
