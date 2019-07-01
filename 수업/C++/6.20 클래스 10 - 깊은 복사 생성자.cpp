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


/*
	얕은 복사 (Shallow copy)와 깊은 복사(Deep Copy)
*/

class CObj
{
public:
	CObj(const char* pName)
	{
		int iLenght = strlen(pName);
		m_pName = new char[iLenght+1];
		strcpy_s(m_pName, iLenght+1,pName);
		//*m_pName = pName;
	}
	//얕은 복사
	// 실제 복사해야될 대상은 "NeoPeople"이지만
	//단순 주소 번지만 복사하고있다
	//따라서 원본과 사본이 같은 메모리 공간을 바라보고 있기 때문에
	//추후 댕글링 포인터 문제가 발생한다.
	//CObj(const CObj& _Obj)
	//{
	//	m_pName = _Obj.m_pName;
	//}

	//깊은 복사
	CObj(const CObj& _Obj)
	{
		int iLenght = strlen(_Obj.m_pName);
		m_pName = new char[iLenght+1];
		//깊은 복사는 실제 값을 복사한다!!
		strcpy_s(m_pName , iLenght+1, _Obj.m_pName);
	}

	~CObj()
	{
		delete[] m_pName;
		cout << "소멸자" << endl;
	}
public:
	void WhatIsYourName()
	{
		cout << m_pName << endl;
	}

private:
	char* m_pName;
};

int main()
{
	CObj ObjA("NeoPeole");
	ObjA.WhatIsYourName();

	CObj ObjB = ObjA;
	ObjB.WhatIsYourName();

	//Main은 스택이므로 delete는 ObjB -> ObjA 순으로 실행된다
	//얕은 복사의 경우 ObjB.m_pName은 ObjA.m_pName의 'heap주소'를 갖게 되므로,
	//ObjB.m_pName가 할당 해제 되면서 ObjA.mpName이 가르키고 있던 heap이 해제되고 , ObjA.mpName는 댕그리 포인터가 되어버린다.
	//ObjA.m_pName이 할당 해제가 될때 이미 할당해제된 곳을 해제하려고 하니까 런타임 에러가 난다.
}
