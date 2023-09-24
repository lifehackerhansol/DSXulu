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

void PrintProgramName() {
	consoleClear();
	printf("\n");
	printf("<------------------------------>\n");
	printf("            DSXulu              \n");
	printf("   DS-Xtreme Universal Loader   \n");
	printf("<------------------------------>\n\n");
}

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
	// Change console palette so text is black and background is white
	BG_PALETTE_SUB[0] = RGB15(31,31,31);
	BG_PALETTE_SUB[255] = RGB15(0,0,0);
	PrintProgramName();
	iprintf("Loading...\n");
	if (!fatInitDefault()) 
	{
		PrintProgramName();
		iprintf("FAT init failed!\n");
		return exitBootstrap();
	}
	if(access("/boot.nds", F_OK) != 0)
	{
		PrintProgramName();
		iprintf("/boot.nds not found!\n");
		return exitBootstrap();
	}
	int err = runNdsFile("/boot.nds", 0, NULL);
	PrintProgramName();
	iprintf("Bootloader returned error %d\n", err);
	return exitBootstrap();
}
