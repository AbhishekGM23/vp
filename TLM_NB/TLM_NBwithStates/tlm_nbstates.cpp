// nb_tlm_with_states.cpp

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace std;

////////////////////////////////////////////////////////////
// MEMORY (Target)
////////////////////////////////////////////////////////////
struct Memory : sc_module {

    tlm_utils::simple_target_socket<Memory> socket;
    unsigned char mem[256];

    SC_CTOR(Memory) : socket("socket") {
        socket.register_nb_transport_fw(this, &Memory::nb_transport_fw);

        for(int i=0;i<256;i++)
            mem[i] = i+1;
    }

    tlm_sync_enum nb_transport_fw(tlm_generic_payload& trans,
                                  tlm_phase& phase,
                                  sc_time& delay)
    {
        if (phase == BEGIN_REQ) {

            cout << "Memory: BEGIN_REQ @ "
                 << sc_time_stamp() << endl;

            phase = END_REQ;
            delay += sc_time(5, SC_NS);

            // simulate processing latency
            sc_spawn([this, &trans]() {

                wait(20, SC_NS);

                // perform READ
                if (trans.get_command() == TLM_READ_COMMAND) {
                    unsigned char* ptr = trans.get_data_ptr();
                    sc_dt::uint64 addr = trans.get_address();
                    ptr[0] = mem[addr];
                }

                tlm_phase resp_phase = BEGIN_RESP;
                sc_time resp_delay = SC_ZERO_TIME;

                cout << "Memory: BEGIN_RESP @ "
                     << sc_time_stamp() << endl;

                socket->nb_transport_bw(trans,
                                        resp_phase,
                                        resp_delay);
            });

            return TLM_UPDATED;
        }

        if (phase == END_RESP) {
            cout << "Memory: END_RESP received @ "
                 << sc_time_stamp() << endl;

            return TLM_COMPLETED;
        }

        return TLM_ACCEPTED;
    }
};

////////////////////////////////////////////////////////////
// INITIATOR (CPU)
////////////////////////////////////////////////////////////
struct Initiator : sc_module {

    tlm_utils::simple_initiator_socket<Initiator> socket;

    enum TxnState {
        IDLE,
        REQ_SENT,
        REQ_ACCEPTED,
        RESP_RECEIVED,
        COMPLETED
    };

    TxnState state;

    SC_CTOR(Initiator) : socket("socket"), state(IDLE) {
        socket.register_nb_transport_bw(this, &Initiator::nb_transport_bw);
        SC_THREAD(thread_process);
    }

    void thread_process() {

        tlm_generic_payload trans;
        sc_time delay = SC_ZERO_TIME;
        tlm_phase phase = BEGIN_REQ;

        unsigned char data;

        trans.set_command(TLM_READ_COMMAND);
        trans.set_address(10);
        trans.set_data_ptr(&data);
        trans.set_data_length(1);

        cout << "Initiator: Sending BEGIN_REQ @ "
             << sc_time_stamp() << endl;

        state = REQ_SENT;

        tlm_sync_enum status =
            socket->nb_transport_fw(trans, phase, delay);

        if (status == TLM_UPDATED && phase == END_REQ) {
            state = REQ_ACCEPTED;
            cout << "Initiator: END_REQ received @ "
                 << sc_time_stamp() + delay << endl;
        }

        wait(100, SC_NS);

        cout << "Final Data Read = "
             << (int)data << endl;

        sc_stop();
    }

    tlm_sync_enum nb_transport_bw(tlm_generic_payload& trans,
                                  tlm_phase& phase,
                                  sc_time& delay)
    {
        if (phase == BEGIN_RESP) {

            state = RESP_RECEIVED;

            cout << "Initiator: BEGIN_RESP @ "
                 << sc_time_stamp() << endl;

            phase = END_RESP;

            socket->nb_transport_fw(trans,
                                    phase,
                                    delay);

            state = COMPLETED;

            cout << "Initiator: END_RESP sent @ "
                 << sc_time_stamp() << endl;

            return TLM_COMPLETED;
        }

        return TLM_ACCEPTED;
    }
};

////////////////////////////////////////////////////////////
// sc_main
////////////////////////////////////////////////////////////
int sc_main(int argc, char* argv[]) {

    Initiator cpu("cpu");
    Memory memory("memory");

    cpu.socket.bind(memory.socket);

    sc_start();
    return 0;
}
