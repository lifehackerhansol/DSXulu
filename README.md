# DSXulu

DS-Xtreme Universal Loader

https://github.com/lifehackerhansol/DSXulu

This is a custom firmware for the DS-Xtreme.

This will simply launch `BOOT.NDS` homebrew on the root of the NAND. Only homebrew files are supported (not that the DS-Xtreme really supports any games anyway.)

If `BOOT.NDS` is not found, it will fall back to a built in file browser.

### Flashing instructions

1. Download [dsxTool](https://github.com/ApacheThunder/dsxTool)
1. Copy `dsx_firmware.nds` and `dsxTool.nds` to your DS-Xtreme's root
1. Boot your DS-Xtreme, and launch dsxTool
1. Press `A` to dump your current firmware and wait for it to finish
	- You will need this if you ever wish to easily revert to your old firmware. You never know when that is!
1. Press `X` to flash `dsx_firmware.nds` to your DS-Xtreme and wait for it to finish
1. After the process is complete, reboot and see your changes live!

### License

```
	NDS Homebrew Menu
	Copyright (C) 2005-2013 Michael Chisholm (Chishm)
	Copyright (C) 2005-2023 Dave Murphy (WinterMute)

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
```
