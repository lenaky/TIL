#include <iostream>
#include <type_traits>

class TestClass
{
public:
    TestClass()
    {

    }

    int ShouldHaveThisFunc() const
    {
        return 0;
    }

    int ShouldHaveThisFuncToo() const
    {
        return 0;
    }
};

class TestClass2
{
public:
    TestClass2()
    {

    }
};

template<typename T,
           typename = std::void_t<decltype(std::declval<T>().ShouldHaveThisFunc()),
                                  decltype(std::declval<T>().ShouldHaveThisFuncToo())>>
class SomeTemplateClass
{
public:
    SomeTemplateClass() {}
};

int main()
{
    SomeTemplateClass<TestClass> stc;
    // SomeTemplateClass<TestClass2> stc2; // ���� �߻�. void_t �� ���� �̻ڰ� �������� �� �� ����. 2a���� concept�� �� �̻ڰ� ���� �� ����.

    return 0;
}