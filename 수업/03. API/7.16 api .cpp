// FrameWock99C.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "FrameWock99C.h"
#include "Defined.h"

#define MAX_LOADSTRING 100


#define WINCX 800			//윈도우 크기 조정
#define WINCY 600			//윈도우 크기 조정



RECT rc = { 100, 100, 150, 150 };
Player player(rc);



// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


//wWinMain Win32의 Main함수
//H(Handle)	: 대상마다 부여된 고유 식별 번호
//핸들끼리 중볻된 값을 가질 수 없다.
//정수 형태를 취한다.
//운영체제가 부여한다.

//INSTANCE	: 메모리에 등록된 실체 (변수 , 객체, 실행중인 프로그램)
//HINSTANCE : 프로그램의 핸들
//hPrevInstance : 이전에 실행된 프로그램의 핸들
//LPWSTR lpCmdLine	: 실행과 동시에 명령어를 전달할 char*형 (Main함수에 인자로 전달될 문자열)
//nCmdShow			:디폴트 윈도우를 어캐할건지.. 처음 켯을때 창모드 ? 전체화면 ?

//LPWSTR의 뜻
//LP = Pointer
//W = WBCS

//CBCS : Single Byte Character Set
//단일 문자를 사용할 때 1바이트를 사용한다.
//char  아스키코드.

//MBCS : Multi Byte Character Set
//char를 사용하지만 때에 따라 1바이트 혹은 2바이트를 사용한다.	

//WBCS : Wide Byte Character Set
//단일 문자를 사용할 때 2바이트를 사용한다
//wchar_t 유니코드


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRAMEWOCK99C, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRAMEWOCK99C));

    MSG msg;
	/*typedef struct tagMSG {
    HWND        hwnd;		//메시지가 전달될 hwnd
    UINT        message;	//메시지 내용
    WPARAM      wParam;		//키보드 내용
    LPARAM      lParam;		//마우스 내용
    DWORD       time;		//메시지 발생 시각	(DWORD : us long 타입)
    POINT       pt;			//마우스 좌표
	}MSG*/

    // 기본 메시지 루프입니다.
	//GetMessage 함수 : 운영체제가 갖고있는 메시지 큐에서 메시지를 얻어오는 함수.
	//msg가 WM_QUIT(종료 메시지)를 얻어오면 FALSE반환 나머지 TRUE 반환.
	//만약에 메시지큐에 얻어올 메시지가 없다면.
	//해당 응용프로그램은 다음 메시지가 발생 될때까지 대기 상태 돌입.

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;									// 수직, 수평 크기가 변화하게 되면 다시 그려지는 창을 그리겠다.
    wcex.lpfnWndProc    = WndProc;													// 어떤 메시지 이벤트가 발생했을 경우 WndProc 호출	(콜백함수)										
    wcex.cbClsExtra     = 0;														
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRAMEWOCK99C));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);							//IDC_ARROW 커서 사용 나중에 텍스쳐로 바꿀거라 딱히 쓸일 없음.
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= nullptr;//MAKEINTRESOURCEW(IDC_FRAMEWOCK99C);				//nullptr을 넣으면 상단 메뉴가 사라진다.
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	RECT rc = { 0,0 ,WINCX ,WINCY };
	//순수 클라이언트 영역의 크기를 조정하는 함수.
	//원하는 클라이언트 영역의 크기를 RECT에 담고 전달하면
	//전달한 클라이언트 크기가 반영된 전체 윈도우 크기를 다시 RECT에 반환한다.
		//중단점 걸어서 확인해보면 rc값이 변경되는걸 볼수있음 ㅇㅇ
		//이제 이걸 CreateWindowW 에 인자로 넣자
	AdjustWindowRect(&rc , WS_OVERLAPPEDWINDOW,false);



   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //CreateWindowW() 실질적으로 window를 만드는 함수. 고유의 HWND(핸들 윈도우) 를 반환한다.
   // 단 하나의 인스턴스가 여러개의 HWND를 가질수 있다. vs를 예를 들면 솔루션탐색기, 도구 , 속성 등 모두 HWND가 따로 있다
   //szWindowClass 윈도우 정보
   //szTitle : 타이틀 이름 string 
   //WS_OVERLAPPEDWINDOW window의 프레임 정보. 타이틀바를 갖고.. 프레임을 갖고.. X버튼을 갖고.. 등등..WS_OVERLAPPEDWINDOW는 가장 보편적인 모양
   //CW_USEDEFAULT, 0, CW_USEDEFAULT, 0  : x , y 위치에 w,h 크기의 윈도우로 생성함.		CW_USEDEFAULT는 걍 대충 적절한곳에 생성해줌
  
   //nullptr, nullptr, hInstance, nullptr);
   //첫번째 nullptr은 현재 만든 창이 부모창이면, nullptr자리에 부모창의 HWND를 넘겨줘야함.
   //두번째거는 메뉴 핸들인데, nullptr이면 이전에 쓰던 핸들을 그래도 쓴다는 뜻
   //hInstance 현재 만들어지는 창의 주인이 hInstance라는뜻.
   //마지막은 몰라두 됨.
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, rc.right-rc.left, rc.bottom- rc.top, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)		//초기화 실패
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}




