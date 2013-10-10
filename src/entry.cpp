#include "kernel.h"
#include <stdio.h>

int A()
{
  PSTART;
  
  while(1)
  {
	PBREAK;
    printf("hello world\n");
  }
  
  PEND;
}

int B()
{
  PSTART;
  
  while(1)
  {
	PBREAK;
    printf("Hi!\n");
  }
  
  PEND;
}

int main()
{
  InitKernel();
  AddProcess(A);
  AddProcess(B);
  Scheduler();
  return 0;
}
