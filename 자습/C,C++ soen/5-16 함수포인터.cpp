#include <iostream>

typedef int (*PFTYPE)(int, int);
// 이런식으로 typedef를 해두면 해당 함수포인터를 PFTYPE pf; 처럼 간단하게 선언 할 수 있따.
// PFTYPE pf;    는         int (*pf)(int,int); 와 똑같은 선언이다.

using namespace std;

int add(int a, int b)
{
	return a + b;
}
int sub(int a, int b)
{
	return a - b;
}

void func(int a, double b)
{
	cout << a <<" " << b << endl;
}

int main()
{

	int(*pf)(int, int);	// int 형을 반환하고 int형 인수 2개를 인자로 받는 함수포인터.
	pf = add;			//함수의 이름은 함수의 시작 주소를알리기 때문에 add만 써주면 된다.
	cout << pf(10, 20) << endl;

	pf = (int(*)(int, int))func; // 만약 pf함수포인터와 형식이 다른 함수를 pf에 캐스팅할경우 
	pf(10, 20);					 // 캐스팅 방법 
								 // 1. int(*pf)(int, int);		pf이 선언 방식에서 변수명을 지운다.
								 // 2. int(*)(int,int)		    전체를 ()로 감싼다
								 // 3. (int(*)(int, int))		캐스팅되는 대상의 함수명을 쓴다.
								 // 4. (int(*)(int, int))func   짜잔!

							     //두번째 인자는 int을 double로 캐스팅 한것이므로, 올바른 수가 나오지 않는다!
								 //이런식으로 인수가 다른 함수를 함수포인터에 강제로 캐스팅하여 대입할경우 스택구조가 망가지니 주의 !
								 // 앵간하면 강제 캐스팅하지 말자
	
	//함수 포인터 배열
	// int (*pf2[2])(int, int) = { Func1, Func2}; 이렇게 선언하고 초기화
	cout  <<"======================= typedef 식의 함수포인터 선언================="<< endl;
	PFTYPE pf2[2];		//typedef int (*PFTYPE)(int, int);	//하는 김에 함수포인터 배열을 사용해보자
	pf2[0] = add;
	cout << pf2[0](40, 50)<< endl;

	pf2[0] = add;
	pf2[1] = sub;
											
	int select = 0;							// select 가 0일때는 pf2 는 add, 1일때는 sub
	cout <<" pf2[select](20, 40) , "<< "select is " << select << " : "<< pf2[select](20, 40) << endl;



	//auto형식의 함수는 함수포인터로 받을수 있지만,
	//auto리턴, 탬플릿함수일 경우 함수 포인터로 받을 수 없다.
	//T리턴, T템플릿일경우 auto로 받을 수 있다.



	return 0;
}