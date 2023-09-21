/*
	DSXulu
	DS-Xtreme Universal Loader
	By lifehackerhansol

	SPDX-License-Identifier: 0BSD
*/

#include <nds.h>
#include <fat.h>

#include <stdio.h>
#include <unistd.h>

#include "nds_loader_arm9.h"

int exitBootstrap(void) {
	iprintf("Press START to power off.");
	while(1) {
		swiWaitForVBlank();
		scanKeys();
		int pressed = keysDown();
		if(pressed & KEY_START) break;
	}
	fifoSendValue32(FIFO_USER_01, 1); // turn off ARM7
	return 0;
}

int main(void) {
	consoleDemoInit();
	iprintf("DSXulu\nDS-Xtreme Universal Loader\n\n");
	if (!fatInitDefault()) 
	{
		iprintf("FAT init failed!\n");
		return exitBootstrap();
	}
	if(access("/boot.nds", F_OK) != 0)
	{
		iprintf("/boot.nds not found!\n");
		return exitBootstrap();
	}
	int err = runNdsFile("/boot.nds", 0, NULL);
	iprintf("Bootloader returned error %d\n", err);
	return exitBootstrap();
}
