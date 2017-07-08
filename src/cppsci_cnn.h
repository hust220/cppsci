/***************************************************************************
 *
 * Author: "Jian Wang"
 * Email: "wj_hust08@hust.edu.cn"
 *
 ***************************************************************************/

#pragma once

#include "cppsci_array.h"
#include "cppsci_fft.h"

namespace cppsci {

    using namespace STD_;

    struct CNN {

        struct Layer {
            char type;
            STD_::vector<Arrayd> a;

            Layer(int type_) : type(type_) {}
        };

        struct InputLayer : public Layer {
            InputLayer() :
                Layer('i')
            {}
        };

        struct ConvLayer : public Layer {
            int outputmaps;
            int kernelsize;
            Arrayd b;
            Arrayd k;

            ConvLayer(int outputmaps_, int kernelsize_) : 
                outputmaps(outputmaps_), kernelsize(kernelsize_), Layer('c')
            {}
        };

        struct SampLayer : public Layer {
            int scale;
            Arrayd b;

            SampLayer(int scale_) :
                scale(scale_), Layer('s')
            {}
        };

        using Layers = STD_::vector<Layer *>;

        Layers layers;

        ~CNN() {
            for (auto && l : layers) {
                if (l->type == 'i') delete (InputLayer *)l;
                else if (l->type == 'c') delete (ConvLayer *)l;
                else if (l->type == 's') delete (SampLayer *)l;
            }
        }
    };

    template<typename _CNN, typename _X, typename _Y>
    void cnn_setup(_CNN && net, _X && x, _Y && y) {
        int inputmaps = 1;
        Shape mapsize = x.shape();
        for (aut && i : mapsize) i /= x.shape(2);

        for (auto && layer : net.layers) {
            if (layer->type == 's') {
                SampLayer *l = (SampLayer *)layer;
                for (auto && i : mapsize) i /= l->scale;
                l->b = Arrayd({inputmaps}, 0);
            }
            else if (layer->type == 'c') {
                ConvLayer *l = (ConvLayer *)layer;
                for (auto && i : mapsize) i -= l->kernelsize - 1;
                fan_in = inputmaps * (l->kernelsize) * (l->kernelsize);
                fan_out = (l->outputmaps) * (l->kernelsize) * (l->kernelsize);
                l->b = Arrayd({outputmaps}, 0);
                l->k = Arrayd({inputmaps, outputmaps, l->kernelsize, l->kernelsize});
                for (int j = 0; j < l->outputmaps; j++) {
                    for (int i = 0; i < inputmaps; i++)
                        for (int m = 0; m < l->kernelsize; m++)
                            for (int n = 0; n < l->kernelsize; n++)
                                l->k(i, j, m, n) = (rand() - 0.5) * 2 * STD_::sqrt(6 / (fan_in + fan_out));
                }
                inputmaps = l->outputmaps;
            }
            else if (layer.type == 'i') {
                // pass
            }
            else {
                // pass
            }
        }
    }

    void cnn_ff();

    void cnn_bp();

    void cnn_test();

    void cnn_train();

    void cnn_applygrads();

    void cnn_numgradcheck();

} // namespace cppsci

