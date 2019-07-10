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

//#1  맴버 접근 지시자
// public		: 클래스 내부 외부 모두 접근 허용
// protected	: 상속 관계에서 접근 허용, 외부에서 접근 불가.
// private		: 클래스 내부에서만 접근 허용

class CTest
{
public:
	int m_iA;
private:
	int m_iB;

};

class CCustomer
{
	int m_iMoney;
};

struct tagCustomer
{
	int m_iMoney;
};

int main()
{
	CTest obj;
	obj.m_iA = 100;

	CCustomer obj1;
	tagCustomer obj2;

	//obj1.m_iMoney = 100;			//에러 class는 맴버 접근 지시자를 안쓰면 기본 private이다
	obj2.m_iMoney = 200;			//struct는 기본 public


	return 0;
}