#pragma once
#include <string>
#include "ImageRecogniser.h"
#include "Figure.h"

static class DigitRecogniser
{
public:
	static int RecogniseDigit(const Figure& Image)
	{
		if (!RecognisersAreInitialized)
			Initialization();

		unsigned char NumberRate[11];
		NumberRate[0] = NumberRate[1] = NumberRate[2]
			= NumberRate[3] = NumberRate[4] = NumberRate[5]
			= NumberRate[6] = NumberRate[7] = NumberRate[8]
			= NumberRate[9] = 0;
		for (int i = 0; i < 6; ++i)
			++NumberRate[Recognisers[i].RecognizeImage(Image)];

		int index = 0;
		for (int i = 0; i < 10; ++i)
			if (NumberRate[i] > NumberRate[index])
				index = i;
		return index;
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

bool DigitRecogniser::RecognisersAreInitialized = false;
std::vector<ImageRecogniser> DigitRecogniser::Recognisers = std::vector<ImageRecogniser>();

