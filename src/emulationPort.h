#ifndef EMPORT_H
#define EMPORT_H

#include "kernel.h"

#define EMPORT_BUFFERSIZE 20

void EmulationPortBindStream(Stream* fStreamIn, Stream* fStreamOut);
int EmulationPort();

#endif