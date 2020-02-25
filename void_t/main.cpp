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
    // SomeTemplateClass<TestClass2> stc2; // 에러 발생. void_t 로 좀더 이쁘게 제약조건 줄 수 있음. 2a에선 concept로 더 이쁘게 만들 수 있음.

    return 0;
}