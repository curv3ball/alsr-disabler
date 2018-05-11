#include <Windows.h>
#include <ImageHlp.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "ImageHlp.lib")

bool override(LPCSTR path, bool ASLR, bool DEP)
{
	LOADED_IMAGE PE;
	if (MapAndLoad(path, 0, &PE, 0, 0))
	{
		if (ASLR) // Enable address space layout randomization
			PE.FileHeader->OptionalHeader.DllCharacteristics = IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE;
		else // Disable address space layout randomization
			PE.FileHeader->OptionalHeader.DllCharacteristics = NULL;
		UnMapAndLoad(&PE);
		return true;
	}
	return false;
}

int main()
{
	override("test.exe", false, false);
}
