#ifndef KERNEL_H
#define KERNEL_H

#define MAX_PROCESS_NUMBER 10
#define PSTART Process* p=GetAtiveProcessPtr(); switch(p->codePosition) { case 0:
#define PBREAK do { p->codePosition=__LINE__; return 0; case __LINE__:; } while (0)
#define PEND }

#define P_ACTIVE 0
#define P_IDLE 1
#define P_PAUSED 2
#define P_DEAD 3
#define P_START 4

typedef struct _stream
{
  void* data;
  unsigned int* size;
}Stream;

unsigned int StreamRead(void* fData, unsigned int fSize, unsigned int fCount, Stream* fStream);
unsigned int StreamWrite(void* fData, unsigned int fSize, unsigned int fCount, Stream* fStream);
int StreamBind(void* fBuffer, unsigned int* fSize, Stream* fStream);
int Flush(Stream* fStream);

typedef int (*ProcessMain)();
typedef struct _process
{
  unsigned char state;
  unsigned int codePosition;
  ProcessMain processMain;
  Stream stdIn;
  Stream stdOut;
}Process;

void InitKernel();
unsigned int AddProcess(ProcessMain fMain);
unsigned int AddProcessPaused(ProcessMain fMain);
void RestartProcess(unsigned int fProcessId);
void PauseProcess(unsigned int fProcessId);
void ResumeProcess(unsigned int fProcessId);
void KillProcess(unsigned int fProcessId);
Process* GetProcess(unsigned int fProcessId);
unsigned int GetAtiveProcessIndex();
Process* GetAtiveProcessPtr();
void Scheduler();

#endif
