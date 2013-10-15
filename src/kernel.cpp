#include "kernel.h"

unsigned int currentActiveProcessIndex;
Process process[MAX_PROCESS_NUMBER];
unsigned int processNumber;
unsigned int schedulerIndex;

int StreamRead(void* fData, unsigned int fSize, unsigned int fCount, Stream* fStream)
{
	unsigned int i = 0;
	while(i < fCount * fSize)
	{
		while(*fStream->size <= 0)
		{
			
		}
		((char*)fData)[i] = ((char*)fStream->data)[*fStream->size - 1];
		(*fStream->size)--;
		i++;
	}
}

int StreamWrite(void* fData, unsigned int fSize, unsigned int fCount, Stream* fStream)
{
	int i = fCount * fSize - 1;
	while(i >= 0)
	{
		((char*)(fStream->data))[*(fStream->size)] = ((char*)fData)[i];
		(*(fStream->size))++;
		i--;
	}
}

int StreamOpen(void* fBuffer, unsigned int* fSize, Stream* fStream)
{
	fStream->data = fBuffer;
	fStream->size = fSize;
}

int StreamFlush(Stream* fStream)
{
	*fStream->size = 0;
}

void InitKernel()
{
  currentActiveProcessIndex = 0;
  processNumber = 0;
  schedulerIndex = 0;
  for(unsigned int i = 0; i < MAX_PROCESS_NUMBER; i++)
  {
    process[i].state = P_DEAD;
    process[i].codePosition = 0;
    process[i].processMain = 0;
  }
}

unsigned int AddProcess(ProcessMain fMain)
{
  for(int i = 0; i < MAX_PROCESS_NUMBER; i++)
  {
    if(process[i].state == P_DEAD)
    {
      process[i].state = P_START;
      process[i].codePosition = 0;
      process[i].processMain = fMain;
      processNumber++;
      return i;
    }
  }
}

unsigned int AddProcessPaused(ProcessMain fMain)
{
  for(int i = 0; i < MAX_PROCESS_NUMBER; i++)
  {
    if(process[i].state == P_DEAD)
    {
      process[i].state = P_PAUSED;
      process[i].codePosition = 0;
      process[i].processMain = fMain;
      processNumber++;
      return i;
    }
  }
}

void RestartProcess(unsigned int fProcessId)
{
   process[fProcessId].state = P_START;
}

void PauseProcess(unsigned int fProcessId)
{
  process[fProcessId].state = P_PAUSED;
}

void ResumeProcess(unsigned int fProcessId)
{
  process[fProcessId].state = P_IDLE;
}

void KillProcess(unsigned int fProcessId)
{
  process[fProcessId].state = P_DEAD;
  processNumber--;
}

Process* GetProcess(unsigned int fProcessId)
{
	return &process[fProcessId];
}

unsigned int GetAtiveProcessIndex()
{
 return currentActiveProcessIndex;
}

Process* GetAtiveProcessPtr()
{
  return &process[currentActiveProcessIndex];
}

void RunProcess(unsigned int fIndex)
{
  currentActiveProcessIndex = fIndex;
  process[fIndex].state = P_ACTIVE;
  (*process[fIndex].processMain)();
  process[fIndex].state = P_IDLE;
}

void Scheduler()
{
  while(1)
  {
    if(process[schedulerIndex].state == P_IDLE)
    {
      RunProcess(schedulerIndex);
    }
      
    else if(process[schedulerIndex].state == P_START)
    {
      process[schedulerIndex].codePosition = 0;
      RunProcess(schedulerIndex);
    }
    
    schedulerIndex++;
    if(schedulerIndex >= processNumber)
      schedulerIndex = 0;
  }
}

