//halfadder.h
#include <systemc.h>
SC_MODULE(fulladder)
{
	sc_in<bool> a;
	sc_in<bool> b;
	sc_in<bool> cin;
	sc_out<bool> s;
	sc_out<bool> co;
	void compute_fa()
	{
		s.write(a.read() ^ b.read() ^ cin.read());
		co.write((a.read() & b.read()) | cin.read() & (a.read() ^ b.read()));
	}
	SC_CTOR(fulladder)
	{
		SC_METHOD(compute_fa);
		sensitive<<a<<b<<cin;
	}
};
