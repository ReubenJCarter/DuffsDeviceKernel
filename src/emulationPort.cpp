#include "emulationPort.h"
#include <stdio.h>

char bufferIn[20];
char bufferOut[20];
unsigned int sizeIn;
unsigned int sizeOut;

void EmulationPortBindStream(Stream* fStreamIn, Stream* fStreamOut)
{
	StreamBind((char*)bufferIn, &sizeIn, fStreamIn);
	StreamBind((char*)bufferOut, &sizeOut, fStreamOut);
}

int EmulationPort()
{
  PSTART;
  
  sizeIn = 0;
  sizeOut = 0;
  
  while(1)
  {
	PBLOCK;
	unsigned int i = 0;
    while(sizeOut > 0)
	{
		sizeOut--;
		putchar(bufferOut[sizeOut]);
	}
  }
  
  PEND;
}