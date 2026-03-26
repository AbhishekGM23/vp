#include <systemc.h>
#include "siso.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> d,q0,q1,q2,q3;
	sc_clock  testclk("testclock",5,SC_NS,0.5);

	siso siso1("siso");
	driver drive("driver");
	monitor mon("monitor");

	siso1.d(d); siso1.q0(q0);siso1.q1(q1);siso1.q2(q2);siso1.q3(q3); siso1.clk(testclk); 
	drive.d(d); drive.clk(testclk); 
	mon.d(d); mon.q0(q0);mon.q1(q1);mon.q2(q2);mon.q3(q3); mon.clk(testclk); 
	// waveform

	sc_trace_file *Tf;
	Tf = sc_create_vcd_trace_file("traces");
	sc_trace(Tf, d, "d");
	sc_trace(Tf, q0, "q0");
	sc_trace(Tf, q1, "q1");
	sc_trace(Tf, q2, "q2");
	sc_trace(Tf, q3, "q3");
	sc_trace(Tf,testclk,"testclk");
	
	sc_start(30, SC_NS);
	sc_close_vcd_trace_file(Tf);
	return 0; 
}
