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
#include <set>


using namespace std;

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}
/*
두 종류의 연관 컨테이너 중 상대적으로 간단한 셋부터 알아보자. 셋(Set)은 영어 단어 뜻 그대로 집합을 의미하는데 동일한 타입의 데이터를 모아 놓은 것이다.
저장하는 데이터 자체가 키로 사용되며 값은 저장되지 않는다. 
동일 타입의 집합이라는 면에서는 벡터와 같지만 아무 위치에나 삽입되는 것이 아니라 정렬된 위치에 삽입된다는 점이 다르며 그래서 검색 속도가 아주 빠르다.

셋은 키의 중복을 허용하지 않으므로 같은 키를 두 번 넣을 수 없는 반면 멀티셋은 키의 중복을 허용하므로 같은 키를 여러 번 넣을 수 있다.
중복을 허용하는 집합인가 아닌가에 따라 두 컨테이너 중 하나를 선택해서 사용하면 된다.



셋 클래스STL의 다른 컨테이너들과 마찬가지로 셋도 템플릿으로 정의되어 있다. 셋의 템플릿 정의는 다음과 같다.
		//template<class Key, class BinPred = less<Key>, class A = allocator<Key> >
		//class set { ... }

세 개의 템플릿 인수가 전달되는데 Key는 셋에 저장되는 키의 타입이다. 기본 타입은 물론이고 사용자 정의 타입에 대해서도 셋을 만들 수 있다.
BinPred는 키를 정렬하기 위한 비교 함수 객체인데 디폴트는 less로 되어 있어 작은 값이 앞쪽에 배치되는 오름차순으로 정렬된다.
다른 함수 객체를 지정하면 정렬 방법을 변경할 수도 있지만 어차피 정렬 자체가 목적이 아니라 빠른 검색이 목적이므로 미만 비교만으로도 충분하다.
마지막 변수는 할당기니까 신경쓰지 말도록 하자.

비교 객체와 할당기는 대개의 경우 생략하므로 셋 타입을 만들기 위해 꼭 필요한 것은 키의 타입밖에 없는 셈이다. 
set<int>는 정수형의 집합이며 set<Time>은 Time 객체의 집합이다.

 연관 컨테이너도 시퀀스와 마찬가지로 내부에서 사용하는 타입을 정의하는데 value_type, iterator, const_iterator, reference 등의 같은 이름을 사용한다.
 이 외에 다음 세 개의 타입을 추가로 정의한다.

 ===============================
타입				설명
key_type		키의 타입이다. 셋은 키가 곧 값이므로 value_type과 동일하며 맵은 키와 값의 pair 타입으로 정의된다.

key_compare		키를 비교하는 함수 객체 타입이다. 디폴트는 less로 되어 있다.

value_compare	값을 비교하는 함수 객체 타입이다. 셋에서는 key_compare와 동일한 타입으로 정의되며 맵에서는 pair를 비교한다.
 ===============================
value_compare는 사실상 셋에는 꼭 필요치 않은 타입인데 셋은 키만 저장되고 별도의 값이 없으므로 
key_compare 대신 value_comapre도 쓸 수 있도록 동의어를 정의해 놓았을 뿐이다.

생성자는 다음과 같이 세개가 있다.

		//explicit set(const BinPred& comp = BinPred());				//디폴트 생성자인데 요소를 가지지 않는 빈 셋을 만든다.
		//set(const set& x);											//복사 생성자   
		//set(InIt first, InIt last, const BinPred& comp = BinPred());	//반복자 구간의 요소들로 셋을 생성한다
			//이때 반복자 구간은 입력 반복자이기만 하면 되므로 다른 컨테이너의 구간을 가져올 수도 있다. 
			//만약 중복된 키가 있다면 이때는 한 번만 삽입되며 멀티셋이라면 전부 삽입될 것이다

멀티 셋은 키의 중복을 허용한다는 것만 빼고는 셋과 동일하다. 클래스 이름은 //!multiset이며 클래스 정의문이나 생성자도 셋과 완전히 동일하다.

=====================삽입, 삭제=======================
셋에 키를 삽입할 때는 insert 멤버 함수를 사용한다. 세 가지 버전이 제공된다.

		//pair<iterator, bool> insert(const value_type& val);				
			=값 하나를 셋에 삽입하되 삽입 대상이 되는 값 val만 인수로 전달받으며 삽입 위치는 별도로 전달받지 않는다.
			입한 결과로 삽입한 위치의 반복자와 삽입 성공 여부 두 개가 pair로 묶여 리턴된다. 
			셋은 중복을 허용하지 않으므로 val가 이미 존재할 경우 삽입에 실패할 수도 있다.
			키 하나를 삽입하면 삽입된 위치와 성공 여부를 동시에 리턴해야 하며 그래서 pair 구조체가 리턴된다.
			복자에 실패를 뜻하는 특이값이 없기 때문에 반복자와 bool의 짝을 리턴할 수밖에 없다.
			 insert를 호출한 후 성공 여부를 알고 싶다면 리턴된 pair의 second 멤버를 읽어 보고 이 값이 true이면 first 멤버에서 삽입된 반복자 위치를 구할 수 있다. 
			 삽입 성공 여부나 삽입된 위치에 관심이 없다면 리턴값은 무시해도 상관없다.
					 멀티셋에서는  리턴 타입이 다른데 중복이 허용되므로 val이 셋에 이미 포함되어 있더라도 삽입은 항상 성공한다.
					  그래서 성공 여부는 리턴할 필요가 없으며 삽입된 위치를 가리키는 반복자만 리턴된다.
							//멀티셋 insert 함수 :  iterator insert(const value_type& val);  // 멀티셋의 나머지 insert함수는 밑에 나오는 set insert와 동일

		//iterator insert(iterator it, const value_type& val);
			 두 번째 버전의 insert는 삽입 위치를 지정하는 반복자가 인수로 전달되는데 
			 이 반복자는 빠른 삽입을 위해 우선 검색할 시작 위치를 제공하는 힌트 역할을 할 뿐이다.
			 예를 들어 작은 값부터 큰 값을 차례대로 추가한다면 셋의 끝 부분에 배치될 확률이 높으므로 삽입 위치로 end()를 주는 것이 유리하다.
		//void insert((iterator first, iterator last);
			insert는 반복자 구간의 값들을 한꺼번에 삽입한다. 하나씩 삽입하는 것보다는 훨씬 더 빠르게 삽입될 것이다

			
		
셋에서 요소를 삭제할 때는 erase 함수를 사용한다.
		//iterator erase(iterator it);
		//iterator erase(iterator first, iterator last);
		//size_type erase(const Key& key);
키를 지정하는 erase의 경우 지정한 키가 셋에 포함되어 있지 않으면 아무 것도 하지 않으며 멀티셋의 경우 같은 키값을 가지는 모든 요소를 한꺼번에 삭제한다.




=====================검색=======================
셋에서 특정 키를 찾을 때는 다음과 같이 선언된 find 멤버 함수를 사용한다. 상수 버전과 비상수 버전이 중복 정의되어 있다.

		//iterator find(const Key& val);
		//const_iterator find(const Key& val) const;

인수로 찾고자 하는 키만 전달하면 된다. val 키가 발견되면 그 반복자를 리턴하며 없을 경우는 end()가 리턴된다. 

셋의 반복자가 임의 접근이 아니므로 전역 find 함수는 셋의 모든 요소를 순회하면서 순차적으로 검색하지만 
find 멤버 함수는 정렬되어 있다는 특성을 이용하여 이진 트리 검색을 하므로 훨씬 더 빠르다.
또한 find알고리즘은 다음에 설명할 동등성이 아닌 동일성 개념으로 요소를 검색한다는 면에서 셋과는 어울리지 않는다.

멀티셋의 경우 find 멤버 함수로 찾으면 중간 중간을 쿡쿡 찔러가며 검색하므로 중복된 키 중 어떤 것이 검색될 지 알 수 없는데 이는 이진 검색의 일반적인 특성이다.
반면 find 전역 함수는 처음부터 순서대로 검색하므로 항상 첫 번째 요소가 검색된다.
 중복된 키 중 첫 번째 또는 마지막 요소를 찾고 싶으면 lower_bound, upper_bound 함수를 사용해야 하며 
 둘을 한꺼번에 조사하고 싶으면 equal_range 멤버 함수를 사용한다. equal_range는 처음과 끝 반복자의 쌍을 조사하여 리턴한다.

		//iterator lower_bound(const Key& _Key);
		//iterator upper_bound(const Key& _Key);
		//pair <iterator, iterator> equal_range (const Key& _Key);

예를 들어 다음과 같은 정수 멀티셋에서 7을 찾는다고 해 보자. 7이 다섯 개나 중복되어 있는데 호출하는 함수에 따라 어떤 7이 검색될지가 달라진다.
             uper_bound
		        I
	123456777777897				 맴버 find함수는 이진탐색이므로, 7을 찾긴하나, 저 7들 중 어떤게 반환될지는모른다.
	      I
		lower_bound, 전역find

find 전역 함수와 lower_bound가 찾는 키는 우연히 같지만 이 둘의 검색 속도는 엄청난 차이가 있다. 
upper_bound 함수는 마지막 요소를 찾는 것이 아니라 마지막 요소의 다음을 찾는다는 점을 주의하자.


*/

