DirectX3D 에서는 IDirect3DTexture9 인터페이스로 텍스처를 표현한다.
텍스쳐는 픽셀의 메트릭스이며 표면과 비슷하지만 삼각형에 입힐 수 있다.




Direct3 는 수평으로 진행하는 축과 수직으로 진행하는 v-축으로 구성된 텍스처 좌표 시스템 을 이용한다. 
u, v 좌표 시스템은 텍셀이라 는 텍스처의 요소를 표현하는데 사용되 데,
v- 축은 아래쪽이 양의 방향이라는 것에 주의하자. 


 u,v
(0,0)                   (1,0)
  -----------------------
 ㅣ                     ㅣ
 ㅣ                     ㅣ
 ㅣ                     ㅣ
 ㅣ       Texture       ㅣ
 ㅣ                     ㅣ
 ㅣ                     ㅣ
 ㅣ                     ㅣ
  -----------------------
  (0,1)                 (1,1)

//FVF 내용은 다음과 같다.
 Vertex::FVF = D3DFVF XYZ | D3DFVF NORMAL | D3DFVF_TEX1; 
//버텍스 포맷 기술에 D3DFVF_TEX1 을 추가하여 버텍스 구조체에 한 쌍의 텍스처 좌표가 포함되어 있음을 지정하였다.

/*
대응되는 텍스처 삼각형을 3D 삼각형으로 지정하기는 했지만 3D 삼각형을 스크런 스페이스로
변환하는 래스터라이즈 단계 전까지는 텍스처가 입혀지지 않는다. 
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
텍스처의 작성과 활성화.
텍스처는 일반적으로 디스크에서 읽어온 후 IDirect3DTexture9 객체로 로드 된다.
이작업을 위해 다음 과 같은 함수가 사용된다.

HRESULT D3DXCreateTextureFromFile(
  LPDIRECT3DDEVICE9 pDevice ,   // 텍스처를 만들어낼 장치
  LPCSTR pSrcFile ,             // 이미지를 읽어틀일 파일명
  LPDIRECT3DTEXTURE9* ppTexture // 만들어진 텍스처를 받을 포인터 
)

이 함수는 BMP, DDS, DIB,JPG, PNG, TGA 등의 이미지 파일 포맷을 읽어들일 수 있다.
이함수는 다음과 같이 작성하면 된다.

IDirect3Dtexture9* stonewall;
D3DXCreateTextureFromFile(_device , "stonewall.bmp " , &_stonewall); 


현재 텍스처를 지정하는 방법은 다음과 같다.
HRESULT IDirect3DDevice9::SetTexture(
DWORD Stage ,                   // 0- 7 범위의 값으로 텍스처를 지정한다 .
                                // stage 이어지는 노트를 참고한다.
IDirect3DBaseTexture9* pTexture // 지정할 텍스처의 포인터
);

예제 ) Device->SetTexture(O, stonewall);

/*
Direct3D에서는 8개까지의 텍스처를 결합하여 좀더 자세한 이미지를 만들어낼 수 있다 이와 같은 테크닉을 멀티텍스처링이라 한다. 
이 책에서는 파트 IV 전까지 멀티 텍스처링을 이용하지 않을 것이므로 현재로서는 이 값에 항상 0을 넣는다. 
*/


특정한 텍스처링 상태에 텍스처 를 이용하지 않고자 한다면 pTexture 를 로 지정한다. 
예를 들어， 물체에 텍스처를 입히지 않고자 한다면 다음과 같은 코드를 이용한다.
Device->SetTexture(O, 0);
renderObjectWithoutTexture() ;


만약 장면 내에 서로 다른 텍스처를 이용하는 삼각형이 있다면 다음과 비슷한 코드구조를 이용해야 한다. 

Device- >SetTexture(O , texO) ;
drawTrisUsingTexO();


Device- >SetTexture(O , texl) ;
drawTrisUsingTexl(); 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






