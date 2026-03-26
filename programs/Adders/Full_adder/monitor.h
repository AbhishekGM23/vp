//monitor.h
#include<systemc.h>
SC_MODULE(monitor)
{
	sc_in<bool> a,b,cin,s,co;

	void mon()
	{
		cout<<"Inputs: "<<a<<b<<cin<<"Output: "<<s<<co<<endl;
	}

	SC_CTOR(monitor)
	{
		SC_METHOD(mon);
		sensitive<<a<<b<<cin;
	}
};
