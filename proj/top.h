#ifndef TOP_H
#define TOP_H

#include "counter.h"
#include "initiator.h"

struct Top : sc_module {

    Counter* counter;
    Initiator* initiator;

    SC_CTOR(Top) {
        counter = new Counter("counter");
        initiator = new Initiator("initiator");

        initiator->socket.bind(counter->socket);
    }
};

#endif