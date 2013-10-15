#include "emulationPort.h"
#include <stdio.h>

char bufferIn[20];
char bufferOut[20];
unsigned int sizeIn;
unsigned int sizeOut;

void EmulationPortConnectStream(Stream* fStreamIn, Stream* fStreamOut)
{
	fStreamIn->data = bufferIn;
	fStreamOut->data = bufferOut;
	fStreamIn->size = &sizeIn;
	fStreamOut->size = &sizeOut;
}

int EmulationPort()
{
  PSTART;
  
  sizeIn = 0;
  sizeOut = 0;
  
  while(1)
  {
	PBREAK;
	unsigned int i = 0;
    while(sizeOut > 0)
	{
		sizeOut--;
		putchar(bufferOut[sizeOut]);
	}
	/*
    while(1)
	{
		int c = getchar();
		printf("v");
		if(c == EOF || sizeIn >= EMPORT_BUFFERSIZE)
			break;
		else
			bufferIn[sizeIn] = c;
		sizeIn++;
	}*/
  }
  
  PEND;
}