#include <bitset>
#include <iostream>
#include "include/DigitRecogniser.h"

int main()
{
	std::cout << "1:" << DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample1.png")) << std::endl;
	std::cout << "2:" << DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample2.png")) << std::endl;
	std::cout << "3:" << DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample3.png")) << std::endl;
	std::cout << "4:" << DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample4.png")) << std::endl;
	std::cout << "5:" << DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample5.png")) << std::endl;
	std::cout << "6:" << DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample6.png")) << std::endl;
	std::cout << "7:" << DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample7.png")) << std::endl;
	std::cout << "8:" << DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample8.png")) << std::endl;
	std::cout << "9:" << DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample9.png")) << std::endl;
	std::cout << "0:" << DigitRecogniser::RecogniseDigit(std::string("SampleImages/sample0.png")) << std::endl;

	return 0;
}
