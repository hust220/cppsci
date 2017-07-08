/***************************************************************************
 *
 * Authors: "Yongbei(Glow) Ma,Jiayi (Timmy) Wu, Youdong (Jack) Mao"
 * Dana-Farber Cancer Institute, Harvard Medical School and Peking University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * This complete copyright notice must be included in any revised version of the
 * source code. Additional authorship citations may be added, but existing
 * author citations must be preserved.
 ***************************************************************************/
/***************************************************************************
 *
 * Author: "Jian Wang"
 * Email: "wj_hust08@hust.edu.cn"
 *
 ***************************************************************************/

#include <cfloat>
#include "cppsci_array.h"
#include "cppsci_fft.h"
#include "cppsci_filter.h"
#include "./mpi.h"

namespace cppsci {

int correlate1d(Arrayd &input, Arrayd &output, const Arrayd &weights, int axis, int mode_code, double cval, int origin) {
    using namespace std;
    int filter_size = weights.shape(0);
    int size1 = filter_size / 2;
    int size2 = filter_size - size1 - 1;
    const double *fw = weights.data;
    int symmetric = 0;
    int ii, jj, ll;
    if (filter_size & 0x1) {
        symmetric = 1;
        for(ii = 1; ii <= filter_size / 2; ii++) {
            if (fabs(fw[ii + size1] - fw[size1 - ii]) > DBL_EPSILON) {
                symmetric = 0;
                break;
            }
        }
        if (symmetric == 0) {
            symmetric = -1;
            for(ii = 1; ii <= filter_size / 2; ii++) {
                if (fabs(fw[size1 + ii] + fw[size1 - ii]) > DBL_EPSILON) {
                    symmetric = 0;
                    break;
                }
            }
        }
    }
    //MPI_LOG << "symmetric: " << symmetric << ::std::endl;
    fw += size1;
    int length = input.shape(axis);
    //MPI_LOG << input.shape(0) << ' ' << axis << ' ' << size1+origin << ' ' << size2-origin << ::std::endl;
    ArrayLines ilines(input.shape(), axis, size1+origin, size2-origin);
    //MPI_LOG << "input:\n" << input << ::std::endl;
    ilines.read_array(input);
    ArrayLines olines(input.shape(), axis, 0, 0);
    double *pi = ilines.data;
    double *po = olines.data;

//#ifdef USEMPI
//
//    int mSize = mpiSize();
//    int mRank = mpiRank();
//    int mBin = int(::std::ceil(ilines.shape(0)/(double)mSize));
//    int lastBin = ilines.shape(0) - (mRank-1)*mBin;
//    int mBeg = mRank*mBin;
//    for (int ii = mBeg; ii < mBeg+mBin && ii < ilines.shape(0); ii++) {
//
//#else

#pragma omp parallel for
    for (int ii = 0; ii < ilines.shape(0); ii++) {

//#endif

        double *iline = ilines.data + ii * (length + size1 + size2) + size1;
        double *oline = olines.data + ii * length;
//        double *iline = pi + size1;
//        double *oline = po;
        /* the correlation calculation: */
        if (symmetric > 0) {
            for(ll = 0; ll < length; ll++) {
                oline[ll] = iline[0] * fw[0];
                for(jj = -size1 ; jj < 0; jj++) oline[ll] += (iline[jj] + iline[-jj]) * fw[jj];
                ++iline;
            }
        } else if (symmetric < 0) {
            for(ll = 0; ll < length; ll++) {
                oline[ll] = iline[0] * fw[0];
                for(jj = -size1 ; jj < 0; jj++) oline[ll] += (iline[jj] - iline[-jj]) * fw[jj];
                ++iline;
            }
        } else {
            for(ll = 0; ll < length; ll++) {
                oline[ll] = iline[size2] * fw[size2];
                for(jj = -size1; jj < size2; jj++) oline[ll] += iline[jj] * fw[jj];
                ++iline;
            }
        }
//        pi += length + size1 + size2;
//        po += length;
    }

//#ifdef USEMPI
//
//    double *tempBuf = new double[olines.size()];
//
//    int sendBin = (mRank==mSize-1 ? lastBin : mBin);
//    for (int i = 0; i < mSize; i++)  if (i != mRank) {
//        MPI_Send(olines.data+mBeg, sendBin, MPI_DOUBLE, i, mRank, MPI_COMM_WORLD);
//    }
//    MPI_Status mpiStatus;
//    for (int i = 0; i < mSize; i++)  if (i != mRank) {
//        int recvBin = (i==mSize-1 ? lastBin : mBin);
//        MPI_Recv(tempBuf+mBeg, recvBin, MPI_DOUBLE, i, i, MPI_COMM_WORLD, &mpiStatus);
//    }
//
//    delete [] olines.data;
//    olines.data = tempBuf;
//
//#endif

    olines.write_array(output);
    return 1;
}

static int extend_mode_to_code(::std::string mode) {
    if (mode == "nearest") return 0;
    else if (mode == "wrap") return 1;
    else if (mode == "reflect") return 2;
    else if (mode == "mirror") return 3;
    else if (mode == "constant") return 4;
    else return -1;
}

static bool gaussian_filter1d(Arrayd &input, double sigma, int axis, int order, ::std::string mode, double cval, double truncate) {
    if (order > 4 || order < 0) return false;
    int mode_code = extend_mode_to_code(mode);
    double sd = sigma;
    // make the radius of the filter equal to truncate standard deviations
    int lw = int(truncate * sd + 0.5);
    Arrayd weights({2*lw+1}, 0.0);
    weights[lw] = 1.0;
    double sum = 1.0;
    sd = sd * sd;
    // calculate the kernel:
    for (int ii = 1; ii < lw+1; ii++) {
        double tmp = ::std::exp(-0.5 * double(ii * ii) / sd);
        weights[lw + ii] = tmp;
        weights[lw - ii] = tmp;
        sum += 2.0 * tmp;
    }
    for (int ii = 0; ii < 2*lw+1; ii++) weights[ii] /= sum;
    // implement first, second and third order derivatives:
    if (order == 1) {  // first derivative
        weights[lw] = 0.0;
        for (int ii = 1; ii < lw+1; ii++) {
            double x = double(ii);
            double tmp = -x / sd * weights[lw + ii];
            weights[lw + ii] = -tmp;
            weights[lw - ii] = tmp;
        }
    }
    else if (order == 2) {  // second derivative
        weights[lw] *= -1.0 / sd;
        for (int ii = 1; ii < lw+1; ii++) {
            double x = double(ii);
            double tmp = (x * x / sd - 1.0) * weights[lw + ii] / sd;
            weights[lw + ii] = tmp;
            weights[lw - ii] = tmp;
        }
    }
    else if (order == 3) {  // third derivative
        weights[lw] = 0.0;
        double sd2 = sd * sd;
        for (int ii = 1; ii < lw+1; ii++) {
            double x = double(ii);
            double tmp = (3.0 - x * x / sd) * x * weights[lw + ii] / sd2;
            weights[lw + ii] = -tmp;
            weights[lw - ii] = tmp;
        }
    }
    return correlate1d(input, input, weights, axis, mode_code, cval, 0);
}

Arrayd gaussian_filter(const Arrayd &input, double sigma, int order, ::std::string mode, double cval, double truncate) {
    Arrayd output = input;
    for (int i = 0; i < output.dim(); i++) {
        gaussian_filter1d(output, sigma, i, order, mode, cval, truncate);
    }
    return ::std::move(output);
}

} // namespace cppsci
