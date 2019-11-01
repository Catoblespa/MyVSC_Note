/*
c++에서 string 클래스의 사용법 정리
*/

#include <string.h>

/* string 문자열에 문자열 추가하기*/
//방법1: += 연산자 이용
string base = "hello world!";
base += "x";
//방법2: append() 멤버 함수 이용
string base = "hello world!";
base.append("appended!");


//string의 길이 구하기
// lenghh()함수와 size()함수는 이름만 다를뿐 같은 기능을 하는 함수.
string base = "hello world!";
 base.length();
  base.size();


/*메모리에 관하여 
capacity()는 해당 문자열이 재할당을 하지 않고도 저장할 수 있는 문자열의 길이를 반환한다. 
문자열은 문자열이 늘어났을 때, 현재 capacity보다 클 경우 더 큰 메모리를 사용할 수 있도록 재할당된다.
*/
string base = "hello world!";
base.capacity();

max_size()
string base = "hello world!";
base.max_size();
myString.max_size()는 최대한 메모리를 할당했을 경우, 저장할 수 있는 문자열의 길이를 반환한다.

