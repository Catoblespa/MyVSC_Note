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
merge 함수는 두 반복자 구간의 요소를 병합한다. 

두 구간은 정렬되어 있어야 하며 합쳐진 결과도 정렬된다. 
inplace_merge는 한 컨테이너의 정렬된 두 연속 구간을 합쳐 원래 구간에 써 넣는다.

		//OutIt merge(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt result [, BinPred F]);			//BinPred : 이항, bool리턴
		//void inplace_merge(BiIt first, BiIt middle, BiIt last [, BinPred F]);

merge는 first1 ~ last1 구간과 first2 ~ last2 구간을 병합하여 result에 작성한다. 
result는 두 구간을 모두 받을 수 있을만한 충분한 공간을 확보하고 있든가 아니면 삽입 반복자여야 한다. 

inplace_merge는 frist ~ middle과 middle ~ last를 병합하여 first ~ last 구간을 다시 작성한다.
둘 다 안정성은 있으므로 동등한 값의 원래 순서가 유지된다.
*/




template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{
	int i;
	vector<int> vi1, vi2, vi3;
	for (i = 1; i < 5; i++) vi1.push_back(i);
	for (i = 3; i < 9; i++) vi2.push_back(i);
	merge(vi1.begin(), vi1.end(), vi2.begin(), vi2.end(), back_inserter(vi3));
	dump("merge", vi3);
	//vi1 과 vi2를 병합하여 vi3에 정렬한다.


	vector<int> vi4;
	for (i = 1; i < 5; i++) vi4.push_back(i);
	for (i = 3; i < 9; i++) vi4.push_back(i);
	inplace_merge(vi4.begin(), vi4.begin() + 4, vi4.end());
	dump("inplace_merge", vi4);

	//1 ~ 4까지의 정수 벡터와 3 ~ 8까지의 정렬된 두 벡터를 병합하여 vi3 빈 벡터에 새로 써 넣었으며 vi4에 연속된 구간을 만들고 두 구간을 병합해 보았다.
		//merge			== > 1 2 3 3 4 4 5 6 7 8
		//inplace_merge == > 1 2 3 3 4 4 5 6 7 8
	//둘 다 원본이 같기 때문에 병합한 결과도 같다.

	return 0;
}
