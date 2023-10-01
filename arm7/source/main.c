/*
	DSXulu
	DS-Xtreme Universal Loader
	Copyright (c) 2023 lifehackerhansol

	Default ARM7 core
	Copyright (c) 2005-2010 Michael Noland (joat)
	Copyright (c) 2005-2010 Jason Rogers (dovoto)
	Copyright (c) 2005-2010 Dave Murphy (WinterMute)

	SPDX-License-Identifier: Zlib
*/

#include <nds.h>

volatile bool exitflag = false;

void powerButtonCB() {
	exitflag = true;
}

int main(void) {
	// clear sound registers
	dmaFillWords(0, (void*)0x04000400, 0x100);

	readUserSettings();
	ledBlink(0);

	irqInit();
	initClockIRQ();
	fifoInit();
	installSystemFIFO();

	setPowerButtonCB(powerButtonCB);

	while (!exitflag) {
		swiWaitForVBlank();

		if(fifoCheckValue32(FIFO_USER_01)) {
			fifoGetValue32(FIFO_USER_01);
			exitflag = true;
		}
	}
	return 0;
}
