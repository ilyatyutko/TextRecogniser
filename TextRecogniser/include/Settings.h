#pragma once
#include <IL/il.h>
#include <IL/ilu.h>
using volume = unsigned char;
static class Settings
{
public:
	const static size_t ImageRecognitionWidth = 20;
	const static size_t ImageRecognitionHeight = 20;

	const static double ContrastFilterPower;
	const static double SharpeningLevel;
	const static ILint SharpeningIterationsCount = 0;

	const static size_t FiltrationLevel = 0;
	const static volume BorderSeparationColorDifference = 25;

	const static bool inverseOverX = false;
	const static bool inverseOverY = true;

	const static size_t XminSymbolSizeOnImage = 15;
	const static size_t YminSymbolSizeOnImage = 25;

	static std::string learningHolders;
	static bool LearningMode;

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

//private:
	static bool ILWasINIT;
};
const double Settings::ContrastFilterPower = 505.;
const double Settings::SharpeningLevel = 70.;
bool Settings::ILWasINIT = false;
std::string Settings::learningHolders = "";
bool Settings::LearningMode = false;

