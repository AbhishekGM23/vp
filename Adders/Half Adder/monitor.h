//monitor.h
#include<systemc.h>
SC_MODULE(monitor)
{
	sc_in<bool> a,b,s,c;

	void mon()
	{
		cout<<"Inputs: "<<a<<b<<"Output: "<<s<<c<<endl;
	}

	SC_CTOR(monitor)
	{
		SC_METHOD(mon);
		sensitive<<a<<b;
	}
};
