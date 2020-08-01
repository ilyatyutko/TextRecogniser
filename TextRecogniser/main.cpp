#include <iostream>
#include <ctime>
#include "include/NumberRecogniser.h"

int main()
{
	//auto answer = InputImageCutter::CutImage(std::string("SampleImages/RecogniseSample.png"));
	//return 0;

	//auto str = InputImageCutter::CutImage(std::string("SampleImages/RecogniseSample.png"));
	//for (auto itr = str.begin(); itr != str.end(); ++itr)
	////	/*itr->SaveAsImage();*/
	//	std::cout << DigitRecogniser::RecogniseDigit(*itr);


	NumberRecogniser a;
	auto begin = clock();
	for(int i = 10; i; --i)
		std::cout << a.RecogniseNumber(std::string("SampleImages/RecogniseSample.png")) << std::endl;
	std::cout << (clock() - begin) / 1000  << "  SEC";

		//for (int i = 1000000; i; --i)
		//{
		//	//auto a = InputImageCutter::CutImage(std::string("SampleImages/RecogniseSample.png"));
		//	DigitRecogniser a;
		//	ilShutDown();
		//}
		
	return 1;
}
