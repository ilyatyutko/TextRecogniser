#pragma once
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <list>
#include <string>
#include <iostream>
#include "Hopfild.h"
#include "Settings.h"
#include "Figure.h"
#include "InputImageCutter.h"

using FileName = std::string;

class ImageRecogniser
{
private:
	Hopfild<int> NeuralNet;
public:
	ImageRecogniser(const std::list<std::pair<FileName, int>>& FileList)
	{
		if (FileList.size() == 0)
			throw std::exception("Empty Input List");

		std::list<std::pair<std::vector<bool>, int>> Images;

		for (auto& file : FileList)
		{
			auto SymbolToLearn = InputImageCutter::CutImage(file.first).front();
			auto tmp = SymbolToLearn.GetBlackAndWhiteVector();
			Images.push_back( 
				std::make_pair(tmp
							   , file.second));
		}

		//there -1 is element, which means impossibility to recognise
		NeuralNet = Hopfild<int>(Images, -1); 
	}
	int RecognizeImage(const Figure& BinaryImage) const
	{
		return NeuralNet.recognition(BinaryImage.GetBlackAndWhiteVector());
	}
	int RecognizeImage(const std::vector<bool>& VectorizedImage) const
	{
		if (VectorizedImage.size() != 
			Settings::ImageRecognitionWidth *  Settings::ImageRecognitionHeight)
			throw std::exception("input VectorImage has wrong size");
			return NeuralNet.recognition(VectorizedImage);
	}
};

