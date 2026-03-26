//driver.h
#include <systemc.h>
SC_MODULE(driver)
{
	int i=0;
	sc_out<bool> rst,en;
	sc_in<bool> clk;

	void inputs()
	{
		while(i < 10){
			rst.write(true);
			wait(1,SC_NS);
			rst.write(false);
			en.write(true);
			wait(1,SC_NS);
			if (i == 5)
				en.write(!en.read());
			i++;
		}
		
		
	}
		SC_CTOR(driver)
		{
			SC_THREAD(inputs);
			sensitive <<clk.pos()<<rst<<en;
		}
	
};
