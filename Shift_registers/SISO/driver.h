//driver.h
#include <systemc.h>
SC_MODULE(driver)
{
	sc_out<sc_logic> d;
	sc_in<bool> clk;

	void inputs()
	{
		wait();
		wait();
		d = sc_logic_0;
		wait();
		d = sc_logic_1;
		wait();
		d = sc_logic_0;
		wait();
		d = sc_logic_0;
		wait();
	}
		SC_CTOR(driver)
		{
			SC_THREAD(inputs);
			sensitive <<clk.pos();
		}
	
};
