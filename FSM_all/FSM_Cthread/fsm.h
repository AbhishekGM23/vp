#include "systemc.h"
SC_MODULE(fsm)
{
sc_in<bool> rst, in, clk;
sc_out<bool> out;
sc_uint<2> state,next_state;

void update_state()
{
	while(true)
	{
		if (rst.read() == true)
		{
			state = 0; 
		}
		else 
		{
			state = next_state; 
		}
		wait();
	}
}

void ns_logic()
{// Determine next state and output
	while(true)
	{
		switch(state) 
		{
		case 0:
			if (in.read()) 
			{
				next_state= 1;
				out=0;
			}
			else
			{
				next_state= 0; 
				out=0;
			}
			break; 
		case 1:
			if (in.read())
			{
				next_state= 1;
				out=0;
			}
			else
			{
				next_state= 2;
				out=0;
			}
			break;
		case 2:
			if (in.read())
			{
				next_state= 1;
				out=1;
			}
			else
			{
				next_state= 0;
				out=0;
			}
			break;
		default:
			{
				next_state= 0;
				out=0;
			}
			break;
		}
		wait();
	}
}

SC_CTOR(fsm)
{
	SC_CTHREAD(update_state,clk.neg());
	//sensitive << clk.pos()<<rst;
	SC_CTHREAD(ns_logic,clk.neg());
	//sensitive <<clk.pos()<<in<<rst;
}};
