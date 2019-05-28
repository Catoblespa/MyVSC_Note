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
컨테이너 어댑터 ' 큐 ' 
큐는 스택에 비해 먼저 들어간 값이 먼저 나오는(FIFO) 자료 구조이다. 
자료를 관리하는 기본적인 기능은 시퀀스의 것을 그대로 재사용할 수 있으며 
FIFO 원리대로 동작하기 위해 꼭 필요한 인터페이스는 다음 4가지 밖에 없다.


push, pop : 앞뒤에서 값을 추가하거나 제거한다.
front, back : 앞뒤의 값을 읽는다.
이 4 개의 주요 함수와 size, empty 그리고 생성자가 큐의 함수 전부이다. 
이 정도 기능만 있으면 큐를 얼마든지 사용할 수 있다. 


스택과 마찬가지로 pop은 값을 제거하기만 하며 리턴하지 않으므로 front, back으로 값을 따로 읽어야 한다. 

큐의 템플릿 선언은 다음과 같다.
		//template<class T, class Cont=deque<T> >
		//class queue { ... }

큐에 저장할 타입과 기본 컨테이너를 템플릿 인수로 지정하는데 디폴트 컨테이너는 데크로 되어 있다. 
원한다면 리스트로 변경할 수도 있지만 벡터는 큐 구현에는 사용할 수 없다. 
왜냐하면 벡터는 앞쪽에서 삽입, 삭제 기능을 제공하지 않으므로 큐 구현에는 적합하지 않기 때문이다. 

간단한 컨테이너지만 그냥 넘어가면 섭섭하므로 예제나 하나 만들어 보자.
*/

int main()
{
	queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	while (!q.empty()) {
		cout << q.front() << endl;
		q.pop();
	}
	return 0;
}
