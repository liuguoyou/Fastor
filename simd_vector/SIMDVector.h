#ifndef SIMDVECTOR_H
#define SIMDVECTOR_H

#include "simd_vector_base.h"
#include "simd_vector_float.h"
#include "simd_vector_double.h"
#include "simd_vector_int.h"
#include "simd_vector_int64.h"


// Generic overloads
namespace Fastor {

template<typename T>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> exp(const SIMDVector<T,DEFAULT_ABI> &a) {
    SIMDVector<T,DEFAULT_ABI> out;
    out.value = internal_exp(a.value);
    return out;
}

template<typename T>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> log(const SIMDVector<T,DEFAULT_ABI> &a) {
    SIMDVector<T,DEFAULT_ABI> out;
    out.value = internal_log(a.value);
    return out;
}

template<typename T, typename U>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> pow(const SIMDVector<T,DEFAULT_ABI> &a, const SIMDVector<U,DEFAULT_ABI> &b) {
    SIMDVector<T,DEFAULT_ABI> out;
    out.value = internal_pow(a.value, b.value);
    return out;
}

template<typename T, typename U>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> pow(const SIMDVector<T,DEFAULT_ABI> &a, U bb) {
    SIMDVector<T,DEFAULT_ABI> out;
    SIMDVector<T,DEFAULT_ABI> b = static_cast<T>(bb);
    out.value = internal_pow(a.value, b.value);
    return out;
}

template<typename T>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> sin(const SIMDVector<T,DEFAULT_ABI> &a) {
    SIMDVector<T,DEFAULT_ABI> out;
    out.value = internal_sin(a.value);
    return out;
}

template<typename T>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> cos(const SIMDVector<T,DEFAULT_ABI> &a) {
    SIMDVector<T,DEFAULT_ABI> out;
    out.value = internal_cos(a.value);
    return out;
}

template<typename T>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> tan(const SIMDVector<T,DEFAULT_ABI> &a) {
    SIMDVector<T,DEFAULT_ABI> out;
    out.value = internal_tan(a.value);
    return out;
}

template<typename T>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> asin(const SIMDVector<T,DEFAULT_ABI> &a) {
    SIMDVector<T,DEFAULT_ABI> out;
    out.value = internal_asin(a.value);
    return out;
}

template<typename T>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> acos(const SIMDVector<T,DEFAULT_ABI> &a) {
    SIMDVector<T,DEFAULT_ABI> out;
    out.value = internal_acos(a.value);
    return out;
}

template<typename T>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> atan(const SIMDVector<T,DEFAULT_ABI> &a) {
    SIMDVector<T,DEFAULT_ABI> out;
    out.value = internal_atan(a.value);
    return out;
}

template<typename T>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> sinh(const SIMDVector<T,DEFAULT_ABI> &a) {
    SIMDVector<T,DEFAULT_ABI> out;
    out.value = internal_sinh(a.value);
    return out;
}

template<typename T>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> cosh(const SIMDVector<T,DEFAULT_ABI> &a) {
    SIMDVector<T,DEFAULT_ABI> out;
    out.value = internal_cosh(a.value);
    return out;
}

template<typename T>
FASTOR_INLINE SIMDVector<T,DEFAULT_ABI> tanh(const SIMDVector<T,DEFAULT_ABI> &a) {
    SIMDVector<T,DEFAULT_ABI> out;
    out.value = internal_tanh(a.value);
    return out;
}





// Broadcasting vectorisation on general strides [gather operations]
//----------------------------------------------------------------------------------------------------------------
// 4 word scalar
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==4 && ABI==32,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, int idx, int ) {
    vec.set(data[idx]);
}
// 4 word SSE
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==4 && ABI==128,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, int idx, int general_stride) {
    vec.set(data[idx+3*general_stride],data[idx+2*general_stride],data[idx+general_stride],data[idx]);
}
// 4 word AVX
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==4 && ABI==256,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, int idx, int general_stride) {
    vec.set(data[idx+7*general_stride],data[idx+6*general_stride],
            data[idx+5*general_stride],data[idx+4*general_stride],
            data[idx+3*general_stride],data[idx+2*general_stride],
            data[idx+general_stride],data[idx]);
}
// 4 word AVX 512
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==4 && ABI==512,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, int idx, int general_stride) {
    vec.set(data[idx+15*general_stride],data[idx+14*general_stride],
            data[idx+13*general_stride],data[idx+12*general_stride],
            data[idx+11*general_stride],data[idx+10*general_stride],
            data[idx+9*general_stride],data[idx+8*general_stride],
            data[idx+7*general_stride],data[idx+6*general_stride],
            data[idx+5*general_stride],data[idx+4*general_stride],
            data[idx+3*general_stride],data[idx+2*general_stride],
            data[idx+general_stride],data[idx]);
}

