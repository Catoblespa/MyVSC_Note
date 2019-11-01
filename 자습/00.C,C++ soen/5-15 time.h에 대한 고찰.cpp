
// 난수 생성시 유용함.

#include <iostream>
#include <time.h>

using namespace std;

// 
int main()
{

	//time_t time(time_t* timer);			time 함수 선언원형
	//char* ctime(const time_t* timer);		ctime 함수 선언원형

	time_t now;
	cout << time(&now) << endl;		// time(&now) 함수가 조사하는 시간은 초단위로 구하기 떄문에 일상적으로 사용하는 시간을
									//구하기는 힘들다.

	/*ctime이 변환 결과를 저장하기 위해 사용하는 버퍼는 라이브러리에서 미리 할당해 놓은 정적 메모리 영역이며 
	이 영역은 asctime, gmtime, localtime 등의 함수들이 공유한다. 
	따라서 상기 함수 중 하나를 호출하면 다른 함수가 작성한 문자열은 파괴되므로 변환한 문자열을 계속 사용하려면 사본을 복사해 두어야 한다*/
	time_t now2;
	char buf[256];							// ctime_s에서 now2로 추출한 현재 시간을 buf에 저장하기 위해 선언
	time(&now2);							// now2에 현재 시간 초를 담는다.
	ctime_s(buf, sizeof(buf), &now2);		//초단위로 표현된 now2를 현실세계의 시간으로 치환하여 buf에 담는다.
	cout <<"현재 시간 :"<< buf << endl;	

	//==========================================================================================================================[

	// 현재시간을 날짜별, 시간별로 담는 법
	char Date[10];
	char Time[10];
	char buf_date[256];
	char buf_time[256];
	_strdate_s(buf_date, sizeof(buf_date));
	_strtime_s(buf_time, sizeof(buf_time));
	cout << "날짜 :" << buf_date << "시간 :" << buf_time << endl;
	return 0;
}

