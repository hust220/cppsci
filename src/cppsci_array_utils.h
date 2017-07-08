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

#pragma once

#include "cppsci_array_core.h"

namespace cppsci {

#define JN_IS_COMPLEX(_type) jn_is_complex<typename jn_array_val<_type>::type>::value

    template<typename T>
    struct jn_is_complex {
        private:
            using F = typename ::std::decay<T>::type;
            template<typename _Val> static ::std::true_type check(::std::complex<_Val>);
            static ::std::false_type check(...);
        public:
            enum { value = ::std::is_same<decltype(check(::std::declval<F>())), ::std::true_type>::value };
    };

    template<typename T>
    struct jn_complex_val {
        private:
            using F = typename ::std::decay<T>::type;
            template<typename _Val> static _Val check(::std::complex<_Val>);
            static T check(...);
        public:
            using type = decltype(check(::std::declval<F>()));
    };

    template<typename T>
    struct jn_array_val {
        private:
            using F = typename ::std::decay<T>::type;
            template<typename _Val, typename _Derived> static _Val check(BasicArray<_Val, _Derived>);
            template<typename _Val                   > static _Val check(Array<_Val>);
            template<typename _Val                   > static _Val check(SubArray<_Val>);
            template<typename _Val                   > static _Val check(MapArray<_Val>);
            static T check(...);
        public:
            using type = decltype(check(::std::declval<F>()));
    };

#define JN_DEF_BINARY_OP(T, V, W) \
        static W check(T, V); \
        static W check(V, T);

    template<typename T, typename V>
    struct jn_simple_op_type {
        private:
            using F = typename ::std::decay<T>::type;
            using G = typename ::std::decay<V>::type;
            template<typename K> static K check(K, K);
            //static ::std::false check(...);
    JN_DEF_BINARY_OP(bool, unsigned int,       unsigned int)
    JN_DEF_BINARY_OP(bool, unsigned long,      unsigned long)
    JN_DEF_BINARY_OP(bool, unsigned long long, unsigned long long)
    JN_DEF_BINARY_OP(bool, short,              short)
    JN_DEF_BINARY_OP(bool, int,                int)
    JN_DEF_BINARY_OP(bool, long,               long)
    JN_DEF_BINARY_OP(bool, long long,          long long)
    JN_DEF_BINARY_OP(bool, float,              float)
    JN_DEF_BINARY_OP(bool, double,             double)
    JN_DEF_BINARY_OP(bool, long double,        long double)

    JN_DEF_BINARY_OP(unsigned short, unsigned int,       unsigned int)
    JN_DEF_BINARY_OP(unsigned short, unsigned long,      unsigned long)
    JN_DEF_BINARY_OP(unsigned short, unsigned long long, unsigned long long)
    JN_DEF_BINARY_OP(unsigned short, short,              short)
    JN_DEF_BINARY_OP(unsigned short, int,                int)
    JN_DEF_BINARY_OP(unsigned short, long,               long)
    JN_DEF_BINARY_OP(unsigned short, long long,          long long)
    JN_DEF_BINARY_OP(unsigned short, float,              float)
    JN_DEF_BINARY_OP(unsigned short, double,             double)
    JN_DEF_BINARY_OP(unsigned short, long double,        long double)

    JN_DEF_BINARY_OP(unsigned int, unsigned long,      unsigned long)
    JN_DEF_BINARY_OP(unsigned int, unsigned long long, unsigned long long)
    //JN_DEF_BINARY_OP(unsigned int, short,              short)
    JN_DEF_BINARY_OP(unsigned int, int,                int)
    JN_DEF_BINARY_OP(unsigned int, long,               long)
    JN_DEF_BINARY_OP(unsigned int, long long,          long long)
    JN_DEF_BINARY_OP(unsigned int, float,              float)
    JN_DEF_BINARY_OP(unsigned int, double,             double)
    JN_DEF_BINARY_OP(unsigned int, long double,        long double)

    JN_DEF_BINARY_OP(unsigned long, unsigned long long, unsigned long long)
    //JN_DEF_BINARY_OP(unsigned long, short,              short)
    //JN_DEF_BINARY_OP(unsigned long, int,                int)
    JN_DEF_BINARY_OP(unsigned long, long,               long)
    JN_DEF_BINARY_OP(unsigned long, long long,          long long)
    JN_DEF_BINARY_OP(unsigned long, float,              float)
    JN_DEF_BINARY_OP(unsigned long, double,             double)
    JN_DEF_BINARY_OP(unsigned long, long double,        long double)

    //JN_DEF_BINARY_OP(unsigned long long, short,              short)
    //JN_DEF_BINARY_OP(unsigned long long, int,                int)
    //JN_DEF_BINARY_OP(unsigned long long, long,               long)
    JN_DEF_BINARY_OP(unsigned long long, long long,          long long)
    JN_DEF_BINARY_OP(unsigned long long, float,              float)
    JN_DEF_BINARY_OP(unsigned long long, double,             double)
    JN_DEF_BINARY_OP(unsigned long long, long double,        long double)

