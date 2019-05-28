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
객체의 셋
*/

class Time
{
	friend  struct TimeComp;
protected:
	int hour, min, sec;

public:
	Time(int h, int m, int s) { hour = h; min = m; sec = s; }
	void OutTime() { printf("%d:%d:%d\n", hour, min, sec); }
	bool operator <(const Time& T) const {
		return (hour * 3600 + min * 60 + sec < T.hour * 3600 + T.min * 60 + T.sec);
	}
	// 만약 set의 비교 객체를 greater로 변경한다면 이때는 < 연산자가 아닌 > 연산자를 정의해야 한다. 
	bool operator >(const Time& T) const {
		return (hour * 3600 + min * 60 + sec > T.hour * 3600 + T.min * 60 + T.sec);
	}
};


struct Timeless : public binary_function<Time, Time, bool>
{
	bool operator()(const Time* a, const Time* b) const {
		/*return (a->hour * 3600 + a->min * 60 + a->sec < b->hour * 3600 + b->min * 60 + b->sec);*/
		//비교 연산자 operator < 가 Time에 정의 되어 있으므로 참조 a와 b의 값만 비교하면 된다.
		return *a < *b;
	}
};


int main()
{
	//set<Time*> Times;
	//set<Time*, greater<Time>> Times;
	set<Time*, Timeless > Times;
	//set 템플릿의 두 번째 인수로 TimeComp 타입을 지정하면 
	//set의 디폴트 생성자는 이 타입의 디폴트 생성자를 호출하여 비교 객체를 하나 만들고 비교가 필요할 때마다 이 함수 객체의 () 연산자를 호출할 것이다
	//이 코드는 Time 객체를 비교하므로 실행 결과는 일단 동일하다.
	//이렇게 함수 객체를 기본으로 할당해주면, 비교 알고리즘을 사용자 정의로 바꿀 수있으므로, 활용성면에서 뛰어나다.
	//템플릿의 인수로 전달되어야 하므로 단순한 함수 포인터는 사용할 수 없으며 반드시 타입으로 정의되는 클래스여야 한다.
	Times.insert(new Time(1, 1, 1));		
	Times.insert(new Time(9, 8, 7));
	Times.insert(new Time(2, 3, 4));
	//만약 Time클래스에서  operator <연산자를 주석해보자.
	//셋의 insert 함수는 새로 삽입되는 키의 위치를 조사하기 위해 이미 삽입된 키와 비교하는데 이 과정에서 비교 함수 객체를 호출한다. 
	//디폴트 비교 함수 객체가 less로 지정되어 있으므로 이 객체의 () 연산자가 호출되는데 
	//이 연산자 본체에서는 셋의 요소 타입에 정의되어 있는 < 연산자로 요소끼리 비교를 수행한다. 
	//그런데 Time이 < 연산자를 제공하지 않으므로 에러가 나는 것이 당연하다.
			//struct less : public binary_function<T, T, bool>
			//{
			//	bool operator()(const T& Left, const T& Right) const {
			//		return (Left < Right);
			//	}
			//};



	set<Time*>::iterator it;

	for (it = Times.begin(); it != Times.end(); it++) 
	{							//요소를 삽입할 때의 순서와는 다르게 오름차순으로 잘 정렬되어 있는데 이런 정렬이 가능한 이유는 
		(**it).OutTime();		//Time이 < 연산자를 정의하여 시간 객체끼리 대소 관계를 결정할 수 있는 기능을 제공하기 때문이다. 
								//만약 Time 클래스의 < 연산자를 주석 처리해 버리면 엉뚱한 곳에서 에러가 발생한다.
	}
	//new 연산자로 Time 객체를 동적 할당하여 셋에 삽입하고 종료 전에 셋의 요소를 순회하면서 delete로 직접 삭제했다. 
	//벡터와 마찬가지로 셋도 요소만 관리할 뿐 요소가 가리키는 실체까지 관리하지는 않는다. 
	//셋에 저장된 타입이 Time*이므로 반복자가 가리키는 곳에는 Time *가 있을 뿐이다. 
	//그래서 출력할 때도 **it로 두 번 참조해야 Time 객체를 읽을 수 있다. 


	return 0;
}
