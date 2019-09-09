

/*
밉맵

앞서 6.3 섹션에서 언급했듯이 화변의 삼각형은 텍스처 삼각형과는 크기가 다른 것
이 일반적이다. 텍스처의 크기를 급격하게 변경하는 것을 막는 테크닉으로 
텍스처의 밉맵을 만드는 방법이 있는데， 이는 중요하게 생각하는 일을 보존하면서
여러개의 작은 해상도로 텍스처로 만드는 방식이다.
*/

/*

 밉맵 필터
Direct3 가 밉맵을 이용하는 방법을 결정하기 위해 밉맵 필터를 지정할 수 있으며
다음과 같은 코드 형식 을 이용한다. 
*/
Device->SetSamplerState(O , D3DSAMP_MIPFILTER, Filter);

Filter는 다음 옵션 중 하나를 사용한다.
 D3DTEXF_NONE     - 밉맵을 사용하지 않는다
 D3DTEXF_POINT    - 이 필터를 이용하면 Direct3D 는 스크린 삼각형과 가장 비슷한 크기의 밉맵 레벨을 선택한다 
                  일단 레벨이 선택되면 된 min과 mag 태그에 따라 선택된 레벨을 필터링한다
 D3DTEXF_LINEAR   -이 필터를 사용하면 Direct3D 는 가장 비슷한 두 개의 밉맵 레벨에 min과mag 필터에 따른 필터링을 한다
                   즉 선형적으로 조합된 두 개의 레벨을 이용해 최종 픽셀 컬러를 계산해낸다.


/*Direct3D 에서 밉맵 이용하기*/

Direct3D 에서의 밉맵 사용은 매우 간단하다 만약 장치에서 밉맵을 지원 한다면 
D3DXCreateTextureFromFile 을 통해 자동으로 밉맵 체인을 완성할 수 있다.
게다가 Direct3D는 스크린 삼각형에 가장 잘맞는 밉맵을 자동으로 선택해준다. 
즉， 밉맵의 구성과에 필요한 부분의 과정은 자동 으로 처리된다.


/* 어드레스 모드 */

앞서 우리는 텍스처 좌표의 범위가 반드시 [0, 1] 내에 있어야 한다고 이야기 했지만,
이는 기술적으로 정확한 표현은아니며 , 때로는 범위를 넘어설 수 있다.
[0,1]범위를 넘어서는 텍스처 좌표를 처리하는 방법은 Direct3D 어드레스 모드에 의해 정의 된다.
어드레스 모드에는 wrap , border, color, clamp, mirror의 네가지 종류가 있다

//그림은 용첵 176p에서 확인.


같은 크기의 이미지가 3x3개가 배열되어있는 하나의 이미지일 경우
이 사각형에서 네 개의 텍스처 좌표는 각각 (0 ,0) (0,3) (3,0) (3,3)이다.
세 개의 그림에서는 u- 축과 v-축방향으로 각각 3x3영역 매트릭스로
사각형을 나눌 수 있는데 만약 5x5 타일로 사각형을 나누고자 한다면
wrap어드레스 모드로 지정하고 텍스처 좌표로 0,0 0,5 5,0  5,5를 이용하면 된다.

다음 코드는  AddressModes 예제의 일부로 네 개의 어드레스 모드를 지정하는 방법을 보여주고 있다.


// wrap 어드레스 모드로 지정한다.
if(GetAsyncKeyState('W') & Ox8000f )
{
      Device->SetSamplerState(O , D3DSAMP_ADDRESSU , D3DTADDRESS_WRAP) ;
      Device- >SetSamplerState(O , D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP) ;
}

// border color 어드레스 모드로 지정한다.
if(GetAsyncKeyState('B') & Ox8000f )
{
      Device->SetSamplerState(O , D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
      Device- >SetSamplerState(O , D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
      Device- >SetSamplerState(O , D3DSAMP BORDERCOLOR, OxOOOOOOff);
}

// clamp 어드래스 모드로 지정한다.
if(GetAsyncKeyState('C') & Ox8000f )
{
      Device- >SetSamplerState(O , D3DSAMP_ADDRESSU , D3DTADDRESS_CLAMP);
      Device- >SetSamplerState(O , D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP) ; 
}

 // mirror 어드례스 모드로 지정한다.
if(GetAsyncKeyState('M') & Ox8000f )
Device- >SetSamplerState(O, D3DSAMP_ADDRESSU , D3DTADDRESS_MIRROR);
Device->SetSamplerState(O, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR); 
