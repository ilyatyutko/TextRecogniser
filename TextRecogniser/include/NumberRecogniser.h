#pragma once
#include <string>
#include "Symbol.h"
#include "InputImageCutter.h"

static class NumberRecogniser
{
public:
	static std::list<std::string> RecogniseNumbersOnImage(const std::string& FileName)
	{
		auto ImageInfo = InputImageCutter::CutImage(FileName);
		auto Figures = std::get<0>(ImageInfo);
		auto Width = std::get<1>(ImageInfo);
		auto Height = std::get<2>(ImageInfo);

		std::list<Symbol> Symbols;
		for (auto itr = Figures.begin(); itr != Figures.end(); ++itr)
		{
			auto tmp = Symbol(*itr);
			if(std::isprint(tmp.ASCII))
				Symbols.push_back(tmp);
		}

		Symbols.sort( Symbol::Comparer::OX());


		std::list<std::string> NumbersList;
		while (!Symbols.empty())
		{
			auto LineEnd = Symbols.front();
			Symbols.erase(Symbols.begin());

			std::string line = std::string("") + LineEnd.ASCII;			
			for (auto itr = Symbols.begin(); itr != Symbols.end(); ++itr)
			{
				if (LineEnd.isPrevTo(*itr))
				{
					LineEnd = *itr;
					line += LineEnd.ASCII;
					Symbols.erase(itr);
				}
			}
			NumbersList.push_back(line);
		}

		

		return NumbersList;
	}
};