int main()
{
	int ar[] = { 1,4,8,1,9,6,3 };						//1이 중복 되어있는 배열이다.
	int i;
	set<int> s;

	for (i = 0; i < sizeof(ar) / sizeof(ar[0]); i++) 
	{
		s.insert(ar[i]);								//set에 키값ar[i]를 하나씩 넣되, 이미 값이 있는 중복일 경우 제외 된다.
	}
	dump("원본", s);

	set<int> s2 = s;
	dump("사본", s2);

	const char* str = "ASDFASDFGHJKL";
	multiset<char> sc(&str[0], &str[13]);					//멀티셋 구간 생성자.
	dump("문자셋", sc);										//요소의 크기 순서대로 정렬된다 (이 경우 아스키코드가 기준)



	set<int>::iterator it;

	it = find(s.begin(), s.end(), 3);
	if (it != s.end()) 
		cout <<"find int :" << *it << endl;
	else
		cout << "찾는 키가 없습니다." << endl;

	cout << "멀티셋 검색알고리즘 종류" << endl;
	const char* sstr = "1234567777777789";
	multiset<char> s3(&sstr[0], &sstr[16]);
	multiset<char>::iterator mit;
	dump("s3 상태",s3);

	mit = s3.find(7);
	mit = s3.upper_bound(7);
	mit = s3.lower_bound(7);
	pair<multiset<char>::iterator, multiset<char>::iterator> p1;
	p1 = s3.equal_range(7);

	return 0;
}
