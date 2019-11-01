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
min,max
min, max는 두 값 중 큰 값과 작은 값을 조사한다. 
C 라이브러리에도 동일한 이름의 매크로 함수가 정의되어 있지만 STL의 min, max는 템플릿 버전이라는 점에서 좀 더 우월하다.


	//const T& min(const T& x, const T& y [, BinPred F]);
	//const T& max(const T& x, const T& y [, BinPred F]);

인수로 비교 대상이 되는 두 값을 전달받는데 마지막 인수로 조건자를 지정할 수 있다. 
크다, 작다라는 비교 연산은 지극히 단순한 개념이지만 사용자 정의 타입에서는 이런 간단한 비교조차도 다른 의미를 가질 수 있으므로 조건자가 비교하도록 할 수 있다. 


다음 두 함수는 반복자 구간에서 가장 큰 요소, 가장 작은 요소를 찾아 반복자를 리턴한다.
		//FwdIt min_element(FwdIt first, FwdIt last[, BinPred F]);
		//FwdIt max_element(FwdIt first, FwdIt last[, BinPred F]);
최대, 최소값을 찾기 위해 전체를 정렬한 후 first와 last-1 위치를 읽을 수도 있다. 
그러나 고작 하나의 값을 찾는데 쓰기에 정렬은 너무 비싼 알고리즘이므로 이럴 때는 이 함수들을 쓰는 것이 좋다. 
순차 검색 방법을 사용하므로 반복자 구간은 굳이 정렬되어 있지 않아도 상관없고 임의 접근 반복자일 필요도 없다. 

아주 간단한 함수들이므로 예제만 만들어 보자.

*/
template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{

	int i = 3, j = 5;
	printf("둘 중 작은 값은 %d이고 큰 값은 %d이다.\n", min(i, j), max(i, j));

	int ari[] = { 49,26,19,77,34,52,84,34,92,69 };
	vector<int> vi(&ari[0], &ari[10]);
	printf("벡터에서 가장 작은 값은 %d이고 가장 큰 값은 %d이다.\n",
		*min_element(vi.begin(), vi.end()), *max_element(vi.begin(), vi.end()));
        
	return 0;
}
