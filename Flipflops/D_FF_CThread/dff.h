//andgate.h
#include <systemc.h>
SC_MODULE(dff)
{
	sc_in<bool> d;
	sc_out<bool> q;
	sc_in<bool> clk;
	
	void compute_dff()
	{
		while(true){
			q.write(d.read());
			wait();
		}
	}
	SC_CTOR(dff)
	{
		// SC_METHOD(compute_dff);
		// sensitive<<clk.pos();
		SC_CTHREAD(compute_dff, clk.pos());
	}
};
