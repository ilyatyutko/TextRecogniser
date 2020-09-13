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
		for (IncludingElimination<char> incl{ '0','1','2','3','4','5','6','7','8','9' }; incl.NotLast(); ++incl)
		{
			DigitRecogniser::ReLearnOn(*incl);

			auto counter = 0;

			if (NumberRecogniser::RecogniseNumbersOnImage(std::string("SampleImages/0.png")).front() == std::string("0"))	++counter;
			if (NumberRecogniser::RecogniseNumbersOnImage(std::string("SampleImages/1.png")).front() == std::string("1"))	++counter;
			if (NumberRecogniser::RecogniseNumbersOnImage(std::string("SampleImages/2.png")).front() == std::string("2"))	++counter;
			if (NumberRecogniser::RecogniseNumbersOnImage(std::string("SampleImages/3.png")).front() == std::string("3"))	++counter;
			if (NumberRecogniser::RecogniseNumbersOnImage(std::string("SampleImages/4.png")).front() == std::string("4"))	++counter;
			if (NumberRecogniser::RecogniseNumbersOnImage(std::string("SampleImages/5.png")).front() == std::string("5"))	++counter;
			if (NumberRecogniser::RecogniseNumbersOnImage(std::string("SampleImages/6.png")).front() == std::string("6"))	++counter;
			if (NumberRecogniser::RecogniseNumbersOnImage(std::string("SampleImages/7.png")).front() == std::string("7"))	++counter;
			if (NumberRecogniser::RecogniseNumbersOnImage(std::string("SampleImages/8.png")).front() == std::string("8"))	++counter;
			if (NumberRecogniser::RecogniseNumbersOnImage(std::string("SampleImages/9.png")).front() == std::string("9"))	++counter;

			if (counter >= 5)
			{
				for (auto i : *incl)
					std::cout << i;
				std::cout << std::endl;
			}
		}
	}

};