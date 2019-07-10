
/////////////////////////////////////////////////CBoy.h///////////////////////////////////////////////////////
#pragma once

class CGrirl;


class CBoy
{
	//friend 키워드
	//자신의 private 맴버에 대해 다른 클래스에게 접근 권한을 부여한다.
	friend class CGrirl;

private :
	int m_iWeight = 10;
	int m_iHeight = 183;
public:
	CBoy();
	~CBoy();

	//특정 대상(함수)에게만 friend가능!
	friend void CGrirl::MyBoyfriendInfo(CBoy* pBoy);
};




//////////////////////////////////////////////////CBoy.cpp////////////////////////////////////////////////////////////
#include "CBoy.h"
CBoy::CBoy()
{
}
CBoy::~CBoy()
{
}


/////////////////////////////////////////////////Cgirl.h///////////////////////////////////////////////////////
#pragma once
#include <iostream>
class CBoy;

using namespace std;

class CGrirl
{
	//CTest는 CBoy의 private에 접근권할을 가질 수 없다
	//friend의 friend는 연속되지 않는다!
	//친구의 친구는 내친구 아님!
	friend class CTest;
public:
	CGrirl();
	~CGrirl();

	void MyBoyfriendInfo(CBoy * pBoy);

	void Func(CBoy* pBoy);

	
};




//////////////////////////////////////////////////Cgirl.cpp////////////////////////////////////////////////////////////
#include "CGrirl.h"
#include "CBoy.h"


CGrirl::CGrirl()
{
}


CGrirl::~CGrirl()
{
}

void CGrirl::MyBoyfriendInfo(CBoy* pBoy)
{
	cout << "His Weight : "<< pBoy->m_iWeight << endl;
	cout << "His Height : "<< pBoy->m_iHeight << endl;

}

void CGrirl::Func(CBoy* pBoy)
{
	cout << "His Weight : " << pBoy->m_iWeight << endl;
	cout << "His Height : " << pBoy->m_iHeight << endl;
}


//////////////////////////////////////////////////Main/////////////////////////////////////////////////////////
