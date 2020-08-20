#include <iostream>
#include <ctime>
#include "include/NumberRecogniser.h"
#include "include/LearningMode.h"

int main()
{
	//auto answer = InputImageCutter::CutImage(std::string("SampleImages/RecogniseSample.png"));
	//return 0;

	//auto str = InputImageCutter::CutImage(std::string("SampleImages/RecogniseSample.png"));
	//for (auto itr = str.begin(); itr != str.end(); ++itr)
	//	/*itr->SaveAsImage();*/
	//	std::cout << DigitRecogniser::RecogniseDigit(*itr);

	auto time = clock();
	for(int i = 0; i < 1000; ++i)
		for (auto i : NumberRecogniser::RecogniseNumbersOnImage(std::string("SampleImages/1_avg.png")))
		{
			std::cout << i << std::endl;
		}
	std::cout << (clock() - time) / 1000;
	//for (int i = 0; i < 1000; ++i)
	//LearningMode::PrintLearningTable();
	
	return 0;


	/*ILuint id;
	ilInit();
	ilGenImages(1, &id);
	ilBindImage(id);
	ilLoad(IL_PNG, reinterpret_cast<wchar_t*>(const_cast<char*>("SampleImages/Filter_Sample.png")));

	bool err = ilGetError();
	auto wqe = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
	Filter::AverageFilter(ilGetData(), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_WIDTH));
	Filter::AverageFilter(ilGetData(), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_WIDTH));
	Filter::AverageFilter(ilGetData(), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_WIDTH));
	Filter::AverageFilter(ilGetData(), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_WIDTH));
	Filter::TransformToBlackAndWhiteForm(ilGetData(), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_WIDTH));
	ilSave(IL_PNG,reinterpret_cast<wchar_t*>(const_cast<char*>("SampleImages/Filter_SampleOutn.png")));*/

	/*unsigned long long begin = clock();
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
	std::cout << (clock() - begin) / 1000  << "  SEC";*/
	return 0;
}
