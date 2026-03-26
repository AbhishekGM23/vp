//driver.h
#include <systemc.h>
SC_MODULE(driver)
{
	sc_out<bool> a,b,cin;

	void inputs()
	{
		a.write(false);
		b.write(false);
		cin.write(false);
		wait(5, SC_NS);

		a.write(true);
		b.write(true);
		cin.write(false);
		wait(5, SC_NS);
		
		a.write(false);
		b.write(false);
		cin.write(true);
		wait(5, SC_NS);
		
		a.write(true);
		b.write(true);
		cin.write(true);
		wait(5, SC_NS);
		

		
	}
		SC_CTOR(driver)
		{
			SC_THREAD(inputs);
			sensitive <<a <<b<<cin;
		}
	
};
