#include "kernel.h"

unsigned int currentActiveProcessIndex;
Process process[MAX_PROCESS_NUMBER];
unsigned int processNumber;
unsigned int schedulerIndex;

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

