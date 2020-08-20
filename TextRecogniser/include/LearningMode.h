#pragma once
#include <iostream>
#include "IncludingElimination.h"
#include "Settings.h"
#include "NumberRecogniser.h"

static class LearningMode
{
public:
	static void PrintLearningTable()
	{
		//Settings::LearningMode = true;

		for (IncludingElimination<char> incl{ '0','1','2','3','4','5','6','7','8','9' }; incl.NotLast(); ++incl)
		{
			std::string str = "";
			for (auto i : *incl)
				str += i;
			//std::cout << str << std::endl;
			Settings::learningHolders = std::move(str);

			NumberRecogniser::RecogniseNumbersOnImage(std::string("SampleImages/0.png"));
		}
		Settings::LearningMode = false;
	}

};