//monitor.h
#include<systemc.h>
SC_MODULE(monitor)
{
	sc_in<sc_logic> d,r;
	
	sc_in<bool> clk;

	void mon()
	{
		cout<<"Input D: "<<d<<" Output Q:= "<<r<<endl;
	}

	SC_CTOR(monitor)
	{
		SC_METHOD(mon);
		sensitive<<clk.pos();
	}
};
