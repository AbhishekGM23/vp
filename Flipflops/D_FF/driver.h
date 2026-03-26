//driver.h
#include <systemc.h>
SC_MODULE(driver)
{
	sc_out<bool> d;
	sc_in<bool> clk;

	void inputs()
	{
		//wait();
		d.write(false);
		wait(5, SC_NS);
		//wait();
		d.write(true);
		wait(5, SC_NS);
		//wait();
		d.write(true);
		wait(5, SC_NS);
		//wait();
		d.write(false);
		wait(5, SC_NS);
		//wait();
	}
		SC_CTOR(driver)
		{
			SC_THREAD(inputs);
			sensitive <<clk.pos();
		}
	
};
