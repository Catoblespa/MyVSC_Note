
/*

 환경광(Ambienl Light) - 환경광은 다른 표면에 반사되어 전반적인 장면을 밝게 하는 을 모델링한
다 예를 들어 물체의 일부분은 광원의 직접적인 시야에서 가려져 있더라도 약간의 빛을 받는다 이런
부분은 다른 표면에서 반사된 빛을 받는 것이다 환경광은 이와 같이 반사된 빛을 비교적 저렴하고 간단
게 구현하는 방법이다


 난반사광(Diffuse Light) 난반사광은 특정한 방향으로 진행하며 ， 표면에 닿으면 모든 방향으로 동일
하게 반사된다 모든 방향으로 동일하게 반사되므로 위치와는 관계없이 관칠자의 눈에 이 도달하고
관칠자의 위치를 고려할 요가 없다 즉， 난반사광의 방정 식에는 빛의 방향과 표면의 형태만을 고려하
면 된다， 난반사광은 광원에서 발산되는 가장 일반적인 빛이다 


믿 정반사광 (Specular Li ght) - 정반사광은 특정한 방향으로 진행하며 , 표면에 닿으면 한 방향으로 강하게
반사하여 특정한 각도에서만 관찰할 수 있다 한 방향으로만 빛을 반사하기 때문에 정반사광의 방정식
에는 빛의 방향과 표면의 형태 그리고 관찰자의 시점을 모두 고려해야 한다 정반사광은 반짝이는 표면
에 빛이 반사하는 효과를 모델링하는 데 이용된다

*/


정반사광은 다른 타입의 빛에 비해 더 많은 계산을 필요로 하기 때문에 Direct3D는 이를 끌 수 있는 옵션을 공한다.
실제로 이 옵션은 폴트로 꺼져 있으며， 
정반사광을 활성화하기 위해서는 D3DRS SPECULARENABLE 렌더 상태 를 설정해야 한다 


//정반사광을 켜는 함수
Device->SetRenderState(D3DRS_SPECULARENABLE, true) ; 


각각의 빛의 형은 빛의 컬러를 표현하는 D3DXCOLOR나 03 DCOLORVALUE 구조체로
나타낼 수 있다. 음은 몇 가지 빛의 컬러 예이다 

D3DXCOLOR redAmbient(1.0f, 0.0f, 0.0f, 1.0f) ;
D3DXCOLOR blueDiffuse(0.0f, 0.0f, 1.0f, 1.0f) ;
D3DXCOLOR whiteSpecular(1.0f, 1.0f,1.0f, 1.0f) ; 

//////////////////////////////////////////////////////////////////////////////////////////////////////////
SetRenderState()

- 렌더링 상태( RenderState )를 설정하는 함수이다.

 

HRESULT  IDirect3DDevice9::SetRenderState(

     D3DRENDERSTATETYPE    State,              //< D3DRENDERSTATETYPE 열거형 멤버

     DWORD                            Value,             //< state에 의한 결정

);

 

D3DRENDERSTATETYPE 열거형 멤버

 

 

D3DRS_ZENABLE

- z버퍼를 유효하게 하라면, D3DZB_TRUE, 

- w버퍼를 유효하게 하려면 D3DZB_USEW, 깊이 버퍼링을 무효하게 하려면 D3DZB_FALSE를 쓴다.

- D3DZB_TRUE는 EnableAutoDepthStencil멤버를 TRUE로 설정하고, 스텐실이 스왑체인과 함꼐 생성되도록 한다.

- D3DZB_FALSE는 EnableAutoDepthStencil멤버를 FALSE로 설정하고, 스텐실을 생성되지 않게 한다.

 

 

D3DRS_FILLMODE

- D3DFILL_POINT : 점으로 채운다. 즉 점을 그린다.

- D3DFILL_WIREFRAME : WIREFRAME으로 채운다. WIREFRAME으로 그린다.

- D3DFILL_SOLID : 면을 채운다. 면으로 그린다.

 

 

