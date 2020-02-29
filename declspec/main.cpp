#include <iostream>

#define NOVTABLE __declspec(novtable)
//#define NOVTABLE 
class NOVTABLE SomePureIF
{
public:
    virtual int SomeVirtualFunction();
    int SomeNotVirtualFunction()
    {
        return 100;
    }
};

class SomeTestClass : public SomePureIF
{
public:
    virtual int SomeVirtualFunction() override
    {
        return -1;
    }
};

int main()
{
    // novtable은 생성자와 소멸자에서 vfptr 초기화 코드를 넣지 않음.
    // 순수 추상클래스에서만 사용할 수 있음.
    // 테스트해보니 ilk 파일은 7kb 정도 증가, main object는 1kb 정도 증가.
    SomePureIF* sp = new SomeTestClass; // ok
    // 문제는 코드를 삭제하다보니 vftable에 있는 함수를 링크하려고 안할테니 구현부없는 virtual 함수를 선언하고
    // 인스턴스화하여 접근하면 Access Violation이 뜬다.
    sp->SomeVirtualFunction();
    delete sp;

    SomePureIF* sp2 = new SomePureIF;
    sp2->SomeVirtualFunction(); // <- Access Violation
    // ex) sp를 SomePureIF로 생성해서 SomeVirtualFunction에 접근하면 Access Violation 남.
    // NOVTABLE 을 선언하지 않으면 링크타임때 알아냄
    delete sp2; 

    return 0;
}