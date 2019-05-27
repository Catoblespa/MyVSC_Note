#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>		
#include <iterator>		//여러 종류의 반복자의 정의 담음.

using namespace std;

/*
벡터

벡터는 동일 타입의 자료 집합인 시퀀스 컨테이너의 대표이다.
템플릿 기반이므로 임의 타입을 요소로 가질 수 있으며 요소의 개수에 따라 자동으로 메모리를 관리한다.
즉 벡터는 임의 타입의 동적 배열로 정의할 수 있다.
구조가 단순하고 사용법이 쉬우며 몇 가지 경우를 제외하고 대부분의 경우 자료 관리에 탁월한 성능을 보이므로 STL 컨테이너 중 활용 빈도가 가장 높고 실용적이다.

벡터의 내부적인 구성 원리는 C의 정적 배열과 거의 유사하며 특성과 장단점도 배열과 동일하다.
요소들의 크기가 똑같고 인접한 위치에 이웃하여 배치되므로 메모리를 적게 차지하며 임의 위치를 빠른 속도로 액세스할 수 있다.
최상위 레벨의 임의 접근 반복자를 제공하므로 STL의 모든 알고리즘을 사용할 수 있다.

그러나 삽입, 삭제시 요소의 인접 배치 원칙을 지키기 위해 요소를 이동시켜야 하는 번거로움이 있어 삽입, 삭제 속도가 느리다는 것이 단점이다.
삽입, 삭제가 아주 빈번할 때는 벡터보다는 리스트를 사용하는 것이 좋다.

벡터뿐만 아니라 STL의 모든 컨테이너는 클래스 템플릿으로 정의되어 있다. 그래서 템플릿으로 전달되는 임의의 인수 타입들을 저장할 수 있는 것이다. 벡터의 선언문은 다음과 같다.
	//template <class Type, class Allocator = allocator<Type> > class vector
Type은 벡터에 저장되는 요소의 타입이며 벡터는 이 타입의 집합을 관리한다.
이 템플릿안에는 벡터를 관리하는 멤버 변수와 멤버 함수들이 포함되어 있다.
또한 컨테이너에서 사용하는 타입들도 typedef로 정의되어 있는데 이 타입은 STL의 모든 구성 요소들이 사용하는 일종의 약속이다.
모든 컨테이너는 자신이 정의하는 타입을 약속된 이름으로 제공해야 하며 반복자나 알고리즘은 컨테이너를 조작하기 위해 이 타입들을 사용한다.


타입							설명

value_type					컨테이너의 요소 타입이다.

(const_) pointer			요소를 가리키는 포인터 타입이다. 이하 4개의 타입은 상수 버전도 제공된다.

(const_) reference			요소의 레퍼런스 타입이다.

(const_) iterator			요소의 레퍼런스를 가리키는 반복자 타입이다.

(const_) reverse_iterator	역방향 반복자 타입이다.

difference_type				두 반복자의 차를 표현하는 타입이다. 통상 int이다.

size_type					크기를 표현하는 타입이다. 통상 unsigned이다.



		//explicit vector();									//디폴트 생성자
		인수없이 벡터를 생성할 경우 요소를 가지지 않는 빈 벡터가 만들어진다.
		최초 빈 상태로 생성하더라도 메모리가 자동으로 관리되므로 이후 얼마든지 요소를 추가할 수 있다.
		//explicit vector(size_type n, const T& v = T());		//
		생성자는 벡터의 초기 크기를 지정하며 T 타입의 초기값을 지정할 수 있다.
		초기값의 디폴트는 T의 디폴트 생성자가 만든 값으로 지정되어 있는데 통상 0, false, NULL, "" 등이 될 것이다.
		//vector(const vector& x);
		복사 생성자인데 다른 벡터로부터 똑같은 벡터를 만들어 낸다. 내부에서는 아마도 깊은 복사를 할 것이다
		//vector(const_iterator first, const_iterator last);
		네 번째 생성자는 반복자가 지정한 구간의 요소들을 가지는 새로운 벡터를 생성한다.
		이때 반복자는 꼭 벡터의 반복자가 아니더라도 상관없다.
		정적 배열이나 리스트의 반복자를 전달할 수도 있어 다른 컨테이너로부터 벡터를 초기화할 수 있다.


*/



