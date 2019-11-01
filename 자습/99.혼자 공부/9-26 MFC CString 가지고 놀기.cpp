/*

//From에서 To로 가기위한 상대 경로를 만들어서 out에 저장하는 함수.
//이때 From과 To는 동일한 드라이브에 존재해야 한다.
// From : 현재 작업 경로
    ::PathRelativePathT (out , From , FILE_ATTRIBUTE_DIRECTORY,
            To, FILE_ATTRIBUTE_DIRECTORY) 

//파일명만 보기
    ::PathFindFileName(szPath);

//확장자 제거
    ::PathRemoveExtension(); 


PathRelativePathTo -> PathFindFileName ->PathRemoveExtension 순으로 파일 이름만 구해볼 수 있다.



이름에서 숫자만 뽑아내기 

	CString strSelectName = L"Tile123";
	int SelectIndex = 0;
	int i = 0;
	for (; i < strSelectName.GetLength(); i++)
	{
		//글자인지 숫자인지 판별 함수. 숫자라면 true
		if (isdigit(strSelectName[i]))	
			break;

	}

	//CString::Delete(index , count)
	//현재 문자열 index부터 count만큼 제거.
	strSelectName.Delete(0, i);

	문자열을 숫자로 변환
	SelectIndex = _ttoi(strSelectName);

	cout <<123 <<endl;							결과 : 123

					

*/