#include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <map>			//STL Map
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.

using namespace std;

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}
/*
리스트(list) 컨테이너는 이중 연결 리스트를 템플릿으로 추상화한 버전이다. 
동일한 자료의 집합을 관리한다는 용도면에서는 벡터와 같고 실제로 서로 대체도 가능하다. 용도가 같기 때문에 인터페이스도 거의 유사하다.

생성자는 완전히 똑같고 삽입, 삭제 등 주요 멤버 함수의 원형도 벡터와 일치하며 대입, 비교 등의 연산자도 동일하게 제공된다.

제공하는 내부 타입도 value_type, iterator, reference 등 이름이 동일하다. 
물론 두 컨테이너의 내부 구조가 판이하게 다르므로 이 타입들의 실제 구현은 상당히 다르다.

벡터의 반복자는 요소를 직접 가리키는 포인터로 되어 있을 것이고 리스트의 반복자는 링크를 가리키는 포인터로 구현되어 있을 것이다. 
내부 구현이 다르더라도 인터페이스가 동일하므로 사용하는 방법은 동일하다.



벡터와 리스트 컨테이너의 주요 차이점

① 가장 큰 차이점은 반복자의 레벨인데 벡터는 요소들이 인접해 있으므로 임의 접근이 가능하지만 리스트는 노드들이 흩어져 있으므로 양방향으로만 이동할 수 있을 뿐이다.
  반복자가 +n 연산을 지원하지 않으므로 순서값으로 요소를 액세스하는 [ ] 연산자를 지원하지 않으며	at 함수도 당연히 지원되지 않는다.
  임의 위치를 상수 시간에 액세스할 수 없으며 반드시 순회를 해야만 원하는 요소를 찾을 수 있다.
  임의 접근 반복자를 요구하는 sort나 binary_search 알고리즘은 리스트에는 사용할 수 없다.


② 각 요소들이 노드로 할당되어 링크에 의해 논리적으로 연결되어 있으므로 링크만 조작해서 삽입, 삭제를 수행할 수 있다.
  요소들이 인접하지 않아도 상관없어 삽입, 삭제시에 메모리 이동을 할 필요가 없으며 그래서 위치에 상관없이 상수 시간내에 삽입, 삭제를 할 수 있다.
  제일 앞에 요소를 삽입, 삭제하는 push_front, pop_front 멤버 함수도 제공된다.
  에 비해 벡터는 중간에서 삽입, 삭제할 때 요소들을 밀고 당겨야 하므로 속도가 다소 느리다.
  속도 희생없이 언제든지 크기를 늘리거나 줄일 수 있으므로 처음부터 미리 크기를 결정할 필요가 없으며 capacity, reserve도 불필요하다.

③ 링크 구조로 인해 메모리 소모량은 벡터보다 훨씬 더 많다. 요소를 저장하는 노드는 무조건 동적 할당해야 하며 요소간의 순서를 기억하기 위한 링크도 별도의 메모리를 소모한다.
  게다가 삽입, 삭제시마다 노드를 할당, 해제하는 과정을 계속 반복하므로 메모리 단편화도 심해 시스템의 메모리 관리 능력에도 좋지 않은 영향을 미친다.

④ 삽입, 삭제에 의해 요소들의 물리적인 위치가 바뀌지 않으므로 반복자가 무효화되지 않는다. 반복자가 무효화되는 유일한 경우는 반복자가 가리키는 대상을 삭제했을 때 뿐

이 둘의 차이점을 요약하자면 벡터는 읽기에 강하고 리스트는 쓰기에 강한 컨테이너라고 정리할 수 있다. 
읽기 속도가 중요하면 벡터를 선택하는 것이 좋고 삽입, 삭제가 아주 빈번하다면 리스트가 더 나은 선택이다.

이제 리스트의 생성자부터 연구해 보자. 리스트의 생성자는 모두 4개 제공되는데 벡터의 생성자와 원형이 동일하다. 
똑같은 목적에 사용하는 컨테이너이므로 생성하는 방법부터 같을 수밖에 없다

		//explicit list();												//디폴트 생성자
		//explicit list(size_type n, const T& v = T());					// v값 n개를 가지는 생성자, 
		//list(const list& x);											//복사 생성자
		//list(const_iterator first, const_iterator last);				//구간 복사 생성자



*/

struct ifListdelete {
	bool operator()(char a)
	{
		if (a == 'l')
			return 1;
		else 
			return 0;
	}
};

