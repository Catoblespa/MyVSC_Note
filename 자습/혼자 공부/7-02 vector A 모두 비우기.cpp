


class teacher
{
private:

	vector<Student*> stu;
	//Student* stu;
	//int size;
public:

	teacher()
	{
	}
	~teacher()
	{
		while (true)
		{
			if(stu.back() != nullptr)
				delete stu.back();  //맨뒤에서 부터 할당해제
	
			stu.pop_back();         //할당해제된 댕그링 포인터 팝
			if (stu.empty())  // stu 백터가 비어졌으면 break;
				break;
		}
	}
}

