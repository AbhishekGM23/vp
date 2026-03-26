#include <systemc.h>
#include "encoder.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<sc_lv<4>> d;
	sc_signal<sc_lv<2>> y;

	encoder enc("encoder");
	driver drive("driver");
	monitor mon("monitor");

	enc.d(d); enc.y(y);  
	drive.d(d); 
	mon.d(d); mon.y(y);  
	 
	// waveform

	sc_trace_file *Tf;
	Tf = sc_create_vcd_trace_file("traces");
	sc_trace(Tf, d, "d");
	sc_trace(Tf, y, "y");
	/*sc_trace(Tf, en, "en");
	sc_trace(Tf, d0, "d0");
	sc_trace(Tf, d1, "d1");
	sc_trace(Tf, d2, "d2");
	sc_trace(Tf, d3, "d3");*/
	
	sc_start(30, SC_NS);
	sc_close_vcd_trace_file(Tf);
	return 0; 
}
