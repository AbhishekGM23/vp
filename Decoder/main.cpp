#include <systemc.h>
#include "decoder.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> d0,d1,d2,d3,en,s0,s1;

	decoder dec1("decoder");
	driver drive("driver");
	monitor mon("monitor");

	dec1.d0(d0); dec1.d1(d1); dec1.d2(d2); dec1.d3(d3); dec1.en(en); dec1.s0(s0); dec1.s1(s1); 
	drive.en(en); drive.s0(s0); drive.s1(s1);
	mon.d0(d0); mon.d1(d1); mon.d2(d2); mon.d3(d3); mon.en(en); mon.s0(s0); mon.s1(s1); 
	// waveform

	sc_trace_file *Tf;
	Tf = sc_create_vcd_trace_file("traces");
	sc_trace(Tf, s0, "s0");
	sc_trace(Tf, s1, "s1");
	sc_trace(Tf, en, "en");
	sc_trace(Tf, d0, "d0");
	sc_trace(Tf, d1, "d1");
	sc_trace(Tf, d2, "d2");
	sc_trace(Tf, d3, "d3");
	
	sc_start(30, SC_NS);
	sc_close_vcd_trace_file(Tf);
	return 0; 
}
