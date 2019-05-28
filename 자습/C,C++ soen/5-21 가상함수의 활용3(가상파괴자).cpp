#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>

using namespace std;


class Base
{
private:
	char* B_buf;

public:
	Base() { B_buf = new char[10]; puts("Base 생성"); }
	~Base() { delete[] B_buf; puts("Base 파괴"); }
	// virtual ~Base() { delete[] B_buf; puts("Base 파괴"); } //  이게 옳은 코딩. 예제를 위해 주석

};


class Derived : public Base
{
private:
	int* D_buf;

public:
	Derived() { D_buf = new int[32]; puts("Derived 생성"); }
	~Derived() { delete[] D_buf; puts("Derived 파괴"); }
	//virtual ~Derived() { delete[] D_buf; puts("Derived 파괴"); }   // 이게 옳은 코딩. 예제를 위해 주석

};


int main()
{
	//Base의 생성자는 크기 10의 문자형 배열을 동적으로 할당하며 파괴자에서 이 배열을 해제한다. 
	//Base로부터 상속받은 Derived는 생성자에서 크기 32의 정수형 배열을 할당하며 마찬가지로 파괴자에서 해제한다. 
	//각 클래스가 동적 할당을 하고 있지만 파괴자에서 할당된 배열을 제대로 해제하고 있으므로 메모리 누수는 없을 것 같다.
	
	//과연 그런지 main에 Derived D; 선언문만 남겨 놓고 실행해 보자. 
	//각 클래스의 생성자와 파괴자는 자신이 호출되었음을 알리기 위해 문자열을 출력한다. 
	//D 객체가 생성될 때는 부모의 생성자가 먼저 호출되고 자신의 생성자가 실행되며 파괴될 때는 반대 순서로 파괴자가 호출된다. 

	/* 	Derived D;만 남겨 놓고 실행 했을경우	//실행 결과는 다음과 같다.
	Derived D;

	//Base 생성
	//Derived 생성
	//Derived 파괴
	//Base 파괴

	생성자와 파괴자의 호출이 아주 정상적이다. 




	D 객체가 완전히 생성되었을 때 이 객체는 크기 10의 char 배열과 크기 32의 int 배열을 소유할 것이며 이 배열들은 생성된 역순으로 파괴자에서 차례대로 해제된다. 
	그러나 여기에 포인터가 개입되면 문제가 달라진다. 
	
	new 연산자로 Derived의 객체를 만들고 그 포인터를 Base * 타입의 pB에 대입하면
	Derived가 생성될 때 부모와 자신의 생성자가 차례대로 호출되어 두 개의 버퍼를 동적으로 할당할 것이다.

	*/


	Base* pB;

	pB = new Derived;

	delete pB;


	//실행 결과는 다음과 같다
	//Base 생성
	//Derived 생성
	//Base 파괴

	//delete pB;에서 pB의 타입이 Base * 이기 떄문에 부모의 생성자인 pB만을 호출한다.
	//포인터의 타입에 따라 파괴자가 정적으로 결합되다 보니 실제로 파괴되는 객체는 Derived 타입이지만 Derived의 파괴자가 호출되지 못하는 것이다.
	//이렇게 되면 부모가 할당한 char 배열은 잘 해제되지만 Derived가 할당한 int 배열은 해제되지 못하는 메모리 누수가 발생한다.
	//실행해 보면 Derived의 파괴자가 호출되지 않는다는 것을 확인할 수 있다.


	//문제가 무엇인지를 알았으므로 해결하는 것은 아주 간단하다. 파괴자가 동적 결합을 하도록 가상 함수로 만들면 된다. 
	//Base에만 virtual을 붙여도 되지만 가급적이면 둘 다 붙이는 것이 좋다.


	//***** 이런 이유로 기반 클래스로 사용될 가능성이 있는 클래스의 파괴자는 항상 가상 함수로 선언하는 것이 좋다. 



	return 0;
}