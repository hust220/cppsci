#include "unit_test.h"
#include "../src/cppsci_array.h"

TEST_CASE(test_array)
{
    using namespace cppsci;

    Arrayd arr({2, 2}, {0, 1, 2, 3});
    TEST_CHECK(arr[0] == 0);
    TEST_CHECK(arr(0) == 0);
    TEST_CHECK(arr(1, 1) == 3);
    TEST_CHECK(arr({1, 1}) == 3);
    TEST_CHECK(arr.trace() == 3);

    Arrayd arr2({2, 2, 3}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
    TEST_CHECK(arr2[1] == 1);
    TEST_CHECK(arr2(6) == 6);
    TEST_CHECK(arr2(1, 1, 1) == 10);

    auto && sub2 = arr2.sub({{0,2},{0,2},{1,3}});
    TEST_CHECK(sub2(1, 1, 1) == 11);
    TEST_CHECK(sub2({1, 1, 1}) == 11);
    TEST_CHECK(sub2.trace() == 12);

    sub2.selfTimes(2).selfPlus(5).selfMinus(5);
    TEST_CHECK(sub2(1, 1, 1) == 22);
    TEST_CHECK(arr2(1, 1, 2) == 22);
    sub2 *= 0.5;
    TEST_CHECK(sub2(1, 1, 1) == 11);
    sub2.selfDivide(0.1);
    TEST_CHECK(sub2(1, 1, 1) == 110);
    sub2 /= 10;
    TEST_CHECK(sub2(1, 1, 1) == 11);
    TEST_CHECK(sub2.argmax() == 7);
    TEST_CHECK(sub2.max() == 11);
    TEST_CHECK(sub2.argmin() == 0);
    TEST_CHECK(sub2.min() == 1);
    TEST_CHECK(sub2.sum() == 48);

    Arrayd arr3({2, 2}, {5, 4, 3, 2});
    arr3.selfMinus(arr);
    TEST_CHECK(arr3(1, 1) == -1);
    TEST_CHECK(arr3.sum() == 8);
    arr3.selfTimes(arr);
    TEST_CHECK(arr3(1, 1) == -3);
    TEST_CHECK(arr3.max() == 3);

    auto && arr4 = Arrayd::plus(arr3, arr);
    TEST_CHECK(arr4.trace() == 0);

    Arrayd arr5({79}, 0);
    TEST_CHECK(arr5.sum() == 0);

    Arrayd arr6({15}, {3.1, 2.2,-1.8, -5.3, 7.543, 8.7, 3, 2, 9, 0, -1, -5, 4, -2, 3});
    //Arrayd arr7({5}, {1,2,3,5,7});
    for (auto && n : arr6) ::std::cout << n+1 << ::std::endl;
    ::std::sort(arr6.begin(), arr6.end());
    arr6.printFull();
    //TEST_CHECK((arr6-arr7).all([](int a){return a == 0;}));

    Arraycd a7({2}, {::std::complex<double>(1,2), ::std::complex<double>(2,3)});
    Arraycd b7({2}, {::std::complex<double>(3,4), ::std::complex<double>(5,6)});
    ::std::cout << Arraycd::times(a7, b7) << ::std::endl;
//    ::std::cout << a7 * b7 << ::std::endl;

}