template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";
	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}


int main()
{
	vector<string> v1; dump("v1", v1);
	vector<double> v2(10); dump("v2", v2);
	vector<int> v3(10, 7); dump("v3", v3);
	vector<int> v4(v3); dump("v4", v4);

	int ar[] = { 1,2,3,4,5,6,7,8,9 };

	vector<int> v5(&ar[2], &ar[5]); dump("v5", v5);

	/*
	벡터는 요소 저장을 위한 메모리를 자동으로 관리한다.
	요소가 삽입될 때는 벡터 크기를 신축적으로 늘리고 벡터가 파괴될 때 할당한 메모리도 알아서 정리한다.
	그래서 별도로 벡터 정리 코드를 작성할 필요가 없다.
	벡터의 메모리 관리 기능은 알아서 동작하도록 자동화되어 있지만 가끔은 개발자가 직접 개입하여 크기를 관리해야 할 필요도 있다.

	함수				설명
	size			요소 개수를 조사한다.

	max_size		벡터가 관리할 수 있는 최대 요소 개수를 조사한다.

	capacity		할당된 요소 개수를 구한다. (할당되어 있는 메모리양)

	resize(n)		크기를 변경한다. 새 크기가 더 클 경우 벡터의 원래 내용은 유지하며 새로 할당된 요소는 0으로 초기화된다.

	reserve(n)		최소한의 크기를 지정하며 '메모리'를 미리 할당해 놓는다. 새 크기가 더 클 경우 벡터의 원래 내용은 유지한다. 새로 할당된 요소는 초기화되지 않는다.

	clear(n)		모든 요소를 삭제한다.

	empty			비어 있는지 조사한다.
	*/

	cout << "====== Vector Func ======" << endl;
	vector<int> vi;

	printf("max_size = %d\n", vi.max_size());
	printf("size = %d, capacity = %d\n", vi.size(), vi.capacity());
	vi.push_back(123);
	vi.push_back(456);
	printf("size = %d, capacity = %d\n", vi.size(), vi.capacity());
	vi.resize(10);
	printf("size = %d, capacity = %d\n", vi.size(), vi.capacity());
	vi.reserve(20);
	printf("size = %d, capacity = %d\n", vi.size(), vi.capacity());

	/*
		요소의 집합을 관리하는 컨테이너에서 삽입과 삭제는 가장 기본적인 동작이다.
		각 컨테이너별로 내부적인 구조가 다르기 때문에 삽입, 삭제 방식도 컨테이너별로 다를 수밖에 없다.
		그래서 삽입, 삭제 함수는 일반 알고리즘으로 제공되기보다는 컨테이너의 멤버 함수로 제공된다. 다음 두 함수는 벡터의 제일 끝 부분에서 삽입, 삭제를 수행한다.
				//void push_back(const T & x);				 벡터 끝에 새 요소 x를 추가하고 필요할 경우 메모리 관리, 용량이 부족할 경우 재할당
				//void pop_back();							벡터의 끝 요소를 삭제
				//앞뒤의 요소를 읽을 때는 front, back 멤버 함수를 사용하는데 이 함수는 T형의 레퍼런스를 리턴하므로 양끝의 멤버를 읽거나 쓸 수 있다.

		벡터는 앞쪽에서 요소를 삽입하거나 삭제하는 push_front, pop_front 함수는 제공하지 않는다.
		벡터의 끝 부분에 추가하는 것은 빠르지만 중간이나 처음에 삽입, 삭제하는 것은 요소의 인접성을 유지하기 위해 뒤쪽 요소를 이동시켜야 하므로 무척 느리다.
		만약 꼭 벡터의 중간에 요소를 삽입하고 싶다면 insert 함수를 사용한다.
		벡터에 대해 push_front(V)를 하려면 insert(begin(),V)을 대신 호출하면 된다.

				//iterator insert(iterator it, const T& x = T());
				//void insert(iterator it, size_type n, const T& x);
				//void insert(iterator it, const_iterator first, const_iterator last);
		세 가지 원형이 제공되는데 세 버전 모두 첫 번째 인수는 삽입 위치를 나타내는 벡터 내의 반복자이다.
		나머지 인수로 삽입 대상을 지정하는데 요소 하나, 같은 값 여러 개, 다른 반복자 구간을 삽입할 수 있다.

		요소를 삭제할 때는 erase 함수를 사용한다.
				//iterator erase(iterator it);
				//iterator erase(iterator first, iterator last);
		반복자가 지정하는 요소 하나 또는 반복자 구간을 삭제할 수 있다.
		insert와 erase는 요소를 관리하는 기본 동작이므로 대부분의 컨테이너에 동일한 이름과 형식으로 존재한다.

	*/
	cout << "====vector insert func====" << endl;
	const char* str = "0123456789";

	vector<char> vc(&str[0], &str[10]); dump("생성 직후 ", vc);
	vc.push_back('A'); dump("A 추가", vc);
	vc.insert(vc.begin() + 3, 'B'); dump("B 삽입", vc);
	vc.pop_back(); dump("끝 요소 삭제", vc);
	vc.erase(vc.begin() + 5, vc.begin() + 8); dump("5~8 삭제", vc);


	/*
	한꺼번에 삽입, 삭제하기
	*/
	cout << "====한꺼번에 삽입, 삭제하기====" << endl;
	vector<char> vc1;

	for (int i = 0; i < 10; i++) {		//매번 메모리 재할당, 삽입
		vc1.insert(vc1.begin(), 'Z');
	}
	dump("개별 추가", vc1);


	vector<char>vc2;
	vc2.insert(vc2.begin(), 10, 'Z');	//한번에 메모리 할당후, 삽입./
	dump("한꺼번에 추가", vc2);


	/*
	다른 컨테이너와 요소 교환하기
	*/
	cout << "====다른 컨테이너와 요소 교환하기====" << endl;
	list<int> li;
	for (int i = 0; i < 100; i++) {
		li.push_back(i);
	}

	vector<int> vi2;
	vi2.insert(vi2.begin(), find(li.begin(), li.end(), 8), find(li.begin(), li.end(), 25));
	dump("추가 후", vi2);

	/*
	반복자 무효화 현상

	반복자는 컨테이너 내의 요소 위치를 가리키는 일종의 포인터인데 특정 요소를 가리키도록 한 번 설정하면 계속 같은 요소를 가리킨다.
	그러나 컨테이너에 삽입, 삭제가 일어나면 메모리 재할당 및 이동이 발생하므로 이때는 조사해 놓은 반복자가 무효화될 수 있다.
	즉, 반복자가 더 이상 정확한 요소를 가리키지 못하는 것이다.

	먼저 삽입의 경우를 보자. 중간에 한 요소가 삽입되면 뒤쪽의 요소들은 삽입된 개수만큼 이동하므로 뒤쪽 요소를 가리키던 반복자들은 모두 무효화된다.
	insert 함수가 요소는 이동시키지만 이 컨테이너의 다른 요소를 가리키는 반복자까지 같이 이동시킬 수는 없기 때문이다.

	삽입된 위치의 앞쪽은 무효화될 수도 있고 그렇지 않을 수도 있는데 재할당에 의해 메모리 번지가 바뀌면 무효화될 것이고 그렇지 않다면 영향을 받지 않을 것이다.
	삽입에 의해 재할당이 자주 발생하지는 않지만 모든 경우에 유효성이 보장된다고 할 수는 없으므로 삽입하면 전 반복자가 무효화된다고 보는 것이 옳다.
	삭제시는 삭제 구간의 뒤쪽은 무효화되지만 앞쪽은 영향을 받지 않는다.
	삭제는 삽입과는 달리 메모리 재할당이 절대로 일어나지 않으므로 앞쪽 요소는 원래 자리를 항상 그대로 유지하기 때문이다.
	*/
	cout << "====반복자 무효화 현상====" << endl;
	vector<int> vi3;
	for (int i = 0; i < 80; i++) {
		vi3.push_back(i);
	}

	vector<int>::iterator iter;
	iter = find(vi3.begin(), vi3.end(), 55);
	cout << "erase 전 " << *iter << endl;
	vi3.erase(iter - 1);						// iter +1일 경우 iter반복자가 삭제 대상 앞에 있으므로, 무효화가 되지 않음.
	cout << "erase 후 " << *iter << endl;		// 에러! vector의 앞부분이 삭제되어, 그 이후에 있는 반복자 들이 무효화됨.





	return 0;
}