D3DRS_SHADEMODE

- D3DSHADE_FLAT : 플랫 쉐이딩 모드( Flat Shading Mode ), 보간되지 않는 색이 삼각형 전체에 적용된다.

- D3DSHADE_GOURAUD : 고러드 쉐이딩 모드( Gouraud Shading Mode )

                                     표면의 색성분과 스펙큘러 성분은, 삼각형의 3개의 정점간의 보간에 의해 결정된다.

- D3D_PHONG : 퐁 쉐이딩 모드( Phong Shading Mode ), 고러드 쉐이딩 보다 정점간의 보간이 더욱 잘된 것

 

 

D3DRS_ZWRITTENABLE

- APP에 의한 깊이 버퍼에 쓰기를 유효하게 하려면 TRUE로 설정하여, 시스템이 새로운 깊이 값으로의 깊이 버퍼 갱신을 막을 수 있다.

 

 

D3DRS_ALPHATESTENABLE

- 픽셀마다 알파 테스트를 유효하게 하려면 TRUE로 설정

-  테스트가 성공하게 되면 픽셍이 frame buffer에 의해 처리되고, 실패하면 그 픽셀의 모든 frame buffer 처리는 스킵한다.

- D3DRS_ALPHAFUNC 렌더링 스테이트에서 제공되는 비교함수를 사용하여 들어오는 알파값을 기준 알파값과 비교해 테스트를 실시한다.

 

※ 기준 알파값 : D3DRS_ALPHAREF의 설정값에 의해 결정된다.

 

D3DRS_ZFUNC

- 픽셀의 깊이 값을 깊이 버퍼의 값과 비교한다.

- 픽셀의 깊이 값이 비교함수로 허가되면 픽셀이 출력된다.

- 깊이 값이 깊이 버퍼에 출력되는 것은, RenderState가 TRUE일 경우이다.

즉, 픽셀 렌더링 처리를 실시하지 않는 경우에는 텍스처를 필터 처리하거나 곱셈 할 필요가 없기 때문에 깊이 테스트에 실패하는 쪽이 

소프트웨어에 의한 레스터화나 하드웨어 가속 처리는 빨라진다.

 

 

D3DRS_SRCBLEND

- D3DBLEND_ZERO : ( 0, 0, 0, 0 )

- D3DBLEND_ONE : ( 1, 1, 1, 1 ) - Default값

- D3DBLEND_SRCCOLOR : ( R, G, B, A )

- D3DBLEND_INVSRCCOLOR : ( 1-R, 1-G, 1-B, 1-A )

- D3DBLEND_SRCALPHA : ( A, A, A, A )

- D3DBLEND_INVSRCALPHA : ( 1-A, 1-A, 1-A, 1-A )

- D3DBLEND_DESTALPHA : ( A, A, A, A )

- D3DBLEND_INVDESTALPHA : ( 1-A, 1-A, 1-A, 1-A )

- D3DBLEND_DESTCOLOR : ( R, G, B, A )

- D3DBLEND_INVDESTCOLOR : ( 1-R, 1-G, 1-B, 1-A )

- D3DBLEND_SRCALPHASAT : ( f, f, f, 1 ), f = min( A, 1-A )

- D3DBLEND_BOTHINVSRCALPHA

- D3DRS_SRCBLEND rendering state에 대해서만 지원 된다.

 

 

D3DBLEND_BLENDFACTOR

- frame buffer 블랜더가 사용하는 정수 컬러 혼합 계수

- D3DPBLEND_BLENDFACTOR 가 on인 경우에만 지원된다.

 

 

D3DBLEND_INVBLENDFACTOR

- frame buffer 블랜더가 사용하는 정수 컬러 혼합 계수의 보수

- D3DCAPS9의 SrcBlendCaps 멤버에 D3DPBLEND_BLENDFACTOR 비트가 설정되어있는 경우만, blend factor가 지원 된다.

 

 

D3DRS_DESTBLEND

