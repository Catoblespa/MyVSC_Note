#include<iostream>


using namespace std;

class Count
{
private:
	int Value;
	static int Num;	//정적 맴버 변수 선언. 
					//정적 맴버 변수는  모든 Count 객체가 공유하는 변수이다.
					//해당 변수의 메모리는 객체가 갖지 않는다.

					//관습에 따라 클래스를 헤더 파일에 선언하고 멤버 함수를 구현 파일에 작성할 때
					//정적 멤버에 대한 외부 정의는 통상 클래스 구현 파일(*.cpp)에 작성한다.
public:
	Count() { Num++; }		//Num은 생성자에서 ++, 파괴자에서 -- 하므로, Count의 객체 수와 같다.
	~Count() { Num--; }


	static void InitNum()	//정적 맴버 함수 선언.
	{						// 외부에 작성할 때 static 키워드는 생략한다 (cpp, h 나눌경우!)
		Num = 0;			//Num변수는 객체가 갖는 변수가 아니므로, 객체가 존재 하지 않아도 출력이 가능하다.
		//Value = 0 // Error
	}						//정적 맴버 변수에소는 일반 맴버 변수에는 접근 할 수 없다.
							// 맴버변수에서 변수를 사용할때는 묵시적으로 this-> 가 붙게 되는데,
							// static은 this라고 할 객체가 없기 떄문이다 (클래스가 직접 갖기 때문에 객체와 상관 없다.

	static void OutNum() 
	{
		printf("현재 객체 개수 = %d\n", Num);
	}
};

//정적맴버 변수 초기화 방법!
int Count::Num;//  int Count::Num; = 0;



int main()
{

	cout << "정적 맴버 변수 ---------" << endl;
	Count::InitNum();
	Count::OutNum();
	Count C;
	Count C1;

	Count::OutNum;		//Num 변수는 정적맴버변수로, 클래스가 직접 관리 하므로, 객체를 통하지 않고 접근 가능하다.
	C.OutNum;			// 물론 이것도됨.

	cout << "정적 맴버 함수 ---------" << endl;

	Count* pC;

	pC->OutNum();               // 생성 전에도 호출 가능
	pC = new Count;
	pC->OutNum();               // 생성 후에도 호출 가능
	delete pC;
	pC->OutNum();               // 파괴된 후에도 호출 가능
								//OutNum이 정적 맴버 함수 이기 떄문에 객체에 메모리가 할당 되지 않아도 호출이 가능하다!!


	/* 
		*단 한 번만 해야 하는 전역 자원의 초기화
		정적 맴버 함수는 프로그램 실행중 단 한번 초기화 되어야 하는 전역자원을 관리할 떄 쓴다.
		그리고 해당 전역자원은 클래스의 모든 객체가 공유해야 할경우에 사용하면 매우 유용하다.
		만약 모든 객체가 똑같은 자원을 사용해야하는데, 생성할떄마다 초기화를 해준다면 연산 낭비가 심해진다.


		* 읽기 전용 자원의 초기화
		객체는 스스로 동작할 수 있지만 때로는 외부의 환경이나 자원에 대한 정보를 필요로 한다. 
		예를 들어 정확한 출력을 위해 화면 크기를 알아야 할 경우도 있고 장식을 위해 외부에 정의된 예쁜 비트맵 리소스를 읽어야 하는 경우도 있다. 
		이런 정보들은 일반적으로 한 번 읽어서 여러 번 사용할 수 있는 읽기 전용이기 때문에 객체별로 이 값을 일일이 조사하고 따로 유지할 필요가 없다.

		*모든 객체가 공유해야 하는 정보 관리
		중요한 계산을 하는 객체의 경우 계산에 필요한 기준값이 있을 수 있다.
		예를 들어 환율이나 이자율 따위는 금융, 재무 처리에 상당히 중요한 기준값으로 작용하며 기준값에 따라 계산 결과가 달라진다.
		이런 값들은 프로그램이 동작중일 때도 수시로 변할 수 있지만 일단 정해지면 모든 객체에 일관되게 적용된다. 
		그래서 개별 객체들이 각자 멤버로 가질 필요가 없으며 정적 멤버로 선언해 두고 공유하면 항상 최신의 기준값을 제공받게 된다.
	
	*/

	return 0;
}