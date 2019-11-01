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
binary_search

binary_search는 정렬된 구간에서 이분 검색으로 값의 존재 여부를 조사한다. 
이분 검색은 값의 대소를 기준으로 구간을 절반씩 나누어 값을 검색하므로 반복자 구간은 반드시 정렬되어 있어야 한다. 
정렬된 자료를 검색하므로 검색 속도는 굉장히 빠르다. 
만약 정렬되어 있지 않다면 결과는 예측할 수 없다.

bool binary_search(FwdIt first, FwdIt last, const T& val [, BinPred F]);
이 함수는 단지 원하는 값이 구간내에 있는지 조사만 할 뿐이지 어디쯤에 있는지는 조사하지 않는다.
값이 존재하면 true를 리턴하고 그렇지 않으면 false를 리턴한다.
이 함수가 값의 위치를 조사하지 못하는 이유는 중복된 값이 있을 경우 정확하게 원하는 값인지 아닌지를 확신할 수 없기 때문이다.
값의 위치를 검색하려면 다음 함수들을 사용해야 한다. 셋, 맵에 있는 검색 멤버 함수와 개념적으로 동일하게 동작한다.


FwdIt lower_bound(FwdIt first, FwdIt last, const T& val [,BinPred F]);
FwdIt upper_bound(FwdIt first, FwdIt last, const T& val [,BinPred F]);
pair< FwdIt, FwdIt > equal_range(FwdIt first, FwdIt last, const T& val [,BinPred F]);

lower_bound는 값이 있는 첫 번째 위치를 리턴하며 만약 없다면 이 값이 삽입될 수 있는 위치를 조사한다. 
upper_bound는 반대로 마지막 위치의 다음 위치를 리턴하는데 이는 검색값보다 큰 최초의 값 위치이다. 
equal_range는 두 함수의 결과를 pair로 묶어서 리턴한다.

*/


template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{
	int ari[] = { 49,26,19,77,34,52,84,34,92,69 };
	vector<int> vi(&ari[0], &ari[10]);
	vector<int>::iterator it;

	dump("원본", vi);
	sort(vi.begin(), vi.end());

	it = lower_bound(vi.begin(), vi.end(), 50);

	if (*it == 50) {
		cout << "찾는 값이 존재합니다." << endl;
	}
	else {					//찾고 있던 50이 없으면 50을 삽입하라.
		vi.insert(it, 50);
		dump("삽입 후", vi);
	}

	//정수 벡터를 정렬한 다음에 lower_bound로 50을 검색해 보았다. 
	//이 값이 이미 있다면 위치가 검색될 것이고 없다면 50이 들어갈 수 있는 위치인 52의 위치가 검색된다. 
	//이 경우 upper_bound로 검색해도 결과는 동일하다.


	/*
	
	만약 중북되어 있는 값 34를 검색한다면 어떤 함수로 검색하는가에 따라 결과가 달라진다.

				lower_bound가 찾는위치
						  ㅣ
					19 26 34 34 49 50 52 69 77 84 92
							    ㅣ
					  upper_bound가 찾는 위치
	*/
	cout << endl;
	cout << "정렬후 equal_range가 반환한 pair의 위치 찾기	" << endl;
	auto pair = equal_range(vi.begin(), vi.end(), 34);
	cout << "pair.first Pos:" << pair.first - vi.begin()   << endl;
	cout << "pair.second Pos:" << pair.second - vi.begin() << endl;


	return 0;
}
