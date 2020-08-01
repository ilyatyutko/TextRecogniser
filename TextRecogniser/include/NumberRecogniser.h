#pragma once
#include <string>
#include "DigitRecogniser.h"
#include "InputImageCutter.h"

class NumberRecogniser
{
public:
	std::string RecogniseNumber(const std::string& FileName)
	{
		auto Symbols = InputImageCutter::CutImage(FileName);
		std::string answer = "";
		for (auto itr = Symbols.begin(); itr != Symbols.end(); ++itr)
			answer += recogniser.RecogniseDigit(*itr);
		return answer;
	}
	void RecogniseNumber(const std::string& FileName, std::string& toWrite)
	{
		auto Symbols = InputImageCutter::CutImage(FileName);
		std::string answer = "";
		for (auto itr = Symbols.begin(); itr != Symbols.end(); ++itr)
			answer += recogniser.RecogniseDigit(*itr);
		toWrite = answer;
	}
private: 
	DigitRecogniser recogniser;

};
