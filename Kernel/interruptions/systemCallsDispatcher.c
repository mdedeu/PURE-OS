#include <stdint.h>
#include "systemCalls.h"
#include "memorymanager.h"
#include "pcb.h"
#include "time.h"

uint64_t systemCallsDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	switch (rdi) {
		case 0:
            return write(rsi, rdx, rcx);
        case 1:
            return read(rsi, rdx, rcx);
        case 2:
            return getTime((char)rsi);
        case 3:
            createProcess((void(*)(int, char**))rsi,(int)rdx,(char**)rcx,(int)r8,(int*)r9); 
            break;
        case 4: 
            return (uint64_t) mallocMM(rsi);
        case 5:
            freeMM((void *) rsi);
            break;
        case 14:
            psDisplay();
            break;
        case 10:
            killProcess(rsi);
            break;
        case 11:
            blockProcess(rsi);
            break;
        case 12:
            unBlockProcess(rsi);
            break;
        case 13:
            return getPID();
        case 15 :
            nice(rsi,rdx);
        case 17:
            return ticks_elapsed();
        case 22:
            killProcess(rsi);
            break;
        default:
            return -1;
	}
}