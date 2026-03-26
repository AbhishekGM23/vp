//decoder.h
#include <systemc.h>
SC_MODULE(decoder)
{
	sc_in<bool> s0;
	sc_in<bool> s1;
	sc_in<bool> en;
	sc_out<bool> d0;
	sc_out<bool> d1;
	sc_out<bool> d2;
	sc_out<bool> d3;
	void compute_decoder()
	{
		if(en.read()==true){
			if( (s1.read()==false) && (s0.read()==false))
			{
				d0.write(true);
				d1.write(false);
				d2.write(false);
				d3.write(false);
			}
			else if((s1.read()==false) && (s0.read()==true))
			{
				d0.write(false);
				d1.write(true);
				d2.write(false);
				d3.write(false);
			}
			else if( (s1.read()==true) && (s0.read()==false))
			{
				d0.write(false);
				d1.write(false);
				d2.write(true);
				d3.write(false);
			}
			else if( (s1.read()==true) && (s0.read()==true))
			{
				d0.write(false);
				d1.write(false);
				d2.write(false);
				d3.write(true);
			}
		}
		else if(en.read()==false)
		{
			d0.write(false);
			d1.write(false);
			d2.write(false);
			d3.write(false);
		}

	}
	SC_CTOR(decoder)
	{
		SC_METHOD(compute_decoder);
		sensitive<<s0<<s1<<en;
	}
};
