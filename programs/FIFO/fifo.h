#include "systemc.h"
SC_MODULE(example_fifo) {
// Declare the FIFO
sc_fifo<int> packet_fifo;
void fiforead(void) {
int val;
for (;;){
	wait(3, SC_NS);
	packet_fifo.read(val);
	cout<< sc_time_stamp() << ": Read " << val<<endl;
	cout<< sc_time_stamp()<<"No.of Data in FIFO "<<packet_fifo.num_available()<<endl;
	}
}


void fifowrite(void) {
int val= 10;
for (;;) {
	wait(2, SC_NS);
	val++;
	packet_fifo.write(val);
	cout<< sc_time_stamp() << ": wrote " << val<< "  No. of Free Slots in FIFO "<<packet_fifo.num_free()<<endl;
	}
}

SC_CTOR(example_fifo) :packet_fifo(10)
{
	SC_THREAD(fifowrite);
	SC_THREAD(fiforead);
	}
};
