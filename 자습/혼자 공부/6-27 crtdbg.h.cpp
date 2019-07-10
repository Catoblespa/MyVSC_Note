#include <crtdbg.h>



void MemoryLeakCheck()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1365);      //누수 라인 중단점
	_CrtDumpMemoryLeaks();			//메모리 누수 출력 (디버그 모드)
}