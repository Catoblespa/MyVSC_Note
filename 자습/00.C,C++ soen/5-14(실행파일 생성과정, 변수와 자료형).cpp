/*실행 파일 생성 과정(빌드)
     코드 작성 -> 전처리기 -> 컴파일 ->어셈블러 -> 링크 ->exe파일 생성
     1.코드작성  : 프로그래머가 원시코드를 작성
     2.전처리기  : 프로그래머가 작성한 원시코드가 원활히 번역이 되도록
                컴파일 전에 적절하게 수정 및 보완을 해주는 단계  
     3.컴파일    : 원시코드를 어셈블리어로 번역
     4.어셈블러  : 번역된 어셈블리어를 바이너리(기계어)로 번역     -> 여기까지 거쳐야 obj 파일이 생성됨.
     5.링크      : 번역된 기계어 들을 하나로 묶는 작업
             -> .obj파일과 .lib파일을 하나로 묶어 실행 파일을 만든다.

        전처리기 ?
         '#'으로 시작하는 모든 것들.
        <iostream> : Input Output Stream : C++에서 Console에 대한 입출력 기능을 제공
        #include : 파일을 포함시키는 전처리기 명령어

*/

#include <iostream>             
using namespace std;

int main()
{
	// :: (스코프 연산자 , 네임스페이스 연산자 라고 함)
	std::cout << "asdasd" << endl;

		return 0;
}

//======================================================================================================================
/* 
변수와 자료형 
        변수    : 값을 저장하기 위한 저장 공간 , 값을 재사용하기 위해 사용
                값이 저장된 공ㅇ간에 이름을 붙여주는 역할을 한다.

        자료형 : 어떤 유형의 값인지, 저장공간의 크기는 얼마인지를 결정

        변수의 이름을 정할떄 주의사항
        1. 숫자가 알파벳보다 앞에 나올 수 없다.
        2. 특수문자는 사용하면 안된다 (단, '_'은 허용한다)
        3. 변수 이름에 공백을 포함 할 수 없다. (공백 대신 _를 사용한다)
        4. 시스템에서 기본으로 제공하는 키워드로 변수 이름을 지을 수 없다. intint int namespace

        ※자료형의 종류
                정수타입        실수타입        단일 문자       논리자료형
                int             float          char             bool (참, 거짓)
                short           double         wchar_t          C++부터 사용가능.
                long            long double
                long long        

            1byte   char flaot
            2byte   short   wchar_t
            4byte   int,long,  float
            8byte   long long, doublr,  long double                

        ※unsigned와 signed 의 차이
                unsigned int a; : 양수만 표현한다 (정수 타입에만 사용 할 수 있다.)
                signed int b;   : 양수,음수 모두 표현한다. (int만 사용하면 signed로 인식한다.)      

        ※2의 보수만들기          2진수          
                                1010          
        1의 보수를 취한다.       0101
        1bit을 증가시킨다.       0110          

        즉 부호비트가 1인 음수인 정수 1010의 값을 구할때
        2의 보수를 취한 값을 사용한다.
        1010 -> 0101 -> 0110 -> (-)6                                                                                 
        
        
        ※ 각 자료형의 표현 범위
        unsigned char   : 1byte(8bit) -> 256개의 수 표현        signed char     -> -128 ~ 127
                        -> 0~ 255
        unsigned short  : 2byte(16bit) -> 65536개의 수 표현     signed short    -> -32768 ~ 32767
                        -> 0 ~ 65535 
        unsigend int    : 4byte(32bit) -> 4,294,967,296개의 수  signed int      -> -2,147,483,648  ~ 2,147,483,647
                        ->0 ~ 4,294,967,295
        unsigned long long : 8byte(64bit) -> 18,446,744,073,709,551,616개의 수
                        ->0 ~ 18,446,744,073,709,551,615 

        ※실수의 표현 방식
        -부동 소수점 방식으로 실수를 표현한다.
        -실수는 무조건 signed 이다.
        부동소수점 방식의 구조
                 (32bit : float) : 소수점 7~8자리까지 실수 표현가능
                -1비트의 부호비트   :
                -8비트의 지수부     :소수점의 위치
                -23비트의 가수부.   :값

                (64bit : double) :소수점 15 ~16자리까지 실수 표현가능      
                -1비트의 부호비트
                -11비트의 지수부
                -52비트의 가수부
         => double이 float보다 더 정밀한 수를 나타낼수 있다.


        ※sizeof연산자
        sizeof는 함수가 아니라 연산자다.

        sizeof(char) 은 char형의 크기은 2가 나온다.
        만약 sizeof에 변수가 아닌 상수(5와 같은 정수 또는 문자열, 실수 등) 을 저장 하게 되면 다음을 따른다.
                -정수일 경우 : int로 표현된다. int가 담을 수있는 범위를 벗어날경우 long long에 저장된다. 
                        ->일반적으로 4, int를 넘으면 8
                -실수일 경우 : 기본적으로 double형으로 저장되며 8바이트 , 3.14f 일경우 float로 인식하여 4바이트

*/      
#include <iostream>
using namespace std;

int main()
{
        
        cout <<sizeof(char) <<endl;
        cout <<sizeof(int) <<endl;
        cout <<sizeof(double) <<endl;
        cout <<sizeof(float) <<endl;

        cout << sizeof(5+2) <<endl;
        cout << sizeof(1.55) <<endl;
        cout << sizeof(1.55f) <<endl;
        cout << sizeof("asdasdasd") <<endl;
        return 0;
}

