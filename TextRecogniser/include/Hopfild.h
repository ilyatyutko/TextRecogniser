#pragma once
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <unordered_map>
#include <vector>

#include "Encoder.h"

using namespace boost::numeric::ublas;
using SMatrix = boost::numeric::ublas::matrix<double>;
using VectorHash = std::string;

namespace 
{
	inline double sigmaFunc(double a)
	{
		if (a >= 0.)
			return 1.;
		else
			return -1.;
	}
	inline void inPlaceSigmaFunc(vector<double>& a)
	{
		for (int i = 0; i < a.size(); ++i)
			a(i) = sigmaFunc(a(i));
		return;
	}
	inline VectorHash GetHashOfVector(const std::vector<bool>& input)
	{
		VectorHash answer = "";
		answer.reserve(input.size());
		for (auto i = 0; i < input.size(); ++i)
			answer += (input[i] == true) ? '1' : '0';
		return answer;
	}
	inline VectorHash GetHashOfVector(const vector<double>& input)
	{
		VectorHash answer = "";
		answer.reserve(input.size());
		for (auto i = 0; i < input.size(); ++i)
			answer += input[i] == 1 ? '1' : '0';
		return answer;
	}
}

template <class Assigned>
class Hopfild
{
private:
	unsigned int matrixSize;
	std::unordered_map<VectorHash, Assigned> listOfRemembered;
	Assigned answerIfUncorrect = Assigned();
	SMatrix recognitionMatrix;

	static const int RecognitionCyclesCount = 10;
public:
	Hopfild(const std::list<std::pair<std::vector<bool>, Assigned>>& InputListForRecognition
		, Assigned inputAnswerIfUncorrect = Assigned())
		:matrixSize(InputListForRecognition.begin()->first.size())
		,answerIfUncorrect(inputAnswerIfUncorrect)
	{
		if (matrixSize == 0)
			throw std::exception("Empty List For Remembering");
		for (auto& i : InputListForRecognition)
			listOfRemembered.insert(
				std::make_pair(
					CountingEncoding::Encode(i.first)
					,i.second
				));

		recognitionMatrix = SMatrix(matrixSize, matrixSize);
		for (int i = 0; i < matrixSize; ++i)
			for (int j = 0; j < matrixSize; ++j)
				recognitionMatrix(i, j) = 0.;

		SMatrix tmp(1, matrixSize);
		for (auto &vec : InputListForRecognition)
		{
			if (vec.first.size() != matrixSize)
				throw std::exception("Input vectors have distinct length");
			for (int i = 0; i < matrixSize; ++i)
				tmp(0, i) = (vec.first[i] == true) ? 1. : -1.;
			recognitionMatrix += prod(trans(tmp), tmp) / (double)InputListForRecognition.size();
		}

		for (int i = 0; i < matrixSize; ++i)
			recognitionMatrix(i,i) = 0.;
	}
private:
	Hopfild()
	{}
	friend class ImageRecogniser;

	Assigned recognition(std::vector<bool> vec) const
	{
		vector<double> Vector(vec.size());
		for (int i = 0; i < vec.size(); ++i)
			Vector(i) = (vec[i] == true) ? 1. : -1.;

		bool unstableCondition = true;
		int convertingCounter = RecognitionCyclesCount;
		auto previousVectorCondition = std::move(Vector);

		while (unstableCondition && (convertingCounter--))
		{
			unstableCondition = false;
			previousVectorCondition = std::move(Vector);
			Vector = prod(recognitionMatrix, previousVectorCondition);
			inPlaceSigmaFunc(Vector);
			for (int i = 0; i < Vector.size(); ++i)
				if (Vector(i) != previousVectorCondition(i))
				{
					unstableCondition = true;
					break;
				}
		}
		if (convertingCounter)
		{
			auto tmp = CountingEncoding::Encode(Vector);
			auto iter = listOfRemembered.find(tmp);
			if (iter != listOfRemembered.end())
				return iter->second;
			else
				return answerIfUncorrect;
		}
		else
			return answerIfUncorrect;
	}
};