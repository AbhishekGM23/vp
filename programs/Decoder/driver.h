//driver.h
#include <systemc.h>
SC_MODULE(driver)
{
	sc_out<bool> s0,s1,en;

	void inputs()
	{
		s0.write(false);
		s1.write(false);
		en.write(true);
		wait(5, SC_NS);
		
		s0.write(true);
		s1.write(false);
		en.write(true);
		wait(5, SC_NS);
		
		s0.write(false);
		s1.write(true);
		en.write(false);
		wait(5, SC_NS);
		
		s0.write(true);
		s1.write(true);
		en.write(true);
		wait(5, SC_NS);
		
	}
		SC_CTOR(driver)
		{
			SC_THREAD(inputs);
			sensitive <<s0<<s1<<en;
		}
	
};
