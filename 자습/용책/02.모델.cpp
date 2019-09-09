
D3DXCreateBox
D3DXCreateSphere
D3DXCreateCylinder
D3DXCreate Teapot
D3DXCreatePolygon
D3DXCreate Torus

HRESULT D3DXCreateTeapot(
LPDIRECT3DDEVICE9 pDevice ,			// 메쉬와 연게된 장치 
LPD3DXMESH* ppMesh,					// 메쉬를 받을 포인터 
LPD3DXBUFFER* ppAdjacency			// 현재는 으로 지정한다.

//ex)
ID3DXMesh* mesh = 0;
D3DXCreateTeapot( device , &mesh , 0) 

/*
메쉬 데이터 를 생성한 다음에는 ID3DXMesh::DrawSubset 메서드를 이용해 이를 그려낼 수 있다 
이 메서 드는 메쉬 부분 집합을 지정하는 하나의 인자를 받으며， 
앞서의 D3DXCreate* 함수로 생성된 메쉬 는 한 개의 부분 집합만을 가지므로 이 인자에는 을 지정할 수 있다. 
다음 코드는 메쉬 를 렌더링하는 예시를 보여준다

*/
device->BeginScene();
mesh->DrawSubset(0);
device->EndScene();


//사용이 끝난 메쉬는 해제 해주어야 한다.
mesh->Release() ;
mesh =0;


