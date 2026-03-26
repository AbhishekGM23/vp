//andgate.h
#include <systemc.h>
SC_MODULE(upcounter)
{
	sc_in<bool> rst,en;
	sc_out<sc_uint<8>> counter_out;
	sc_in<bool> clk;
	sc_uint<8>	count;
	
	void compute_upcounter()
	{
		if (rst.read() == 1) 
		{
      		count =  0;
      		counter_out.write(count); 
      		}
      		else if (en.read() == 1)
      		 {
      		  count = count + 1;
                  counter_out.write(count);
      
   		 }
	}
	SC_CTOR(upcounter)
	{
		SC_METHOD(compute_upcounter);
		sensitive<<clk.pos()<<rst;
	}
};
