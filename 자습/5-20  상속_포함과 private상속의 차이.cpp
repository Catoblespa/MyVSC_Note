#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>
/*
--5-20
http://soen.kr/lecture/ccpp/cpp3/29-4-2.htm
private상속과 인터페이스 상속, protect 상속에 대해 모두 정리 하지 않았으니, 자세한건 해당 링크에서 다시 확인할것 
*/

using namespace std;

class Date
{
protected:
	int year, month, day;

public:
	Date(int y, int m, int d) { year = y; month = m; day = d; }
	void OutDate() { printf("%d/%d/%d", year, month, day); }
};


/*
ValidTo 멤버를 빼고 Date로부터 private 상속했으며 초기화 리스트에서는 Date 클래스의 생성자를 호출하여 상속받은 멤버를 초기화했다. 
이렇게 되면 Product는 Date의 모든 멤버를 상속받으며 상속받은 멤버로 제품의 유효기간을 표현할 수 있다. 
포함은 클래스 타입의 객체를 멤버로 선언하는데 비해 private 상속은 기반 클래스로부터 필요한 멤버를 상속받는 기법이다. 실행 결과는 이전 예제와 동일하다.

그러나 클래스를 포함하고 있을때와 private 상속을 받을때와 다른점이 여러 존재한다.
이를테면, product가 생산일자 뿐만 아니라, 유효기간 또한 표시하고 싶을때 포함클래스에선 Date를 맴버변수로 2개 선언하면 된다.
하지만 상속에서는 같은 이름의 클래스를 두번 상속하는건 문법에 맞지 않다. 같은 클래스를 두번 상속 받을경우 상속받을 맴버 변수,함수에 대해 모호함이 발생하기 떄문이다.

포함과 private 상속의 또 다른 차이점은 protected 멤버에 대한 액세스 허가 여부이다.
포함의 경우 포함된 객체의 public 액세스 속성을 가지는 것만 직접 참조할 수 있다. 
Product가 아무리 Date의 객체를 포함한다 하더라도 Product는 분명히 Date의 외부이기 때문이다. 
포함된 객체의 private 멤버는 물론 액세스할 수 없으며 protected 멤버도 액세스할 수 없다. 
반면 private상속의 경우는 protected 멤버를 파생 클래스가 액세스할 수 있으므로 포함보다는 좀 더 긴밀한 관계라고 할 수 있다.

*/
class Product : private Date
{
private:
	char Name[64];
	char Company[32];
	//Date ValidTo;				
	int Price;

public:
	Product(const char* aN, const char* aC, int y, int m, int d, int aP) : Date(y, m, d)
	{
		strcpy_s(Name,sizeof(Name), aN);
		strcpy_s(Company,sizeof(Company), aC);
		Price = aP;
	}

	void OutProduct() 
	{
		printf("이름:%s\n", Name);
		printf("제조사:%s\n", Company);
		printf("유효기간:");
		OutDate();		//ValidTo.OutDate(); 였었따-
		puts("");
		printf("가격:%d\n", Price);
	}

};

void main()
{

	Product S("새우깡", "농심", 2009, 8, 15, 900);

	S.OutProduct();

}