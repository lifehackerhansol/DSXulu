/*
	DSXulu
	DS-Xtreme Universal Loader
	Copyright (c) 2023 lifehackerhansol

	Homebrew Menu
	Copyright (c) 2005-2013 Claudio (sverx)
	Copyright (c) 2005-2019 Michael Chisholm (Chishm)
	Copyright (c) 2005-2019 Dave Murphy (WinterMute)

	SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <nds.h>
#include <stdio.h>
#include <fat.h>
#include <sys/stat.h>
#include <limits.h>

#include <string.h>
#include <unistd.h>

#include "args.h"
#include "file_browse.h"
#include "hbmenu_banner.h"
#include "iconTitle.h"
#include "nds_loader_arm9.h"

using namespace std;

int exitProgram(void) {
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

void InitGUI (void) {
	iconTitleInit();
	// Subscreen as a console
	videoSetModeSub(MODE_0_2D);
	vramSetBankH(VRAM_H_SUB_BG);
	consoleInit(NULL, 0, BgType_Text4bpp, BgSize_T_256x256, 15, 0, false, true);
	BG_PALETTE_SUB[0] = RGB15(31,31,31);
	BG_PALETTE_SUB[255] = RGB15(0,0,0);
	keysSetRepeat(25,5);
}

int FileBrowser(int argc, char argv) {
	InitGUI();
	chdir("/nds");
	vector<string> extensionList = argsGetExtensionList();
	while(1) {
		string filename = browseForFile(extensionList);
		// Construct a command line
		vector<string> argarray;
		if (!argsFillArray(filename, argarray)) {
			iprintf("Invalid NDS or arg file selected\n");
		} else {
			iprintf("Running %s with %d parameters\n", argarray[0].c_str(), argarray.size());
			// Make a copy of argarray using C strings, for the sake of runNdsFile
			vector<const char*> c_args;
			for (const auto& arg: argarray) { c_args.push_back(arg.c_str()); }
			// Try to run the NDS file with the given arguments
			int err = runNdsFile(c_args[0], c_args.size(), &c_args[0]);
			iprintf("Start failed. Error %i\n", err);
		}
		argarray.clear();
		while (1) {
			swiWaitForVBlank();
			scanKeys();
			if (!(keysHeld() & KEY_A)) break;
		}
	}
}

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------
	// overwrite reboot stub identifier
	// so tapping power on DSi returns to DSi menu
	extern u64 *fake_heap_end;
	*fake_heap_end = 0;
	
	if (!fatInitDefault()) {
		InitGUI();
		iprintf ("FAT init failed!\n");
		return exitProgram();
	} else if(access("/boot.nds", F_OK) == 0) {
		int err = runNdsFile("/boot.nds", 0, NULL);
		InitGUI();
		iprintf("Bootloader returned error %d\n", err);
		return exitProgram();
	} else {
		// Fire up the file browser GUI if boot.nds isn't found
		return FileBrowser(argc, **argv);
	}
	return 0;
}
