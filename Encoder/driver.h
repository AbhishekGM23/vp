//driver.h
#include <systemc.h>
SC_MODULE(driver)
{
	sc_out<sc_lv<4>> d;

	void inputs()
	{
		d.write("0001");
		wait(5, SC_NS);
		
		d.write("0010");
		wait(5, SC_NS);
		
		d.write("1000");
		wait(5, SC_NS);
		
		d.write("0000");
		wait(5, SC_NS);
		
		
		
	}
		SC_CTOR(driver)
		{
			SC_THREAD(inputs);
			sensitive <<d;
		}
	
};
