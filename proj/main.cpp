#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include <tlm_utils/peq_with_cb_and_phase.h>
#include "trace.h"

using namespace sc_core;
using namespace tlm;
using namespace std;
using namespace sc_dt;


// ---------------- REGISTERS ----------------
#define TIMER_CONTROL_REG 0
#define TIMER_VALUE_REG 1
#define TIMER_COMPARE_REG 2
#define TIMER_IRQ_STATUS_REG 3

sc_dt::sc_bv<32> timer_reg[4];

// ---------------- TIMER (TARGET) ----------------
struct Timer : sc_module {
    tlm_utils::simple_target_socket<Timer> socket;
    tlm_utils::peq_with_cb_and_phase<Timer> peq;

    sc_dt::sc_uint<8> counter = 0;

    SC_CTOR(Timer) : peq(this, &Timer::peq_cb) {
        socket.register_nb_transport_fw(this, &Timer::nb_transport_fw);
        SC_THREAD(timer_thread);
    }

    // Forward path
    tlm_sync_enum nb_transport_fw(tlm_generic_payload &trans,
                                 tlm_phase &phase,
                                 sc_time &delay) {

        if (phase == BEGIN_REQ) {
            peq.notify(trans, phase, delay + sc_time(10, SC_NS));

            phase = END_REQ;
            return TLM_UPDATED;
        }
        return TLM_ACCEPTED;
    }

    // PEQ processing
    void peq_cb(tlm_generic_payload &trans, const tlm_phase &phase) {
        if (phase == BEGIN_REQ) {
            uint64_t addr = trans.get_address();
            unsigned char *ptr = trans.get_data_ptr();

            if (trans.is_write()) {
                timer_reg[addr] = *ptr;

                cout << "Write: Addr=" << addr
                     << " Data=" << (int)*ptr
                     << " at " << sc_time_stamp() << endl;

                // Clear IRQ
                if (addr == TIMER_IRQ_STATUS_REG) {
                    if (*ptr & 1) timer_reg[3][0] = 0;
                    if (*ptr & 2) timer_reg[3][1] = 0;
                }
            } else {
                *ptr = timer_reg[addr].to_uint();
            }

            // Send response
            tlm_phase resp = BEGIN_RESP;
            sc_time delay = sc_time(10, SC_NS);

            socket->nb_transport_bw(trans, resp, delay);
        }
    }

    // Timer logic
    void timer_thread() {
        sc_time period(10, SC_NS);

        while (true) {
            wait(period);

            if (timer_reg[TIMER_CONTROL_REG][0]) {
                counter++;
                timer_reg[TIMER_VALUE_REG] = counter;

                cout << "Count = " << counter
                     << " at " << sc_time_stamp() << endl;

                // Compare interrupt
                if (timer_reg[TIMER_CONTROL_REG][1] &&
                    counter == timer_reg[TIMER_COMPARE_REG]) {
                    cout << ">>> Compare IRQ at "
                         << sc_time_stamp() << endl;
                    timer_reg[TIMER_IRQ_STATUS_REG][0] = 1;
                }

                // Overflow interrupt
                if (counter == 0xFF &&
                    timer_reg[TIMER_CONTROL_REG][2]) {
                    cout << ">>> Overflow IRQ at "
                         << sc_time_stamp() << endl;
                    timer_reg[TIMER_IRQ_STATUS_REG][1] = 1;
                    counter = 0;
                }
                    count_sig.write(counter);
                    ctrl_sig.write(timer_reg[TIMER_CONTROL_REG].to_uint());
                    cmp_sig.write(timer_reg[TIMER_COMPARE_REG].to_uint());
                   irq_status_sig.write(timer_reg[TIMER_IRQ_STATUS_REG].to_uint());
            }
        }
    }
};

// ---------------- INITIATOR ----------------
struct Initiator : sc_module {
    tlm_utils::simple_initiator_socket<Initiator> socket;

    SC_CTOR(Initiator) {
        socket.register_nb_transport_bw(this, &Initiator::nb_transport_bw);
        SC_THREAD(run);
    }

    void send(uint64_t addr, uint8_t value) {

    tlm_generic_payload *trans = new tlm_generic_payload;

    uint8_t *data = new uint8_t;   // ✔ allocate memory
    *data = value;

    trans->set_command(TLM_WRITE_COMMAND);
    trans->set_address(addr);
    trans->set_data_ptr(data);
    trans->set_data_length(1);

    tlm_phase phase = BEGIN_REQ;
    sc_time delay = SC_ZERO_TIME;

    cout << "Send Addr=" << addr
         << " Data=" << (int)value
         << " at " << sc_time_stamp() << endl;

    socket->nb_transport_fw(*trans, phase, delay);
}

    void run() {
        wait(5, SC_NS);
        
        // FIX: maintain order
        send(TIMER_CONTROL_REG, 0x5);
        wait(5, SC_NS);

        send(TIMER_COMPARE_REG, 10);

        wait(200, SC_NS);
    }

    tlm_sync_enum nb_transport_bw(tlm_generic_payload &trans,
                                 tlm_phase &phase,
                                 sc_time &delay) {

        if (phase == BEGIN_RESP) {
            cout << "Response at " << sc_time_stamp() << endl;

            phase = END_RESP;
            return TLM_COMPLETED;
        }
        return TLM_ACCEPTED;
    }
};

// ---------------- TOP ----------------
struct Top : sc_module {
    Timer *t;
    Initiator *i;

    SC_CTOR(Top) {
        t = new Timer("timer");
        i = new Initiator("initiator");

        i->socket.bind(t->socket);
    }
};

// ---------------- MAIN ----------------
int sc_main(int argc, char *argv[]) {

    init_trace(); 
    
    Top top("top");
    sc_start(3000, SC_NS);
    
    close_trace(); 
    
    return 0;
}
