#include <iostream>
using namespace std;
//#1  클래스
// 객체를 표현한 사용자 정의 자료형. C++부터 등장한 개념.
// 객체의 추상화!
// 추상화 : 공통된 것을 묶어둔것.

class CCustomer
{
private :
	int m_iMoney;
public:

	void OrderProduct()
	{
		cout << "물건 주문" << endl;
	}
	void TakeProduct()
	{
		cout << "물건 받음" << endl;
	}
};


int main()
{
	//#2. 객체 (Object)
	//객체는 클래스의 구체화다.
	//instance 뜻 : 실제 메모리에 등록됨 을 뜻함.
	//Object도 또한 메모리에 등록되므로 Instance의 종류중 하나이다.
	CCustomer object;

	object.OrderProduct();
	object.TakeProduct();

	return 0;
}