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
	Hopfild<char> NeuralNet;
public:
	ImageRecogniser(const std::list<std::pair<FileName, char>>& FileList)
	{
		if (FileList.size() == 0)
			throw std::exception("Empty Input List");

		std::list<std::pair<std::vector<bool>, char>> Images;

		for (auto& file : FileList)
		{
			Images.push_back( 
				std::make_pair(
					InputImageCutter::CutImage(file.first).front().GetBlackAndWhiteVector()
							   , file.second));
		}

		//there '\a' is element, which means impossibility to recognise
		NeuralNet = Hopfild<char>(Images, '\a'); 
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