- D3DBLEND_ZERO가 디폴트 값이다.

 

 

D3DRS_ALPHAREF

- 알파 테스트가 유효하게 설정 되어 있는 경우에, 픽셀 테스트를 하기 위한 기준 알파값을 기정하는 값

 

 

D3DRS_ALPHAFUNC

- D3DCMPFUNC의 멤버

- 디폴트 값으로 D3DCMP_ALWAYS 이고, 수락 또는 알파값을 기반으로 픽셀을 거부하는 응용프로그램을 가능하게 한다.

 

 

D3DRS_CULLMODE

- 컬링 하는 경우에 방법을 지정

- 디폴트는 D3DCULL_CCW로 되어있다.

- D3DCULL_NONE, D3DCULL_CW, D3DCULL_CCW가 있다.

 

 

D3DRS_LASTPIXEL

- 디폴트로 true를 가지며, 라인 상의 마지막 점 그리기를 가능하게 한다.

 

 

D3DRS_DITHERENABLE

- 디폴트로 FALSE를 가지며, 일종의 색 혼합법이다.

 

 

D3DRS_ALPHABLENDENABLE

- Alpha Blend( 혼합 ) Type은 D3DRS_SRCBLEND와 D3DRS_DESTBLEND 의 렌더링 상태에 의해 결정된다.

 

 

D3DRS_FOGENABLE

- 안개 블렌딩을 사용하려면 TRUE, 기본값으로는 FALSE로 되어있다.

 

 

D3DRS_FOGCOLOR

- 안개의 색상을 지정한다. 기본값으로는 0이다.

 

 

D3DRS_FOGTABLEMODE : 안개의 모드를 정해준다.

- D3DFOG_NONE : 안개효과 없음 - 기본값

- D3DFOG_EXP : 안개 효과가 기하 급수적으로 나타남

- D3DFOG_EXP2 : 안개 효과가 거리의 제곱으로 기하 급수적으로 나타남

- D3DFOG_LINEAR : 안개 효과가 시작 및 종료 포인트 사이에서 직선의 형태로 나타남

 

 

D3DRS_FOGSTART

- 픽셀 또는 정점 포그 효과가 선형 안개 모드로 시작되는 깊이

 

 

D3DRS_FOGEND

- 픽셀 또는 정점 포그 효과가 선형 안개 모드로 종료되는 깊이

 

 

D3DRS_RANGEFOGENABLE

- TRUE는 범위 기반 꼭지점 안개를 사용하도록 설정

- FALSE는 시스템이 깊이 기반 안개를 사용하도록 설정 - 기본값

- 범위는 안개 계산에 사용하는 적절한 요소지만, 범위는 시간 소모적 계산을 한다.

 

 

D3DRS_FOGVERTEXMODE

- 안개 공식은 정점 포그를 사용할 수 있다.

- 기본 값은 D3DFOG_NONE이다.

 

 

D3DRS_STENCILENABLE

- 스텐실을 사용하려면 TRUE를, 사용하지 않으려면 FALSE를 쓴다.

 

 

D3DRS_STENCILFAIL

- 스텐실 테스트가 실패하면 스텐실 동작을 수행한다. ( D3DSTENCILOP 열거형 사용 )

- D3DSTENCILOP_KEEP : 스텐실 버퍼의 항목을 업데이트 하지 않는다. - 기본값

- D3DSTENCILOP_ZERO : 0으로 스텐실 버퍼 항목을 설정

- D3DSTENCILOP_REPLACE : 기준 값으로 스텐실 버퍼 항목을 교체한다.

- D3DSTENCILOP_INCRSAT : 최대 값( 최대 클램핑 )으로 설정, 스텐실 버퍼 항목을 증가시킨다.

- D3DSTENCILOP_DECRASAT : 제로로 설정( 제로 클램핑 ) , 스텐실 버퍼 항목을 감소시킨다.

- D3DSTENCILOP_INVERT : 스텐실 버퍼 항목의 비트를 반전시킨다.

