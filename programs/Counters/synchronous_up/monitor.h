//monitor.h
#include<systemc.h>
SC_MODULE(monitor)
{
	sc_in<bool> rst,en;
	sc_in<sc_uint<8>> counter_out;
	
	sc_in<bool> clk;

	void mon()
	{
		cout<<"Input rst: "<<rst<<"Output counter_out:= "<<counter_out<<endl;
	}

	SC_CTOR(monitor)
	{
		SC_METHOD(mon);
		sensitive<<clk.pos()<<rst;
	}
};
