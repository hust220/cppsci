#include "unit_test.h"
#include "../src/cppsci_utils.h"
#include "../src/cppsci_signal.h"

TEST_CASE(test_signal) {
    using namespace cppsci;

    ::std::cout << "test_signal" << ::std::endl;

    Arrayd data({78}, {0.68082612, 1.02089301, 1.38014076, 0.84597076, 0.68683996, 0.61863042, 0.55475005, 0.79318099, 0.39312936, 0.11514612, 0.54262644, 0.37564635, 0.39733657, 0.27889355, 0.07114224, 0.03431048, -0.02489486, -0.04658673, 0.05027256, 0.12018476, 0.14864147, 0.1939832, 0.28320927, 0.27195177, 0.13904299, 0.14460032, 0.24454763, 0.25501036, 0.20073157, 0.16981645, 0.15854496, 0.02510022, 0.00728042, 0.03213757, -0.06792908, 0.00451952, -0.05023178, -0.09036858, -0.09288989, -0.09203746, -0.05631148, -0.11792277, -0.15031258, -0.11372971, -0.11921412, -0.0389679, -0.14066871, -0.15971611, -0.11294486, -0.11996022, -0.100716, 0.04369869, 0.32319373, 0.61594171, 1.04053734, 1.5785106, 2.31351962, 2.62696023, 0.67388271, 0.14314512, 0.11106108, 0.06912054, 0.05106574, 0.03016483, -0.0119369, -0.03341066, -0.05061825, -0.07017359, -0.10610097, -0.16361512, -0.19629324, -0.1920573, -0.16637824, -0.16855309, -0.14437561, -0.15157812, -0.15811192, 1.48569187});
    signal::cwt(data, Arrayi::range(1,10), signal::ricker).identify("cwt");
    signal::find_peaks_cwt(data, Arrayd::range(1,10)).printFull();

    signal::convolve_same(Arrayd({3},{1,2,3}),Arrayd({3},{4,5,6})).printFull();

    Arrayi data2({3,3}, {1,3,2,2,2,1,1,3,1});
    data2.printFull();
    data2.takes(::std::vector<int>{1,2},0).printFull();
    data2.takes(::std::vector<int>{0,1},1).printFull();
    signal::boolrelextrema(data2, ::std::greater<int>{}, 0).printFull();
    signal::boolrelextrema(data2, ::std::greater<int>{}, 1).printFull();

    Arrayd bb({6}, {1,2,4,4,4,5});
    ::std::cout << signal::quantile(bb,0.1) << ::std::endl;;

//    Arrayd v1({3}, {1,2,3});
//    Arrayd v2({3}, {3,4,5});
//    auto && v3 = Arrayd::convolve(v1, v2);
//    Arrayd v4({3}, {26,23,23});
//    v3.printFull();
//    v4.printFull();
//    (v3 - v4).printFull();
//    TEST_CHECK((v3 - v4).all([](double d){::std::cout << d << ::std::endl;::std::cout << (d<1e-5) << ::std::endl;return d<1e-5;}));
//
//    auto && w = find_peaks_cwt(data, Arrayi::range(2, 33, 1));
//    for (auto && n : w) ::std::cout << n << ' '; ::std::cout << ::std::endl;
}



