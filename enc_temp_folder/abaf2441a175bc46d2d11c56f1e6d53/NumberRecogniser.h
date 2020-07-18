#pragma once
#include <string>
#include "ImageRecogniser.h"

static class NumberRecogniser
{
public:
	static int RecogniseNumber(const std::string& FileName)
	{
		if (!RecognisersAreInitialized)
			Initialization();

		std::string possibleNumbers = "";
		for (int i = 0; i < 6; ++i)
			possibleNumbers += Recognisers[i].RecognizeImage(FileName);
		int q = 12;
	////TODO: must Find mediane of this str and return it as an answer
		return possibleNumbers[0] - '0';
	}
private:
	static bool RecognisersAreInitialized;
	static std::vector<ImageRecogniser> Recognisers;
	static void Initialization()
	{
		if (RecognisersAreInitialized)
			return;
		 
		RecognisersAreInitialized = true;
		std::list<std::pair<std::string, char>> a;

		Recognisers.reserve(6);

		a.push_back(std::make_pair("SampleImages/3.png", '3'));
		a.push_back(std::make_pair("SampleImages/4.png", '4'));
		a.push_back(std::make_pair("SampleImages/7.png", '7'));
		a.push_back(std::make_pair("SampleImages/0.png", '0'));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/2.png", '2'));
		a.push_back(std::make_pair("SampleImages/6.png", '6'));
		a.push_back(std::make_pair("SampleImages/7.png", '7'));
		a.push_back(std::make_pair("SampleImages/9.png", '9'));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/1.png", '1'));
		a.push_back(std::make_pair("SampleImages/3.png", '3'));
		a.push_back(std::make_pair("SampleImages/6.png", '6'));
		a.push_back(std::make_pair("SampleImages/0.png", '0'));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/4.png", '4'));
		a.push_back(std::make_pair("SampleImages/5.png", '5'));
		a.push_back(std::make_pair("SampleImages/7.png", '7'));
		a.push_back(std::make_pair("SampleImages/8.png", '8'));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/1.png", '1'));
		a.push_back(std::make_pair("SampleImages/4.png", '4'));
		a.push_back(std::make_pair("SampleImages/6.png", '6'));
		a.push_back(std::make_pair("SampleImages/8.png", '8'));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/2.png", '2'));
		a.push_back(std::make_pair("SampleImages/6.png", '6'));
		a.push_back(std::make_pair("SampleImages/7.png", '7'));
		a.push_back(std::make_pair("SampleImages/9.png", '9'));
		Recognisers.push_back(ImageRecogniser(a));
		return;
	}
};

bool NumberRecogniser::RecognisersAreInitialized = false;
std::vector<ImageRecogniser> NumberRecogniser::Recognisers = std::vector<ImageRecogniser>();

