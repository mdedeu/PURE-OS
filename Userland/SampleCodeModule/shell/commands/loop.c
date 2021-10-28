#include "loop.h"
#include "system.h"
#include "shell.h"
#include "libc.h"

#define NULL (void*) 0 


int ticksElapsed()
{
      return syscall(TICKS_ELAPSED, 0, 0, 0, 0, 0, 0);
}

void waitCycles(int cycles)
{
      int goal = ticksElapsed() + cycles;
      while (ticksElapsed() < goal);
}

void loopProc(int argc, char** argv){

    uint64_t pid = syscall(GET_PID, 0, 0, 0, 0, 0, 0);
    while (1)
    {
        waitCycles(10);
        char buff[20];
        char* window = argv[0];
        int* offset = (int*) argv[1];
        addText("Hello Nigerian Prince :) ", window, offset);
        addText(itoa(pid, buff, 10), window, offset);
        printWindow(window);
        substractLine(window, offset);
    }
    exit(); //implementar syscall exit
}

void loop(char* window, int * offset){
    char* argv[2] = {window, (char*) offset};
    sys_loadProcess(&loopProc, 3, argv, 0, NULL, "loop");
}

