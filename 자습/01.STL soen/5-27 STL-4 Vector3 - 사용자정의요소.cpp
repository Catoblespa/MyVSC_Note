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

class Time;

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";
	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

template<typename C> void dump_p(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";
	for (unsigned i = 0; i < c.size(); i++) { c[i]->OutObject(); } cout << endl;
}

template<typename C> void dump_o(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";
	for (unsigned i = 0; i < c.size(); i++) { c[i].OutObject(); } cout << endl;
}
/*
벡터는 타입을 받아 들이는 클래스 템플릿이므로 임의의 모든 타입을 요소로 가질 수 있다.
지금까지는 예제 제작의 편의를 위해 주로 정수형의 벡터만 만들어 보았지만 클래스 객체를 요소로 가지는 벡터도 얼마든지 만들 수 있다.


*/

class Time
{
protected:
	int hour, min, sec;

public:
	Time(int h, int m, int s) { hour = h; min = m; sec = s; }
	void OutObject() { printf("%d:%d:%d ", hour, min, sec); }
};


class Dynamic
{
	friend struct DynCompare;
	friend struct DynFind;
private:
	char* ptr;

public:
	Dynamic()
	{
		ptr = new char[1];
		ptr[0] = 0;
	}

	Dynamic(const char* str)
	{
		ptr = new char[strlen(str) + 1];
		strcpy_s(ptr, strlen(str) + 1, str);
	}

	Dynamic(const Dynamic& Other)
	{
		ptr = new char[strlen(Other.ptr) + 1];
		strcpy_s(ptr, strlen(Other.ptr) + 1, Other.ptr);
	}

	Dynamic& operator =(const Dynamic& Other)
	{
		if (this != &Other) {
			delete[] ptr;
			ptr = new char[strlen(Other.ptr) + 1];
			strcpy_s(ptr, strlen(Other.ptr) + 1, Other.ptr);
		}
		return *this;
	}

	int operator ==(const Dynamic& Other) const
	{
		return strcmp(ptr, Other.ptr);
	}

	int operator <(const Dynamic& Other) const
	{
		return strcmp(ptr, Other.ptr) < 0;
	}

	virtual ~Dynamic()
	{
		delete[] ptr;
	}

	virtual void OutObject()
	{
		cout << ptr << ' ';
	}
};


struct DynCompare {
	bool operator()(Dynamic* a, Dynamic* b) const {
		return strcmp(a->ptr, b->ptr) < 0;
	}
};



struct DynFind {
	bool operator()(Dynamic* a) const {
		return strcmp(a->ptr, "cat") == 0;
	}
};


