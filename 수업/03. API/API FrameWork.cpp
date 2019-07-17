// FrameWock99C.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "FrameWock99C.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
    switch (message)
    {		//WM : window message

	case WM_KEYDOWN:	//키가 눌렸다!?

		switch (wParam)	//wParam값이 ~면 ?
		{
		case VK_ESCAPE:	//esc키값이면 ?
			DestroyWindow(hWnd);	//윈도우파괴 WM_DESTROY가 발생됨.
			break;
		}
		break;


    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
