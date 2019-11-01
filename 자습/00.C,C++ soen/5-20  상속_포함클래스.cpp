#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>
/*
상속은 이미 만들어진 클래스를 재활용하는 객체 지향적인 기법의 하나이다.
상속을 받으면 기반 클래스에 이미 정의된 속성과 동작을 그대로 재사용할 수 있어 클래스를 만드는 시간과 노력을 절감할 수 있다.
이전의 절차식 프로그래밍 기법에서는 찾아볼 수 없는 기발하고 멋진 방법이기는 하다.그러나 상속만이 클래스를 재활용하는 유일한 기법은 아니다.

상속외에도 전통적인 포함 방법을 사용할 수 있다.
포함(Containment)이란 재활용하고 싶은 클래스의 객체를 멤버 변수로 선언하는 방법이다.
클래스에 포함되는 멤버의 타입에는 제한이 없으므로 다른 클래스의 객체도 당연히 멤버가 될 수 있다.
C에서 구조체가 다른 구조체를 포함할 수 있는 것과 개념적으로 동일하며 사실 별로 특별한 기법도 아니다.
다음 예제는 포함 기법으로 Date 클래스를 재활용하는 것을 보여 준다.

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



class Product
{
private:
	char Name[64];
	char Company[32];
	Date ValidTo;				//이미 만들어져 있는 Date 클래스를 재활용하기 위해 Date의 객체 ValidTo를 멤버로 선언했다. 
	int Price;

public:
	Product(const char* aN, const char* aC, int y, int m, int d, int aP) : ValidTo(y, m, d)
	{
		strcpy_s(Name,sizeof(Name), aN);
		strcpy_s(Company,sizeof(Company), aC);
		Price = aP;
	}
	//포함된 객체는 반드시 초기화 리스트에서, 즉 생성자 본체 이전에 초기화해야 한다. 
	//이때 초기화 리스트에는 클래스 이름이 아닌 초기화하고자 하는 객체의 멤버 이름을 사용한다. 
	//상속과 달리 Date 클래스를 초기화하는 것이 아니라 Product에 포함된 ValidTo 객체를 초기화하는 것이므로 Date(y, m, d)로 적어서는 안된다.
	//만약 포함된 객체에 대한 초기식이 초기화 리스트에서 발견되지 않으면 이때는 디폴트 생성자가 호출된다.
	//Date 클래스가 디폴트 생성자를 정의하고 있지 않으므로, 초기화 리스트에서 ValidTo(y, m, d) 를 제거하면 오류가 발생한다.

	/*
	Product(char *aN, char *aC, int y,int m,int d, int aP)
	{
		ValidTo=Date(y,m,d);
		strcpy(Name,aN);
		strcpy(Company,aC);
		Price=aP;
     }
	초기화 리스트에 ValidTo 초기식을 빼고 대신 생성자 본체에 대입문을 작성했다. 
	이렇게 하면 에러없이 컴파일되고 Product 객체가 정상적으로 초기화되기는 하지만 초기화 과정은 상당히 달라진다. 
	Date의 디폴트 생성자에 의해 ValidTo가 일단 쓰레기값으로 초기화된 후 Product의 생성자 본체에서 다시 Date(int, int, int) 생성자를 호출하여
	임시 객체를 생성하고 이 임시 객체가 ValidTo 객체로 대입되며 이 과정에서 대입 연산자가 실행될 것이다.

	두 개의 생성자가 차례대로 호출되는 이중 생성 과정을 거치며 대입 연산자까지 호출된다. 
	Date는 아주 작은 클래스라 별 부담이 없지만 대형 클래스는 이 차이를 무시할 수 없다. 디폴트 초기화, 임시 객체 생성, 
	대입 연산 중의 깊은 복사, 임시 객체 파괴까지 엄청나게 긴 과정을 거쳐야 초기화가 완료된다. 

	이런 복잡한 과정이 싫으면 문법의 정상적인 권고대로 초기화 리스트에서 포함 객체를 초기화하는 것이 좋다.
	
	*/

	void OutProduct() 
	{
		printf("이름:%s\n", Name);
		printf("제조사:%s\n", Company);
		printf("유효기간:");
		ValidTo.OutDate();
		puts("");
		printf("가격:%d\n", Price);
	}

};


//Product가 Date를 포함하고 있는 이런 관계를 HAS A 관계라고 하는데 일종의 소유 관계이며 상속 관계를 표현하는 IS A와는 의미가 다르다.
//제품이 유효기간 표현을 위해 날짜를 소유(Product has a Date)하는 것이지 제품이 일종의 날짜(Product is a Date)인 것은 아니다. 
//두 클래스의 관계가 IS A 관계일 때는 주로 public 상속을 사용하고 HAS A 관계일 때는 포함 기법이 적합하다.
//그러나 모든 클래스의 관계가 이처럼 명확하게 구분되는 것은 아니므로 절대적인 재활용 법칙이라고 하기는 어렵다.
void main()
{

	Product S("새우깡", "농심", 2009, 8, 15, 900);

	S.OutProduct();

}