#include <systemc.h>
#include "halfadder.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> a,b,s,c;

	halfadder ha("halfadder");
	driver drive("driver");
	monitor mon("monitor");

	ha.a(a); ha.b(b); ha.s(s); ha.c(c); 
	drive.a(a); drive.b(b); 
	mon.a(a); mon.b(b); mon.c(c); mon.s(s);

	// waveform

	sc_trace_file *Tf;
	Tf = sc_create_vcd_trace_file("traces");
	sc_trace(Tf, a, "a");
	sc_trace(Tf, b, "b");
	sc_trace(Tf, c, "c");
	sc_trace(Tf, s, "s");
	sc_start(30, SC_NS);
	sc_close_vcd_trace_file(Tf);
	return 0; 
}
