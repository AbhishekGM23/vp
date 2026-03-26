//siso.h
#include <systemc.h>
SC_MODULE(siso)
{
	sc_in<sc_logic> d;
	sc_out<sc_logic> r;
	sc_in<bool> clk;
	sc_lv<3> temp;

	void compute_siso()
	{
		r=temp[2];
		temp[2]=temp[1];
		temp[1]=temp[0];
		temp[0]=d.read();
		cout <<sc_time_stamp<< " Temp[2]: "<< temp[2]<< " Temp[1]: "<< temp[1] << " Temp[0]: "<< temp[0]<<endl;
	}
	SC_CTOR(siso)
	{
		SC_METHOD(compute_siso);
		sensitive<<clk.pos();
	}
};
