#include <systemc>
#include "top.h"

int sc_main(int argc, char* argv[]) {

    Top top("top");

    sc_start(5, SC_SEC);

    return 0;
}