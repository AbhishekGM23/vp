#include "systemc.h"
#include "fifo.h"
int sc_main(int argc, char* argv[])
{
	example_fifo ex_fifo("ex_fifo0");
	sc_start(10, SC_NS);
	return 0;
}