    JN_DEF_BINARY_OP(short, int,                int)
    JN_DEF_BINARY_OP(short, long,               long)
    JN_DEF_BINARY_OP(short, long long,          long long)
    JN_DEF_BINARY_OP(short, float,              float)
    JN_DEF_BINARY_OP(short, double,             double)
    JN_DEF_BINARY_OP(short, long double,        long double)

    JN_DEF_BINARY_OP(int, long,               long)
    JN_DEF_BINARY_OP(int, long long,          long long)
    JN_DEF_BINARY_OP(int, float,              float)
    JN_DEF_BINARY_OP(int, double,             double)
    JN_DEF_BINARY_OP(int, long double,        long double)

    JN_DEF_BINARY_OP(long, long long,          long long)
    JN_DEF_BINARY_OP(long, float,              float)
    JN_DEF_BINARY_OP(long, double,             double)
    JN_DEF_BINARY_OP(long, long double,        long double)

    JN_DEF_BINARY_OP(long long, float,              float)
    JN_DEF_BINARY_OP(long long, double,             double)
    JN_DEF_BINARY_OP(long long, long double,        long double)

    JN_DEF_BINARY_OP(float, double,             double)
    JN_DEF_BINARY_OP(float, long double,        long double)

    JN_DEF_BINARY_OP(double, long double,        long double)
        public:
            using type = decltype(check(::std::declval<F>(), ::std::declval<G>()));
    };

    template<typename T, typename V>
    struct jn_complex_op_type {
        private:
            using F = typename ::std::decay<T>::type;
            using G = typename ::std::decay<V>::type;
            template<typename _V1, typename _V2, JN_ENABLE(JN_IS_COMPLEX(_V1) || JN_IS_COMPLEX(_V2))>
            static auto check(_V1, _V2)
                -> typename jn_simple_op_type<typename jn_complex_val<_V1>::type, typename jn_complex_val<_V2>::type>::type;
            static auto check(...)
                -> typename jn_simple_op_type<F, G>::type;
        public:
            using type = decltype(check(::std::declval<F>(), ::std::declval<G>()));
    };

#define JN_BINARY_OP_TYPE(T, V) typename jn_complex_op_type<typename ::std::decay<T>::type, typename ::std::decay<V>::type>::type

#define JN_ARR_BIN_RT(type1, type2)                                                     \
            Array<JN_BINARY_OP_TYPE(typename jn_array_val<type1>::type, typename jn_array_val<type2>::type)>

#define JN_DEF_ARRAY_BINARY_OP(name, name2)                                                   \
        template<typename T, typename V, JN_ENABLE(JN_IS_ARRAY(T) || JN_IS_ARRAY(V))>                                                       \
        auto name(const T &a1, const V &a2) -> JN_ARR_BIN_RT(T, V)         \
        {                                                                                      \
            using rt = JN_ARR_BIN_RT(T, V); \
            return rt::name2(a1, a2);                              \
        }

    JN_DEF_ARRAY_BINARY_OP(operator +,  plus         )
    JN_DEF_ARRAY_BINARY_OP(operator -,  minus        )
    JN_DEF_ARRAY_BINARY_OP(operator *,  times        )
    JN_DEF_ARRAY_BINARY_OP(operator /,  divide       )
    JN_DEF_ARRAY_BINARY_OP(operator >,  gt           )
    JN_DEF_ARRAY_BINARY_OP(operator <,  lt           )
    JN_DEF_ARRAY_BINARY_OP(operator >=, ge           )
    JN_DEF_ARRAY_BINARY_OP(operator <=, le           )
    JN_DEF_ARRAY_BINARY_OP(operator ==, eq           )

        // Note: These four operators can't be overloaded !!!
    //JN_DEF_ARRAY_BINARY_OP(operator &,  bitAnd       )
    //JN_DEF_ARRAY_BINARY_OP(operator |,  bitOr        )
    //JN_DEF_ARRAY_BINARY_OP(operator &&, logicalAnd   )
    //JN_DEF_ARRAY_BINARY_OP(operator ||, logicalOr    )

} // namespace cppsci

namespace std {

    using namespace cppsci;

    JN_DEF_ARRAY_BINARY_OP(pow, pow);

    template<typename T, JN_ENABLE(JN_IS_ARRAY(T))>                                                                   
    T log(const T &a1)                    
    {                                                                                      
        return T::log(a1);                                                           
    }

    template<typename T, JN_ENABLE(JN_IS_ARRAY(T))>                                                                   
    T exp(const T &a1)                    
    {                                                                                      
        return T::exp(a1);                                                           
    }

    template<typename T, JN_ENABLE(JN_IS_ARRAY(T) && JN_IS_COMPLEX(T))>                                                                   
    T conj(const T &a1)                    
    {                                                                                      
        return T::conj(a1);                                                           
    }

