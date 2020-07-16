#pragma once
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "Encoder.h"

using namespace boost::numeric::ublas;
using SMatrix = boost::numeric::ublas::matrix<short>;
using VectorHash = std::string;

template <class Assigned>
class Hopfild
{
private:
	unsigned int matrixSize;
	std::unordered_map<VectorHash, Assigned> listOfRemembered;
	Assigned answerIfUncorrect;
	SMatrix recognitionMatrix;

	static const int RecognitionCyclesCount = 50;

	inline static short sigmaFunc(short a)
	{
		if (a >= 0)
			return 1;
		else
			return -1;
	}
	inline static vector<short> sigmaFunc(const vector<short>&a)
	{
		auto answer = a;
		for (int i = 0; i < answer.size(); ++i)
			answer(i) = sigmaFunc(answer(i));
		return answer;
	}
	inline static void inPlaceSigmaFunc(vector<short>& a)
	{
		for (int i = 0; i < a.size(); ++i)
			a(i) = sigmaFunc(a(i));
		return;
	}

	inline static vector<short> stdVecToUblasVec(std::vector<bool> input)
	{
		vector<short> answer(input.size());
		for (int i = 0; i < input.size(); ++i)
			answer(i) = (input[i] == true) ? 1 : -1;
		return answer;
	}
	inline static VectorHash GetHashOfVector(std::vector<bool> input)
	{
		VectorHash answer = "";
		answer.reserve(input.size());
		for (auto i = 0; i < input.size(); ++i)
			answer += (input[i] == true) ? '1' : '0';
		return answer;
	}
	inline static VectorHash GetHashOfVector(vector<short> input)
	{
		VectorHash answer = "";
		answer.reserve(input.size());
		for (auto i = 0; i < input.size(); ++i)
			answer += input[i] == 1 ? '1' : '0';
		return answer;
	}
public:
	Hopfild(const std::list<std::pair<std::vector<bool>, Assigned>> &InputListForRecognition
			, Assigned inputAnswerIfUncorrect = Assigned())
	{
		if (InputListForRecognition.size() == 0)
			throw std::exception("Empty List For Remembering");

		answerIfUncorrect = inputAnswerIfUncorrect;
		int Size = InputListForRecognition.begin()->first.size();
		for (auto& i : InputListForRecognition)
			listOfRemembered.insert(
				std::make_pair(
					//StringEncoder::Huffman(GetHashOfVector(i.first))
					GetHashOfVector(i.first)
					,i.second
				));

		matrixSize = Size;
		recognitionMatrix = SMatrix(Size, Size);
		for (int i = 0; i < Size; ++i)
			for (int j = 0; j < Size; ++j)
				recognitionMatrix(i, j) = 0;

		SMatrix tmp(1, Size);
		for (auto &vec : InputListForRecognition)
		{
			if (vec.first.size() != Size)
				throw std::exception("Input vectors have distinct length");
			for (int i = 0; i < Size; ++i)
				tmp(0, i) = (vec.first[i] == true) ? 1 : -1;
			recognitionMatrix += prod(trans(tmp), tmp) ;
		}

		for (int i = 0; i < Size; ++i)
			recognitionMatrix(i,i) = 0;
	}
private:
	Hopfild()
	{}
	friend class ImageRecogniser;

	Assigned recognition(std::vector<bool> vec)
	{
		vector<short> Vector(vec.size());
		for (int i = 0; i < vec.size(); ++i)
			Vector(i) = (vec[i] == true) ? 1 : -1;


		bool cycle = true;
		int counter = RecognitionCyclesCount;
		while (cycle && (counter--))
		{
			cycle = false;
			auto Copy = std::move(Vector);
			Vector = prod(recognitionMatrix, Vector);
			inPlaceSigmaFunc(Vector);
			for(int i = 0; i < Vector.size(); ++i)
				if (Vector(i) != Copy(i))
				{
					cycle = true;
					break;
				}
		}
		if (counter)
		{
			auto vec = GetHashOfVector(Vector); //StringEncoder::Huffman(GetHashOfVector(Vector));
			std::cout << std::endl;

			const int magicConst = 25;
			for (int y = 0; y < magicConst; ++y)
			{
				for (int x = 0; x < magicConst; ++x)
					std::cout << (Vector[magicConst * y + x] == 1) ? 1 : -1;
				std::cout << std::endl;
			}
			std::cout << std::endl;
			return listOfRemembered[vec];
		}
		else
			return answerIfUncorrect;
	}
};