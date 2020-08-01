#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <zlib.h>
#include "Settings.h"
static class Encoder
{
public:
	static std::string CountEncoding(const std::vector<bool>& source)
	{
		bool condition = false;
		unsigned short count = 0;
		std::string answer = "";
		for (int i = 0; i < source.size(); ++i)
		{
			if (source[i] == condition)
				++count;
			else
			{
				answer.push_back((char)(count >> 8));
				answer.push_back((char)(count & 0b11111111));
				condition ^= 1;
				count = 1;
			}
		}
		/*for (auto itr = 0; itr != answer.size(); ++itr)
			std::cout <<(unsigned int) answer[itr];
		std::cout << std::endl;*/
		return answer;
	}

};