int main()
{
	vector<Time*> vt;
	vt.push_back(new Time(1, 1, 1));
	vt.push_back(new Time(2, 2, 2));
	dump_p("요소 2개", vt);


	vector<Time> vta;
	vta.push_back(Time(1, 2, 3));

	cout << typeid(*vta.begin()).name() << endl;

	vector<Time*>::iterator it;

	for (it = vt.begin(); it != vt.end(); it++) {

		delete* it;

	}
	//벡터의 타입이 vector<Time *>로 변경되었으며 벡터에 요소를 추가할 때 Time 객체가 아니라 new 연산자로 동적 생성한 Time 객체의 포인터를 저장했다
	//값을 저장하는 벡터는 Time 객체를 직접 가지지만 포인터를 저장하는 벡터는 동적 생성된 Time 객체의 포인터만을 가진다
	//포인터를 가지는 벡터를 파괴할 때는 각 포인터가 가리키는 객체를 직접 파괴해야 한다.
	//그렇지 않으면 동적으로 생성한 객체가 파괴되지 않으므로 메모리 누수가 발생한다
	//벡터는 요소를 관리할 뿐이지 요소가 가리키는 객체까지는 관리하지 못한다.


	//벡터에 임의의 타입을 저장할 수 있지만 그렇다고 정말 아무 타입이나 저장할 수 있는 것은 아니며 일정한 조건을 만족하는 타입만 저장할 수 있다. 
	//다음 예제는 내부에서 동적 할당을 하는 객체를 요소로 가지는 벡터를 만든다. 
	//!동적_할당을 하는 클래스는 생성자, 가상 파괴자, 복사 생성자, 대입 연산자를 적절히 정의해야 한다.

	cout << "=================동적할당을 하는 클래스의 vector====================" << endl;

	vector<Dynamic*> vt2;
	Dynamic a("dog");
	Dynamic b("cow");
	vt2.push_back(&a);
	vt2.push_back(&b);

	dump_p("요소 2개", vt2);
	//Dynamic 클래스의 정의문이 꽤 긴데 디폴트 생성자, 변환 생성자, 복사 생성자, = 대입 연산자, ==, < 비교 연산자, 가상 파괴자 등이 제대로 정의되어 있다
	//main에서 Dynamic 타입을 저장하는 벡터 vt를 선언하고 두 개의 Dynamic 객체를 벡터 끝에 추가한 후 출력해 보았다. 별 이상없이 잘 동작할 것이다.

	//그러나 아무 대가없이 이렇게 잘 동작하는 것은 아니며 Dynamic이 벡터 템플릿이 요구하는 조건을 모두 만족하기 때문이다.

	//과연 어떤 조건이 필요한지 몇 가지 테스트를 해 보자. push_back 함수로 객체를 벡터 끝에 추가할 때 복사가 발생하며 이때 객체의 복사 생성자가 호출된다.
				//!단, 여기서 내가 예제소스에서 vector를 Dynamic * 형으로 했는데, 원래 예제는 Dynamic형 vector이므로, 복사 생성자가 호출되었다.
	//만약 Dynamic이 복사 생성자를 정의하지 않으면 이 예제는 다운된다. 
	//복사 생성자가 정의되어 있지 않으면 디폴트 복사 생성자가 얕은 복사를 하게 될 것이고 정리될 때 
	//객체 a와 벡터에 추가된 사본이 같은 버퍼를 이중 정리하므로 문제가 생기는 것이다
	vector<Dynamic> vt3;
	Dynamic c("dog");
	Dynamic d("cow");
	vt3.push_back(c);
	vt3.push_back(d);

	Dynamic e;
	e = vt3[1];
	//새로운 객체 c를 선언한 후 vt[1] 번째 요소(즉 b객체의 사본)을 대입받았다. 
	//별다른 이상없이 잘 동작하는데 Dynamic 클래스가 대입 연산자를 제대로 정의하고 있기 때문이다.



	Dynamic  f("cat");
	find(vt3.begin(), vt3.end(), f);
	//다음은 == 연산자가 왜 필요한지 살펴보기 위해 다음 코드를 작성 했다.
	//"cat" 문자열을 가지는 Dynamic 객체가 벡터에 있는지 find 함수로 검색해 보았는데 별다른 이상없이 컴파일되고 검색도 된다. 
	//이 코드가 잘 컴파일되는 이유는 == 연산자 함수가 정의되어 있어서 find가 벡터내의 객체와 인수로 주어진 d객체를 비교할 수 있기 때문이다.
	//== 연산자를 주석 처리하면 필요한 기능이 정의되지 않았다는 에러가 find 함수 본체에서 발생할 것이다. 


	sort(vt3.begin(), vt3.end());
	dump_o("정렬 후", vt3);
	//고작 두 개밖에 안들어 있기는 하지만 정렬 결과도 제대로 나온다. 
	//이런 정렬이 가능한 이유는 < 연산자가 정의되어 있어 Dynamic 객체끼리 대소 비교가 가능하기 때문이다. 
	//이 연산자를 주석 처리하면 역시 에러 메시지가 출력될 것이다. 
	//파괴자를 생략하면 컴파일과 실행에는 이상이 없지만 할당한 메모리가 해제되지 않으므로 메모리 누수가 발생하며 
	//파괴자가 가상이 아니면 파생 클래스가 제대로 정리되지 않는다.

	//결국 Dynamic 클래스가 벡터에 저장되려면 위 소스에 정의되어 있는 모든 장치들이 필요하다. 
	// 하나라도 빠지면 벡터 템플릿과 알고리즘의 요구 조건을 만족하지 못하므로 컨테이너에 저장할 수 없거나 동작 중에 다운되거나 컴파일이 거부된다.
	//무슨 조건이 저렇게 많으냐고 하겠지만 원칙은 아주 간단하다. int와 똑같이 동작하는 타입이면 아무런 문제가 없다.
	//사용자 정의 타입을 벡터에 넣기는 아주 어렵다는 느낌이 들겠지만 다행히 그렇지는 않다. 
	//Dynamic 클래스는 동적 할당을 하기 때문에 많은 함수들이 필요하지만 Time 같은 단순 멤버만 가진 클래스는 컴파일러가 만들어주는 디폴트만으로도 충분하며 
	//비교 연산자 정도만 정의하면 된다. 
	
	//동적 할당을 하는 타입의 포인터에 대한 벡터도 물론 만들 수 있으며 포인터에 대한 검색, 정렬도 가능하다.
			// 여기서 나는 위의 예제부터 타입의 포인터에 대한 백터를 사용했다.
	vector<Dynamic*> v_pd;
	v_pd.push_back(new Dynamic("dog"));
	v_pd.push_back(new Dynamic("cow"));

	dump_p("요소 2개", v_pd);

	Dynamic g("cat");
	v_pd.push_back(new Dynamic(g));


	puts(find_if(v_pd.begin(), v_pd.end(), DynFind()) == v_pd.end() ? "없다" : "있다");
	sort(v_pd.begin(), v_pd.end(), DynCompare());

	dump_p("정렬 후", v_pd);



	vector<Dynamic*>::iterator it5;
	for (it5 = v_pd.begin(); it5 != v_pd.end(); it5++) {
		delete* it5;
	}

	return 0;
}
