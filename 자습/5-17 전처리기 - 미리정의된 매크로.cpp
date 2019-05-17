#include <iostream>
#include <Windows.h>
using namespace std;

/*
__DATE__
컴파일될 때의 날짜를 나타내는 문자열이다.

__TIME__
현재 소스가 최후 컴파일된 시간을 나타내는 문자열이다.
_
__TIMESTAMP__
현재 소스가 최후로 수정된 날짜와 시간을 나타낸다.

__FILE__
현재 소스 파일의 완전 경로이다.

__LINE__
이 매크로가 포함된 소스상의 줄 번호이다. 10진 정수이다.

__STDC__
컴파일러가 ANSI C 표준을 따를 경우 1로 정의되며 그렇지 않을 경우 정의되지 않는다. C++로 컴파일할 때는 이 매크로가 없다.





_DEBUG
디버그 모드로 컴파일중일 때만 정의된다.

__cplusplus
C++ 모드로 컴파일중일 때만 정의된다.

_DLL
DLL 프로젝트일 때만 정의된다.

_MSC_VER
비주얼 C++의 컴파일러 버전을 나타낸다. 6.0은 1200으로 정의되며 7.0(닷넷)은 1300으로 정의된다.

_MFC_VER
MFC 라이브러리의 버전값

_ATL_VER
ATL의 버전값

_WIN32
Win32 환경일 때 정의된다.

_WIN64
Win64 환경일 때 정의된다.

__COUNTER__
참조될 때마다 1씩 증가하는 정수값이다. 유일한 이름을 만들고자 할 때 이 매크로를 사용한다. 7.0 이상에서만 제공된다.

_M_ALPHA, _M_IX86, _M_IA64, _M_MPPC
CPU의 종류이다. 플랫폼에 따라 약간씩 코드가 달려져야 할 때 이 매크로를 참조한다.


*/





int main()
{
     printf("오늘은 %s이고  최후 컴파일된 시간은 %s입니다.\n", __DATE__, __TIME__);
     printf("이 파일이 최종 수정된 시간은 %s입니다.\n", __TIMESTAMP__);
     printf("이 파일은 %s이고 이 줄은 %d입니다.\n",__FILE__, __LINE__);

#ifdef __STDC__
     printf("이 컴파일러는 ANSI C표준을 따릅니다.\n");
#else
     printf("이 컴파일러는 ANSI C표준의 확장(C++)입니다.\n");
#endif

	return 0;
}