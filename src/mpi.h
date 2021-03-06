/***************************************************************************
 *
 * Authors: "Jian Wang"
 * 
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

#ifndef MPI_H_
#define MPI_H_

#include <cmath>
#include <iostream>
#include <cstring> /*memcpy*/
#include "cppsci_mkl.h"

#include "./macros.h"

// image division strategy for multi-nodes will be same as one-node.
// for Map2d_optimizer_old,Map3d_optimizer_old
//#define SAME_IMAGE_DIVISION

// build with MPI
//#define USEMPI

#ifdef USEMPI
#include <mpi.h>
#endif

#ifdef USEMPI
# define MPI_INITIALIZE(argc, argv) MPI_Init(argc, argv)
# define MPI_FINALIZE MPI_Finalize()
#else
# define MPI_INITIALIZE(argc, argv)
# define MPI_FINALIZE
#endif

inline int mpiRank() {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    return rank;
}

inline int mpiSize() {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    return size;
}

#define MPI_IS_ROOT (mpiRank() == 0)

#ifdef USEMPI
# define MPI_LOG if (MPI_IS_ROOT) ::std::cout
#else
# define MPI_LOG ::std::cout
#endif

#ifdef USEMPI
# define NODE0ONLY if (0 == node)
# define MASTERNODE if (0 == MPI::COMM_WORLD.Get_rank()) // when not define node
#else
# define NODE0ONLY
# define MASTERNODE
#endif

// Support compile-time checking of the MPI code
//
//#define FAKEMPI

#ifdef FAKEMPI
#define USEMPI UsingFakeMPI
static const int MPI_MAX_PROCESSOR_NAME = 256;
namespace MPI {
    enum E {DOUBLE,FLOAT,SUM};
    class COMM_WORLD_CLASS {
    public:
        static void Barrier() {}
        static void Bcast(void*, int, E, int) {}
        static void Reduce(void*, void*, int, E, E, int) {}
        static void Allreduce(void*, void*, int, E, E) {}
    } COMM_WORLD;
};
#endif

#if defined(FLOAT_PRECISION)
#define MPI_FDOUBLE MPI::FLOAT
#else
#define MPI_FDOUBLE MPI::DOUBLE 
#endif


// Divides a number into most equally groups
int divide_equally(int N, int size, int rank,int &first,int &last);

// Devides a number into most equally groups
// consider the nr_pool in map,this will give same Devided Strategy for different nodes
int divide_equally_pool(int N, int nr_pool, int size, int rank,int &first,int &last);

// In which group from divide_equally is myself?
int divide_equally_which_group(int N, int size,int myself);

// devide N by nodes
int divideIndex(int N,int nodes,int node,int &n_start,int &n_end);


//#if 0
//#include <mpi.h>
//
///**** out-place tranposition of Mat(NxD) in cluster,the Mat size is (N/node)xD in each node,
//and newMat size is Dx(D/nodes) ****/
//void transposeMatCluster(double* Mat,double *newMat,int N,int D,int node,int nodes);
//void transposeMatCluster(float* Mat,float *newMat,int N,int D,int node,int nodes);
//
///**** using the file IO to tranpose matrix in cluster ****/
//void transposeMatClusterIO(float* Mat,float *newMat,int N,int D,int node,int nodes);
//
///**** gather specific rows of Mat(NxD) from each node,the rowIndex store the specific row index and 
//Mat size is (N/nodes)xD in each node ,the newMat size is number_of_rowxD ****/
//void gaterOneMatCluster(float* Mat,float *newMat,int N,int D,int *rowIndex,int rowIndexLength,int dist_node,int node,int nodes);
//
///**** using the file IO to gather specific row of Matrix for each node,
//be careful !!!!!!,make sure your rowIndex for each node is form small to large   ****/
//void gaterMatClusterIO(float* Mat,float *newMat,int N,int D,int *rowIndex,int *rowIndexLength,int node,int nodes,bool updateTemp = true);
//
///**** divided the Matrix(N*D) in cluster,each Mat in node will have different number of Row for Matrix
//the newMat is equally divided by nodes****/
//void divideMatClusterIO(float* Mat,float *newMat,int *subN,int D,int node,int nodes);
//#endif

#endif
