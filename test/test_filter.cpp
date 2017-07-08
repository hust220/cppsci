#include "unit_test.h"
#include "../src/cppsci_array.h"
#include "../src/cppsci_filter.h"

TEST_CASE(test_filter)
{
    using namespace cppsci;

    ::std::cout << "TEST: filter..." << ::std::endl;
    Arrayd a1({4}, {1,2,3,4});
    ArrayLines lines(a1.shape(), 0, 3, 3);
    lines.read_array(a1);
    ::std::cout << "lines\n" << ::std::endl;
    lines.printFull();
    Arrayd b1(a1.shape());
    lines.write_array(b1);
    ::std::cout << "b1\n" << b1 << ::std::endl;
    Arrayd c1 = cppsci::gaussian_filter(a1, 0.5);
    ::std::cout << c1 << ::std::endl;
    Arrayd d1(a1.shape());
    correlate1d(a1, d1, Arrayd({5},{0.1,0.2,0.3,0.2,0.1}));
    ::std::cout << d1 << ::std::endl;
    ::std::cout << "END: filter..." << ::std::endl;
}



