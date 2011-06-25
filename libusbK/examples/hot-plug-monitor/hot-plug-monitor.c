/*!
#
# Copyright (c) 2011 Travis Robinson <libusbdotnet@gmail.com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
# IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
# PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TRAVIS LEE ROBINSON
# BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
# THE POSSIBILITY OF SUCH DAMAGE.
#
*/
#include "examples.h"

VOID KUSB_API OnHotPlugEvent(
    __in KHOT_HANDLE Handle,
    __in PKHOT_PARAMS Params,
    __in PCKLST_DEV_INFO DeviceInfo,
    __in KHOT_PLUG_TYPE NotificationType)
{
	UNREFERENCED_PARAMETER(Handle);

	printf(
	    "\n"
	    "UsbK device %s: %s\n"
	    "  %s (%s) [%s]\n\n",
	    NotificationType == KHOT_PLUG_ARRIVAL ? "arrival" : "removal",
	    DeviceInfo->DeviceInstance,
	    DeviceInfo->DeviceDesc,
	    DeviceInfo->Mfg,
	    DeviceInfo->Service);
}

DWORD __cdecl main(int argc, char* argv[])
{
	PKLST_HANDLE deviceList = NULL;
	PKLST_DEV_INFO deviceInfo = NULL;
	LIBUSBK_INTERFACE_HANDLE handle = NULL;
	DWORD errorCode = ERROR_SUCCESS;
	KHOT_HANDLE hotHandle = NULL;
	KHOT_PARAMS hotParams;
	KLST_INIT_PARAMS listParams;
	CHAR chKey = '\0';

	/*!
	Find the test device. Uses "vid=hhhh pid=hhhh" arguments supplied on the
	command line. (default is: vid=04D8 pid=FA2E)
	*/
	memset(&listParams, 0, sizeof(listParams));

	listParams.ShowDisconnectedDevices = TRUE;

	if (!Examples_GetTestDeviceEx(&deviceList, &deviceInfo, argc, argv, &listParams))
		return GetLastError();

	memset(&hotParams, 0, sizeof(hotParams));
	hotParams.OnHotPlugEvent = OnHotPlugEvent;
	hotParams.Flags.PlugAllOnInit = 1;
	strcpy(hotParams.DevInstIdPatternMatch, deviceInfo->DeviceInstance);

	if (!HotK_Init(&hotHandle, &hotParams))
	{
		errorCode = GetLastError();
		printf("HotK_Init failed. Win32Error=%u (0x%08X)\n", errorCode, errorCode);
		goto Done;
	}

	printf("Monitoring hot-plug events. Press 'q' to exit..\n\n");

	for(;;)
	{
		if (_kbhit())
		{
			chKey = _getch();
			if (chKey == 'q' || chKey == 'Q')
				break;

			chKey = '\0';
			continue;
		}

		Sleep(100);
		SwitchToThread();

	}

	if (!HotK_Free(&hotHandle))
	{
		errorCode = GetLastError();
		printf("HotK_Free failed. Win32Error=%u (0x%08X)\n", errorCode, errorCode);
		goto Done;
	}

	/*!
	Open the device. This creates the physical USB device handle.
	if (!UsbK_Open(deviceInfo, &handle))
	{
		errorCode = GetLastError();
		printf("Open device failed. Win32Error=%u (0x%08X)\n", errorCode, errorCode);
		goto Done;
	}
	printf("Device opened successfully!\n");
	*/

	/*!
	------------------------
	TODO: [APPLICATION CODE]
	------------------------
	*/
	printf("Auto-generated by kGen: Example not finished yet!\n");

Done:
	/*!
	Close the device handle. If handle is invalid (NULL), has no effect.
	UsbK_Close(handle);
	*/

	/*!
	Free the device list. If deviceList is invalid (NULL), has no effect.
	*/
	LstK_Free(&deviceList);

	return errorCode;
}