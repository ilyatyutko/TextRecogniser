#pragma once
#include <string>
#include "include/ImageRecogniser.h"

static class NumberRecogniser
{
public:
	static bool RecognisersAreInitialized;
	static ImageRecogniser Recognisers[6];

	static int RecogniseNumber(const std::string& FileName)
	{
		if (!RecognisersAreInitialized)
			Initialization();

		std::string possibleNumbers = "";
		for (int i = 0; i < 6; ++i)
			possibleNumbers += Recognisers[i].RecognizeImage(FileName);

		return possibleNumbers[0] - '0';
	}
private:
	static void Initialization()
	{
		if (RecognisersAreInitialized)
			return;
		std::list<std::pair<std::string, std::string>> a;

		a.push_back(std::make_pair("SampleImages/3.png", "3"));
		a.push_back(std::make_pair("SampleImages/4.png", "4"));
		a.push_back(std::make_pair("SampleImages/7.png", "7"));
		a.push_back(std::make_pair("SampleImages/0.png", "0"));
		Recognisers[0] = ImageRecogniser(a);

		a.clear();
		a.push_back(std::make_pair("SampleImages/2.png", "2"));
		a.push_back(std::make_pair("SampleImages/6.png", "6"));
		a.push_back(std::make_pair("SampleImages/7.png", "7"));
		a.push_back(std::make_pair("SampleImages/9.png", "9"));
		Recognisers[1] = ImageRecogniser(a);

		a.clear();
		a.push_back(std::make_pair("SampleImages/1.png", "1"));
		a.push_back(std::make_pair("SampleImages/3.png", "3"));
		a.push_back(std::make_pair("SampleImages/6.png", "6"));
		a.push_back(std::make_pair("SampleImages/0.png", "0"));
		Recognisers[2] = ImageRecogniser(a);

		a.clear();
		a.push_back(std::make_pair("SampleImages/4.png", "4"));
		a.push_back(std::make_pair("SampleImages/5.png", "5"));
		a.push_back(std::make_pair("SampleImages/7.png", "7"));
		a.push_back(std::make_pair("SampleImages/8.png", "8"));
		Recognisers[3] = ImageRecogniser(a);

		a.clear();
		a.push_back(std::make_pair("SampleImages/1.png", "1"));
		a.push_back(std::make_pair("SampleImages/4.png", "4"));
		a.push_back(std::make_pair("SampleImages/6.png", "6"));
		a.push_back(std::make_pair("SampleImages/8.png", "8"));
		Recognisers[4] = ImageRecogniser(a);

		a.clear();
		a.push_back(std::make_pair("SampleImages/2.png", "2"));
		a.push_back(std::make_pair("SampleImages/6.png", "6"));
		a.push_back(std::make_pair("SampleImages/7.png", "7"));
		a.push_back(std::make_pair("SampleImages/9.png", "9"));
		Recognisers[5] = ImageRecogniser(a);


		return;
	}
};

bool NumberRecogniser::RecognisersAreInitialized = false;

