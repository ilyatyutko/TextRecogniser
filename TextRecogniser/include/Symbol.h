#pragma once
#include "Figure.h"
#include "DigitRecogniser.h"
class Symbol
{
public:
	size_t width;
	size_t height;

	size_t X_offset;
	size_t Y_offset;

	char ASCII;
	bool isPrevTo(const Symbol& another)
	{
		bool ISRighter = another.X_offset >= (this->X_offset + std::ceil(0.8 * this->width))
			&& another.X_offset <= (this->X_offset + std::ceil(1.5 * this->width));
		bool ISSameUnderLine = (another.Y_offset + another.height) <= (this->Y_offset + std::ceil(1.1 * this->height))
			&& (another.Y_offset + another.height) >= (this->Y_offset + std::ceil(0.9 * this->height));
		bool ISSameCenter = (another.Y_offset + (another.height >> 1)) >= ((this->Y_offset + (this->height >> 1)) - std::ceil(0.2 * max(this->height, another.height)))
			&& (another.Y_offset + (another.height >> 1)) <= ((this->Y_offset + (this->height >> 1)) + std::ceil(0.2 * max(this->height, another.height)));
		return ISRighter && (ISSameUnderLine || ISSameCenter);
	}

	Symbol(const Figure& source)
		:width(source.RealWidth)
		,height(source.RealHeight)
		,X_offset(source.offset_x)
		,Y_offset(source.offset_y)
		,ASCII(DigitRecogniser::RecogniseDigit(source))
	{}
	Symbol(const Symbol& source)
		:width(source.width)
		, height(source.height)
		, X_offset(source.X_offset)
		, Y_offset(source.Y_offset)
		, ASCII(source.ASCII)
	{}
	Symbol& operator= (const Symbol& source)
	{
		this->width = source.width;
		this->height = source.height;
		this->X_offset = source.X_offset;
		this->Y_offset = source.Y_offset;
		this->ASCII = source.ASCII;
	}

	class Comparer
	{
	public:
		class OX
		{
		public:
			bool operator()(Symbol a, Symbol b)
			{
				return a.X_offset < b.X_offset;
			}
		};
		class OY
		{
		public:
			bool operator()(Symbol a, Symbol b)
			{
				return a.Y_offset < b.Y_offset;
			}
		};
	};
};