    template<typename T, JN_ENABLE(JN_IS_ARRAY(T) && JN_IS_COMPLEX(T))>                                                                   
    Array<typename jn_complex_val<typename jn_array_val<T>::type>::type> real(const T &a1)                    
    {                                                                                      
        return T::real(a1);                                                           
    }

    template<typename T, JN_ENABLE(JN_IS_ARRAY(T) && JN_IS_COMPLEX(T))>                                                                   
    Array<typename jn_complex_val<typename jn_array_val<T>::type>::type> imag(const T &a1)                    
    {                                                                                      
        return T::imag(a1);                                                           
    }

    template<typename T, JN_ENABLE(JN_IS_ARRAY(T))>                                                                   
    Array<typename jn_complex_val<typename jn_array_val<T>::type>::type> abs(const T &a1)                    
    {                                                                                      
        return T::abs(a1);                                                           
    }

    template<typename T, JN_ENABLE(JN_IS_ARRAY(T))>                                                                   
    T diag(const T &a1)                    
    {                                                                                      
        return T::diag(a1);                                                           
    }

} // namespace std

namespace cppsci {

inline void extend_line(double *l, int length, int size1, int size2) {
    if (size1 != 0) {
        double *ll = l + size1-1;
        double *rr = ll+1;
        int n = size1 / length;
        int r = size1 % length;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < length; j++) *ll-- = *rr++;
            rr -= 2*length;
        }
        for (int j = 0; j < r; j++) *ll-- = *rr++;
    }

    if (size2 != 0) {
        double *ll = l + size1 + length -1;
        double *rr = ll+1;
        int n = size2 / length;
        int r = size2 % length;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < length; j++) *rr++ = *ll--;
            ll += 2*length;
        }
        for (int j = 0; j < r; j++) *rr++ = *ll--;
    }
}

class ArrayLines : public Arrayd {
public:
    using base_type = Arrayd;

    Shape array_shape;
    Shape array_coeff;

    int axis;
    int size1;
    int size2;
    int nd;
    int length;

    ArrayLines(const Shape &_shape, int _axis, int _size1 = 0, int _size2 = 0) :
        array_shape(_shape), axis(_axis), size1(_size1), size2(_size2), 
        Arrayd({::std::accumulate(_shape.begin(), _shape.end(), 1, [](int a, int b){return a *b;}) / _shape[_axis], _shape[_axis]+_size1+_size2})
    {
        nd = _shape.size();
        length = _shape[_axis];
        array_coeff.resize(nd);
        int l = length+size1+size2;
        int k = l;
        for (int j = nd-1; j >= 0; j--) {
            if (j == axis) array_coeff[j] = 1;
            else {
                array_coeff[j] = k;
                k *= _shape[j];
            }
        }
        //MPI_LOG << "array_coeff: ";
        //for (auto && n : array_coeff) MPI_LOG << n << ' '; MPI_LOG << ::std::endl;
    }

    void read_array(const Arrayd &array) {
//        MPI_LOG << __FUNCTION__ << ::std::endl;
//        MPI_LOG << "lss: " << length << ' ' << size1 << ' ' << size2 << ::std::endl;
//        MPI_LOG << "shape: " << base_type::shape(0) << ' ' << base_type::shape(1) << ::std::endl;
        int m = 0;
//        MPI_LOG << "nd: " << nd << ::std::endl;
        ARRAY_EACH(array.shape(), ind) {
//            for (int i = 0;i < nd; i++) MPI_LOG << ind[i] << ' '; MPI_LOG << ::std::endl;
//            MPI_LOG << "coeff1: "; for (int i = 0;i < nd; i++) MPI_LOG << array_coeff[i] << ' '; MPI_LOG << ::std::endl;
            int n = 0;
            for (int j = 0; j < nd; j++) n += array_coeff[j]*ind[j];
//            MPI_LOG << "coeff2: "; for (int i = 0;i < nd; i++) MPI_LOG << array_coeff[i] << ' '; MPI_LOG << ::std::endl;
//            MPI_LOG << n+size1 << ' ' << m << ::std::endl;
//            MPI_LOG << "coeff3: "; for (int i = 0;i < nd; i++) MPI_LOG << array_coeff[i] << ' '; MPI_LOG << ::std::endl;
//            MPI_LOG << base_type::size() << ::std::endl;
            base_type::at(n+size1) = array[m];
//            MPI_LOG << "coeff4: "; for (int i = 0;i < nd; i++) MPI_LOG << array_coeff[i] << ' '; MPI_LOG << ::std::endl;
            m++;
        }
        double *p = base_type::data;
        for (int j = 0; j < base_type::shape(0); j++) {
            extend_line(p, length, size1, size2);
            p += length+size1+size2;
        }
    }

    void write_array(Arrayd &array) {
        int m = 0;
        ARRAY_EACH(array.shape(), ind) {
            int n = 0;
            for (int j = 0; j < nd; j++) n += array_coeff[j]*ind[j];
            array[m] = base_type::at(n+size1);
            m++;
        }
    }

};

} // namespace cppsci


