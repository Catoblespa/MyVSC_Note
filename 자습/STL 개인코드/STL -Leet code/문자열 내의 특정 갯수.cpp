#include <iostream>
#include <time.h>
#include <string>\
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	\
#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;


bool solution(string s)
{
	transform(s.begin(), s.end(), s.begin(), tolower);
	cout << s << endl;
	bool answer = true;
	int pCount = 0;
	int yCount = 0;

	
	for_each(s.begin(), s.end(), [&pCount, &yCount](char ch) {

		if (ch == 'p')
			pCount++;

		if (ch == 'y')
			yCount++;
		});

	if (pCount == yCount)
		answer = true;
	else
		answer = false;


	return answer;
}
int main()
{

	cout << solution("pPoooyy") << endl;
	return 0;
}