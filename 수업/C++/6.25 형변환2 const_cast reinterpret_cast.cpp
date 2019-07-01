#include <iostream>
using namespace std;


/*
	C++ 형변환(캐스팅) 연산자
	static_cast
	dynamic_cast
	const_cast
	reinterpret_cast
*/

int main()
{
	////## 1  const_cast
	////const 타입 포인터나 레퍼런스에 대해 사용하는 형변환 연산자
	////포인터나 레퍼런스에 대해 const를 없애준다
	////단! 포인터나 레퍼런스가 아닌 일반 변수에 대한 const_cast는 사용 할 수 없다!!!!
	//int a = 100;
	//const int* ptr = &a;
	////int *ptr2 = ptr ; //Error

	//int* ptr2 = const_cast<int*>(ptr);		//const를 해제해서 ptr2에 전달 쌉가능
	//*ptr2 = 200;							//ptr2 참조해서 값을 변경할 수 있음
	//cout << a << endl;


	//const int a = 100;
	//const_cast<int>(a) = 200;			//ERROR!!!



	// ##   reinterpret_cast
	// 형변환 대상이 포인터나 레퍼런스이다. 강제 형변환으로는 불가능한 문법
	//다른 타입의 포인터를 서로 캐스팅 할수 있게 해준다.
	int a = 100;
	//float* ptr = &a; //Error!
	//float *ptr = static_cast<float*>(&a) //ERROR!!

	float* ptr = reinterpret_cast<float*>(&a);	//reinterpret_cast하면 가능 남발하지 말것


	return 0;
}