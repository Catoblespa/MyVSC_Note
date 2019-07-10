#include <iostream>
using namespace std;

/*

	객체 포인터

	숙제 !
	text RPG 상속을 사용해서!

*/


class Dot
{
public:
	virtual void Draw()
	{
		cout << "점" << endl;
	}
};

class Tri : public Dot
{
public:
	void Draw()
	{
		cout << "삼각형" << endl;
	}
};

class Rect :public Dot
{
public :
	void Draw()
	{
		cout << "사각형" << endl;
	}
};



int main()
{
	Tri Tr;
	Rect rect;


	//객체 포인터 특징
	// 부모타입 포인터는 자식객체의 주소를 담을 수 있다.
	Dot* ptr1 = &Tr;
	Dot* ptr2 = &rect;

	
	/*
	dynamic_cast<Tri*>(ptr1)->Draw();
	dynamic_cast<Rect*>(ptr2)->Draw();*/
	ptr2->Draw();


	return 0;
}