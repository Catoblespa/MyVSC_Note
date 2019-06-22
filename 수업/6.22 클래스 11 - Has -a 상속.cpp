#include <iostream>


using namespace std;

class CSword
{
public:
	void Using()
	{
		cout << "검을 휘두른다" << endl;
	}
};

class CAxe
{
public:
	void Using()
	{
		cout << "도끼를 휘두른다" << endl;
	}
};

// Has -a 관계 상속의 문제점
// 1. 플레이어는 무조건 검을 들고 있어야한다 (종속적이다,)
// 2. 다중 상속으로 인해 모호성이 발생 할 수 있다.

// 3. Has - a  관계는 상속이 아닌 포함관계로 구성하는게 옳다.
class CPlayer 
{

private:
	CAxe axe;
	CSword sword;

public:
	void Using()
	{
		axe.Using();
		sword.Using();
	}
};
//자식 객체 생성 과정 : 메모리 할당 -> 부모 생성자 -> 자식 생성자
//자식 객체 소멸 과정 : 메모리 할당 -> 부모 소멸자 -> 자식 소멸자

int main()
{

	CPlayer player;
	player.Using();

	return 0;
}