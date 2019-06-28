

void Foo(int n)
{

}



//delete키워드
//Foo함수에 대해 float 묵시적 형변환을 허용하지 않는다!
//g해당 
void Foo(float n) = delete;


void main()
{
    Foo(100);
    //Foo(3.14f); Error!
}