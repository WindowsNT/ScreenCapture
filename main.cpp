#include "stdafx.h"
#include "capture.hpp"
#include <iostream>

int wmain()
{
	CoInitializeEx(0, COINIT_APARTMENTTHREADED);
	MFStartup(MF_VERSION);
	std::cout << "Capturing screen for 10 seconds...";
	DESKTOPCAPTUREPARAMS dp;
	dp.Cursor = 0;
	// To Video
	dp.VIDEO_ENCODING_FORMAT = MFVideoFormat_HEVC;
	dp.f = L"capture.mp4";

	// To Stream
/*	dp.f = L"";
	dp.PrepareAttributes = [](IMFAttributes* attrs)
	{
		attrs->SetGUID(MF_TRANSCODE_CONTAINERTYPE, MFTranscodeContainerType_ASF);
	};
	dp.Streamer = [](const BYTE* b,size_t sz,void* cb)
	{
		FILE* fp = 0;
		_wfopen_s(&fp, L"capture.asf", L"a+b");
		fwrite(b, 1, sz, fp);
		fclose(fp);
		return S_OK;
	};
	*/
	
	// To callback frame
	/*
	dp.f = L"";
	dp.HasAudio = 0;
	dp.HasVideo = 1;
	dp.Framer = [](const BYTE* b, size_t sz,void* cb)
	{
		if (sz)
			return S_OK;
		return S_FALSE;
	};
	*/

	dp.EndMS = 10000;
	DesktopCapture(dp);
	ShellExecute(0, L"open", L"capture.mp4", 0, 0, SW_SHOWNORMAL);
	std::cout << "Done.\r\n";
	return 0;
}

