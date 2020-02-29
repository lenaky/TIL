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
    // novtable�� �����ڿ� �Ҹ��ڿ��� vfptr �ʱ�ȭ �ڵ带 ���� ����.
    // ���� �߻�Ŭ���������� ����� �� ����.
    // �׽�Ʈ�غ��� ilk ������ 7kb ���� ����, main object�� 1kb ���� ����.
    SomePureIF* sp = new SomeTestClass; // ok
    // ������ �ڵ带 �����ϴٺ��� vftable�� �ִ� �Լ��� ��ũ�Ϸ��� �����״� �����ξ��� virtual �Լ��� �����ϰ�
    // �ν��Ͻ�ȭ�Ͽ� �����ϸ� Access Violation�� ���.
    sp->SomeVirtualFunction();
    delete sp;

    SomePureIF* sp2 = new SomePureIF;
    sp2->SomeVirtualFunction(); // <- Access Violation
    // ex) sp�� SomePureIF�� �����ؼ� SomeVirtualFunction�� �����ϸ� Access Violation ��.
    // NOVTABLE �� �������� ������ ��ũŸ�Ӷ� �˾Ƴ�
    delete sp2; 

    return 0;
}