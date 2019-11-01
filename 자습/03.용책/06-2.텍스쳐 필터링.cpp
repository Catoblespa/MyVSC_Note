/*
 텍스처는 스크린 스페이스에서 삼각형에 입혀진다. 
 일반적으로 텍스처 삼각형과 스크린 삼각형의 크기는 서로 다른데,
 텍스처 삼각형이 스크린 삼각형보다 작은 경우에는 텍스처 삼각형을 확대하여 크기를 맞추고,
 텍스처 삼각형이 더 큰 경우에는 텍스처 삼각형을 축소하낟.alignas

두 가지 경우에 모두 얼마간의 왜곡이 발생하므로 필터링을 통해
이와 같은 왜곡 현상을 줄이고 부드러운 이미지를 만들어 낼 수있다.

*/


/*
Direct3D는 세가지 다른 타입의 필터를 제공하며 각각의 필터는 서로 다른 수준의 품질을 제공한다.
품질이 높아질수록 속도는 저하되므로 목적에 따라 품질과 속도 사이에서
적절한 타협이 필요하다.
텍스처 필터를 지정하기 위해서는  IDirect3DDevice9::SetSamplerState()를 이용한다.
*/
 근접접 샘플링 (Nearest point sampling) 
 - 디폴트 필터링 방식이며 가장 떨어지는 품질의 결과를 만
들어내지만 또한 가장 빠른 속도를 가진다 다음 코드는 축소와 대 필터에 근접점 필터를 이용한 예시다 
      Device->SetSamplerState(O, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
      Device->SetSamplerState(O, D3DSAMP_MINFILTER, D3DTEXF_POINT);


선형 필터링(Linear filtering) 
- 선형 필터링은 비교적 높은 품질의 과물을 만들어내며 현재의 하드웨어 성능을 고려 하면 실행 속도 또한 빠른 편이다 
보통은 최소한 선형 필터링을 이용하는 이 권장된다 다음 코드는 축소와 확대 필터에 선형 필터링을 용한 예이다.
      Device->SetSamplerState(O, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR) ;
      Device->SetSamplerState(O , D3DSAMP_MINFILTER, D3DTEXF_LINEAR) ; 

 비등방성 필터링 (Anisotropic filtering) 
 - 비등방성 필터링은 가장 높은 품질의 결과물을 만들어내지만
실행 속도 또한 가장 느리다. 다음 코드는 축소와 확대 필터에 비등방성 필터링을 이용한 예시다.
      Device->SetSamplerState(O , D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC) ;
      Device->SetSamplerState(O, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC) ; 


      비등방성 필터링을 이용할 때는 비등방성 필터링의 품질을 결정하는 D3DSAMP_MAXANISOTROPY 레벨을 지정해야 한다. 
      높은 값을 지정할수록 좀더 높은 품질의 결과물을 얻을 수 있으며， 
      다음과 같은 방식으로 지정한다. 여러분의 장치에서 지원하는 값의 범위를 알기 위해서는 /*D3DCAPS9 구조체*/를 확인하면 된다
      Device->SetSamplerState(O , D3DSAMP MAXANISOTROPY, 4);

