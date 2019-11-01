// ConsoleApplication2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <memory>

class Object
{
private:
	static int count;

public:
	Object()
	{
		count++;
		ID = count;
	};
	int ID;
	virtual void Rend()
	{
		cout << ID << endl;
	}
};
int Object::count = 0;
class Block :public Object
{
public:
	virtual void Rend()
	{
		cout << ID * 100 << endl;
	}
};


void PrintBlock(shared_ptr<Block> pblc, size_t A)
{
	for (size_t i = 0; i < A; i++)
	{
		pblc->Rend();
	}
}

int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1365);      //누수 라인 중단점
	_CrtDumpMemoryLeaks();			//메모리 누수 출력 (디버그 모드)
	vector<auto_ptr<Object>> ptV;


	//auto_ptr<Object> obj1 = new Object라고 가정하자
	//만약 auto_ptr<object> obj2 =obj1 ;가 실행될때
	//새로 생성된 object 의 삭제권한이 obj2로 이항되면서 , obj1은 null을 가르키게 된다
	//그이유는 object에 대해서 소멸자가 두번 실행되면 안되기 때문!


	// 스마트 포인터들은 객체를 소멸시킬때 delete연산을한다.
	// 여기서 주의할점은 스마트포인터를 사용할때 배열을 사용할 때다.
	// auto_ptr 이나 shared_ptr은 배열에 대한 동작을 지원하지 않는다는 뜻이다.
	// 대부분 배열을 사용할 때는 , vector나 부스트라이브러리의 Array, shared_Array를 사용하면 사용할 수는 있다.





	// 수동으로 pop하면 자동으로 소멸자가 호출되어 delete된다.. 
	//그러나 다른 참조 아래의 for_each, rfor 등등.. 이 오게 되면 값을유지안하고 NULL이 된다..
	ptV.push_back(auto_ptr<Object>(new Object));
	ptV.push_back(auto_ptr<Object>(new Object));
	ptV.push_back(auto_ptr<Object>(new Object));
	ptV.push_back(auto_ptr<Object>(new Block));
	ptV.push_back(auto_ptr<Object>(new Block));
	ptV.push_back(auto_ptr<Object>(new Block));



	//for_each(ptV.begin(), ptV.end(), [](auto_ptr<Object> a)
	//{
	//	a->Rend();
	//});
	//cout << "=================" << endl;

	//for (auto& i : ptV)
	//{
	//	i->Rend();
	//}

	//cout << "======================" << endl;
	//auto begin = ptV.begin();
	//auto end = ptV.end();
	//for (; begin != end; ++begin)
	//{
	//	(*begin)->Rend();
	//}

	while (true)
	{
		if (ptV.empty())
			break;
		ptV.pop_back();
	}



	cout << "shard_ptr" << endl;


	//vector<auto_ptr<Object>> ptV;
	vector<shared_ptr<Object>> sV;
	//shard_ptr은 컨테이너에 대해 중복 참조를 허용한다.
	//std::shared_ptr는 이름처럼 가리키는 객체의 소유권을 다른 포인터들과 공유할 수 있는 포인터다. 
	//std::unique_ptr과는 다르게 복사도 마음껏 할 수 있다. 같은 객체를 가리키는 std::shared_ptr은 레퍼런스 카운팅으로 추적된다. 
	//참조된 횟수를 세는 것이므로 포인터가 복사될 때 마다 1씩 증가한다. 
	//그리고 해제될 때 마다 1씩 감소한다. 
	//포인터가 가리키는 객체의 메모리가 해제되는 시점은 레퍼런스 카운트가 0이 될 때이다. 
	//레퍼런스 카운트는 use_count() 멤버 함수로 가져올 수 있다.

	sV.push_back(shared_ptr<Object>(new Object));
	sV.push_back(shared_ptr<Object>(new Object));
	sV.push_back(shared_ptr<Object>(new Object));
	sV.push_back(shared_ptr<Object>(new Block));
	sV.push_back(shared_ptr<Object>(new Block));
	sV.push_back(shared_ptr<Object>(new Block));


	cout << "sv.back()의 use_count() : " << sV.back().use_count() << endl;

	for (auto& i : sV)	// 쌉가능
	{
		i->Rend();
	}

	cout << "shared_ptr<Object> A = sV.back()" << endl;
	shared_ptr<Object> A = sV.back();
	cout << "A.use_count() :" << A.use_count() << endl;


	//get 함수.
	A->Rend();	// shared_ptr<Object>객체에서 ->Rend를하는거
	A.get()->Rend();  //Object->Rend(); 이다.

	//Object * B = A;		//Error 다 A는 object객체가 아니라 shared_ptr<Object> 객체이기 때문이지
	Object * B = A.get();	//shared_ptr가 들고있는 원본의 포인터를 get함수를 통해 반환할 수있다.

	cout << sV.back().use_count() << endl;
	cout << A.use_count() << endl;
	// get 함수로 원본 포인터를 반환받아 값을 저장할경우 count가 올라가지 않는다.
	// shared_ptr의 count가 0이 되어 힙데이터에서 delete되면 B는 댕글링 포인터가 되어버린다.


	// shard_ptr을 인자로 받는 함수를 사용할경우 주의점
	// 스마트포인터를 함수의인자로 전달할때는 인자에서 생성하지말아라
	
	//PrintBlock(new Block, 10);		//PrintBlock은 첫번째 인자타입이 shared_ptr<Block>타입이기 때문에 컴파일에러!
	PrintBlock(shared_ptr<Block>(new Block), 10);	//가능은하지만..
		//컴파일러가 해당 라인을 실행할는 순서가 달라질 수 도 있다.
		
		/*
			우리가 생각하기에는 .. 
			1.PrintBlock 호출
			2. shared_ptr<Block> 생성자 호출
			3. new Block 실행

			일거 같지만

			실제로는
			1. new Block 실행
			2.PrintBLock 호출
			3.shared_ptr<Block> 생성자 호출
			
			일수도 있다는말이다..
			이럴경우 2번째인 PrintBlock의 실행에서 예외가 발생했을때 어떻게 되겠는가?
			new Block으로 만들어진 포인터가 유실되는 결과를 가져온다! 메모리 누수가 일어난다는 뜻이다
			왜나혀면 shared_ptr에 저장되기도 전에 PrintBlock이 예외를 발생시켰으니까 !

			이를 해결하는 방법은 PrintBlock을 호출하기전에 미리 shared_ptr에 담아두는 방법이다.
		*/

	shared_ptr<Block> spBlock(new Block);

	PrintBlock(spBlock, 10);

	//정리하자면 new로 생성한 객체를 스마트포인터로 넣는 코드는	별도의 한 문장으로 만들자
	//이게 안되어있음연 PrintBlock이 예외를 발생시켰을때 디버깅하기 힘든 자원누수를 만들수도 있다..

	return 0;
}
