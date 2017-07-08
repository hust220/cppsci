/***************************************************************************
 *
 * Author: "Jian Wang"
 * Email: "wj_hust08@hust.edu.cn"
 *
 ***************************************************************************/

#include "cppsci_cnn.h"

namespace cppsci { namespace mlearn {
    /*
    template<typename _Net, typename _X>
    void cnn_ff(_Net && net, _X && x) {
        int n = net.layers.size();
        net.layers[0].a.push_back(STD_::move(x));
//        net.layers[0].a[0] = x;
        int inputmaps = 1;
        for (int l = 1; l < n; l++) {
            Layer *prev_layer = net.layers[l-1];
            if (net.layers[l]->type == 'c') {
                ConvLayer *layer = (ConvLayer *)(net.layers[l]);
                // below can probably be handled by insane matrix operations
                for (int j = 0; j < layer->outputmaps; j++) {
                    Shape shapez = prev_layer->a[0].shape();
                    shapez[0] -= layer->kernelsize-1;
                    shapez[1] -= layer->kernelsize-1;
                    Arrayd z(shapez, 0);
                    for (int i = 0; i < inputmaps; i++) {
                        z.selfPlus(convolve(prev_layer->a[i], layer->k.sub({{i},{j}}), CPPSCI_CONVOLVE_VALID));
                    }
                    //  add bias, pass through nonlinearity
                    layer->a[j] = sigm(z + layer->b{j});
                }
                //  set number of input maps to this layers number of outputmaps
                inputmaps = layer->outputmaps;
            }
            else if (net.layers[l].type == 's') {
                SampLayer *layer = (SampLayer *)layer;
                // downsample
                for (int j = 0; j < inputmaps; j++) {
                    z = convn(prev_layer->a[j], Arrayd({layer->scale, layer->scale}, 1.0 / square(layer->scale)), "valid");
                    layer->a[j] = z.sub({{1,end,layer->scale},{1,end,layer->scale},{}});
                }
            }
        }
        // concatenate all end layer feature maps into vector
        net.fv = [];
        for (int j = 0; j < net.layers[n].a.size(); j++) {
            sa = net.layers[n].a[j].size();
            net.fv = [net.fv; reshape(net.layers{n}.a{j}, sa(1) * sa(2), sa(3))];
        }
        // feedforward into output perceptrons
        net.o = sigm(net.ffW * net.fv + repmat(net.ffb, 1, size(net.fv, 2)));
    }

    void cnn_bp() {
        int n = net.layers.size();
        //   error
        net.e = net.o - y;
        //  loss function
        net.L = 0.5 * Arrayd::square(net.e).sum() / net.e.shape(1);
//        net.L = 1/2* sum(net.e(:) .^ 2) / size(net.e, 2);

        //  backprop deltas
        net.od = net.e * (net.o * (1 - net.o));   //  output delta
        net.fvd = (net.ffW.transpose() * net.od);              //  feature vector delta
        if (net.layers[n].type == 'c') {
            net.fvd.selfTimes(net.fv * (1 - net.fv));
        }

        //  reshape feature vector deltas into output map style
        sa = size(net.layers{n}.a{1});
        fvnum = sa(1) * sa(2);
        for j = 1 : numel(net.layers{n}.a)
            net.layers{n}.d{j} = reshape(net.fvd(((j - 1) * fvnum + 1) : j * fvnum, :), sa(1), sa(2), sa(3));
        end

        for l = (n - 1) : -1 : 1
            if strcmp(net.layers{l}.type, 'c')
                for j = 1 : numel(net.layers{l}.a)
                    net.layers{l}.d{j} = net.layers{l}.a{j} .* (1 - net.layers{l}.a{j}) .* (expand(net.layers{l + 1}.d{j}, [net.layers{l + 1}.scale net.layers{l + 1}.scale 1]) / net.layers{l + 1}.scale ^ 2);
                end
            elseif strcmp(net.layers{l}.type, 's')
                for i = 1 : numel(net.layers{l}.a)
                    z = zeros(size(net.layers{l}.a{1}));
                    for j = 1 : numel(net.layers{l + 1}.a)
                         z = z + convn(net.layers{l + 1}.d{j}, rot180(net.layers{l + 1}.k{i}{j}), 'full');
                    end
                    net.layers{l}.d{i} = z;
                end
            end
        end

        //  calc gradients
        for l = 2 : n
            if strcmp(net.layers{l}.type, 'c')
                for j = 1 : numel(net.layers{l}.a)
                    for i = 1 : numel(net.layers{l - 1}.a)
                        net.layers{l}.dk{i}{j} = convn(flipall(net.layers{l - 1}.a{i}), net.layers{l}.d{j}, 'valid') / size(net.layers{l}.d{j}, 3);
                    end
                    net.layers{l}.db{j} = sum(net.layers{l}.d{j}(:)) / size(net.layers{l}.d{j}, 3);
                end
            end
        end
        net.dffW = net.od * (net.fv)' / size(net.od, 2);
        net.dffb = mean(net.od, 2);

        auto rot180 = [](const Arrayd &X) -> Arrayd {
            return Arrayd::flipdim(Arrayd::flipdim(X, 1), 2);
        };
    }

    void cnn_test() {}

    void cnn_train() {}

    void cnn_applygrads() {}

    void cnn_numgradcheck() {}
    */

}} // namespace cppsci::CNN

