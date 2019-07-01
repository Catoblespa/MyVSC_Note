#include <iostream>
using namespace std;



class MyString
{

	friend ostream&operator<< (ostream& c, MyString& ms);
private:
	char* str;
	int size;
public:
	MyString() 
	{ 
		size = 1;
		str = new char[1];
		str[0] = 0;
	};

	MyString(const char* ch)
	{
		size = strlen(ch)+1;
		str = new char[size];
		strcpy_s(str, size, ch);
	}

	MyString(const MyString& _copy)
	{
		size = _copy.Size();
		str = new char[size];
		strcpy_s(str, size, _copy.str);
	}
	~MyString()
	{
		if ( str != nullptr)	
			delete[] str;
	}

public:

	int Size() const
	{
		return size;
	}

	bool operator==(const MyString& tem)
	{
		if (strcmp(str, tem.str))
		{
			return false;
		}
		else
			return true;
	}

	MyString& operator=(const MyString& tem)
	{
		delete[] str;

		size = tem.Size();
		str = new char[size];
		strcpy_s(str, size, tem.str);
		return *this;
	}

	MyString operator+(const MyString& tem) const
	{
		char* ch = nullptr;

		int chsize = size + tem.size+1;
		ch = new char[chsize];


		strcpy_s(ch, chsize, str);
		strcat_s(ch, chsize, tem.str);
		//strcpy_s(str, size, tem.str);
		MyString tmep = ch;

		delete[] ch;
		return tmep;
	}

	MyString& operator+=(const MyString& tem)
	{
		*this = *this + tem;
		return *this ;
	}


	char* Getstr()
	{
		return str;
	}

	void print()
	{
		cout << str << endl;
	}
};

ostream& operator<< (ostream& _cout,MyString& ms) 
{
	_cout << ms.str;
	return _cout;
}


int main()
{
	MyString a = "aa";
	a.print();
	MyString b = a;
	b.print();
	//MyString c;


	//c = a;

	//c.print();


	if (a == b)
	{
		cout << "같음" << endl;
	}
	else
		cout << "다름" << endl;


	MyString s1 = "Hello";
	MyString s2 = "World";
	MyString s3 = s1 + s2;

	s3 += s2;

	s3.print();

	cout << s3 << endl;

	return 0;
}