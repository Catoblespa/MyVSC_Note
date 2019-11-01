#include <iostream>
using namespace std;

#include <iostream>
#include <vector>
using namespace std;

char greeting[] = "Hellor";

char* p = greeting;					//비상수 포인터
									//비상수 데이터

const char* p1 = greeting;			//비상수 포인터
									//상수 데이터

char* const p2 = greeting;			//상수 포인터
									//비상수 데이터

const char* const p3 = greeting;		//상수 포인터
									//상수 데이터.

char const* p4 = greeting;			//비상수 포인터
									//상수 데이터.

// const가 *포인터의 왼쪽에 있으면 데이터를 상수화
// 오른쪽에 있으면 포인터를 상수화 한다는 뜻이다
// 양쪽에 있으면 모두 상수화라는 뜻이다.


class Widget
{

};

void f1(const Widget* pw);		//f1은 상수 Widget 객체에 대한 
								//포인터를 매개변수로로 취합니다.
void f2(Widget const* pw);		// f2도 똑같은 뜻이다.



/*
STL 반복자는 포인터를 본뜬 것이기 때문에 기본동작이 T* 포인터와 굉장히 흡사하다.
다만, 어떤 반복자를 const로 선언하는 일은 포인터를 상수로 선언하는거와 같다.
		// const vector<int>::iterator iter; 는 
		// 즉 T* const A;					 이거처럼 포인터가 상수화된다는 뜻이다.

위와 같이 하면 반복자는 자신이 가리키는 대상이아닌 것을 가리키는 경우가 허용되지 않지만, 
반복자가 가리키는 대상 자체는 변경이 가능하게 됩니다.

만약 변경이 불가능한 객체를 가리키는 반복자가 필요할경우 const_iterator를 사용해야한다.
*/



int main()
{

	vector<int> vec;

	vec.push_back(1);

	const vector<int>::iterator iter = vec.begin();
	//iter는 T* const처럼 동작한다
	*iter = 10;					//쌉가능
	//++iter;					//iter가 상수임!


	vector<int>vec3;
	vector<int>::const_iterator iter2 = vec3.begin();
	//*iter2 = 10;				//	iter2가 그르키는 *iter2가 상수이므로 에러
	++iter2;					// 쌉 ㅋ 가능 ㅋ
	return 0;
}
