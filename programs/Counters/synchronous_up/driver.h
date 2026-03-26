//driver.h
#include <systemc.h>
SC_MODULE(driver)
{
	sc_out<bool> rst,en;
	sc_in<bool> clk;

	void inputs()
	{
		rst.write(true);
		wait(1,SC_NS);
		rst.write(false);
		en.write(true);
		wait(1,SC_NS);
		
		
	}
		SC_CTOR(driver)
		{
			SC_THREAD(inputs);
			sensitive <<clk.pos()<<rst<<en;
		}
	
};
