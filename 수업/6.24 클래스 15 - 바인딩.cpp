#include <iostream>
using namespace std;


class CGameObject
{
	char a;
public:
	 void Print()
	{
		cout << "Game Object" << endl;
	}
};

class CPlayer :public CGameObject
{
	short b;
public :
	 void Print()
	{
		cout << "Player Object" << endl;
	}
};

class CWarrior : public CPlayer
{
	double d;
public:
	virtual void Print()
	{
		cout << "Wairror Object" << endl;
	}

};

int main()
{

	////#1 오버라이딩과 다형성
	//CGameObject	gameObject;
	//CPlayer		playerObject;
	//CWarrior		warriorObject;

	////정적 바인딩 : Print함수가 어떤 클래스의 Print함수로 호출될지가 컴파일 시점에 결정 된다.
	////이 때 객체 타입으로 결정됨.
	//gameObject.Print();
	//playerObject.Print();
	//warriorObject.Print();


	////#2 오버라이딩과 객체 포인터
	CWarrior warriorObject;

	CGameObject* ptr1 = &warriorObject;
	CPlayer* ptr2 = &warriorObject;
	CWarrior* ptr3 = &warriorObject;

	////정적 바인딩 때문에 다형성이 제대로 이루어지고 있지 않음!!
	////이때 컴파일러는 단순 포인터 타입으로 판단해버린다!
	////동적 바인딩으로 바꿔라!!!!! -> virtual 키워드의 역할이다!!
	////virtual 키워드로 맴버 함수 구현 했으면, 이제부터는 함수를 호출할지는 런타임 때 결정된다! -> 동적바인딩
	ptr1->Print();
	ptr2->Print();
	ptr3->Print();


	//클래스에 맴버변수가 아무것도 없을때 보통 1바이트의 크기를 갖는다.
	//가상함수를 만들고 나면 맴버 변수가 없어도 class의 크기가 4바이트가 된다!
	//## virtual 키워드가 하나라도 존재하는 클래스를 컴파일 할때 
	//컴파일러는 가상함수 포인터(vfptr)와 가상함수 테이블(vftable)을 생성한다!!!!!!
	//따지고 보면 정적바인딩과 동적바인딩을 적절히 섞어둔거임. 테이블을 만드는건 컴파일시점에 바인딩된다는 뜻이기도함!
	cout << sizeof(CGameObject) << endl;
	cout << sizeof(CPlayer) << endl;
	cout << sizeof(CWarrior) << endl;

	//CGameObject gameObject;		//중단점 걸고 조사식으로 열어보면 vfptr이 들어있다!!!!! vfptr 까보면 동적바인딩된 Print함수가 있쥬 ?
	//CPlayer playerObject;
	//CWarrior warriorObject;
	//cout << "======================" << endl;
	//cout << sizeof(gameObject) << endl;
	//cout << sizeof(playerObject) << endl;
	//cout << sizeof(warriorObject) << endl;


	return 0;
}

/*
	//동적바인딩을 쓸경우 
	void Damaged(CGameObject *To, CGameObject From);
	//동적바인딩을 쓰지 않을 경우
	void DamagedFromMonster(CPlayer *TO , CMonsyer *From);
	void DamagedFromMonster(CMonsyer *TO , CPlayer *From);


*/