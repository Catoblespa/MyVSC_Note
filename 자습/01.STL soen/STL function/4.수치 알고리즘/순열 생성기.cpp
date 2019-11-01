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
순열 생성기
순열이란 요소들을 순서대로 배치하는 방법이다. 
다음 두 함수는 반복자 구간에 있는 요소의 현재값에 대한 다음, 이전 순열을 계산한다. 
이때 다음, 이전 순열이라는 것은 값의 대소 관계를 기준으로 하며 별도의 함수 객체로 이 관계를 지정할 수 있다.

			//bool next_permutation(BiIt first, BiIt last [, BinPred F]);
			//bool prev_permutation(BiIt first, BiIt last [, BinPred F]);

두 함수 모두 이전, 이후 순열의 존재 유무를 리턴하는데 더 이상의 순열이 없으면 false를 리턴한다.



*/


template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

int main()
{
	int i;
	vector<int> vi;
	vi.push_back(1); 
	vi.push_back(2);
	vi.push_back(3);

	dump("원본", vi);

	for (i = 0; i < 6; i++) {						//최대 생성 가능한 순열의 갯수 이상의 반복을 하면, 중복이 발생한다.
		next_permutation(vi.begin(), vi.end());
		dump("다음", vi);
	}


	/*
	벡터에 1, 2, 3 세 개의 정수를 넣어 두고 이 세 값으로 만들 수 있는 순열을 모두 조사해 출력해 보았다. 모두 여섯 개의 순열이 만들어진다.

	원본        ==> 1 2 3
	다음        ==> 1 3 2
	다음        ==> 2 1 3
	다음        ==> 2 3 1
	다음        ==> 3 1 2
	다음        ==> 3 2 1

	벡터의 요소 개수가 많으면 순열의 개수도 기하 급수적으로 늘어날 것이다.
	
	
	*/
	return 0;
}
