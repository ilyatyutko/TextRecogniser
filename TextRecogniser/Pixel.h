#pragma once
using volume = unsigned char;
class Pixel
{
	volume R;
	volume G;
	volume B;
	volume T = 255;

	inline volume brightness() const
	{
		return std::round(((double)R + (double)G + (double)B) / 3 * (double)T / 256);
	}
	inline Pixel GetNegative() const
	{
		Pixel answer;
		answer.R = ~this->R;
		answer.G = ~this->G;
		answer.B = ~this->B;
		return answer;
	}
	inline void SetNegative()
	{
		this->R = ~this->R;
		this->G = ~this->G;
		this->B = ~this->B;
	}
	inline bool isBlack()const
	{
		return !((int)R + G + B);
	}
	inline bool isWhite()const
	{
		return R & G & B == 255;
	}

	Pixel(volume R_set, volume G_set, volume B_set)
		:R(R_set)
		, G(G_set)
		, B(B_set)
	{}
	Pixel()
		:R(0)
		, G(0)
		, B(0)
	{}
};