- D3DSTENCILOP_INCR : 새로운 값이 최대 값을 초과하는 경우에 제로로 만든다. 스텐실 버퍼 항목을 증가시킨다.

- D3DSTENCILOP_DECR : 새로운 값이 0보다 작은 경우 최대 값으로 만든다. 스텐실 버퍼 항목을 감소시킨다.

 

 

D3DRS_STENCILZFAIL

- 스텐실 테스트는 통과하였으나, 깊이 테스트( Z테스트 )에 실패한 경우에 스텐실 작업을 수행

- D3DSTENCILOP 열거형 사용

- D3DSTENCILOP_KEEP 기본 값이다.

 

 

D3DRS_STENCILPASS

- 스텐실 및 깊이 테스트를 모두 통과 하는 경우 스텐실 작업을 수행

- D3DSTENCILOP 열거형 사용, 기본값으로는 D3DSTENCILOP_KEEP를 사용

 

 

D3DRS_STENCILFUNC

- 스텐실 테스트를 위한 비교 함수, D3DCMPFUNC 열거형 사용

- D3DCMP_NEVER : 항상 테스트를 실패한다.

- D3DCMP_LESS : 값이 현재 픽셀의 값보다 작으면 새로운 화소를 받아들인다.

- D3DCMP_EQUAL : 값이 현재 픽셀의 값과 같으면 새로운 화소를 받아들인다.

- D3DCMP_LESSEQUAL : 값이 현재 픽셀의 값과 작거나 같으면 새로운 화소를 받아들인다.

- D3DCMP_GREATER : 값이 현재 픽셀의 값보다 큰 경우에 새로운 화소를 받아들인다.

- D3DCMP_NOTEQUAL : 값이 현재 픽셀의 값과 동일하지 않으면 새로운 화소를 받아들인다.

- D3DCMP_GREATEREQUAL : 값이 현재 픽셀의 값보다 크거나 같으면 새로운 화소를 받아들인다.

- D3DCMP_ALWAYS : 항상 테스트를 통과 - 기본값

 

 

D3DRS_STENCILREF

- 스텐실 테스트를 위한 INT 참조값, 기본값은 0이다.

 

 

D3DRS_STENCILMASK

- 마스크 스텐실 테스트를 위한 유효 비트를 결정하는 기준값 및 각 스텐실 버퍼 항목에 적용

- 기본값으로는 0xffffffff이다.

 

 

D3DRS_STENCILWRITEMASK

- 쓰기 마스크는 스텐실 버퍼에 기입된 값에 적용, 기본값으로는 0xffffffff이다.

 

 

D3DRS_TEXTUREFACTOR

- D3DTA_TFACTOR의 텍스처 혼합 인수 또는 D3DTOP_BLENDFACTORALPHA로 텍스처의 혼합 처리와 다중 텍스처 혼합에 

   사용되는 색상( D3DCOLOR )

- 기본값으로는 불투명한 흰색이다.( 0xffffff )

 

 

D3DRS_WARP0~15

- 질감 좌표의 여러 집합에 대한 질감 래핑 동작

- 디폴트 값은 0으로 모든 방향에서 비활성화 포장을 하였다.

 

 

D3DRS_CLIPPING

- 클리핑을 사용하지 않으려면 FALSE, 사용하려면 TRUE

- 기본값으로는 TRUE가 지정

 

 

D3DRS_LIGHTING

- 조명을 사용하려면 TRUE, 사용하지 않으려면 FALSE

 

 

D3DRS_AMBIENT

- 주변 광 색, D3DCOLOR를 쓴다. 기본값으로는 0이다.

 

 

D3DRS_COLORVERTEX

- 정점 단위의 색을 사용하려면 TRUE, 사용하지 않으려면 FALSE로 지정( 기본값은 TRUE )

- 정점 단위의 색을 사용하면 시스템이 조명 계산과 각 정점에 정의 된 색을 포함할 수 있다.

 

 

- D3DMATERIALCOLORSOURCE 열거형을 사용

