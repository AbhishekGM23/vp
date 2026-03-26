//halfadder.h
#include <systemc.h>
SC_MODULE(halfadder)
{
	sc_in<bool> a;
	sc_in<bool> b;
	sc_out<bool> s;
	sc_out<bool> c;
	void compute_ha()
	{
		s.write(a.read() ^ b.read());
		c.write(a.read() & b.read());
	}
	SC_CTOR(halfadder)
	{
		SC_METHOD(compute_ha);
		sensitive<<a<<b;
	}
};
