#pragma once
#include <string>
#include <thread>
#include <functional>
#include "ImageRecogniser.h"

void ImageRecogniserCallWRAPPER(const ImageRecogniser& Obj, const ImageTransformer& BinaryImage, int& recordPlace)
{
	Obj.RecognizeImage(BinaryImage, recordPlace);
}

static class DigitRecogniser
{
public:
	static int RecogniseDigit(const std::string& FileName)
	{
		if (!RecognisersAreInitialized)
			Initialization();

		ImageTransformer Image(FileName);

		int RecognisingResults[6];

		auto ptr0 
			= std::bind(ImageRecogniserCallWRAPPER, Recognisers[0], Image, RecognisingResults[0]);
		auto ptr1
			= std::bind(ImageRecogniserCallWRAPPER, Recognisers[1], Image, RecognisingResults[1]);
		auto ptr2
			= std::bind(ImageRecogniserCallWRAPPER, Recognisers[2], Image, RecognisingResults[2]);
		auto ptr3
			= std::bind(ImageRecogniserCallWRAPPER, Recognisers[3], Image, RecognisingResults[3]);
		auto ptr4
			= std::bind(ImageRecogniserCallWRAPPER, Recognisers[4], Image, RecognisingResults[4]);
		auto ptr5
			= std::bind(ImageRecogniserCallWRAPPER, Recognisers[5], Image, RecognisingResults[5]);
		std::thread r0(ptr0);
		std::thread r1(ptr1);
		std::thread r2(ptr2);
		std::thread r3(ptr3);
		std::thread r4(ptr4);
		std::thread r5(ptr5);
		if (r0.joinable())
			r0.join();
		if (r1.joinable())
			r1.join();
		if (r2.joinable())
			r2.join();
		if (r3.joinable())
			r3.join();
		if (r4.joinable())
			r4.join();
		if (r5.joinable())
			r5.join();

		unsigned char NumberRate[11];
		NumberRate[0] = NumberRate[1] = NumberRate[2]
			= NumberRate[3] = NumberRate[4] = NumberRate[5]
			= NumberRate[6] = NumberRate[7] = NumberRate[8]
			= NumberRate[9] = 0;
		for (int i = 0; i < 6; ++i)
			++NumberRate[RecognisingResults[i]];

		int index = 0;
		for (int i = 0; i < 10; ++i)
			if (NumberRate[i] > NumberRate[index])
				index = i;

		return index;
	}
	static int RecogniseDigit(const ImageTransformer& Image)
	{
		if (!RecognisersAreInitialized)
			Initialization();

		unsigned char NumberRate[11];
		NumberRate[0] = NumberRate[1] = NumberRate[2]
			= NumberRate[3] = NumberRate[4] = NumberRate[5]
			= NumberRate[6] = NumberRate[7] = NumberRate[8]
			= NumberRate[9] = 0;
		for (int i = 0; i < 6; ++i)
			++NumberRate[Recognisers[i].RecognizeImage(Image)];

		int index = 0;
		for (int i = 0; i < 10; ++i)
			if (NumberRate[i] > NumberRate[index])
				index = i;

		return index;
	}
private:
	static bool RecognisersAreInitialized;
	static std::vector<ImageRecogniser> Recognisers;
	static void Initialization()
	{
		if (RecognisersAreInitialized)
			return;
		 
		RecognisersAreInitialized = true;
		std::list<std::pair<std::string, int>> a;

		Recognisers.reserve(6);

		a.push_back(std::make_pair("SampleImages/3.png", 3));
		a.push_back(std::make_pair("SampleImages/4.png", 4));
		a.push_back(std::make_pair("SampleImages/7.png", 7));
		a.push_back(std::make_pair("SampleImages/0.png", 0));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/2.png", 2));
		a.push_back(std::make_pair("SampleImages/6.png", 6));
		a.push_back(std::make_pair("SampleImages/7.png", 7));
		a.push_back(std::make_pair("SampleImages/9.png", 9));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/1.png", 1));
		a.push_back(std::make_pair("SampleImages/3.png", 3));
		a.push_back(std::make_pair("SampleImages/6.png", 6));
		a.push_back(std::make_pair("SampleImages/0.png", 0));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/4.png", 4));
		a.push_back(std::make_pair("SampleImages/5.png", 5));
		a.push_back(std::make_pair("SampleImages/7.png", 7));
		a.push_back(std::make_pair("SampleImages/8.png", 8));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/1.png", 1));
		a.push_back(std::make_pair("SampleImages/4.png", 4));
		a.push_back(std::make_pair("SampleImages/6.png", 6));
		a.push_back(std::make_pair("SampleImages/8.png", 8));
		Recognisers.push_back(ImageRecogniser(a));

		a.clear();
		a.push_back(std::make_pair("SampleImages/2.png", 2));
		a.push_back(std::make_pair("SampleImages/6.png", 6));
		a.push_back(std::make_pair("SampleImages/7.png", 7));
		a.push_back(std::make_pair("SampleImages/9.png", 9));
		Recognisers.push_back(ImageRecogniser(a));
		return;
	}
};

bool DigitRecogniser::RecognisersAreInitialized = false;
std::vector<ImageRecogniser> DigitRecogniser::Recognisers = std::vector<ImageRecogniser>();

