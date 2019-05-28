/*
C 언어의 장점 중 하나는 어느 운영체제나 플랫폼으로 쉽게 이식될 수 있는 이식성(Portability)이다. 
유닉스에서 작성한 소스를 윈도우즈로 가져와 컴파일하면 똑같은 동작을 하는 실행 파일을 얻을 수 있다. 
그러나 이 이식성은 어디까지나 소스 차원에서 이식 가능성을 의미하는 것이지 컴파일된 결과인 실행 파일은 그렇지 않다. 
C언어는 이식성이 있지만 C언어를 특정 플랫폼에 맞게 컴파일하여 고유의 실행 파일을 만들어 내는 컴파일러는 본질적으로 플랫폼에 종속적이다.

그래서 각 플랫폼에서 실행되는 컴파일러는 플랫폼의 고유한 기능을 수행하기 위한 지원을 해야 한다. 
플랫폼별로 구조나 기능이 다르기 때문에 구현도 약간씩 달라질 수 있는데 
예를 들어 메모리를 관리하는 방식이나 실행 파일의 특수한 구조로 인한 코드 배치 방법이 플랫폼별로 고유하다.
 #pragma 지시자는 플랫폼별로 다른 이런 기능에 대한 지시 사항을 컴파일러에게 전달하는 방법이다. 
 #문자로 시작하므로 전처리 명령처럼 보이지만 컴파일러 지시자이다. #pragma 지시자의 기본 형식은 다음과 같다.


#pragma 토큰문자열
#pragma 다음에 지시 사항을 전달하는 토큰 문자열이 오는데 이 토큰의 종류는 컴파일러별로 다르다. 플랫폼에 종속적인 기능에 대한 지시자이므로 #pragma 지시자는 컴파일러에 대해서 종속적일 수밖에 없다. 그래서 특정 플랫폼을 위한 프로그램을 작성할 때만 사용해야 하며 꼭 이식성을 유지하려면 조건부 컴파일 지시자와 함께 사용해야 한다. 컴파일러는 #pragma 다음의 토큰을 인식할 수 없을 경우 단순히 무시해 버리며 컴파일은 계속 수행한다. 다음은 비주얼 C++ 6.0의 pragma 토큰들이다.

alloc_text, auto_inline, bss_seg, check_stack, code_seg, comment, component, conform
const_seg, data_seg, deprecated, function, hdrstop, include_alias, init_seg, inline_depth
inline_recursion, intrinsic, managed, message, once, optimize, pack, pointers_to_members
pop_macro, push_macro, runtime_checks, section, setlocale, unmanaged, vtordisp, warning

종류가 굉장히 많고 이 중 몇 가지는 굉장히 어렵고 복잡한 것도 있다. 
우선 가장 이해하기 쉬운 once부터 구경해 보자. 
이 지시자를 헤더 파일 선두에 써 두면 컴파일러는 딱 한 번만 헤더 파일을 포함하여 컴파일 시간을 절약한다.
 다음과 같은 조건부 컴파일 지시자로 한 번만 포함되도록 하는 것과 효과가 동일하다.

#ifndef _SOME_HEADER_FILE
#define _SOME_HEADER_FILE
// 헤더 파일 내용
#endif // _SOME_HEADER_FILE

같은 헤더 파일을 일부러 두 번 포함하지는 않겠지만 헤더 파일끼리 서로 중첩을 하다 보면 원치 않게 두 번 포함되는 경우도 있다. 
헤더 파일에 중복해도 상관없는 선언만 있다면 아무 문제가 없겠지만 중복해서는 안되는 정의가 있는 경우는 
이런 식으로 한 번만 포함하도록 해야 한다.
*/

#pragma once

//C의 헤더 파일 최상단에서 자주 볼 수 있는 이 코드는 컴파일러에게 이 헤더 파일이 한번만 빌드되도록 알려주는 명령입니다.

#pragma warning

/*

once:번호
반복되는 경고를 한 번만 출력한다.

default:번호
원래 설정대로 되돌린다.

disable:번호
경고를 출력하지 않는다.

error:번호
경고를 에러로 처리한다.

레벨:번호
경고의 레벨(1~4)을 변경한다.

push[,n]
모든 경고의 레벨을 저장한다. n이 있을 경우 저장과 동시에 전역 경고 레벨을 n으로 변경한다.

pop
스택에 마지막으로 저장된 경고 레벨을 복원한다.

 

소스의 어느 위치에나 다음 명령을 삽입하면 이후부터 컴파일러가 경고를 통제하는 방법이 바뀐다.

#pragma warning (disable:4101)            // 경고를 무시하도록 한다.
#pragma warning (once:4101)          // 4101경고를 한 번만 출력한다.
#pragma warning (error:4700)               // 경고 대신 에러를 출력한다.
#pragma warning (3:4706)                // 4706번 경고를 레벨 3으로 올린다.


#pragma warning(push)
// 중간에 경고 레벨을 마음대로 바꾼다.
#pragma warning(pop)

 
*/

