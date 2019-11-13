#include "pch.h"
#include <vector>
#include <cstdio>
#include "SADXModLoader.h"

signed int __cdecl sub_643C00(int a1)
{
	return 0;
}

FunctionPointer(void, sub_40E430, (void* a1, __int16 a2, __int16 a3, int a4, int a5, int a6), 0x40E430);
void __cdecl sub_40E430_r(void* a1, __int16 a2, __int16 a3, int a4, int a5, int a6)
{
	sub_40E430(a1, a2, 0, a4, 480, a6);
}

extern "C"
{
	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		char txtpath[MAX_PATH];
		sprintf_s(txtpath, "%s\\recap.txt", path);
		FILE* f;
		if (fopen_s(&f, txtpath, "r"))
		{
			PrintDebug("Could not open recap.txt!\n");
			return;
		}
		std::vector<char*> lines;
		while (true)
		{
			char* buf = new char[51];
			if (!fgets(buf, 51, f))
			{
				delete[] buf;
				break;
			}
			char* lf = strrchr(buf, '\n');
			if (lf)
				*lf = 0;
			lines.push_back(buf);
		}
		fclose(f);
		char** txtbuf = new char* [lines.size()];
		memcpy(txtbuf, lines.data(), lines.size() * sizeof(char*));
		RecapScreen rcs = { 1.5f, (int)lines.size(), (const char**)txtbuf };
		SonicStoryE[0] = rcs;
		TailsStoryE[0] = rcs;
		KnucklesStoryE[0] = rcs;
		AmyStoryE[0] = rcs;
		GammaStoryE[0] = rcs;
		BigStoryE[0] = rcs;
		LastStoryE[0] = rcs;
		WriteJump((void*)0x643C00, sub_643C00);
		WriteCall((void*)0x642820, sub_40E430_r);
		WriteData((float*)0x642437, 480.0f);
		WriteData((short*)0x64243F, (short)480);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}