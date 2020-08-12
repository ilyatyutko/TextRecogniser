#pragma once
#include <vector>
#include <IL/il.h>
#include <IL/ilu.h>
#include <iostream>
#include <functional>
#include "Pixel.h"
#include "Settings.h"
#include "Filter.h"
class Figure
{
private:
	ILuint id;
	std::vector<bool> Get_Binary_Form(Pixel* DataPtr, size_t RealWidth, size_t RealHeight) const
	{
		std::vector<bool> result;
		result.reserve(Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth);

		volume AverageBrightness = Filter::GetAverageColour(DataPtr, RealHeight, RealWidth).brightness();

		auto atPosition = [DataPtr, RealWidth](size_t offset_x, size_t offset_y)->Pixel& {return DataPtr[offset_x + offset_y * RealWidth]; };
		for (size_t offset_y = 0; offset_y < Settings::ImageRecognitionHeight; ++offset_y)
			for (size_t offset_x = 0; offset_x < Settings::ImageRecognitionWidth; ++offset_x)
			{
				if (atPosition(offset_x, offset_y).brightness() > AverageBrightness)
					result.push_back(false);
				else
					result.push_back(true);
			}
		return result;
	}

public:
	size_t offset_x;
	size_t offset_y;

	size_t RealWidth;
	size_t RealHeight;

	Figure(Pixel* DataPtr, size_t _width, size_t _height, size_t _offset_x, size_t _offset_y)
		: offset_x(_offset_x)
		, offset_y(_offset_y)
		, RealWidth(_width)
		, RealHeight(_height)
	{
		Settings::ililuINIT();
		ilGenImages(1, &id);
		ilBindImage(id);

		ilTexImage(_width, _height, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, DataPtr);
		delete[] DataPtr;
		iluScale(Settings::ImageRecognitionWidth, Settings::ImageRecognitionHeight, 1);
	}
	Figure(Figure& source)
		: offset_x(source.offset_x)
		, offset_y(source.offset_y)
		, RealWidth(source.RealWidth)
		, RealHeight(source.RealHeight)
		, id(source.id) {
		source.id = 0;
	}
	Figure(Figure&& source)
		: offset_x(source.offset_x)
		, offset_y(source.offset_y)
		, RealWidth(source.RealWidth)
		, RealHeight(source.RealHeight)
		, id(source.id) {
		source.id = 0;
	}
	Figure& operator=(Figure& source)
	{
		offset_x = source.offset_x;
		offset_y = source.offset_y;
		RealWidth = source.RealWidth;
		RealHeight = source.RealHeight;
		id = source.id;
		source.id = 0;
	}
	Figure& operator=(Figure&& source)
	{
		offset_x = source.offset_x;
		offset_y = source.offset_y;
		RealWidth = source.RealWidth;
		RealHeight = source.RealHeight;
		id = source.id;
		source.id = 0;
	}
	~Figure()
	{
		if(id != 0)
			ilDeleteImages(1, &id);
	}
	inline bool SaveAsImage(std::string FileName) const
	{
		Settings::ililuINIT();
		ilBindImage(id);
		return ilSave(IL_PNG, reinterpret_cast<wchar_t*>(const_cast<char*>(FileName.c_str())));
	}
	inline bool SaveAsImage() const
	{
		Settings::ililuINIT();
		ilBindImage(id);

		std::string FileName = ".png";
		auto IDtmp = id;
		while (IDtmp)
		{
			FileName = (char)(IDtmp % 10 + '0') + FileName;
			IDtmp /= 10;
		}
		return ilSave(IL_PNG, reinterpret_cast<wchar_t*>(const_cast<char*>(FileName.c_str())));
	}
	inline std::vector<Pixel> GetRealColourPixelVector()const
	{
		std::vector<Pixel> answer;
		answer.reserve(Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth);

		ilBindImage(id);
		auto THISData = reinterpret_cast<Pixel*>( ilGetData());
		auto size = Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth;
		auto At = [THISData](size_t offset)->Pixel&
		{return *(THISData + offset); };
		
		for (int position = 0; position < size; ++position)
			answer.push_back(At(position));

		return answer;
	}
	std::vector<bool> GetBlackAndWhiteVector()const
	{
		std::vector<bool> answer;
		answer.reserve(Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth);

		ilBindImage(id);
		auto THISData = reinterpret_cast<Pixel*>(ilGetData());
		auto size = Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth;
		auto At = [THISData](size_t offset)->Pixel&
		{return *(THISData + offset); };

		auto width = ilGetInteger(IL_IMAGE_WIDTH);

		for (int position = 0; position < size; ++position)
			answer.push_back(At(position) == Colour::Transparent ? false : true);

		return answer;
	}
	inline void TransformToBlackAndWhiteForm()
	{
		Settings::ililuINIT();

		ilBindImage(id);
		auto THISData = reinterpret_cast<Pixel*>(ilGetData());
		auto size = Settings::ImageRecognitionHeight * Settings::ImageRecognitionWidth;
		auto At = [THISData](size_t offset)->Pixel&
		{return *(THISData + offset); };

		for (int position = 0; position < size; ++position)
			At(position) = (At(position) == Colour::Transparent) ? Colour::White : Colour::Black;
	}
	inline void ilBindFigure()const
	{
		::ilBindImage(id);
	}

	friend std::ostream& operator<< (std::ostream& out, const Figure& source);
};

std::ostream& operator<< (std::ostream& out, const Figure& source)
{
	Settings::ililuINIT();
	ilBindImage(source.id);
	size_t RealWidth = ilGetInteger(IL_IMAGE_WIDTH);
	size_t RealHeight = ilGetInteger(IL_IMAGE_HEIGHT);
	ILubyte* data = ilGetData();
	for (int y = 0; y < Settings::ImageRecognitionHeight; ++y)
	{
		for (int x = 0; x < Settings::ImageRecognitionWidth; ++x)
			out << (Filter::atPosition(reinterpret_cast<Pixel*>(data), Settings::ImageRecognitionWidth, x, y).isDark() ? '#' : ' ');
		out << std::endl;
	}
	return out;
}

