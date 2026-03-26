//monitor.h
#include<systemc.h>
SC_MODULE(monitor)
{
	sc_in<bool> d0,d1,d2,d3,en,s0,s1;

	void mon()
	{
		cout<<"Inputs: "<<en<<s0<<s1<<"Output: "<<d0<<d1<<d2<<d3<<endl;
	}

	SC_CTOR(monitor)
	{
		SC_METHOD(mon);
		sensitive<<en<<s0<<s1;
	}
};