- D3DMCS_MATERIAL : 현재 재료로 색을 사용

- D3DMCS_COLOR1 : 확산 정점 색을 사용

- D3DMCS_COLOR2 : 거울 정점 색을 사용

 

 

D3DRS_DIFFUSEMATERIALSOURCE( 난반사광 )

- 기본 값으로 D3DMCS_COLOR1이다.

 

D3DRS_SPECULARMATERIALSOURCE( 정반사광 )

- 기본 값으로 D3DMCS_COLOR2이다.

 

D3DRS_AMBIENTMATERIALSOURCE( 환경광, 주변광 )

- 기본 값으로 D3DMCS_MATERIAL이다.

 

D3DRS_EMISSIVEMATERIALSOURCE( 방사광, 발광 )

- 기본 값으로 D3DMCS_MATERIAL이다.

 

 

D3DRS_LOCALVIEWER

- 카메라에 상대적인 반사 하이라이트 또는 직교 반사 하이라이트를 사용하려면 FALSE, 활성화 하려면 TRUE

 

 

D3DRS_NORMALIZENORMALS

- 정점 법선의 자동 정규화를 사용하려면 TRUE, 사용하지 않으려면 FALSE

- 기본 값으로는 TRUE이다.

- 카메라 공간 후에 정점 법선을 정상화 시킨다.

 

 

D3DRS_VERTEXBLEND

- 지오매트리 혼합을 수행하는 데 사용할 수 있는 행렬의 수를 구한다.

- D3DVERTEXBLENDFLAGS 열거형을 사용, 기본값으로는 D3DVBF_DISABLE

- D3DVBF_DISABLE : 정점 혼합을 비활성화시킨다, 인덱스 값 0

- D3DVBF_1WEIGHTS : 설정된 두 매트릭스 간의 정점 혼합에 사용, 인덱스 값은 0과 1이다. 

- D3DVBF_2WEIGHTS : 설정된 3개의 행렬들 사이의 정점 혼합에 사용, 인덱스 값은 0, 1, 2

- D3DVBF_3WEIGHTS : 설정된 4개의 행렬 간의 정점 혼합에 사용, 인덱스는 0, 1, 2, 3

- D3DVBF_TWEENING : 정점 혼합을 D3DRS_TWEENFACTOR에 할당된 값을 사용하여 수행한다.

- D3DVBF_0WEIGHTS : 1.0 무게를 가진 하나의 매트릭스를 사용

 

 

D3DRS_CLIPPLANEENABLE

- 사용자가 정의한 클리핑 평면을 사용하거나, 사용하지 않도록 설정합니다. 유효한 값은 각 비트의 상태 (설정의 유무)에 해당하는 사용자 정의 자르기 평면의 활성화 상태를 전환하는 임의의 DWORD이다. 최하위 비트 (비트 0)는 인덱스 0의 최초의 클립면을 제어하고, 후속 비트는 그것보다 상위의 인덱스의 클립면을 액티브하게하는 것을 제어 할 수 있습니다. 비트가 설정되면, 시스템은 장면 렌더링 중에 적절한 클리핑 평면을 적용한다. 기본값은 0이다.

- D3DCLIPPLANEn의 매크로에 자르기 평면을 가능하게하는 편리한 방법을 제공하기 위해 정의된다.

 

 

D3DRS_POINTSIZE

- 각 정점에 대해서 포인트의 크기가 지정되지 않은 경우에 포인트 크기 계산에 사용할 크기를 지정하는 부동 소수점 값

- 정점의 포인트의 크기가 포함 된 경우는 이 값을 사용하지 않는다.

- D3DRS_POINTSCALEENABLE의 값이 FALSE이면 화면공간 단위이고, TRUE이면 월드 공간 단위이다.

 

 

D3DRS_POINTSIZE_MAX

- 포인트 스프라이트가 제한되는 최대 사이즈를 지정하는 float값

- 최소값이 D3DRS_POINTSIZE_MIN 이상이어야 한다.