// 8 word scalar
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==8 && ABI==64,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, int idx, int ) {
    vec.set(data[idx]);
}
// 8 word SSE
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==8 && ABI==128,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, int idx, int general_stride) {
    vec.set(data[idx+general_stride],data[idx]);
}
// 8 word AVX
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==8 && ABI==256,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, int idx, int general_stride) {
    vec.set(data[idx+3*general_stride],data[idx+2*general_stride],
            data[idx+general_stride],data[idx]);
}
// 8 word AVX 512
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==8 && ABI==512,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, int idx, int general_stride) {
    vec.set(data[idx+7*general_stride],data[idx+6*general_stride],
            data[idx+5*general_stride],data[idx+4*general_stride],
            data[idx+3*general_stride],data[idx+2*general_stride],
            data[idx+general_stride],data[idx]);
}
//----------------------------------------------------------------------------------------------------------------


// [Gather operations], when strides are not constant (i.e totally random)
//----------------------------------------------------------------------------------------------------------------
// 4 word scalar
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==4 && ABI==32,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, const std::array<int,1> &a) {
    vec.set(data[a[0]]);
}
// 4 word SSE
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==4 && ABI==128,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, const std::array<int,4> a) {
    vec.set(data[a[3]],data[a[2]],data[a[1]],data[a[0]]);
}
// 4 word AVX
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==4 && ABI==256,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, const std::array<int,8> a) {
    vec.set(data[a[7]],data[a[6]],data[a[5]],data[a[4]],
            data[a[3]],data[a[2]],data[a[1]],data[a[0]]);
}
// 4 word AVX 512
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==4 && ABI==512,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, const std::array<int,16> a) {
    vec.set(data[a[15]],data[a[14]],data[a[13]],data[a[12]],
            data[a[11]],data[a[10]],data[a[9]],data[a[8]],
            data[a[7]],data[a[6]],data[a[5]],data[a[4]],
            data[a[3]],data[a[2]],data[a[1]],data[a[0]]);
}

// 8 word scalar
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==8 && ABI==64,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, const std::array<int,1> &a) {
    vec.set(data[a[0]]);
}
// 8 word SSE
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==8 && ABI==128,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, const std::array<int,2> a) {
    vec.set(data[a[1]],data[a[0]]);
}
// 8 word AVX
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==8 && ABI==256,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, const std::array<int,4> a) {
    vec.set(data[a[3]],data[a[2]],data[a[1]],data[a[0]]);
}
// 8 word AVX 512
template<typename T, int ABI,
         typename std::enable_if<sizeof(T)==8 && ABI==512,bool>::type=0>
