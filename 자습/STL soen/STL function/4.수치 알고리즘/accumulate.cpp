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
수치 관련 알고리즘들은 STL에 직접적으로 소속되지 않으며 C++ 라이브러리로 분류된다.
그러나 수치 알고리즘도 STL 컨테이너와 함께 훌륭하게 동작하며 STL이 C++ 표준 라이브러리에 흡수된 이상 이를 굳이 구분할 필요는 없다.
단, 이 함수들은 numeric 헤더 파일에 정의되어 있으므로 수치 관련 함수를 쓸 때는 이 헤더 파일을 꼭 포함하도록 하자. 



누적 합을 구하는 함수는 다음 두 가지이다.
	//T accumulate(InIt first, InIt last, T val [, BinOp op]);
	//OutIt partial_sum (InIt first, InIt last, OutIt result [ ,BinOp op]);
accumulate 함수는 first ~ last 구간에 속한 값들의 총합을 구한다. 
세 번째 인수 val은 누적 총합의 초기값인데 0으로 지정하면 순수한 합을 구할 수 있다. 
partial_sum은 first ~ last까지의 부분합들을 구해 result 반복자 위치에 순서대로 대입한다.

*/


template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{

	int ar1[] = { 49,26,19,77,34,52,84,34,92,69 };
	vector<int> vi1(&ar1[0], &ar1[10]);
	printf("벡터의 총합은 %d이다.\n", accumulate(vi1.begin(), vi1.end(), 0));

	cout << endl;	

	int ar2[] = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> vi2(&ar2[0], &ar2[10]);
	vector<int> vi3;
	partial_sum(vi2.begin(), vi2.end(), back_inserter(vi3));

	dump("vi2의 부분합", vi3);
	printf("vi2 벡터의 총합은 %d이다.\n", accumulate(vi2.begin(), vi2.end(), 0));

	//부분합이란 first에서부터 반복자까지의 합을 더한 값의 벡터인데 
	//1까지 더하면 1, 1과 2를 더하면 3, 1과 2와 3을 더하면 6, 이런 식으로 앞 요소들의 값을 계속 더해 나가면서 중간 중간의 결과값을 벡터로 다시 작성한다.

	//accumulate 함수는 반복자 구간을 순회하면서 이 값들을 계속 더하여 전체 총합을 만들어 낸다.
	//이때 별도의 함수 객체를 지정하면 더하기가 아닌 다른 연산을 할 수도 있다.
	//예를 들어 accumulate(vi1.begin(), vi1.end(), 1, multiplies<int>()) 연산을 하면 모든 요소의 누적곱이 구해진다.
	//이때 초기값은 곱셈의 항등원인 1로 지정해야 할 것이다. 
	// 아무튼 accumulate는 구간의 모든 요소들에 대해 어떤 연산을 적용한 결과를 계산하며 디폴트 연산이 덧셈일 뿐이다.



	/*
		다음 함수는 partial_sum 함수와 유사하게 동작하는데 인접 요소들의 차를 계산해 result 반복자에 차례대로 대입한다.
				OutIt adjacent_difference(InIt first, InIt last, OutIt result [ ,BinOp op]);
	*/

	int ar[] = { 1,2,5,10,15,12,20 };
	vector<int> vi4(&ar[0], &ar[7]);
	vector<int> vi5;

	adjacent_difference(vi4.begin(), vi4.end(), back_inserter(vi5));
	dump("부분차 ", vi5);
	//     1   2   5   10   15   12   20 
	//   1   1   3    5    5   -3   8				부분차
	//첫 번째 요소는 그대로 내려오고 첫 번째 요소와 두 번째 요소의 차가 새 벡터의 두 번째 요소에 기록된다.
	//결과 벡터의 n번째 요소는 원본의 n - 1 요소와 n 요소의 차이라고 할 수 있다.
	//만약 원본 벡터가 월별 판매량이었다면 결과 벡터는 그 달의 판매 증가량이라고 할 수 있다.
	//result 반복자는 컨테이너 내부의 반복자일 수도 있으므로 차를 구해 곧바로 자신에게 다시 대입하는 것도 가능하다.


	return 0;
}
