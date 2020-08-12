#pragma once
using volume = unsigned char;
class Pixel
{
public:
	volume R;
	volume G;
	volume B;
	volume T = 255;

	inline bool operator==(const Pixel& b)const
	{
		return R == b.R &&
			G == b.G &&
			B == b.B &&
			T == b.T;
	}
	inline bool operator!=(const Pixel& b)const
	{
		return R != b.R ||
			G != b.G ||
			B != b.B ||
			T != b.T;
	}

	inline void SetWhiteWithTransparency()
	{
		R = G = B = 255;
	}
	inline void SetBlackWithTransparency()
	{
		R = G = B = 0;
	}
	inline volume brightness() const
	{
		return std::round((double)(R + G + B) * T / 256. / 3.);
	}
	inline Pixel GetNegative() const
	{
		return Pixel(~this->R, ~this->G, ~this->B);
	}
	inline void SetNegative()
	{
		this->R = ~(this->R);
		this->G = ~(this->G);
		this->B = ~(this->B);
	}
	inline bool isDark() const
	{
		return this->brightness() < 127;
	}
	inline bool isDarkerThan(const Pixel& a)const
	{
		return this->brightness() < a.brightness();
	}
	inline bool isBrighterThan(const Pixel& a)const
	{
		return this->brightness() > a.brightness();
	}
	inline bool isBright() const
	{
		return this->brightness() > 126;
	}
	inline bool isBlack()const
	{
		return !((int)R + G + B);
	}
	inline bool isWhite()const
	{
		return (R & G & B) == 255;
	}
	inline static volume colorDifference(const Pixel& a, const Pixel& b)
	{
		return std::ceil(std::abs(a.R - b.R) + std::abs(a.G - b.G) + std::abs(a.B - b.B));
	}

	Pixel(volume R_set, volume G_set, volume B_set, volume T_set = 255)
		:R(R_set)
		, G(G_set)
		, B(B_set)
		, T(T_set)
	{}
	Pixel()
		: R(0)
		, G(0)
		, B(0)
		, T(255)
	{}
};
namespace Colour {
	Pixel Black = Pixel(0, 0, 0);
	Pixel White = Pixel(255, 255, 255);
	Pixel Transparent = Pixel(0,0,0,0);
}