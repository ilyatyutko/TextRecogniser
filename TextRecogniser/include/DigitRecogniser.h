#pragma once
#include <string>
#include "ImageRecogniser.h"
#include "Figure.h"

class DigitRecogniser
{
public:
	DigitRecogniser()
	{
		Initialization();
	}
	char RecogniseDigit(const Figure& Image)
	{
		for (int i = 0; i < SymbolsCount; ++i)
			NumberRate[i] = 0;
		int index = -1;
		size_t maxRate = 0;
		for (int i = 0; i < RecognisersCount; ++i)
		{
			auto resultOfRecognising = Recognisers[i].RecognizeImage(Image);
			if (resultOfRecognising != -1)
			{
				if(++NumberRate[resultOfRecognising] > maxRate)
				{
					index = i;
					maxRate = NumberRate[i];
				}
			}
		}
		return GetSymbolOfIndex(index);
	}
private:
	static constexpr size_t SymbolsCount = 10;
	static constexpr size_t RecognisersCount = 6;

	unsigned char NumberRate[SymbolsCount];
	char SymbolIndexTranslation[SymbolsCount];
	std::vector<ImageRecogniser> Recognisers;
	void Initialization()
	{
		std::list<std::pair<std::string, int>> a;

		Recognisers.reserve(6);

		a.push_back(std::make_pair("SampleImages/3.png", 3));
		a.push_back(std::make_pair("SampleImages/4.png", 4));
		a.push_back(std::make_pair("SampleImages/7.png", 7));
		a.push_back(std::make_pair("SampleImages/0.png", 0));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/2.png", 2));
		a.push_back(std::make_pair("SampleImages/6.png", 6));
		a.push_back(std::make_pair("SampleImages/7.png", 7));
		a.push_back(std::make_pair("SampleImages/9.png", 9));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/1.png", 1));
		a.push_back(std::make_pair("SampleImages/3.png", 3));
		a.push_back(std::make_pair("SampleImages/6.png", 6));
		a.push_back(std::make_pair("SampleImages/0.png", 0));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/4.png", 4));
		a.push_back(std::make_pair("SampleImages/5.png", 5));
		a.push_back(std::make_pair("SampleImages/7.png", 7));
		a.push_back(std::make_pair("SampleImages/8.png", 8));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/1.png", 1));
		a.push_back(std::make_pair("SampleImages/4.png", 4));
		a.push_back(std::make_pair("SampleImages/6.png", 6));
		a.push_back(std::make_pair("SampleImages/8.png", 8));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/2.png", 2));
		a.push_back(std::make_pair("SampleImages/6.png", 6));
		a.push_back(std::make_pair("SampleImages/7.png", 7));
		a.push_back(std::make_pair("SampleImages/9.png", 9));
		Recognisers.push_back(ImageRecogniser(a));

		SymbolIndexTranslation[0] = ' ';
		SymbolIndexTranslation[1] = '1';
		SymbolIndexTranslation[2] = '2';
		SymbolIndexTranslation[3] = '3';
		SymbolIndexTranslation[4] = '4';
		SymbolIndexTranslation[5] = '5';
		SymbolIndexTranslation[6] = '6';
		SymbolIndexTranslation[7] = '7';
		SymbolIndexTranslation[8] = '8';
		SymbolIndexTranslation[9] = '9';
	}
	inline char GetSymbolOfIndex(const int index) const
	{
		if (index == -1)
			return '\a';
		else if ((-1 < index) && (index < SymbolsCount))
				return SymbolIndexTranslation[index];
		else throw std::exception("undefined index");
	}
};

