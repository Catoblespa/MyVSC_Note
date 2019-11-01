


1. LPD3DXFONT 객체 생성과 초기화


@ params

- Height  : 글자의 높이
- Width : 넓이. 0을 넣어주면 글자체에 따른 넓이가 자동으로 setup
- Weight : Bold의 유무. WinGDI.h 헤더에 설정하는 값들이 저장되어 있다. 기본 값은 FW_NORMAL
- MipLevel : 기본값 1 설정
- Italic : Italic체 사용의 유무
- CharSet : DEFAULT_CHARSET 설정, 기본 문자셋을 사용한다.
- OutputPrecision : OUT_DEFAULT_PRECIS 설정.  실제 화면에 출력되는 폰트가 여기서 지정한 속성과 어느 정도 비슷해야 하는지 설정한다.
- Quality : DEFAULT_QUALITY. 여기서 설정하는 폰트와 실제 폰트의 품질이 얼마나 비슷해야 하는가를 설정한다. 
- PitchAndFamily : DEFAULT_PITCH | FF_DONTCARE , 기본 피치를 사용하고 폰트군은 상관 없음.
- pFacename : 사용하고자할 글자체 명시
- *ppFont : Font 객체 주소가 담길 포인터 변수




2. D3DXCreateFont() 함수 설정

LPD3DXFONT Font;
D3DXCreateFont(m_pd3dDevice, 20, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
  DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &Font);






3. 출력
	RECT rt;
	SetRect(&rt, 100, 430, 0, 0);
	CDeviceManager::GetInstance()->GetFont()->DrawText(NULL, L"Test", -1, &rt, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
