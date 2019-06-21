

void Foo(int n)
{

}



//delete키워드
//Foo함수에 대해 float
void Foo(float n) = delete;


void main()
{
    Foo(100);
    //Foo(3.14f); Error!
}