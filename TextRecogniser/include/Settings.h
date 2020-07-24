#pragma once
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

	static bool ILWasINIT;
};
const double Settings::ContrastFilterPower = 5.;
const double Settings::SharpeningLevel = 700.;
bool Settings::ILWasINIT = false;