//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
//  #define  CALLBACK	__stdcall __stdcall함수 호출규약을 갖는 함수이다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//함수 호출 규약.
	//함수가 종료 될때 Stack이 반환되는데 이 Stack을 누가 정리할 것이냐에 대한 약속
	// __cdecl, __stdcall, tastcall , thiscall

	//__cdecl : C언어의 대표적인 호출 규약.  가변인자함수(printf, scanf 등)이 사용
		// - 호출자(caller)가 Stack을 정리함.

	//__stdcall : API의 대표적인 호출규약  고정인자함수.			 tastcall , thiscall도 고정인자함수로 , 피호출자가 stack을 정리한다.
		// - 피호출자(callee)가 Stack을 정리한다.

	//fastcall : 3개 이상의 인자를 가질경우 2개의 인자를 바로 레지스터에 올려버린다.
	//thiscall : 맴버함수 호출 규약 this포인터를 사용하여 맴버함수를 호출한다.


	/*

		void A()			//호출자
		{
			B(a, b, c);		//피호출자		//B함수가 가변인자일경우 B는 자신이 몇개의 인자가 들어올지 알 수 없기때문에 호출자가 Stack을 정리한다.
		}									//B함수가 고정인자일 경우 B는 스스로 인자가 무엇인지 인지하기 때문에 피호출자가 스스로 Stack을 정리한다.


		만약 B함수가 B가변인자,
		A함수가 고정인자 함수일경우! 컴파일후 코드는 이런식이 된다.
		
		void A()			//호출자
		{
			B(a, b, c);		//피호출자	
			-B함수 stack 정리 코드-		//B가 __edecl이므로 stack을 A에서 정리 된다.


			-A함수 stack 정리 코드-		//Ar가 __stdcall이므로 stack을 A안에서 정리한다.
		}								
	*/
	static RECT rc = { 20,20,40,40 };
    switch (message)
    {		//WM : window message
	case WM_CREATE:		//윈도우 생성시 발생하는메시지. (초기화 메시지) 여기서 초기화 코드 들어가면 됨.
		//타이머를 생성하는 함수.
		//SetTimer(윈도우 핸들, 타이머의 ID(사용자부여), 타이머 발생 주기(ms = 1000 -> 1초)  디폴트 1, 함수포인터);
		//마지막인자에 nullptr을 전달하게 되면 설정한 주기대로 WM_TIMER 메시지가 발생.
		SetTimer(hWnd,0,10,nullptr);
		break;

	case WM_TIMER:

		for (auto& i : Object::ObjVector)
		{
			i->Update();
		}
		//윈도우 그리기 갱신.
		//InvalidateRect(윈도우 핸들, 윈도우 전체,true면 지우고 다시그리고, false면 그냥 위에 그려버림.);
		InvalidateRect(hWnd, nullptr,true);
		break;

	case WM_KEYDOWN:	//키가 눌렸다!?

		switch (wParam)	//wParam값이 ~면 ?
		{
		case VK_DOWN:
			player.PlayerPosMove(DOWN);
			break;
		case VK_UP:
			player.PlayerPosMove(UP);
			break;
		case VK_LEFT:
			player.PlayerPosMove(LEFT);
			break;
		case VK_RIGHT:
			player.PlayerPosMove(RIGHT);
			break;
		case VK_SPACE:
			player.Shot();
			break;
		case VK_ESCAPE:	//esc키값이면 ?
			DestroyWindow(hWnd);	//윈도우파괴 WM_DESTROY가 발생됨.
			break;
		}
		break;
    case WM_PAINT:		//윈도우를 그릴때 발생되는 메시지
        {
            PAINTSTRUCT ps;

			//DC : Device Context  장치 문맥 ? 맥락 ?
			//그래픽 출력에 필요한 데이터들을 저장하는 공간.
			//HDC : DC의 핸들
			//DC는 GDI(Graphic Device Interface)에서 관리한다.
			//GDI에서는 그리기에 필요한 각종함수들이나 자료형을 제공한다.
            HDC hdc = BeginPaint(hWnd, &ps);

			//static Player p(hdc, message);
			////MoveTo
			////커서 포인트(CP)를 이동시키는 함수.
			////마지막인자는 LPPOINT (POINT구조체의 포인터) 이동하기이전의 커서 포인터의 위치를 받아올 수 있다.
			//MoveToEx(hdc, 200, 200,nullptr);	
			////LineTo
			////현재 CP위치로부터 xy지점까지 선을 그리는 함수.
			//LineTo(hdc, 300, 200);
			//LineTo(hdc, 300, 300);
			//LineTo(hdc, 200, 300);
			//LineTo(hdc, 200, 200);

			////사각형을 그리는 함수
			//Rectangle(hdc, 10, 10, 250, 250);
			//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
			//Ellipse(hdc, 0, 0, WINCX, WINCY);

			//player.Renderer(hdc);


			for (auto& i : Object::ObjVector)
			{
				i->Renderer(hdc);
			}

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:			//윈도우가 파괴될 때 발생하는 메시지.
        PostQuitMessage(0);
		KillTimer(hWnd,0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}