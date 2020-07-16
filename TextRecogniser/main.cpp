#include "include/ImageRecogniser.h"

int main()
{
	std::list<std::pair<std::string, std::string>> a;
	a.push_back(std::make_pair("SampleImages/1.png", "1"));
	a.push_back(std::make_pair("SampleImages/2.png", "2"));
	//a.push_back(std::make_pair("SampleImages/3.png", "3"));
	a.push_back(std::make_pair("SampleImages/4.png", "4"));
	a.push_back(std::make_pair("SampleImages/5.png", "5"));
	a.push_back(std::make_pair("SampleImages/6.png", "6"));
	a.push_back(std::make_pair("SampleImages/7.png", "7"));
	//a.push_back(std::make_pair("SampleImages/8.png", "8"));
	ImageRecogniser q(a);

	/*auto i = q.RecognizeImage(std::string("SampleImages/sample1.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample2.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample3.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample4.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample5.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample6.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample7.png"));
		 i = q.RecognizeImage(std::string("SampleImages/sample8.png"));*/

	auto i = q.RecognizeImage(std::string("SampleImages/1.png"));
		 i = q.RecognizeImage(std::string("SampleImages/2.png"));
		 i = q.RecognizeImage(std::string("SampleImages/3.png"));
		 i = q.RecognizeImage(std::string("SampleImages/4.png"));
		 i = q.RecognizeImage(std::string("SampleImages/5.png"));
		 i = q.RecognizeImage(std::string("SampleImages/6.png"));
		 i = q.RecognizeImage(std::string("SampleImages/7.png"));
		 i = q.RecognizeImage(std::string("SampleImages/8.png")); 
	int qweqweqwewq = 123;
	return 0;
}
