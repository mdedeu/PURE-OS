#include <stdint.h>
#include "systemCalls.h"
#include "memorymanager.h"
#include "pcb.h"
#include "time.h"
#include "semaphores.h"
#include "pipes.h"

uint64_t systemCallsDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	switch (rdi) {
		case 0:
            return write(rsi, rdx, rcx);
        case 1:
            return read(rsi, rdx, rcx);
        case 2:
            return getTime((char)rsi);
        case 3:
            return createProcess((void(*)(int, char**))rsi,(int)rdx,(char**)rcx,(int)r8,(int*)r9); 
        //legacy syscalls-------------
        case MALLOC: 
            return (uint64_t) mallocMM(rsi);
        case FREE:
            return freeMM((void *) rsi);
        case GET_PPID:
            return getPPID();
    
        case PS:
            return (uint64_t) psDisplay();
        case KILL:
            return killProcess(rsi);
        case BLOCK:
            return blockProcess(rsi);
        case UNBLOCK:
            return unBlockProcess(rsi);
        case GET_PID:
            return getPID();
        case NICE :
            return nice(rsi,rdx);
        case TICKS_ELAPSED:
            return ticks_elapsed();
        case PROCESS_COUNT:
            return getProcessCount();
        case YIELD:
            yield();
            break;
        case SEM_OPEN:
            return sOpen(rsi, rdx);
        case SEM_POST:
            return sPost(rsi);
        case SEM_WAIT:
            return sWait(rsi);
        case SEM_CLOSE: 
            return sClose(rsi);
        case PIPE_OPEN:
            return pOpen(rsi);
        case PIPE_READ:
            return pRead(rsi);
        case PIPE_WRITE:
            return pWrite(rsi, rdx);
        case PIPE_CLOSE:
            return pClose(rsi);
        case GET_PIPES:
            return (uint64_t)getPipes();
        default:
            return -1;
	}
}