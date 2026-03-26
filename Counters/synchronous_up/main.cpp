#include <systemc.h>
#include "sync_up.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> rst,en;
	sc_signal<sc_uint<8>> counter_out;
	sc_clock  testclk("testclock",2,SC_NS,0.5);

	upcounter up("upcounter");
	driver drive("driver");
	monitor mon("monitor");

	up.rst(rst); up.en(en); up.clk(testclk);up.counter_out(counter_out); 
	drive.rst(rst);drive.en(en); drive.clk(testclk); 
	mon.rst(rst); mon.en(en); mon.clk(testclk);mon.counter_out(counter_out); 
	
	// waveform

	sc_trace_file *Tf;
	Tf = sc_create_vcd_trace_file("traces");
	sc_trace(Tf, rst, "rst");
	sc_trace(Tf, en, "en");
	sc_trace(Tf, counter_out, "counter_out");
	sc_trace(Tf,testclk,"testclk");
	
	sc_start(30, SC_NS);
	sc_close_vcd_trace_file(Tf);
	return 0; 
}
