#include <systemc.h>
#include "fulladder.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> a,b,s,co,cin;

	fulladder fa("fulladder");
	driver drive("driver");
	monitor mon("monitor");

	fa.a(a); fa.b(b); fa.s(s); fa.cin(cin); fa.co(co); 
	drive.a(a); drive.b(b);drive.cin(cin); 
	mon.a(a); mon.b(b); mon.cin(cin); mon.s(s);mon.co(co);

	// waveform

	sc_trace_file *Tf;
	Tf = sc_create_vcd_trace_file("traces");
	sc_trace(Tf, a, "a");
	sc_trace(Tf, b, "b");
	sc_trace(Tf, cin, "cin");
	sc_trace(Tf, s, "s");
	sc_trace(Tf, co, "co");
	sc_start(30, SC_NS);
	sc_close_vcd_trace_file(Tf);
	return 0; 
}
