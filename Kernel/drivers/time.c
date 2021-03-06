// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <time.h>
#include <pcb.h>
#include <lib.h>
#include "naiveConsole.h"
static unsigned long ticks = 0;

uint64_t timer_handler(uint64_t rsp) {
	ticks++;
	return scheduler(rsp);
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

int getTime(char option) {
	switch(option) {
		case SECONDS:
			return getTimeGen(SECONDS);
		case MINUTES:
			return getTimeGen(MINUTES);
		case HOURS:
			return getTimeGen(HOURS);
		case DAY:
			return getTimeGen(DAY);
		case MONTH:
			return getTimeGen(MONTH);
		case YEAR:
			return getTimeGen(YEAR);
		default: return -1;
	}
}

void wait(long seconds) {
	while (seconds_elapsed() < seconds);
}