#include "kernel.h"
#include "emulationPort.h"

int A()
{
  PSTART;
  
  while(1)
  {
	PBLOCK;
    StreamWrite((char*)"hello, ", 7, 1, &(p->stdOut));
  }
  
  PEND;
}

int B()
{
  PSTART;
  
  while(1)
  {
	PBLOCK;
	StreamWrite((char*)"test\n", 5, 1, &(p->stdOut));
  }
  
  PEND;
}

int main()
{
  InitKernel();
  AddProcess(EmulationPort);
  unsigned int a = AddProcess(A);
  unsigned int b = AddProcess(B);
  EmulationPortBindStream(&GetProcess(a)->stdIn, &GetProcess(a)->stdOut);
  EmulationPortBindStream(&GetProcess(b)->stdIn, &GetProcess(b)->stdOut);
  Scheduler();
  return 0;
}
