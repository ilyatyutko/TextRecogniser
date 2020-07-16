#include "include/ImageRecogniser.h"

extern double multiplier = 1.3;

int main()
{
	std::list<std::pair<std::string, std::string>> a;
	a.push_back(std::make_pair("SampleImages/1.png", "1"));
	a.push_back(std::make_pair("SampleImages/2.png", "2"));
	a.push_back(std::make_pair("SampleImages/3.png", "3"));
	a.push_back(std::make_pair("SampleImages/4.png", "4"));
	a.push_back(std::make_pair("SampleImages/5.png", "5"));
	a.push_back(std::make_pair("SampleImages/6.png", "6"));
	a.push_back(std::make_pair("SampleImages/7.png", "7"));
	//a.push_back(std::make_pair("SampleImages/8.png", "8"));
	

	/*auto i = q.RecognizeImage(std::string("SampleImages/sample1.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample2.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample3.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample4.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample5.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample6.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample7.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample8.png"));*/
	for (int i = 0; i < 100; ++i)
	{
		ImageRecogniser q(a);
		std::cout << multiplier << std::endl;
	std::cout << q.RecognizeImage(std::string("SampleImages/1.png"));
	std::cout << q.RecognizeImage(std::string("SampleImages/2.png"));
	std::cout << q.RecognizeImage(std::string("SampleImages/3.png"));
	std::cout << q.RecognizeImage(std::string("SampleImages/4.png"));
	std::cout << q.RecognizeImage(std::string("SampleImages/5.png"));
	std::cout << q.RecognizeImage(std::string("SampleImages/6.png"));
	std::cout << q.RecognizeImage(std::string("SampleImages/7.png"));
	std::cout << q.RecognizeImage(std::string("SampleImages/8.png"));
	std::cout << std::endl;
	multiplier += 0.1;
}
	int qweqweqwewq = 123;
	return 0;
}