- 디폴트 값은 64.0f 이다.

 

 

D3DRS_POINTSIZE_MIN

- 포인트는 도형의 최소 크기를 지정하는 부동 소수점 값

- 디폴트 값은 1.0f 이다.

- 점은 픽셀 중심을 포함하지 않고, 안티 앨리어싱을 사용하지 않거나 안티 앨리어싱을 사용하는 경우에는 감소된 값으로 1.0f 보다 작은 값이 설정된다.

 

 

D3DRS_POINTSPRITEENABLE

- BOOL형 값이다. TRUE를 설정하면 텍스처 전체가 각 포인트에 맵핑되도록 하고, 포인트 기본도형의 텍스처 좌표가 설정된다.

- FALSE를 설정하면 정점의 텍스처 좌표가 포인트 전체에 대해서 사용된다. 기본값으로 FALSE가 지정되어 있다.

 

 

D3DRS_POINTSCALEENABLE

- 포인트의 기본 도형에 대한 사아즈 계산을 제어하는 BOOL형 값이다.

- TRUE이면 포인트 사이즈를 카메라 공간의 값으로 해석하여, 거리 함수 및 절두체에 의해 뷰포트의 y축이 스케일 되어 최종적인 스크린 공간의 포인트 사이즈를 계산하게 된다.

- FALSE이면 포인트 사이즈는 스크린 공간의 값으로, 그대로 사용된다. 기본값으로는 FALSE이다.

 

 

D3DRS_POINTSCALE_A, D3DRS_POINTSCALE_B, D3DRS_POINTSCALE_C

- 포인트는 기본도형에 대한 거리 사이즈의 감소를 제어하는 float형 값이다.

- D3DRS_POINTSCALLEENABLE 값이 TRUE일 경우에만 사용할 수 있다. 기본값으로는 1.0f이다.

- 값의 범위는 0.0f 이상이다.

 

 

D3DRS_MULTISAMPLEANTIALIAS

- 멀티 샘플 렌더링의 타겟 버퍼를 사용할 때, 각각의 샘플의 계산방법을 결정하는 BOOL형 값이다.

- TRUE로 설정하면 복수 샘플의 각각 붙어 다른 샘플링 위치에서 샘플링을 하는 것으로 안티 앨리어싱이 가능하도록 한다.

- FALSE로 설정 되면, 안티엘리어싱이 실행되지 않도록 한다. 기본값으로는 TRUE이다.

 

 

D3DRS_MULTISAMPLEMASK

- 최하정도 비트를 선두로 하는 이 마스크의 각 비트는 멀티 샘플 렌더링 타겟의 1개의 샘플에 대한 변경을 제어한다.

- 만약 8개의 샘플에 대한 렌더링 타겟의 경우에는, 8개의 샘플의 각각 대하는 8개의 쓰기 허가 정보가 하위 바이트에 저장된다.

- 싱글 샘플 버퍼에 렌더링 시, 렌더링 스테이트는 이펙트를 가지지 않는다. 기본값으로는 0Xffffffff이다.

 

 

D3DRS_PATCHDGESTYLE

- 패치 엣지가 부동 소수점 스타일의 테셀레이션을 사용할지 안할지를 결정한다. 

- D3DPATCHEDGESTYLE 열거형으로 정의한다.

- D3DPATCHEDGE_DISCRETE : 개별 Edge 스타일, float 테셀레이션을 지정할 수 있지만 정수로 잘린다.

- D3DPATCHEDGE_CONTINUOUS : 연속 Edge 스타일, 연속 모드에서 분할이 원할하다. 부동소수점값으로 지정





D3DRS_DEBUGMONITORTOKEN

-  모니터를 디버그 하는 경우에만 설정한다. D3DDEBUGMONITORTOKENS 열거형으로 정의

- D3DDMT_ENABLE : 디버그 모니터를 사용하도록 설정

- D3DDMT_DISABLE : 디버그 모니터를 사용하지 않도록 설정한다.

 

 

