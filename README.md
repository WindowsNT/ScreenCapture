# ScreenCapture single header library for Windows

Article: https://www.codeproject.com/Articles/5256890/ScreenCapture-Single-header-DirectX-library

Features:
* DirectX hardware screen capture and encoding
* Audio capture and mixing, multiple audio sources, can capture from speakers
* H264/H265/VP80/VP90/MP3/FLAC/AAC support
* Easy interface

```C++
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
```

Where the DESKTOPCAPTUREPARAMS is this structure:


```C++
struct DESKTOPCAPTUREPARAMS
{
    bool HasVideo = 1;
    bool HasAudio = 1;
    std::vector<std::tuple<std::wstring, std::vector<int>>> AudioFrom;
    GUID VIDEO_ENCODING_FORMAT = MFVideoFormat_H264;
    GUID AUDIO_ENCODING_FORMAT = MFAudioFormat_MP3;
    std::wstring f;
    int fps = 25;
    int NumThreads = 0;
    int Qu = -1;
    int vbrm = 0;
    int vbrq = 0;
    int BR = 4000;
    int NCH = 2;
    int SR = 44100;
    int ABR = 192;
    bool Cursor = true;
    RECT rx = { 0,0,0,0 };
    HWND hWnd = 0;
    IDXGIAdapter1* ad = 0;
    UINT nOutput = 0;

    unsigned long long StartMS = 0; // 0, none
    unsigned long long EndMS = 0; // 0, none
    bool MustEnd = false;
    bool Pause = false;
};
```
Where:

* HasVideo = 1 -> You are capturing video. If this is set, the output file must be an MP4 or an ASF regardless of if you have audio or not.
* HasAudio = 1 -> You are capturing audio. If this is set and you do not have a video, the output file must be an MP3 or FLAC. For AAC, you must use MP4.
* AudioFrom = a vector of which audio devices you want to capture. Each element is a tuple of the device unique ID (as returned by the enumeration, see VISTAMIXERS::EnumVistaMixers()) and a vector of the channels you want to record from.

The library can also record from a playback device (like your speakers) in loopback. You can specify multiple sources of recording and the library will mix them all into the final audio stream.

* VIDEO_ENCODING_FORMAT -> One of MFVideoFormat_H264, MFVideoFormat_HEVC, MFVideoFormat_VP90, MFVideoFormat_VP80.
* AUDIO_ENCODING_FORMAT -> One of MFAudioFormat_MP3 or MFAudioFormat_FLAC or MFAudioFormat_AAC. MP3 and AAC support only 44100/48000 2 channel output.
* f -> target file name (MP3/FLAC/AAC for audio only, MP4/ASF else)
* fps -> Frames per second
* NumThreads -> Threads for the video encoder, 0 default. Can be 0-16.
* Qu -> If >= 0 and <= 0, Quality Vs Speed video factor
* vbrm and vbrq -> If 2, then vbrq is a quality value between 0 and 100 (BR is ignored)
* BR -> Video bitrate in KBps, default 4000. If vbrm is 2, BR is ignored
* NCH -> Audio output channels
* SR -> Audio output sample rate
* ABR -> Audio bitrate in Kbps for MP3
* Cursor -> true to capture the cursor
* rx -> If not {0}, capture this specific rect only
* hWnd -> If not {0}, capture this HWND only. If HWND is 0 and rx = {0}, the entire screen is captured
* ad -> If not 0, specifies which adapter you want to capture if you have more than 1 adapter
* nOutput -> The index of the monitor to capture. 0 is the first monitor. For multiple monitors, this specifies the monitor.
* EndMS -> If not 0, the library stops when EndMs milliseconds have been captured. Else you have to stop the library by setting "MustEnd" to true
* MustEnd -> Set to true for the library to stop capturing
* Pause -> If true, capture is paused




