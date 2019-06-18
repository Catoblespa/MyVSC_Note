#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

//#1  ****클래스의 4대 속성
//1. 은닉화(Hidding Information)
//맴버 제어를 private으로 외부에서 접근을 막는다. (데이터 보호)

//2. 캡슐화(encapsulation)
//클래스의 데이터(맴버 변수)와 기능(맴버 함수)을 하나로 묶어 , 구성요소를 외부로부터 숨긴다.

//3. 상속성(inheritance)
// 자식 클래스들의 공통된 요소들을 부모 클래스가 물려준다. 코드 재사용 극대화
// 부모클래스는 자식 클래스 들의 추상적인 존재가 된다.

//4. 다형성(polymorphism)
//전제 조건 : 상속.
//여러 객체가 하나의 메시지를 통해 각기 다른 형태를 취하는 것.
// 프로그래밍 유연성 극대화 
// ex 도형 <- 삼각형   <- 사각형   <- 원 이 있을때 각 자식클래스들은 draw할때 다른 결과가 나온다!


//##2 . 은닉화(Hidding Information)
//맴버 제어를 private으로 외부에서 접근을 막는다. (데이터 보호)
class CPlayer		//은닉화
{
private:
	int m_iAtt;
	int m_iHp;
	int m_MaxHp;

public:			//퍼블릭을 두번써서,, get끼리 set끼리 모아두기 ?!
	void SetDamaged(int iAtt)	//Get함수 (은닉된 데이터 읽기 전용)
	{
		m_iHp -= iAtt;
	}
public:
	int GetAttack()				//Set함수 (은닉된 데이터 쓰기 허용)
	{
		return m_iAtt;
	}
};


//#3. 캡슐화 (encapsulation)
//클래스의 데이터(맴버 변수)와 기능(맴버 함수)을 하나로 묶어 , 구성요소를 외부로부터 숨긴다.




//캡슐화를 하지 않은 경우
class C콧물약
{
public:
	void 복용()
	{
		cout << "콧물이 멎습니다" << endl;
	}
};

class C재채기약
{
public:
	void 복용()
	{
		cout << "재채기이 멎습니다" << endl;
	}
};

class C코막힘약
{
public:
	void 복용()
	{
		cout << "코가 뚫립니다." << endl;
	}
};

//캡슐화 !
//캡슐화는 구현내용을 숨기고, 일련의 행위를 만든다.
//이로써 사용자는 구현내용을 몰라도, 어떤 기능을 하는지만 알면 되도록 한다.
class CContac600
{
private:
	C코막힘약 cap1;
	C콧물약 cap2;
	C재채기약 cap3;

public :
	void  복용()
	{
		cap1.복용();
		cap2.복용();
		cap3.복용();
	}
};


// 상속성
// 자식 클래스들의 공통된 요소들을 부모 클래스가 물려준다. 코드 재사용 극대화
// 부모클래스는 자식 클래스 들의 추상적인 존재가 된다.

int main()
{
	//비캡슐화의 경우
	//만약 복용순서가 반드시 정해져있다면 ?! 이 행위는 캡슐화 되지 않은거임.
	//C코막힘약 cap1;
	//C콧물약 cap2;
	//C재채기약 cap3;

	//cap1.복용();
	//cap2.복용();
	//cap3.복용();


	//캡슐화의 경우
	//플레이어는 복용 순서를 몰라도 캡슐화 되있으므로 복용을 할 수 있음.
	CContac600 cap;
	cap.복용();
	return 0;
}