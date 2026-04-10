#ifndef _TRACE_H_
#define _TRACE_H_

#include <systemc>
using namespace sc_core;

// Trace variables
sc_trace_file *tf;

// Signals to trace
sc_signal<int> count_sig;
sc_signal<int> ctrl_sig;
sc_signal<int> cmp_sig;
sc_signal<int> irq_status_sig;

// Setup trace file
void init_trace()
{
    tf = sc_create_vcd_trace_file("trace");
    tf->set_time_unit(1, SC_NS);

    sc_trace(tf, count_sig, "counter");
    sc_trace(tf, ctrl_sig, "control_reg");
    sc_trace(tf, cmp_sig, "compare_reg");
    sc_trace(tf, irq_status_sig, "irq_status");
}

// Close trace file
void close_trace()
{
    sc_close_vcd_trace_file(tf);
}

#endif
