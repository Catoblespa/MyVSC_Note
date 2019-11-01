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
다음 함수들은 반복자 구간에서 다른 구간 전체가 발견되는 지점을 검색한다. 
문자열에서 부분 문자열의 최초 위치를 검색하는 strstr 함수와 유사한 동작을 하되 임의 타입에 대해 부분 검색이 가능하다는 점에서 훨씬 더 일반적이다.


FwdIt1 search(FwdIt1 first1, FwdIt1 last1, FwdIt2 first2, FwdIt2 last2 [, BinPred F]);
FwdIt1 find_end(FwdIt1 first1, FwdIt1 last1, FwdIt2 first2, FwdIt2 last2 [,BinPred F]);
FwdIt1 search_n (FwdIt1 first1, FwdIt1 last1, Size count, const Type& val[, BinPred F]);

first1~last1 전체 구간에서 first2~last2 구간과 일치하는 패턴을 찾아 그 반복자를 리턴한다.

 search는 전체 구간의 앞쪽에서부터 검색을 하고 find_end는 전체 구간의 뒤쪽에서부터 검색을 한다.
 두 함수가 검색 시작 방향만 틀릴 뿐이다.
 전체 구간을 끝까지 검색했는데 부분 구간이 발견되지 않으면 last1이 리턴된다.

search_n은 반복자 구간에서 val 값이 count번 연속으로 나타나는 지점을 찾는다.


*/
int main()
{
	int ar1[] = { 3,1,4,1,5,9,2,6,5,3,5,8,9,9,9,3,2,3,1,5,9,2,6,4,3 };
	int ar2[] = { 1,5,9 };

	vector<int> vi1(&ar1[0], &ar1[25]);
	vector<int> vi2(&ar2[0], &ar2[3]);
	int* p;

	auto it = vi1.begin();


	it = search(vi1.begin(), vi1.end(), vi2.begin(), vi2.end());

	if (it != vi1.end()) {
		//printf("%d번째에서 구간이 발견되었습니다.\n", it - vi1.size);

		cout << it - vi1.begin() << "번째에서 구간이 발견되었습니다." << endl;
	}



	it = find_end(vi1.begin(), vi1.end(), vi2.begin(), vi2.end());

	if (it != vi1.end()) {
		//printf("%d번째에서 구간이 발견되었습니다.\n", it - vi1.size);

		cout << it -vi1.begin() << "번째에서 구간이 발견되었습니다." << endl;
	}



	it = search_n(vi1.begin(), vi1.end(), 3, 9);

	if (it != vi1.end()) {
		//printf("%d번째에서 3연속의 9를 발견했습니다.\n", it-vi1.size);

		cout << it - vi1.begin() << "번째에서 구간이 발견되었습니다." << endl;
	}

//	auto a = (it - vi1.begin());   => it이 현재 가르키고 있는 vi1에서의 위치값 (몇번째 요소를 가르키고 있는지?!)

	return 0;
}
