#pragma once
#include <IL/il.h>
#include <IL/ilu.h>
using volume = unsigned char;
static class Settings
{
public:
	const static size_t ImageRecognitionWidth = 25;
	const static size_t ImageRecognitionHeight = 25;

	const static double ContrastFilterPower;
	const static double SharpeningLevel;
	const static ILint SharpeningIterationsCount = 5;

	const static size_t FiltrationLevel = 1;
	const static volume BorderSeparationColorDifference = 25;

	const static bool inverseOverX = false;
	const static bool inverseOverY = true;

	const static size_t XminSymbolSizeOnImage = 15;
	const static size_t YminSymbolSizeOnImage = 25;

	inline static void ililuINIT()
	{
		if (!Settings::ILWasINIT)
		{
			ilInit();
			iluInit();
			ilEnable(IL_FILE_OVERWRITE);
			Settings::ILWasINIT = true;
		}
	}

private:
	static bool ILWasINIT;


};
const double Settings::ContrastFilterPower = 5.;
const double Settings::SharpeningLevel = 700.;
bool Settings::ILWasINIT = false;


