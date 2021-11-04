#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include "video.h"
#include "keyboard.h"
#include "time.h"
#include "pcb.h"
#include <interrupts.h>

#include "memorymanager.h"

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;



static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
static void * const sampleCodeModuleHeapAddress = (void *)0x600000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize) {
	memset(bssAddress, 0, bssSize);
}

void * getStackBase() {
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary() {
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

void load_idt();
uint64_t getRSP();

int main() {
    _cli();
	//memInit((char *)sampleCodeModuleHeapAddress, (64*1024*1024));
	memInit(sampleCodeModuleHeapAddress);
	load_idt();
	saveSampleRSP(getRSP());
	char * argv[] = {"Shell"};
	int error = addProcess(sampleCodeModuleAddress, 1, argv, 1, 0,"Shell");
	if(error == -1){
		return -1;
	}
	while(1){
		_hlt();
	}
	
	return 0;
}