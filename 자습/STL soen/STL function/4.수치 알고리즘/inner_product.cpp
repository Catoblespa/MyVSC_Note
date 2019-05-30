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
#include <numeric>		//수치 관련 알고리즘 . STL이 아닌 C+라이브러리에 포함되어 있다.
#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;

/*
inner_product
다음 함수는 내적을 계산한다.

T inner_product(InIt1 first1, InIt1 last1, InIt2 first2, T val [, BinOp op1, BinOp op2]);
내적이란 두 구간의 대응되는 요소끼리 곱한 후 전체를 더한 값이다. 
두 개의 반복자 구간과 초기값 val을 지정하며 내적 계산에 사용될 두 개의 이항 함수 객체를 지정할 수 있다. 
디폴트 연산자는 *와 +로 되어 있어 곱의 합을 구하지만 다른 연산을 지정하면 합의 곱을 구하거나 나머지의 합을 구하는 식으로도 연산할 수 있다.

*/

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{
	int inp;
	vector<int> vi1, vi2;
	vi1.push_back(2); 
	vi1.push_back(3); 
	vi1.push_back(4);

	vi2.push_back(5); 
	vi2.push_back(6); 
	vi2.push_back(7);

	inp = inner_product(vi1.begin(), vi1.end(), vi2.begin(), 0);
	printf("내적 = %d\n", inp);
	//결과는 2*5 + 3*6 + 4*7인 56이다. 벡터의 요소 개수가 많아지면 이 값도 굉장히 커질 수 있다.



	/*
	 다음 함수는 두 컨테이너의 반복자 구간을 사전순으로 비교한다.
		//bool lexicographical_compare (InIt1 first1, InIt1 last1, InIt2 first2 [, BinPred F]);
	두 구간의 대응되는 요소를 차례대로 비교하는데 첫 번째 요소가 두 번째 요소보다 작으면 true를 리턴하고 크면 false를 리턴하며 즉시 종료한다. 
	만약 같다면 다음 요소를 똑같은 방식으로 계속 비교하기를 구간끝까지 반복한다. 
	디폴트 비교 함수 객체가 less이므로 첫 번째 구간이 두 번째 구간보다 작아야만 true를 리턴하며 같을 경우는 작지 않으므로 false가 리턴된다. 
	만약 첫 번째 구간이 먼저 끝나고 두 번째 구간은 아직 값이 남았으면 이 경우는 true를 리턴한다.

	*/

	vector<int> vi3, vi4;
	for (int i = 8; i < 16; i++) {
		vi3.push_back(i);
		vi4.push_back(i);
	}

	//vi3[5]=0;
	if (lexicographical_compare(vi3.begin(), vi3.end(), vi4.begin(), vi4.end())) 
		cout << "vi3이 더 작다" << endl;
	else 
		cout << "vi3이 더 작지 않다" << endl;
	//이대로 컴파일하면 두 벡터가 완전히 동일하므로 더 작지 않다가 출력된다. 주석을 풀어 vi3[5]를 0으로 만들면 vi3이 더 작은 것으로 평가될 것이다.


	return 0;
}
