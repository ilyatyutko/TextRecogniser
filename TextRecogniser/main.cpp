#include "include/ImageRecogniser.h"
#include <bitset>

extern double multiplier = 1.3;

int main()
{
	/*std::list<std::pair<unsigned short, unsigned short>> answer;
	for (unsigned short i = 1; i <= 1023; ++i)
	{
		std::list<std::pair<std::string, std::string>> a;
		if(i & 0b0000000001)
			a.push_back(std::make_pair("SampleImages/1.png", "1"));
		if (i & 0b0000000010)
			a.push_back(std::make_pair("SampleImages/2.png", "2"));
		if (i & 0b0000000100)
			a.push_back(std::make_pair("SampleImages/3.png", "3"));
		if (i & 0b0000001000)
			a.push_back(std::make_pair("SampleImages/4.png", "4"));
		if (i & 0b0000010001)
			a.push_back(std::make_pair("SampleImages/5.png", "5"));
		if (i & 0b0000100001)
			a.push_back(std::make_pair("SampleImages/6.png", "6"));
		if (i & 0b0001000001)
			a.push_back(std::make_pair("SampleImages/7.png", "7"));
		if (i & 0b0010000001)
			a.push_back(std::make_pair("SampleImages/8.png", "8"));
		if (i & 0b0100000001)
			a.push_back(std::make_pair("SampleImages/9.png", "9"));
		if (i & 0b1000000001)
			a.push_back(std::make_pair("SampleImages/0.png", "0"));

		ImageRecogniser q(a);

		bool res = true;
		int goodCount = 0;
		if (i & 0b0000000001)
		{
			if (q.RecognizeImage(std::string("SampleImages/1.png")) != "1"
				|| q.RecognizeImage(std::string("SampleImages/sample1.png")) != "1")
				continue;
			++goodCount;
		}
		else
			if (q.RecognizeImage(std::string("SampleImages/1.png")) != ""
				|| q.RecognizeImage(std::string("SampleImages/sample1.png")) != "")
				continue;
		if (i & 0b0000000010)
		{
			if (q.RecognizeImage(std::string("SampleImages/2.png")) != "2"
				|| q.RecognizeImage(std::string("SampleImages/sample2.png")) != "2")
				continue;
			++goodCount;
		}
		else
			if (q.RecognizeImage(std::string("SampleImages/2.png")) != ""
				|| q.RecognizeImage(std::string("SampleImages/sample2.png")) != "")
				continue;
		if (i & 0b0000000100)
		{
			if (q.RecognizeImage(std::string("SampleImages/3.png")) != "3"
				|| q.RecognizeImage(std::string("SampleImages/sample3.png")) != "3")
				continue;
			++goodCount;
		}
		else
			if (q.RecognizeImage(std::string("SampleImages/3.png")) != ""
				|| q.RecognizeImage(std::string("SampleImages/sample3.png")) != "")
				continue;
		if (i & 0b0000001000)
		{
			if (q.RecognizeImage(std::string("SampleImages/4.png")) != "4"
				|| q.RecognizeImage(std::string("SampleImages/sample4.png")) != "4")
				continue;
			++goodCount;
		}
		else
			if (q.RecognizeImage(std::string("SampleImages/4.png")) != ""
				|| q.RecognizeImage(std::string("SampleImages/sample4.png")) != "")
				continue;
		if (i & 0b0000010000)
		{
			if (q.RecognizeImage(std::string("SampleImages/5.png")) != "5"
				|| q.RecognizeImage(std::string("SampleImages/sample5.png")) != "5")
				continue;
			++goodCount;
		}
		else
			if (q.RecognizeImage(std::string("SampleImages/5.png")) != ""
				|| q.RecognizeImage(std::string("SampleImages/sample5.png")) != "")
				continue;
		if (i & 0b0000100000)
		{
			if (q.RecognizeImage(std::string("SampleImages/6.png")) != "6"
				|| q.RecognizeImage(std::string("SampleImages/sample6.png")) != "6")
				continue;
			++goodCount;
		}
		else
			if (q.RecognizeImage(std::string("SampleImages/6.png")) != ""
				|| q.RecognizeImage(std::string("SampleImages/sample6.png")) != "")
				continue;
		if (i & 0b0001000000)
		{
			if (q.RecognizeImage(std::string("SampleImages/7.png")) != "7"
				|| q.RecognizeImage(std::string("SampleImages/sample7.png")) != "7")
				continue;
			++goodCount;
		}
		else
			if (q.RecognizeImage(std::string("SampleImages/7.png")) != ""
				|| q.RecognizeImage(std::string("SampleImages/sample7.png")) != "")
				continue;
		if (i & 0b0010000000)
		{
			if (q.RecognizeImage(std::string("SampleImages/8.png")) != "8"
				|| q.RecognizeImage(std::string("SampleImages/sample8.png")) != "8")
				continue;
			++goodCount;
		}
		else
			if (q.RecognizeImage(std::string("SampleImages/8.png")) != ""
				|| q.RecognizeImage(std::string("SampleImages/sample8.png")) != "")
				continue;
		if (i & 0b0100000000)
		{
			if (q.RecognizeImage(std::string("SampleImages/9.png")) != "9"
				|| q.RecognizeImage(std::string("SampleImages/sample9.png")) != "9")
				continue;
			++goodCount;
		}
		else
			if (q.RecognizeImage(std::string("SampleImages/9.png")) != ""
				|| q.RecognizeImage(std::string("SampleImages/sample9.png")) != "")
				continue;
		if (i & 0b1000000000)
		{
			if (q.RecognizeImage(std::string("SampleImages/0.png")) != "0"
				|| q.RecognizeImage(std::string("SampleImages/sample0.png")) != "0")
				continue;
			++goodCount;
		}
		else
			if (q.RecognizeImage(std::string("SampleImages/0.png")) != ""
				|| q.RecognizeImage(std::string("SampleImages/sample0.png")) != "")
				continue;
		answer.push_back(std::make_pair(i, goodCount));
	}
	for (auto q : answer)
		std::cout << std::setw(5) << std::bitset<16>(q.first) << "  " << q.second << std::endl;*/
std::list<std::pair<std::string, std::string>> a;
a.push_back(std::make_pair("SampleImages/1.png", "1"));
//a.push_back(std::make_pair("SampleImages/2.png", "2"));
a.push_back(std::make_pair("SampleImages/3.png", "3"));
//a.push_back(std::make_pair("SampleImages/4.png", "4"));
//a.push_back(std::make_pair("SampleImages/5.png", "5"));
a.push_back(std::make_pair("SampleImages/6.png", "6"));
//a.push_back(std::make_pair("SampleImages/7.png", "7"));
//a.push_back(std::make_pair("SampleImages/8.png", "8"));
//a.push_back(std::make_pair("SampleImages/9.png", "9"));
a.push_back(std::make_pair("SampleImages/0.png", "0"));
ImageRecogniser q(a);
std::cout << "1: " << q.RecognizeImage(std::string("SampleImages/1.png")) << std::endl;
std::cout << "2: " << q.RecognizeImage(std::string("SampleImages/2.png")) << std::endl;
std::cout << "3: " << q.RecognizeImage(std::string("SampleImages/3.png")) << std::endl;
std::cout << "4: " << q.RecognizeImage(std::string("SampleImages/4.png")) << std::endl;
std::cout << "5: " << q.RecognizeImage(std::string("SampleImages/5.png")) << std::endl;
std::cout << "6: " << q.RecognizeImage(std::string("SampleImages/6.png")) << std::endl;
std::cout << "7: " << q.RecognizeImage(std::string("SampleImages/7.png")) << std::endl;
std::cout << "8: " << q.RecognizeImage(std::string("SampleImages/8.png")) << std::endl;
std::cout << "9: " << q.RecognizeImage(std::string("SampleImages/9.png")) << std::endl;
std::cout << "0: " << q.RecognizeImage(std::string("SampleImages/0.png"));
std::cout << "" << std::endl;
std::cout << std::endl;
std::cout << "1: " << q.RecognizeImage(std::string("SampleImages/sample1.png")) << std::endl;
std::cout << "2: " << q.RecognizeImage(std::string("SampleImages/sample2.png")) << std::endl;
std::cout << "3: " << q.RecognizeImage(std::string("SampleImages/sample3.png")) << std::endl;
std::cout << "4: " << q.RecognizeImage(std::string("SampleImages/sample4.png")) << std::endl;
std::cout << "5: " << q.RecognizeImage(std::string("SampleImages/sample5.png")) << std::endl;
std::cout << "6: " << q.RecognizeImage(std::string("SampleImages/sample6.png")) << std::endl;
std::cout << "7: " << q.RecognizeImage(std::string("SampleImages/sample7.png")) << std::endl;
std::cout << "8: " << q.RecognizeImage(std::string("SampleImages/sample8.png")) << std::endl;
std::cout << "9: " << q.RecognizeImage(std::string("SampleImages/sample9.png")) << std::endl;
std::cout << "0: " << q.RecognizeImage(std::string("SampleImages/sample0.png"));

	return 0;
}
