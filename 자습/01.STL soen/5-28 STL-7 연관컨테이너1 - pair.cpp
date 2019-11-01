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
연관 컨테이너(Associative Container)는 키와 값처럼 관련이 있는 데이터를 하나의 쌍으로 저장하는 컨테이너이다.

맵은 키와 값의 쌍을 저장하며 셋은 키만 저장하고 값은 저장하지 않는다.
데이터를 저장할 때 아무 곳에나 저장하지 않고 검색을 고려하여 최대한 빠른 속도로 키를 찾을 수 있는 위치에 저장하므로 검색 속도가 굉장히 빠르다.
연관 컨테이너를 구현하는 방법에는 균형 잡힌 이진 트리를 사용하여 정렬된 상태로 저장하는 방법이 있고 해쉬 테이블에 저장하는 방법이 있다.

해쉬는 해쉬 함수에 의해 한 번에 자료를 찾을 수 있으므로 검색 속도가 거의 순식간이라는 장점이 있지만 
성능을 높이기 위해서는 해쉬 테이블이 충분히 커야 하므로 메모리 낭비가 조금 심한 편이다.
또한 검색이 빠르기는 하지만 데이터의 분포 정도에 따라 검색 속도가 운에 좌우되는 경향이 있어 최악의 상황에는 속도가 떨어질 수도 있다.

이에 비해 이진 트리를 사용하는 방법은 메모리의 낭비가 심하지 않고 데이터의 종류에 상관없이 항상 일정한 성능을 보장하므로 훨씬 더 안정적이다.
표준 STL은 이진 트리에 정렬하는 방식으로 구현된 연관 컨테이너만 제공한다. 
해쉬 연관 컨테이너는 비록 표준은 아니지만 확장 라이브러리의 형태로 제공되는 것들이 많아 원한다면 언제든지 구해서 사용할 수 있다.

정렬된 연관 컨테이너는 이진 트리에 데이터를 정렬하여 저장하고 검색할 때는 이진 트리 검색을 사용한다.
 시퀀스는 지정한 자리에 삽입되며 삽입시의 순서가 그대로 유지되는데 비해 연관 컨테이너는 삽입 위치를 지정할 수 없으며 
 컨테이너의 내부적인 관리 규칙에 따라 자동으로 삽입 위치가 결정된다.

 그래서 삽입 속도는 시퀀스보다 느리지만 검색 속도는 월등히 빠르다.


 연관 컨테이너는 저장 대상과 키의 중복 여부에 따라 4가지가 있다. 
	-셋은 키만 저장하는 컨테이너이며 맵은 키와 값을 쌍으로 같이 저장한다. 
	-셋과 맵은 키의 중복을 허용하지 않는데 
	-멀티셋, 멀티맵은 같은 키가 두 번 이상 삽입될 수 있다.


저장 대상		키			키 + 값

중복 불허		셋			맵

중복 허용		멀티셋		멀티맵



//연관 컨테이너의 반복자는 모두 양방향 반복자이이다. 
자료들이 항상 정렬된 상태를 유지하므로 다시 정렬할 필요가 없으며 검색이 워낙 빠르기 때문에 이분 검색을 할 필요도 없다






연관 컨테이너를 연구해 보기 전에 연관 컨테이너들이 키와 값의 쌍을 표현하기 위해 사용하는 pair 구조체에 대해 알아보자. 
셋과 맵 컨테이너는 둘 이상의 값을 묶어서 관리하거나 리턴할 일이 많기 때문에 pair 구조체를 종종 사용한다.
일종의 유틸리티 클래스인데 선언문도 아주 간단하다.

		//template<class T1, class T2>
		//struct pair 
		//{
		//	 typedef T1 first_type;
		//	 typedef T2 second_type;
		//	 T1 first;
		//	 T2 second;
		//	 pair() : first(T1()), second(T2()) {}
		//	 pair(const T1& v1, const T2& v2) : first(v1), second(v2) {}
		//};
두 개씩 짝을 이룬 데이터를 다룬다거나 한꺼번에 두 개의 값을 리턴하고 싶을 때 이 구조체를 사용한다. 
알다시피 함수는 한 번에 하나의 값만 리턴할 수 있으며 굳이 두 개의 값을 리턴하고 싶다면 참조 호출을 쓸 수 있지만 번거롭다.

두 값의 쌍을 포함하는 구조체를 정의하면 이 구조체를 리턴함으로써 포함된 값 두 개를 리턴하는 것과 같다. 
구조체는 값으로 복사, 대입되므로 함수의 리턴 타입으로 사용할 수 있다

다음 예제의 GetPair 함수가 이 구조체를 리턴한다.
*/
//pair 구조체를 사용하려면 utility 헤더 파일을 포함해야 하는데 STL의 다른 헤더 파일을 인클루드하면 utility 헤더 파일도 자동으로 인클루드된다.
typedef pair<string, double> sdpair;


sdpair GetPair()
{
	sdpair temp;
	temp.first = "문자열";
	temp.second = 1.234;
	return temp;
	// return make_pair("문자열",1.234);

}
int main()
{

	sdpair SD;
	SD = GetPair();
	cout << SD.first << "," << SD.second << endl;

	return 0;
}
