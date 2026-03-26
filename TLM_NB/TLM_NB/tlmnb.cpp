// main.cpp
#include <systemc.h>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace std;

/////////////////////////////////////////////////////////
// Target Module
/////////////////////////////////////////////////////////
struct SimpleTarget : sc_module {

    tlm_utils::simple_target_socket<SimpleTarget> socket;

    SC_CTOR(SimpleTarget) : socket("socket") {
        socket.register_nb_transport_fw(this, &SimpleTarget::nb_transport_fw);
    }

    tlm_sync_enum nb_transport_fw(tlm_generic_payload& trans,
                                  tlm_phase& phase,
                                  sc_time& delay)
    {
        if (phase == BEGIN_REQ) {

            cout << "Target: BEGIN_REQ received at "
                 << sc_time_stamp() << endl;

            phase = END_REQ;
            delay += sc_time(5, SC_NS);

            return TLM_UPDATED;
        }

        return TLM_ACCEPTED;
    }
};

/////////////////////////////////////////////////////////
// Initiator Module
/////////////////////////////////////////////////////////
struct SimpleInitiator : sc_module {

    tlm_utils::simple_initiator_socket<SimpleInitiator> socket;

    SC_CTOR(SimpleInitiator) : socket("socket") {
        socket.register_nb_transport_bw(this, &SimpleInitiator::nb_transport_bw);
        SC_THREAD(thread_process);
    }

    void thread_process() {

        tlm_generic_payload trans;
        tlm_phase phase = BEGIN_REQ;
        sc_time delay = SC_ZERO_TIME;

        cout << "Initiator: Sending BEGIN_REQ at "
             << sc_time_stamp() << endl;

        tlm_sync_enum status =
            socket->nb_transport_fw(trans, phase, delay);

        if (status == TLM_UPDATED && phase == END_REQ) {
            cout << "Initiator: END_REQ received at "
                 << sc_time_stamp() + delay << endl;
        }

        wait(20, SC_NS);
        sc_stop();
    }

    tlm_sync_enum nb_transport_bw(tlm_generic_payload& trans,
                                  tlm_phase& phase,
                                  sc_time& delay)
    {
        cout << "Initiator: Backward path called\n";
        return TLM_ACCEPTED;
    }
};

/////////////////////////////////////////////////////////
// sc_main
/////////////////////////////////////////////////////////
int sc_main(int argc, char* argv[]) {

    SimpleInitiator initiator("initiator");
    SimpleTarget target("target");

    initiator.socket.bind(target.socket);

    sc_start();

    return 0;
}
