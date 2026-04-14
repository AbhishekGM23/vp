#ifndef INITIATOR_H
#define INITIATOR_H

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace std;

struct Initiator : sc_module {

    tlm_utils::simple_initiator_socket<Initiator> socket;

    SC_CTOR(Initiator) : socket("socket") {
        SC_THREAD(thread_process);
    }

    void thread_process() {

        while (true) {
            wait(20, SC_NS);

            tlm_generic_payload trans;
            sc_time delay = SC_ZERO_TIME;

            uint32_t data = 0;

            trans.set_command(TLM_READ_COMMAND);
            trans.set_data_ptr((unsigned char*)&data);
            trans.set_data_length(4);

            tlm_phase phase = BEGIN_REQ;

            socket->nb_transport_fw(trans, phase, delay);

            wait(delay);

            cout << "[Initiator] Observed Counter = "
                 << data << " at " << sc_time_stamp() << endl;
        }
    }
};

#endif