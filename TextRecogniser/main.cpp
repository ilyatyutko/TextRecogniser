#include <iostream>
#include <ctime>
#include "include/NumberRecogniser.h"

int main()
{
	//auto answer = InputImageCutter::CutImage(std::string("SampleImages/RecogniseSample.png"));
	//return 0;

	//auto str = InputImageCutter::CutImage(std::string("SampleImages/RecogniseSample.png"));
	//for (auto itr = str.begin(); itr != str.end(); ++itr)
	//	/*itr->SaveAsImage();*/
	//	std::cout << DigitRecogniser::RecogniseDigit(*itr);
	for (int i = 0; i < 50; ++i)
		std::cout << NumberRecogniser::RecogniseNumber(std::string("SampleImages/RecogniseSample.png")) << std::endl;
	//std::cout << str;//int qweweqwe = 1;

	/*for (int i = 0; i < 500; ++i)
	{
		std::list<std::pair<std::string, int>> a;
		a.push_back(std::make_pair("SampleImages/3.png", 3));
		a.push_back(std::make_pair("SampleImages/4.png", 4));
		a.push_back(std::make_pair("SampleImages/7.png",7));
		a.push_back(std::make_pair("SampleImages/0.png", 0));
		auto qww = ImageRecogniser(a);
		a.clear();
		ilShutDown();
	}*/
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
