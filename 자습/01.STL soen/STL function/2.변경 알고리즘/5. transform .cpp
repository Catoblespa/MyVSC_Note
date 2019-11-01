#include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.
#include <deque>		//STL deque 정의 헤더
#include <set>			//STL 연관컨테이너 set
#include <map>			//STL 연관컨테이너 map
#include <stack>		//STL 컨테이너 어댑터 stack
#include <queue>		////STL 컨테이너 어댑터 queue
#include <array>

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;


/*
sform
sform 함수는 반복자 구간에 대해 함수 객체를 적용한 후 그 결과를 다른 구간에 복사한다. 
단항 함수를 취하는 버전과 이항 함수를 취하는 버전 두 가지가 있다.


OutIt sform(InIt first, InIt last, OutIt result, UniOp op);
OutIt sform(InIt1 first1, InIt1 last1, InIt2 first2, OutIt result, BinOp op);
*/

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{
	//int multi2(int a)
	//{
	//	return a * 2;
	//}
	//int add(int a, int b)
	//{
	//	return a + b;
	//}


	vector<int> src(5), dest(5), sum;
	int i;

	for (i = 0; i < 5; i++) src[i] = i;

	transform(src.begin(), src.end(), dest.begin(), [](int a) -> int  
		{
		return a * 2;
		});
	dump("src", src);
	dump("dest", dest);
	//src 벡터에 0 ~ 4까지의 정수를 저장한 상태에서 전체 구간에 대해 단항 multi2 함수 객체를 적용했다.
	// multi2 함수 객체는 0, 1, 2 각각을 받아 0, 2, 4를 만들어 리턴하며 transform은 그 결과를 dest의 반복자에 대입한다.
	//dest에는 src의 2배되는 값들이 저장될 것이다.

	transform(src.begin(), src.end(), dest.begin(), back_inserter(sum), [](int a, int b) -> int
		{
			return a + b;
		});
	dump("sum", sum);
	//다음으로 이항 객체를 취하는 transform 함수를 호출하여 src와 dest의 대응되는 요소를 add 함수 객체로 넘겼다.
	//이 함수는 인수로 전달받은 두 값을 더하여 리턴하며 그 결과는 sum 벡터에 삽입된다. 
	//삽입 반복자를 사용했으므로 add가 리턴한 값이 sum 벡터에 삽입될 것이다.

	return 0;
}
