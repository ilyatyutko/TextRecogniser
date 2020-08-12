#pragma once
#include <string>
static class CountingEncoding
{
public:
	static std::string Encode(const std::vector<bool>& source)
	{
		if (source.size() == 0)
			return std::string("");
		unsigned short counter = 0;
		bool written = false;
		std::string answer = "";

		std::for_each(source.begin(), source.end(),
			[&counter, &written, &answer](bool pos) {
				if (pos == written)
					++counter;
				else
				{
					answer += (char)(counter >> 8);
					answer += (char)(counter & 0b11111111);
					counter = 1;
					written ^= 1;
				}
			});
		if (counter > 1)
		{
			answer += (char)(counter >> 8);
			answer += (char)(counter & 0b11111111);
		}
		return answer;
	}
	static std::string Encode(const boost::numeric::ublas::vector<double>& source)
	{
		if (source.size() == 0)
			return std::string("");
		unsigned short counter = 0;
		bool written = false;
		std::string answer = "";

		auto Converter = [](double val) {return val >= 0.; };

		std::for_each(source.begin(), source.end(),
			[&counter, &written, &answer, &Converter](double pos) {
				if (Converter(pos) == written)
					++counter;
				else
				{
					answer += (char)(counter >> 8);
					answer += (char)(counter & 0b11111111);
					counter = 1;
					written ^= 1;
				}
			});
		if (counter > 1)
		{
			answer += (char)(counter >> 8);
			answer += (char)(counter & 0b11111111);
		}
		return answer;
	}
};