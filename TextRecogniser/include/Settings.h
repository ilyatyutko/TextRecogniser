#pragma once
static class Settings
{
public:
	const static size_t ImageRecognitionWidth = 25;
	const static size_t ImageRecognitionHeight = 25;

	const static double ContrastFilterPower;
	const static double SharpeningLevel;
	const static ILint SharpeningIterationsCount = 5;
};
const double Settings::ContrastFilterPower = 5.;
const double Settings::SharpeningLevel = 700.;


