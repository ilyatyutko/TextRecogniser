#pragma once
#include <string>
#include "DigitRecogniser.h"
#include "InputImageCutter.h"

static class NumberRecogniser
{
private:
		static DigitRecogniser Recogn;
public:
	static std::string RecogniseNumber(const std::string& FileName)
	{
		auto Symbols = InputImageCutter::CutImage(FileName);
		std::string answer = "";
		for (auto itr = Symbols.begin(); itr != Symbols.end(); ++itr)
			answer += Recogn.RecogniseDigit(*itr);
		return answer;
	}
};
DigitRecogniser NumberRecogniser::Recogn = DigitRecogniser();