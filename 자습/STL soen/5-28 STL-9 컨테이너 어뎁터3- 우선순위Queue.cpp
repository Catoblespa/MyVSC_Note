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

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;
/*
컨테이너 어댑터 '우선 순위 큐'

우선 순위 큐는 벡터와 유사하되 값을 빼 낼 때 가장 큰 값을 리턴한다는 점이 다르다. 
필요한 동작은 push, pop, top 세가지밖에 없다. 

템플릿 선언은 다음과 같다.
		//template<class T, class Cont = vector<T>, class BinPred = less<Cont::value_type> >
		//class priority_queue { ... }
T는 우선 순위 큐에 저장될 타입이고 Cont는 기본 컨테이너이되 디폴트는 벡터로 되어 있다.
원할 경우 데크로 변경할 수 있지만 임의 접근이 안되는 리스트는 쓸 수 없다.
 BinPred는 값의 비교에 사용할 비교 함수 객체이되 디폴트는 less로 되어 있으므로 큰 값이 가장 먼저 나온다. 
 
 
 생성자는 다음과 같다.
		//explicit priority_queue(const BinPred& pr = BinPred());											//디폴트 생성자
		//priority_queue(const value_type *first, const value_type *last, const BinPred& pr = BinPred());	//구간 복사 생성자.
비어 있는 채로 생성할 수도 있고 반복자 구간으로 다른 컨테이너에 있는 값을 채울 수도 있다.


*/

int main()
{

	priority_queue<int> q;
	q.push(1);
	q.push(3);
	q.push(2);

	while (!q.empty())
	{
		cout << q.top() << endl;
		q.pop();
	}

	/*
	우선 순위 큐는 큐와 같이 queue 헤더 파일에 정의되어 있으므로 별도의 헤더를 가지지는 않는다.
	1, 3, 2를 넣고 빼냈는데 3, 2, 1이 크기순으로 차례대로 읽혀진다.

	이런 특성을 이용하면 우선 순위가 있는 자료를 다룰 때 아주 편리하다. 
	예를 들어 할일 목록을 관리하는 프로그램에서 할일들의 목록을 무조건 우선 순위 큐에 삽입하고 꺼낼 때는 급한 순서대로 꺼내 처리하도록 할 수 있다.
	*/

	return 0;
}
