#pragma once
#include <string>
#include "ImageRecogniser.h"
#include "Figure.h"

static class DigitRecogniser
{
public:
	static char RecogniseDigit(const Figure& Image)
	{
		if (!RecognisersAreInitialized)
			Initialization();

		unsigned char NumberRate[SymbolsCount];
		for(int i = 0; i < SymbolsCount; ++i)
			NumberRate[i] = 0;
		for (int i = 0; i < Recognisers.size(); ++i)
		{
			auto Result = Recognisers[i].RecognizeImage(Image);
			if(0 <= Result && Result < SymbolsCount)
				++NumberRate[Result];
		}

		std::vector<size_t> indexes;
		int maxHit = 0;
		for (int i = 0; i < SymbolsCount; ++i)
			if (NumberRate[i] > maxHit)
			{
				indexes.clear();
				indexes.push_back(i);
				maxHit = NumberRate[i];
			}
			else if (NumberRate[i] == maxHit)
			{
				indexes.push_back(i);
			}
		size_t randIndex = rand() % indexes.size();
		return GetCharofNumber(indexes[randIndex]);
	}
private:
	static bool RecognisersAreInitialized;
	static constexpr size_t SymbolsCount = 10;
	static char* SymbolTable;
	static std::vector<ImageRecogniser> Recognisers;

	inline static int GetNumberOfSymbol(char symb)
	{
		for (int i = 0; i < SymbolsCount; ++i)
			if (SymbolTable[i] == symb)
				return i;
		throw std::exception("DigitRecogniser::Initializstion - No such symbol:" + symb);
	}
	inline static char GetCharofNumber(int numb)
	{
		if (numb < 0 || numb >= SymbolsCount)
			return '\0';
		return SymbolTable[numb];
	}
	static void Initialization()
	{
		if (RecognisersAreInitialized)
			return;
		Recognisers.clear();
		srand(time(0));

		SymbolTable[0] = '0';
		SymbolTable[1] = '1';
		SymbolTable[2] = '2';
		SymbolTable[3] = '3';
		SymbolTable[4] = '4';
		SymbolTable[5] = '5';
		SymbolTable[6] = '6';
		SymbolTable[7] = '7';
		SymbolTable[8] = '8';
		SymbolTable[9] = '9';

		RecognisersAreInitialized = true;
		std::list<std::pair<std::string, int>> a;

		Recognisers.reserve(6);

		a.push_back(std::make_pair("SampleImages/3.png", GetNumberOfSymbol('3')));
		a.push_back(std::make_pair("SampleImages/4.png", GetNumberOfSymbol('4')));
		a.push_back(std::make_pair("SampleImages/7.png", GetNumberOfSymbol('7')));
		a.push_back(std::make_pair("SampleImages/0.png", GetNumberOfSymbol('0')));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/2.png", GetNumberOfSymbol('2')));
		a.push_back(std::make_pair("SampleImages/6.png", GetNumberOfSymbol('6')));
		a.push_back(std::make_pair("SampleImages/7.png", GetNumberOfSymbol('7')));
		a.push_back(std::make_pair("SampleImages/9.png", GetNumberOfSymbol('9')));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/1.png", GetNumberOfSymbol('1')));
		a.push_back(std::make_pair("SampleImages/3.png", GetNumberOfSymbol('3')));
		a.push_back(std::make_pair("SampleImages/6.png", GetNumberOfSymbol('6')));
		a.push_back(std::make_pair("SampleImages/0.png", GetNumberOfSymbol('0')));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/4.png", GetNumberOfSymbol('4')));
		a.push_back(std::make_pair("SampleImages/5.png", GetNumberOfSymbol('5')));
		a.push_back(std::make_pair("SampleImages/7.png", GetNumberOfSymbol('7')));
		a.push_back(std::make_pair("SampleImages/8.png", GetNumberOfSymbol('8')));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/1.png", GetNumberOfSymbol('1')));
		a.push_back(std::make_pair("SampleImages/4.png", GetNumberOfSymbol('4')));
		a.push_back(std::make_pair("SampleImages/6.png", GetNumberOfSymbol('6')));
		a.push_back(std::make_pair("SampleImages/8.png", GetNumberOfSymbol('8')));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/2.png", GetNumberOfSymbol('2')));
		a.push_back(std::make_pair("SampleImages/6.png", GetNumberOfSymbol('6')));
		a.push_back(std::make_pair("SampleImages/7.png", GetNumberOfSymbol('7')));
		a.push_back(std::make_pair("SampleImages/9.png", GetNumberOfSymbol('9')));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/0.png", GetNumberOfSymbol('0')));
		a.push_back(std::make_pair("SampleImages/1.png", GetNumberOfSymbol('1')));
		a.push_back(std::make_pair("SampleImages/3.png", GetNumberOfSymbol('3')));
		a.push_back(std::make_pair("SampleImages/5.png", GetNumberOfSymbol('5')));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/1.png", GetNumberOfSymbol('1')));
		a.push_back(std::make_pair("SampleImages/4.png", GetNumberOfSymbol('4')));
		a.push_back(std::make_pair("SampleImages/5.png", GetNumberOfSymbol('5')));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/2.png", GetNumberOfSymbol('2')));
		a.push_back(std::make_pair("SampleImages/4.png", GetNumberOfSymbol('4')));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/0.png", GetNumberOfSymbol('0')));
		a.push_back(std::make_pair("SampleImages/3.png", GetNumberOfSymbol('3')));
		a.push_back(std::make_pair("SampleImages/5.png", GetNumberOfSymbol('5')));
		Recognisers.push_back(ImageRecogniser(a));

		return;
	}
	public:
	static void ReLearnOn(std::list<char>source)
	{
		if (!RecognisersAreInitialized)
			Initialization();
		Recognisers.clear();
		std::list<std::pair<std::string, int>> a;
		for (auto i : source)
			a.push_back(std::make_pair(std::string("SampleImages/") + i + std::string(".png"), GetNumberOfSymbol(i)));
		Recognisers.push_back(ImageRecogniser(a));
		return;
	}
};

bool DigitRecogniser::RecognisersAreInitialized = false;
std::vector<ImageRecogniser> DigitRecogniser::Recognisers = std::vector<ImageRecogniser>();
char* DigitRecogniser::SymbolTable = new char[DigitRecogniser::SymbolsCount];