D3DRS_INDEXDVERTEXBLENDENABLE

- 인덱스 첨부의 정점 혼합을 유효 또는 무효를 정하는 BOOL형 값, 디폴트 값으로 FALSE이다.

- TRUE이면 인덱스 정점 혼합이 유효하게 된다.

- FALSE이면 인덱스 정점 혼합이 무효가 된다.

 

 

D3DRS_COLORWRITEENABLE

- 렌더링 타겟의 컬러 버퍼에 대한 채널마다 쓰기를 정하는 UINT값

- 비트를 설정하면 3D 렌더링의 사이에 컬러 채널이 갱신된다.

- 비트가 클리어 되면 컬러 채널을 갱신하지 않는다.





D3DRS_TWEENFACTOR

- 트윈 계수를 제어하는 float값, 디폴트 값은 0.0f 이다.

※트윈이란? 애니메이션이 부드럽게 표시되게 하기 위해 두 개의 키 프레임 사이의 중간 프레임을 생성하는 과정에 대한 애니메이션 용어


 

 

D3DRS_BLENOP

- D3DRS_ALPHABLENDENABLE 가 TRUE로 설정 되어 있는 경우에만 적용된다.

- D3DBLENDOP 열거형으로 정의되어 있으며, 디폴트 값은 D3DBLENDOP_ADD이다.

- D3DBLENDOP_ADD : 결과는 전송 바탕으로 목적지가 덧셈 된다.( 결과 = 전송원 + 목적지 )

- D3DBLENDOP_SUBTRACT : 결과는 전송원으로부터 목적지가 뺄셈된다.( 결과 = 전송원 - 목적지 )

- D3DBLENDOP_REVSUBTRACT : 결과는 목적지로부터 전송원이 뺄셈된다.( 결과 = 목적지 - 전송원 )

- D3DBLENDOP_MIN : 결과는 전송원과 목적지의 최소값이다.( 결과 = MIN( 전송원, 목적지 ) )

- D3DBLENDOP_MAX : 결과는 전송원과 목적지의 최대치이다.( 결과 = MAX( 전송원, 목적지 ) )

 

 

D3DRS_POSITIONDEGREE

- N패치 위의 보간 차수

- D3DDEGREE_CUBIC( 디폴트 ) 또는 D3DDEGREE_LINEAR를 설정할 수 있다.





D3DRS_NORMALDEGREE

- N패치 법선 보간 차수

- D3DDEGREE_LINEAR( 디폴트 ) 또는 D3DDEGREE_QUADRATIC를 설정할 수 있다.

 

 

D3DRS_SCISSORTESTENABLE

- 시저 테스트를 유효하게 하려면 TRUE, 무효로 하려면 FALSE로 설정한다. 디폴트 값은 FALSE이다.

 

 

D3DRS_SLOPESCALEDEPTHBIAS

- z화이팅을 줄이기 위해서 사용한다.

- 동일 평면상의 원시적으로 얼마나 편향을 적용할까를 결정하는데 사용한다.( 디폴트 값은 0이다. )

 

 

D3DRS_ANTIALIASEDLINEEABLE

- 선의 안티 앨리어싱을 유효하게 하는 경우에는 TRUE, 무효로 하는 경우는 FALSE를 설정한다.

- 디폴트 값은 FALSE이다.

 

 

D3DRS_MINITESSELLATIONLEVEL

- 테셀레이션의 최소레벨, 디폴트 값은 1.0f 이다.





D3DRS_MAXTESSLLATIONLEVEL

- 테셀레이션의 최대 레벨, 디폴트 값은 1.0f 이다.

 

 

D3DRS_ADAPTIVETESS_X

- 적응형 테셀레이션의 양( x 축 방향 ), 디폴트 값은 0.0f 이다.

 

 

D3DRS_ADAPTIVETESS_Y

- 적응형 테셀레이션의 양( y축 방향 ), 디폴트 값은 0.0f 이다.

 

 

D3DRS_ADAPTIVETESS_Z

