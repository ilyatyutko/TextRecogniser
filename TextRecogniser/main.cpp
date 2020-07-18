#include <bitset>
#include <iostream>
#include <ctime>
#include "include/DigitRecogniser.h"

int main()
{
	unsigned long long begin = clock();
	for (int i = 0; i < 1000; ++i)
	{
		DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample1.png"));
		DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample2.png"));
		DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample3.png"));
		DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample4.png"));
		DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample5.png"));
		DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample6.png"));
		DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample7.png"));
		DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample8.png"));
		DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample9.png"));
		DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample0.png"));
	}
	std::cout << (clock() - begin) / 1000  << "  SEC";
	return 0;
}
