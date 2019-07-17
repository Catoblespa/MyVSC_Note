API
Application Programming Interface
하드웨어랑   <- 운영체제 -> 응용프로그램 


Win32 API (Windows 32bit)

int APIENTRY WinMain()   = API의 Main함수임  // APIENTRY : 진입점이라는 뜻.


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


cout <<sizeof(wchar_t) <<endl;


//유니코드 계열  char에는 문자열 앞에 L을 붙혀줘야한다.
wchar_t szBuf1[] = L"Hello";
wchar_t szBuf2[] = L"한글";

//멀티바이트에서는 한글 문자열의 정확한 길이가 안나오지만 (1바이트를 1개로 보기 때문에)
//wchar에서는 2바이트로 계산하므로 정확훈 문자의 길이가 나온다.
cout << sizeof(szBuf1)<<endl;

//TCHAR는 프로젝트 속성에 따라  조건부 컴파일에 의해 , char 또는 wchar_t로 바뀐다.
TCHAR szBuf3 = L"ㅎㅇ";	//유니코드 사용시
TCHAR szBuf2 = "하이"; // 싱글바이트 사용시.

TCHAR szBuf4 = _T("하이Hello"); //_T매크로를 TCHAR과 같이 사용하면 멀티,싱글 어디서든 호환된다. _T도 조건부 컴파일링 되어있다.
//학원 프로젝트에서는 TCHAR szBuf3 = L"ㅎㅇ"; 을 사용하도록하자.


//API에서는 char이나 wchar_t를 쓰지않고 TCHAR는을 사용하도록 한다.
