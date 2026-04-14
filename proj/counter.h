#ifndef COUNTER_H
#define COUNTER_H

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace std;

struct Counter : sc_module {

    tlm_utils::simple_target_socket<Counter> socket;

    uint32_t count;

    SC_CTOR(Counter) : socket("socket"), count(0) {
        socket.register_nb_transport_fw(this, &Counter::nb_transport_fw);

        SC_THREAD(counter_thread);
    }

    // Free-running counter (hardware-like)
    void counter_thread() {
        while (true) {
            wait(1, SC_NS);

            count++;   // 32-bit auto wrap

            cout << "[Counter] = " << count
                 << " at " << sc_time_stamp() << endl;

            if (count == 0) {
                cout << "***** OVERFLOW ***** at "
                     << sc_time_stamp() << endl;
            }
        }
    }

    // Non-blocking transport (READ only)
    virtual tlm_sync_enum nb_transport_fw(
        tlm_generic_payload& trans,
        tlm_phase& phase,
        sc_time& delay)
    {
        if (phase == BEGIN_REQ) {

            if (trans.is_read()) {
                unsigned char* ptr = trans.get_data_ptr();
                *((uint32_t*)ptr) = count;

                cout << "[Target] Read = " << count << endl;
            }

            phase = BEGIN_RESP;
            delay += sc_time(5, SC_NS);

            return TLM_UPDATED;
        }

        return TLM_COMPLETED;
    }
};

#endif