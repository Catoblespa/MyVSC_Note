#include <iostream>
using namespace std;


class CGameObject
{
public:
	CGameObject()
	{
		cout << "부모 생성자 " << endl;
	}
	virtual ~CGameObject()				//가상 소멸자
	{
		cout << "부모 소멸자" << endl;
	}
};

class CPlayer :public CGameObject
{
public:
	CPlayer()
	{
		cout << "자식 생성자 " << endl;
	}
	virtual ~CPlayer()
	{
		cout << "자식 소멸자" << endl;
	}
};

//class CWarrior : public CPlayer
//{
//};

int main()
{
	CGameObject* pPlayer = new CPlayer;

	//pPlayer를 할당해제하게 되면 부모 소멸자만 호출되고 끝난다.
	//다형성을 유지하기 위해 상속구조의 소멸자들은 virtaul해줘야한다!
	//소멸자에 virtual 키워드를 달고 난후에는 자식소멸자 -> 부모 소멸자 순으로 호출된다.
	delete pPlayer; 

	//단! 가상 생성자는 존재하지 않는다.
	//


	return 0;
}