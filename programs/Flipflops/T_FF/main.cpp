#include <systemc.h>
#include "tff.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> t,q;
	sc_clock  testclk("testclock",10,SC_NS,0.5);

	tff tff1("tff");
	driver drive("driver");
	monitor mon("monitor");

	tff1.t(t); tff1.q(q); tff1.clk(testclk); 
	drive.t(t); drive.clk(testclk); 
	mon.t(t); mon.q(q); mon.clk(testclk); 
	// waveform

	sc_trace_file *Tf;
	Tf = sc_create_vcd_trace_file("traces");
	sc_trace(Tf, t, "t");
	sc_trace(Tf, q, "q");
	sc_trace(Tf,testclk,"testclk");
	
	sc_start(30, SC_NS);
	sc_close_vcd_trace_file(Tf);
	return 0; 
}
