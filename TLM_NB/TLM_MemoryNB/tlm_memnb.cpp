// nonblocking_memory.cpp

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace std;

/////////////////////////////////////////////////////////////
// Memory (Target)
/////////////////////////////////////////////////////////////
struct Memory : sc_module {

    tlm_utils::simple_target_socket<Memory> socket;
    unsigned char mem[256];  // simple memory

    SC_CTOR(Memory) : socket("socket") {
        socket.register_nb_transport_fw(this, &Memory::nb_transport_fw);

        // initialize memory
        for(int i=0;i<256;i++)
            mem[i] = i;
    }

    tlm_sync_enum nb_transport_fw(tlm_generic_payload& trans,
                                  tlm_phase& phase,
                                  sc_time& delay)
    {
        if (phase == BEGIN_REQ) {

            cout << "Memory: BEGIN_REQ received at "
                 << sc_time_stamp() << endl;

            phase = END_REQ;
            delay += sc_time(10, SC_NS);

            // Notify response after delay
            sc_spawn([this, &trans]() {
                  wait(20, SC_NS);
                tlm_command cmd = trans.get_command();
                sc_dt::uint64 adr = trans.get_address();
                unsigned char *ptr = trans.get_data_ptr();
                if (cmd == TLM_READ_COMMAND)
                    memcpy(ptr, &mem[adr], 1);
                cout << "TLM MEM[adr] : " << int(mem[adr]) <<endl ;

                tlm_phase resp_phase = BEGIN_RESP;
                sc_time resp_delay = SC_ZERO_TIME;

                cout << "Memory: Sending BEGIN_RESP at "
                     << sc_time_stamp() << endl;
                cout << "Memory address " << adr << " Content " << int(mem[adr]) << endl ;
                socket->nb_transport_bw(trans, resp_phase, resp_delay);
            });

            return TLM_UPDATED;
        }

        return TLM_ACCEPTED;
    }
};

/////////////////////////////////////////////////////////////
// Initiator (CPU)
/////////////////////////////////////////////////////////////
struct Initiator : sc_module {

    tlm_utils::simple_initiator_socket<Initiator> socket;

    SC_CTOR(Initiator) : socket("socket") {
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

        cout << "Initiator: Sending BEGIN_REQ at "
             << sc_time_stamp() << endl;

        socket->nb_transport_fw(trans, phase, delay);

        wait(100, SC_NS);
        sc_stop();
    }

    tlm_sync_enum nb_transport_bw(tlm_generic_payload& trans,
                                  tlm_phase& phase,
                                  sc_time& delay)
    {
        if (phase == BEGIN_RESP) {

            tlm_command cmd = trans.get_command();
            sc_dt::uint64 adr = trans.get_address();
            unsigned char *ptr = trans.get_data_ptr();

            cout << "Initiator: BEGIN_RESP received at "
                 << sc_time_stamp() << endl;

            phase = END_RESP;

            socket->nb_transport_fw(trans, phase, delay);

            cout << "Initiator: END_RESP sent at "
                 << sc_time_stamp() << endl;

            int *data=new int;     
            memcpy(data,ptr,1);
            cout << "Initiator address " << adr << " Content " << int(*data) << endl ;

            return TLM_COMPLETED;
        }

        return TLM_ACCEPTED;
    }
};

/////////////////////////////////////////////////////////////
// sc_main
/////////////////////////////////////////////////////////////
int sc_main(int argc, char* argv[]) {

    Initiator cpu("cpu");
    Memory memory("memory");

    cpu.socket.bind(memory.socket);

    sc_start();
    return 0;
}
