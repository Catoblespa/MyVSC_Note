#include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <map>			//STL Map
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.
#include <deque>		//STL deque 정의 헤더


using namespace std;

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

/*
데크(Deque)는 양쪽 끝이 있는 큐이며 양 끝에서 자료를 삽입, 삭제할 수 있다. 
컴파일러에 따라 데크의 구현 방식이 다르겠지만 주로 메모리 블록을 할당하여 연결해 놓고 양쪽 끝으로 추가 할당해 나가는 방식으로 구현된다.

벡터와 비슷한 특성을 가지는데 양쪽에 끝이 있으므로 앞쪽에서도 삽입, 삭제가 빠르다.
 그러나 이는 기능상의 차이는 아니며 속도상의 차이일 뿐인데 벡터도 insert를 사용하면 좀 느리기는 하지만 앞쪽에서 삽입, 삭제가 가능하다.

 앞쪽에서도 자료의 첨삭이 가능하므로 벡터에 비해push_front, pop_font 함수가 추가로 제공된다. 
 대신 성능 향상을 위해 미리 메모리를 추가 확보해 놓을 필요가 없으므로 reserve 함수가 불필요하며 확보해 놓은 용량을 조사하는 capacity 함수도 필요가 없다.

 그리고 내부 구조가 다름으로 인해 삽입, 삭제시의 반복자 무효화 규칙도 차이가 난다.

 앞쪽에서의 삽입, 삭제가 벡터보다 훨씬 빠르다는 이점이 있는 대신 나머지 연산들은 벡터보다 일반적으로 느리다.
 조작 위치에 따라 약간의 속도차만 있을 뿐이므로 백터와 데크는 기능적으로 완전히 대체 가능하다.

 앞 절에서 벡터로 만든 예제들은 거의 대부분 별다른 수정없이 데크로 바꿀 수 있는데 소스의 vector만 deque로 바꾸면 된다. 
 주로 뒤쪽에 추가만 한다면 벡터가 탁월한 선택이며 양쪽에서 추가, 삭제가 발생하면 데크가 더 적합하다.

 벡터와 마찬가지로 임의 접근 반복자를 지원하여 STL의 모든 알고리즘과도 같이 사용할 수 있으며 [ ] 연산자로 임의 위치를 액세스하는 것도 가능하다. 
 제공하는 함수들의 목록과 사용 방법도 벡터와 거의 동일하다. 
 생성자는 완전히 같으며 연산자와 insert, delete 등의 함수들도 동일하다. 
 
 간단한 예제로 데크를 테스트해 보자.


*/

int main()
{

	deque<int> dq;
	dq.push_back(8);
	dq.push_back(9);
	dq.push_front(2);
	dq.push_front(1);

	for (unsigned i = 0; i < dq.size(); i++) { cout << dq[i]; }


	return 0;
}
