#include <systemc.h>
#include "siso.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<sc_logic> d,r;
	sc_clock  testclk("testclock",10,SC_NS,0.5);

	siso siso1("siso");
	driver drive("driver");
	monitor mon("monitor");

	siso1.d(d); siso1.r(r); siso1.clk(testclk); 
	drive.d(d); drive.clk(testclk); 
	mon.d(d); mon.r(r); mon.clk(testclk); 
	// waveform

	sc_trace_file *Tf;
	Tf = sc_create_vcd_trace_file("traces");
	sc_trace(Tf, d, "d");
	sc_trace(Tf, r, "r");
	sc_trace(Tf,testclk,"testclk");
	
	sc_start(60, SC_NS);
	sc_close_vcd_trace_file(Tf);
	return 0; 
}
