#include <systemc.h>
#include "orgate.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> a1, b1,c1, d1;

	orgate ogate("orgate");
	driver drive("driver");
	monitor mon("monitor");

	ogate.a1(a1); ogate.b1(b1); ogate.c1(c1); ogate.d1(d1);
	drive.a1(a1); drive.b1(b1); drive.c1(c1);
	mon.a1(a1); mon.b1(b1); mon.c1(c1); mon.d1(d1);

	// waveform

	sc_trace_file *Tf;
	Tf = sc_create_vcd_trace_file("traces");
	sc_trace(Tf, a1, "a1");
	sc_trace(Tf, b1, "b1");
	sc_trace(Tf, c1, "c1");
	sc_trace(Tf, d1, "d1");
	sc_start(30, SC_NS);
	sc_close_vcd_trace_file(Tf);
	return 0; 
}
