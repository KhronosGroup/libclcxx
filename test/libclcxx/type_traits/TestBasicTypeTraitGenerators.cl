// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_type_traits>
using namespace cl;

template <class expectedRetType_, class... argTypes_>
struct TestResultOf
{
    template <class retType_>
    TestResultOf(retType_(&)(argTypes_ ...))
    {
        typedef retType_(&fnType_)(argTypes_ ...);
        static_assert(is_same<result_of_t<fnType_(argTypes_ ...)>, expectedRetType_>::value, "");
    }

    template <class fnType_>
    TestResultOf(fnType_ fn)
    {
        static_assert(is_same<result_of_t<fnType_(argTypes_ ...)>, expectedRetType_>::value, "");
    }
};

kernel void worker( )
{
    // tests of type generators
    struct c1 { void m( ) { } };
    struct c2 : c1 { };

    static_assert( is_same<typename common_type<int, short, char>::type, int>::value == true, "" );
    static_assert( is_same<typename common_type<c1, c2>::type, c1>::value == true, "" );
    static_assert( is_same<typename common_type<c1*, c2*>::type, c1*>::value == true, "" );

    typedef bool (&PF1)();
    static_assert(is_same<result_of_t<PF1()>, bool>::value, "");
    int foo(int);
    char foo(float);
    float foo(int, int);
    int foo1(long);
    typedef int (&rfoo)(long);
    rfoo rfoo1 = foo1;

    struct S
    {
        operator rfoo();
        short operator()(int, long);
        long operator()(int, int);
    } s;

    TestResultOf<int, int>        test01(foo);
    TestResultOf<char, float>     test02(foo);
    TestResultOf<float, int, int> test03(foo);

    TestResultOf<int, int> test04(foo1); // implicit conversion

    TestResultOf<int, long>        test05(s);
#ifdef TODO //add support for function pointers in unevaluated context
    TestResultOf<short, int, long> test06(s);
    TestResultOf<long, int, int>   test07(s);
#endif
}
