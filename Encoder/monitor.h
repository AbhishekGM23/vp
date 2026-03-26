//monitor.h
#include<systemc.h>
SC_MODULE(monitor)
{
	sc_in<sc_lv<4>> d;
	sc_in<sc_lv<2>> y;

	void mon()
	{
		cout<<"Inputs: "<<d<<"Output: "<<y<<endl;
	}

	SC_CTOR(monitor)
	{
		SC_METHOD(mon);
		sensitive<<d;
	}
};