int main()
{

	cout << "=====list push=====" << endl;
	list<int> li;

	list<int>::iterator it;

	li.push_back(8);		//맨뒤에 8 삽입
	li.push_back(9);
	li.push_front(2);		//맨 앞에 2 삽입
	li.push_front(1);

	for (it = li.begin(); it != li.end(); it++) 
	{
		printf("%d\n", *it);
	}
	/*
	삽입, 삭제 함수도 벡터와 동일하다. 멤버 함수의 이름뿐만 아니라 원형까지 동일하며 사용 방법도 물론 똑같다.

		//iterator insert(iterator it, const T& x = T());
		//void insert(iterator it, size_type n, const T& x);
		//void insert(iterator it, const_iterator first, const_iterator last);
		//iterator erase(iterator it);
		//iterator erase(iterator first, iterator last);

	다만 처리 속도는 벡터보다 훨씬 빠른데 위치와 요소 개수에 상관없이 상수 시간내에 삽입, 삭제된다. 속도가 빠르다는 것 외에도 반복자가 무효화되지 않는 장점도 있다
	 삽입, 삭제되는 노드와 앞 뒤 노드의 링크만 바뀌므로 나머지 노드들은 위치에 전혀 변화가 없다.

	*/

	cout << "=====list 삽입삭제=====" << endl;
	const char* str = "abcdefghij";
	list<char> lc(&str[0], &str[10]);
	list<char>::iterator it_;



	dump("최초", lc);
	it_ = lc.begin(); it_++; it_++; it_++; it_++; it_++;
	lc.insert(it_, 'Z');
	dump("Z 삽입", lc);

	it_ = lc.end(); it_--; it_--; it_--;

	lc.erase(it_);

	dump("h삭제", lc);

	//, 어떤 위치의 값을 삭제하나 항상 일정한 시간내에서 완료할 수 있다. 특정값을 가지는 요소를 모두 삭제하고 싶을 때는 다음 멤버 함수를 사용한다.
			//void remove(const Type & val);
			//void remove_if(UniPred F)
	//move는 삭제할 값을 바로 지정하고 remove_if는 조건자에 맞는 요소만 삭제한다. 
	//값을 검색한 후 삭제하므로 find와 erase를 순서대로 수행한다고 생각하면 된다.


	const char* str2 = "double linked list class";
	list<char> li2(&str2[0], &str2[strlen(str2)]);

	dump("최초", li2);
	li2.remove('l');						//문자들 중 l만 모조리 삭제된다.
	//li2.remove_if(ifListdelete());		//함수 객체를 사용하여 사용자 정의의 삭제알고리즘.
	dump("l삭제", li2);


	/*
	링크의 재배치

	리스트의 노드를 연결하는 링크는 포인터이므로 조작할 수 있는 여지가 아주 많다. 
	다른 컨테이너에서는 요소를 직접 이동해야 하는 작업도 리스트는 링크만 재배치하여 아주 간단하게 빠른 속도로 수행할 수 있다. 
	리스트에는 링크 재배치의 장점을 살릴 수 있는 여러 가지 멤버 함수들이 준비되어 있다.

			//void swap(list& Right);
			//void reverse( );
			//void merge(list& Right);

	이 함수들은 모두 전역 알고리즘 함수로도 제공된다. 
	리스트가 똑같은 이름의 멤버 함수를 제공하는 이유는 링크 재배치의 장점을 활용하면 일반적인 알고리즘보다 훨씬 더 빠르게 동작하기 때문이다.

	예를 들어 리스트끼리 교환하는 swap 함수는 실제로 요소를 교환할 필요없이 리스트끼리 head, tail 정보만 바꾸면 간단하게 구현할 수 있다.
	어차피 노드들은 메모리의 아무 곳에나 흩어져 있고 링크에 의해서만 연결되므로 시작점과 끝점의 링크만 수정하면 소속도 쉽게 바뀐다.


	링크를 조작하는 가장 멋지고도 실용적인 함수는 splice이다. 
	splice는 새끼줄같은 것을 꼬아서 서로 잇는다는 의미인데 뜻 그대로 두 개의 리스트를 서로 잇거나 한쪽 요소들을 뽑아서 다른쪽으로 이동시킨다. 
	다음 세 개의 원형이 정의되어 있다.

			//void splice(iterator it, list& x);								// it 위치에 x리스트의 모든 요소들을 이동시킨다.
																					//복사가 아닌 이동이므로 x에 있던 요소들은 모두 제거된다.(it과 x는 서로 다른 list여야함)
			//void splice(iterator it, list& x, iterator first);				//x의 first위치에 있는 요소 하나만 it위치로 이동시킨다. 
																					
			//void splice(iterator it, list& x, iterator first, iterator last);	//하나의 요소가 아니라 반복자 구간을 지정하여 일정 범위의 요소를 한꺼번에 이동시킨다는 점이 다르다.

	
	*/
	cout << "=====splice=====" << endl;

	const char* alpha = "abcdefghij";
	const char* num = "12345";
	list<char> la(&alpha[0], &alpha[10]);
	list<char> ln(&num[0], &num[5]);
	list<char>::iterator ita, it1, it2;

	dump("알파벳", la); dump("숫자", ln);

	ita = la.begin(); ita++; ita++;
	it1 = ln.begin(); it1++; it1++;
	it2 = ln.end(); it2--;

	// 전체 이동
	//la.splice(ita,ln);							//ita위치에 ln 전체를 이동시킨다.
		
	// 앞쪽 2번째만 이동
	//la.splice(ita,ln,it1);						// ln의 it1에 위치한 요소를 ita로 이동시킨다.

	// 구간 이동
	la.splice(ita, ln, ln.begin(), ln.end());		//ita위치에 in의 begin부터 end까지 요소를 '이동'시킨다. in은 비어있는 list가 된다.

	dump("알파벳", la); dump("숫자", ln);

	return 0;
}
