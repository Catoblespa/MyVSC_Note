
/*추상 팩토리 패턴 */
/*
    오브젝트를 생성할때 공통된 요소를 모아서 캡슐화한 디자인 패턴

 */
#pragma once
class CGameObject
{
public:
	virtual void Initialize()
	{

	};

};

template<typename T>
class CAbstractFactory
{
public:
	static CGameObject* CreateObject()
	{
		CGameObject * pInstance = new T;
		pInstance->Initialize();

		return pInstance;
	}
};

//////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "AbstractFactory.h"

class Player :public CGameObject
{
public: 
	virtual	void Initialize()
	{

	}
};

int main()
{

	CGameObject * p = CAbstractFactory<Player>::CreateObject();

    return 0;
}

