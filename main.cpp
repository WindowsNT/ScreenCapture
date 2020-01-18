#include "stdafx.h"
#include "capture.hpp"
#include <iostream>

int wmain()
{
	CoInitializeEx(0, COINIT_APARTMENTTHREADED);
	MFStartup(MF_VERSION);
	std::cout << "Capturing screen for 10 seconds...";
	DESKTOPCAPTUREPARAMS dp;
	dp.f = L"capture.mp4";
	dp.EndMS = 10000;
	DesktopCapture(dp);
	std::cout << "Done.\r\n";
	return 0;
}

