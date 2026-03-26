//monitor.h
#include<systemc.h>
SC_MODULE(monitor)
{
	sc_in<bool> d,q0,q1,q2,q3;
	
	sc_in<bool> clk;

	void mon()
	{
		cout<<"Input D: "<<d<<"Output Q:= "<<q0<<q1<<q2<<q3<<endl;
	}

	SC_CTOR(monitor)
	{
		SC_METHOD(mon);
		sensitive<<clk.pos();
	}
};
