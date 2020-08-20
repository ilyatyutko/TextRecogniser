#pragma once
#include <vector>
#include <list>
#include <boost/dynamic_bitset.hpp>

template <class T>
class IncludingElimination
{
private:
	boost::dynamic_bitset<> includingTable;
	std::vector<T> correlationTable;
	bool endPosition;
	bool beginPosition;
public:
	IncludingElimination(std::initializer_list<T> list)
		:includingTable(list.size(), 1ul)
	{

		if (list.size() == 0)
			throw std::exception("Empty Initializer List");
		if (list.size() == 1)
			throw std::exception("Initializer List has only one value");

		correlationTable.reserve(list.size());
		for (const auto& i : list)
			correlationTable.push_back(i);

		endPosition = false;
		beginPosition = true;
	}
	std::list<T> operator*()const 
	{
		std::list<T> answer;
		auto size = includingTable.size();
		for (size_t i = 0; i != includingTable.size(); ++i)
			if (includingTable[i])
				answer.push_back(correlationTable[i]);
		return answer;
	}
	IncludingElimination operator++(int)
	{
		auto answer = *this;
		this->operator++();
		return answer;
	}
	IncludingElimination& operator++()
	{
		if (includingTable.all())
		{
			endPosition = true;
			return *this;
		}
		size_t zeroIndex = 0;
		for (size_t i = 0; i != includingTable.size(); ++i)
			if (!includingTable[i])
			{
				zeroIndex = i;
				break;
			}
		for (size_t i = 0; i != zeroIndex; ++i)
			includingTable[i] = 0;
		includingTable[zeroIndex] = 1;
		beginPosition = false;
		return *this;
	}
	IncludingElimination operator--(int)
	{
		auto answer = *this;
		this->operator--();
		return answer;
	}
	IncludingElimination& operator--()
	{
		if (includingTable.count() == 1 && includingTable[0] == 1)
		{
			beginPosition = true;
			return;
		}


		size_t plusIndex = 0;
		for (size_t i = 0; i != includingTable.size(); ++i)
			if (includingTable[i])
			{
				plusIndex = i;
				break;
			}

		for (size_t i = 0; i != plusIndex; ++i)
			includingTable[i] = 1;
		includingTable[plusIndex] = 0;

		endPosition = false;
		return *this;
	}
	inline bool End() const
	{
		return endPosition;
	}
	inline bool Begin() const
	{
		return beginPosition;
	}
	inline bool NotLast() const
	{
		return !endPosition;
	}
	inline bool NotFront() const
	{
		return !beginPosition;
	}
};