#include "unit_test.h"
#include "../src/cppsci_cnn.h"

TEST_CASE(test_cnn)
{
    using namespace cppsci::mlearn;

    CNN cnn;
    cnn.layers = {
        new CNN::InputLayer,
        new CNN::ConvLayer(6, 5),
        new CNN::SampLayer(2),
        new CNN::ConvLayer(12, 5),
        new CNN::SampLayer(2)
    };

}



