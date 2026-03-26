//encoder.h
#include <systemc.h>
SC_MODULE(encoder)
{
	
	sc_in<sc_lv<4>> d;
	sc_out<sc_lv<2>> y;
	
	
	void compute_encoder()
	{
		
			if( d.read()=="0001")
			{
				y.write("00");	
			}
			else if( d.read()=="0010")
			{
				y.write("01");	
			}
			else if( d.read()=="0100")
			{
				y.write("10");	
			}
			else if( d.read()=="1000")
			{
				y.write("11");	
			}
			else if( d.read()=="0000")
			{
				y.write("XX");	
			}
			
			
			
			
			
			
	}
	SC_CTOR(encoder)
	{
		SC_METHOD(compute_encoder);
		sensitive<<d;
	}
};
