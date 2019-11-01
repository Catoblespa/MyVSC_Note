#include <iostream>	

using namespace std;

#define end endl;

// 레퍼런스 변수는 주소에 직접 접근하게 하는 변수이므로, 함수에서 사용할경우
// 포인터와 같은 효과인, 콜바이 레퍼런스이다.

typedef struct tag_Friend 
{
	char Name[10];
	int Age;
	double Height;
}Friend;

void OutFriend(Friend F);
void OutFriendPtr(Friend* F);
void OutFriendRef(Friend& F);

//값 호출
void OutFriend(tag_Friend F){printf("이름=%s, 나이=%d, 키=%.1f\n",F.Name, F.Age, F.Height);}
// 포인터 참조 호출
void OutFriendPtr(tag_Friend* F){printf("이름=%s, 나이=%d, 키=%.1f\n",F->Name, F->Age, F->Height);}
//레퍼런스 참조 호출
void OutFriendRef(tag_Friend& F){printf("이름=%s, 나이=%d, 키=%.1f\n",F.Name, F.Age, F.Height);}



void func(int a) {
	cout << a << end;
}


int main()
{

	// 레퍼런스의 선언법
	// type &변수이름;

	int b = 10;
	int& a = b;	//레퍼런스 변수는 반드시 어떤 대상체의 별명인지 밝혀야한다, 즉 선언과 즉시 정의를 해줘야한다!.
	cout << "변수 b의 값 " << b << endl;				//① 함수의 인수 목록에 사용되는 레퍼런스 형식 인수.함수가 호출될 때 실인수에 대한 별명으로 초기화된다.
	cout << "페퍼런스 a의 값" << a << endl;		    //	이런 예는 바로 다음 항에서 살펴볼 것이다.
	cout << "레퍼런스 a의 주소 :" << &a << endl;	    //② 클래스의 멤버로 선언될 때.이때는 클래스의 생성자에서 반드시 초기화해야 한다.	***중요***
	cout << "변수 b 의 주소    :" << &b << endl;		//	만약 생성자에서 레퍼런스 멤버를 초기화하지 않으면 에러로 처리된다.
													//③ 변수를 extern 선언할 때.이때는 레퍼런스의 초기식이 외부에 선언되어 있다는 뜻이므로 초기값을 주지 않아도 된다. 
													//	extern int& ri; 선언문은 ri가 어떤 변수에 대한 별명으로 외부에 선언되어 있다는 뜻이다.
													//- 레퍼런스는 하나의 대상체만을 별명으로 삼을 수 있으며, 선언과 대입후, 대상체를 바꿀 수 없다.
													//레퍼런스는 변수가 아닌 리터럴 상수를 대상체로 삼을 수 없다.
													// int &i = 123 ; *에러
	//레퍼런스 a에 b를 대입해주면 , a와 동일한 값, 주소를 갖는다. 또한, a와 b 어느 하나의 값을 변경하더라도, 두 변수 모두의 값이 바뀐다.
	//즉 주소를 공유하고 여러가지의 별명을 갖게하는 방법이다.
	/*	레퍼런스는 대상체와 타입이 반드시 같아야한다.
	int i;
	int& ri = i;                      // 가능
	double& rd = i;               // 에러
	short& rs = i;                 // 에러
	unsigned& ru = i;           // 에러
	*/
	cout << "======================================================" << end;


	Friend fri = { "김상형",24,181.2 };
	OutFriend(fri);
	OutFriendPtr(&fri);
	OutFriendRef(fri); //보통 함수명에 Ref나 ByRef같은 접미를 붙여 호출부에서 함수의 형식을 쉽게 파악할 수 있도록 작성하라고 권유
					  // 포인터와 다른 점!
					  //포인터로 값을 넘겨줄경우 포인터의 연산(주소이동)을 사용하여 간접적으로 다른 변수에도 접근 가능하다.
					  //레퍼런스를 사용하면, 해당 변수 값만 사용가능하다.
					//레퍼런스 변수를 인자로 갖는 함수의 경우, 수식이나(ref+1 처럼), 상수를 넘겨 줄수 없다 
					// 단, 함수 원형이 void plusref2(const int &a) 일경우 상수를 넘겨 줄 수 있으나, 값 변경은 당연히 안됨.

	char* pName;
	char*& Name= pName; // 포인터형 레퍼런스 변수 char * 형 변수만 대상체로 지정 가능.
						// 반대로 레퍼런스 포인터 char &*Name 은 선언 불가능.


	//레퍼런스 활용
	int ar[5] = { 100,101,102,103,104 };
	void (&Fref)(int) = func;		// 함수 레퍼런스
	int (&Aref)[5] = ar;			// 배열 레퍼런스.
	//단, 포인터를 2중포인터를 만드는 것과 달리 레퍼런스의 레퍼런스, 즉 2중레퍼런스는 불가능하다.
	


	return 0;

}