- 적응형 테셀레이션의 양( z축 방향 ), 디폴트 값은 1.0f 이다.

 

 

D3DRS_ADAPTIVETESS_W

- 적응형 테셀레이션의 양( w축 방향 ), 디폴트 값은 0.0f 이다.

 

 

D3DRS_ENABLEADAPTIVETESSELATION

- 적응형 테셀레이션을 사용하려면 TRUE, 사용하지 않으려면 FALSE

- 디폴트 값은 FALSE 이다.

 

 

D3DRS_TWOSIDEDSTENCILMODE

- 2면의 스텐실을 사용하려면 TRUE, 사용하지 않으려면 FALSE를 설정

- 디폴트 값은 FALSE이다.

- 2면의 스텐실 모드를 유효하게 하려면 D3DRS_CULLMODE를 D3DCULL_NONE으로 설정해야 한다.

 

 

D3DRS_CCW_STENCILFAIL

- 반시계 회전의 스텐실 테스트에 실패했을 때에 실행하는 스텐실 처리, 디폴트 값은 0x00000001 이다.

 

 

D3DRS_CCW_STENCILZFAIL

- 반시계 회전의 스텐실 테스트를 통과한 후, z테스트에 실패했을 경우에 실행하는 스텐실 처리

- 디폴트 값은 0x00000001 이다.

 

 

D3DRS_CCW_STENCILPASS

- 반시계 회전의 스텐실 테스트 및 z테스트의 양쪽 모두에 패스했을 경우의 스텐실 처리

- 디폴트 값은 0x00000001 이다.

 

 

D3DRS_CCW_STENCILFUNC

-  비교 함수, 반시계 회전의 스텐실 테스트에 패스하는 것은 스텐실 함수가  TRUE일 경우이다.

- 디폴트는 0x00000008 이다.

 

 

D3DRS_COLORWRITEENABLE1~3

- 장치에 대한 추가의 ColorWriteEnable의 값

 

 

D3DRS_BLENDFACTOR

- 알파 혼합 처리에 정수 혼합 계수에 사용하는 D3DCOLOR

 

 

D3DRS_SRGBWRITEENABLE

- 렌더링 타겟의 쓰기에 해당하며, sRGB에의 감마 보정을 유효하게 한다.





D3DRS_DEPTHBIAS

-  깊이 값의 비교에 사용하는 부동 소수점 값, 디폴트 값은 0이다.





D3DRS_SEPARATEALPHABLENDENABLE

- TRUE를 설정하면, 알파 채널에 대한 개별의 혼합 모드가 유효하게 된다.

- 디폴트로는 FALSE 값이다. FALSE일 경우에는 알파에 적용하는 렌더링 타겟의 혼합 계수와 혼합 처리는 강제적으로 색에 대해서 정의한 것과 같은 것이 된다.

 

 

D3DRS_SRCBLENDALPHA

- D3DBLEND 열거의형의 멤버 중 하나

- D3DRS_SEPARATEALPHAENABLE이 TRUE가 아니면 무시된다.

- 디폴트는 D3DBLEND_ONE이다.

 

 

D3DRS_DESTBLENDALPHA

- D3DBLEND 열거형의 멤버중 하나이다. D3DRS_SEPARATEALPHAENABLE 가 TRUE 가 아닌 경우, 이 값은 무시된다.

- 디폴트값은 D3DBLEND_ZERO 이다.

 

 

 

D3DRS_BLENDOPALPHA

- 렌더링 스테이트의 D3DRS_ALPHABLENDENABLE 가 TRUE 로 설정되어 있는 경우에, 개별의 알파 혼합에 적용하는 산술 연산의 

  선택에 사용하는 값.

- 유효한 값은,D3DBLENDOP 열거형으로 정의된다. 디폴트값은 D3DBLENDOP_ADD 이다.

- D3DPMISCCAPS_BLENDOP 장치 능력이 지원되지 않은 경우는, D3DBLENDOP_ADD 가 실행된다.