FASTOR_INLINE void vector_setter(SIMDVector<T,ABI> &vec, const T *data, const std::array<int,8> a) {
    vec.set(data[a[7]],data[a[6]],data[a[5]],data[a[4]],
            data[a[3]],data[a[2]],data[a[1]],data[a[0]]);
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------




// Scatter operations
//----------------------------------------------------------------------------------------------------------------
// 4 word scalar
template<typename T, int ABI, typename Int,
         typename std::enable_if<sizeof(T)==4 && ABI==32,bool>::type=0>
FASTOR_INLINE void data_setter(T *FASTOR_RESTRICT data, const SIMDVector<T,ABI> &vec, Int idx, int ) {
    data[idx] = vec.value;
}
// 4 word SSE
template<typename T, int ABI, typename Int,
         typename std::enable_if<sizeof(T)==4 && ABI==128,bool>::type=0>
FASTOR_INLINE void data_setter(T *FASTOR_RESTRICT data, const SIMDVector<T,ABI> &vec, Int idx, int general_stride=1) {
    data[idx] = vec[0];
    data[idx+general_stride] = vec[1];
    data[idx+2*general_stride] = vec[2];
    data[idx+3*general_stride] = vec[3];
}
// 4 word AVX
template<typename T, int ABI, typename Int,
         typename std::enable_if<sizeof(T)==4 && ABI==256,bool>::type=0>
FASTOR_INLINE void data_setter(T *FASTOR_RESTRICT data, const SIMDVector<T,ABI> &vec, Int idx, int general_stride=1) {
    data[idx] = vec[0];
    data[idx+general_stride] = vec[1];
    data[idx+2*general_stride] = vec[2];
    data[idx+3*general_stride] = vec[3];
    data[idx+4*general_stride] = vec[4];
    data[idx+5*general_stride] = vec[5];
    data[idx+6*general_stride] = vec[6];
    data[idx+7*general_stride] = vec[7];
}
// 4 word AVX 512
template<typename T, int ABI, typename Int,
         typename std::enable_if<sizeof(T)==4 && ABI==512,bool>::type=0>
FASTOR_INLINE void data_setter(T *FASTOR_RESTRICT data, const SIMDVector<T,ABI> &vec, Int idx, int general_stride=1) {
    data[idx] = vec[0];
    data[idx+general_stride] = vec[1];
    data[idx+2*general_stride] = vec[2];
    data[idx+3*general_stride] = vec[3];
    data[idx+4*general_stride] = vec[4];
    data[idx+5*general_stride] = vec[5];
    data[idx+6*general_stride] = vec[6];
    data[idx+7*general_stride] = vec[7];
    data[idx+8*general_stride] = vec[8];
    data[idx+9*general_stride] = vec[9];
    data[idx+10*general_stride] = vec[10];
    data[idx+11*general_stride] = vec[11];
    data[idx+12*general_stride] = vec[12];
    data[idx+13*general_stride] = vec[13];
    data[idx+14*general_stride] = vec[14];
    data[idx+15*general_stride] = vec[15];
}

// 8 word scalar
template<typename T, int ABI, typename Int,
         typename std::enable_if<sizeof(T)==8 && ABI==64,bool>::type=0>
FASTOR_INLINE void data_setter(T *FASTOR_RESTRICT data, const SIMDVector<T,ABI> &vec, Int idx, int ) {
    data[idx] = vec.value;
}
// 8 word SSE
template<typename T, int ABI, typename Int,
         typename std::enable_if<sizeof(T)==8 && ABI==128,bool>::type=0>
FASTOR_INLINE void data_setter(T *FASTOR_RESTRICT data, const SIMDVector<T,ABI> &vec, Int idx, int general_stride) {
    data[idx] = vec[0];
    data[idx+general_stride] = vec[1];
}
// 8 word AVX
template<typename T, int ABI, typename Int,
         typename std::enable_if<sizeof(T)==8 && ABI==256,bool>::type=0>
FASTOR_INLINE void data_setter(T *FASTOR_RESTRICT data, const SIMDVector<T,ABI> &vec, Int idx, int general_stride) {
    data[idx] = vec[0];
    data[idx+general_stride] = vec[1];
    data[idx+2*general_stride] = vec[2];
    data[idx+3*general_stride] = vec[3];
}
// 8 word AVX 512
template<typename T, int ABI, typename Int,
         typename std::enable_if<sizeof(T)==8 && ABI==512,bool>::type=0>
FASTOR_INLINE void data_setter(T *FASTOR_RESTRICT data, const SIMDVector<T,ABI> &vec, Int idx, int general_stride) {
    data[idx] = vec[0];
    data[idx+general_stride] = vec[1];
    data[idx+2*general_stride] = vec[2];
    data[idx+3*general_stride] = vec[3];
    data[idx+4*general_stride] = vec[4];
    data[idx+5*general_stride] = vec[5];
    data[idx+6*general_stride] = vec[6];
    data[idx+7*general_stride] = vec[7];
}
//----------------------------------------------------------------------------------------------------------------









// FMAs
//----------------------------------------------------------------------------------------------------------------
template<typename T, int ABI>
FASTOR_INLINE SIMDVector<T,ABI> fmadd(SIMDVector<T,ABI> a, SIMDVector<T,ABI> b, SIMDVector<T,ABI> c) {
    return a*b+c;
}
// Note that fmsub alternatively adds and subtracts simd vectors
template<typename T, int ABI>
FASTOR_INLINE SIMDVector<T,ABI> fmsub(SIMDVector<T,ABI> a, SIMDVector<T,ABI> b, SIMDVector<T,ABI> c) {
    return a*b+c;
}

#ifdef __FMA__

template<>
FASTOR_INLINE SIMDVector<float,SSE> fmadd<float,SSE>(SIMDVector<float,SSE> a, SIMDVector<float,SSE> b, SIMDVector<float,SSE> c) {
    SIMDVector<float,SSE> out;
    out.value = _mm_fmadd_ps(a.value,b.value,c.value);
    return out;
}
template<>
FASTOR_INLINE SIMDVector<float,AVX> fmadd<float,AVX>(SIMDVector<float,AVX> a, SIMDVector<float,AVX> b, SIMDVector<float,AVX> c) {
    SIMDVector<float,AVX> out;
    out.value = _mm256_fmadd_ps(a.value,b.value,c.value);
    return out;
}
template<>
FASTOR_INLINE SIMDVector<double,SSE> fmadd<double,SSE>(SIMDVector<double,SSE> a, SIMDVector<double,SSE> b, SIMDVector<double,SSE> c) {
    SIMDVector<double,SSE> out;
    out.value = _mm_fmadd_pd(a.value,b.value,c.value);
    return out;
}
template<>
FASTOR_INLINE SIMDVector<double,AVX> fmadd<double,AVX>(SIMDVector<double,AVX> a, SIMDVector<double,AVX> b, SIMDVector<double,AVX> c) {
    SIMDVector<double,AVX> out;
    out.value = _mm256_fmadd_pd(a.value,b.value,c.value);
    return out;
}

template<>
FASTOR_INLINE SIMDVector<float,SSE> fmsub<float,SSE>(SIMDVector<float,SSE> a, SIMDVector<float,SSE> b, SIMDVector<float,SSE> c) {
    SIMDVector<float,SSE> out;
    out.value = _mm_fmadd_ps(a.value,b.value,c.value);
    return out;
}
template<>
FASTOR_INLINE SIMDVector<float,AVX> fmsub<float,AVX>(SIMDVector<float,AVX> a, SIMDVector<float,AVX> b, SIMDVector<float,AVX> c) {
    SIMDVector<float,AVX> out;
    out.value = _mm256_fmadd_ps(a.value,b.value,c.value);
    return out;
}
template<>
FASTOR_INLINE SIMDVector<double,SSE> fmsub<double,SSE>(SIMDVector<double,SSE> a, SIMDVector<double,SSE> b, SIMDVector<double,SSE> c) {
    SIMDVector<double,SSE> out;
    out.value = _mm_fmadd_pd(a.value,b.value,c.value);
    return out;
}
template<>
FASTOR_INLINE SIMDVector<double,AVX> fmsub<double,AVX>(SIMDVector<double,AVX> a, SIMDVector<double,AVX> b, SIMDVector<double,AVX> c) {
    SIMDVector<double,AVX> out;
    out.value = _mm256_fmadd_pd(a.value,b.value,c.value);
    return out;
}

#endif
//----------------------------------------------------------------------------------------------------------------

}

#endif // SIMDVECTOR_H

