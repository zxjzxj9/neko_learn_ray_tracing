//
// Created by Victor Zhang on 2018/12/2.
//

#ifndef NEKO_LEARN_RAY_TRACING_VEC_H
#define NEKO_LEARN_RAY_TRACING_VEC_H

// Define the vec3 class

#include <cstdarg>
#include <memory>
#include <iostream>
#include <cmath>
#include <cassert>
#include <initializer_list>
#include <algorithm>
#include "render.h"

template <int N>
class vec {
public:
    const int dim = N;
    // Sadly va_list not support float
    vec(const std::initializer_list<float>& a) {
        this->data = std::unique_ptr<float []>(new float[N]);
        assert(a.size()==N);
        std::copy(std::begin(a), std::end(a), this->data.get());
    }


    vec(const std::initializer_list<double>& a) {
        this->data = std::unique_ptr<float []>(new float[N]);
        assert(a.size()==N);
        std::transform(std::begin(a), std::end(a), data.get(), [](double x){return static_cast<float>(x);});
        //std::copy(std::begin(a), std::end(a), data.get());
    }
    //vec(Color c, double a1, ...): c(c) {
    //    data = std::unique_ptr<float []>(new float[N]);
    //    va_list args;
    //    va_start(args, a1);
    //    data[0] = static_cast<float>(a1);
    //    for(int i=1; i<N; i++) {
    //        data[i] = static_cast<float>(va_arg(args, double));
    //    }
    //    va_end(args);
    //}

    vec() {
        data = std::unique_ptr<float []>(new float[N]);
    }

    vec(const vec& v) {
        data = std::unique_ptr<float []>(new float[N]);
        for(int i=0; i<N; i++) {
            data[i] = v.data[i];
        }
    }


    vec& operator=(const vec& v) {
       assert(this->dim == v.dim);
       if(!data) {
           data = std::unique_ptr<float[]>(new float[N]);
       }
       for(int i=0; i<N; i++) {
           data[i] = v.data[i];
       }
       return *this;
    }

    //vec(const vec&& v) {
    //    data = std::move(v.data);
    //}

    inline vec<N> operator+(const vec<N>& v) const{
        assert(this->dim == v.dim);
        vec<N> ret{};
        for(int i=0; i<N; i++) {
            ret.data[i] = this->data[i] + v.data[i];
        }
        return ret;
    }

    inline vec<N> operator-(const vec& v) const{
        assert(this->dim == v.dim);
        vec<N> ret{};
        for(int i=0; i<N; i++) {
            ret.data[i] = this->data[i] - v.data[i];
        }
        return ret;
    }

    inline vec<N> operator-() const {
        vec<N> ret{*this};
        for(int i=0; i<N; i++) ret->data[i] = -ret->data[i];
        return ret;
    }

    inline vec<N> operator*(const vec& v) const{
        assert(this->dim == v.dim);
        vec<N> ret{};
        for(int i=0; i<N; i++) {
            ret.data[i] = this->data[i] * v.data[i];
        }
        return ret;
    }

    inline vec<N> operator*(const float c) const {
        vec<N> ret{};
        for(int i=0; i<N; i++) {
            //std::cout<<this->data[i] <<std::endl;
            ret.data[i] = this->data[i] * c;
        }
        return ret;

    }

    inline vec<N> operator/(const vec& v) const{
        assert(this->dim == v.dim);
        vec<N> ret{};
        for(int i=0; i<N; i++) {
            ret.data[i] = this->data[i] / v.data[i];
        }
        return ret;
    }

    inline vec<N>& operator+=(const vec& v) {
        assert(this->dim == v.dim);
        for(int i=0; i<N; i++) {
            this->data[i] += v.data[i];
        }
        return *this;
    }

    inline vec<N>& operator-=(const vec& v) {
        assert(this->dim == v.dim);
        for(int i=0; i<N; i++) {
            this->data[i] -= v.data[i];
        }
        return *this;
    }

    inline vec<N>& operator*=(const vec& v) {
        assert(this->dim == v.dim);
        for(int i=0; i<N; i++) {
            this->data[i] *= v.data[i];
        }
        return *this;
    }

    inline vec<N>& operator/=(const vec& v) {
        assert(this->dim == v.dim);
        for(int i=0; i<N; i++) {
            this->data[i] /= v.data[i];
        }
        return *this;
    }

    inline float dot(const vec& v) const {
        assert(this->dim == v.dim);
        float sum = 0;
        for(int i=0; i<N; i++) {
            sum += this->data[i]*v.data[i];
        }
        return sum;
    }

    inline vec<N>& cross(const vec& v) const {
        assert(this->dim == 3);
        assert(v.dim == 3);
        vec<N> ret{};
        ret.data[0] = this->data[1]*v.data[2] - this->data[2]*v.data[1];
        ret.data[1] = this->data[2]*v.data[0] - this->data[0]*v.data[2];
        ret.data[2] = this->data[0]*v.data[1] - this->data[1]*v.data[0];
        return ret;
    }

    inline float norm() const {
        return sqrt(this->dot(*this));
    }

    inline float normsq() const {
        return this->dot(*this);
    }

    void print();

    void setColor(const Color& c) {
        this -> c = c;
    }

    inline vec<N> unit() const {
        vec<N> ret{*this};
        auto norm = ret.norm();
        for(int i=0; i<dim; i++) {
            ret.data[i] /= norm;
        }
        return ret;
    }

    Color getColor() {return this -> c;}

    float operator[](int i) const {
        return data[i];
    }

private:
    std::unique_ptr<float []> data = nullptr;
    Color c;
};

template <int N>
void vec<N>::print() {
    std::cout<<"vector "<<N<<": (";
    for(int i=0; i<N-1; i++) {
        std::cout<<data[i]<<", ";
    }
    std::cout<<data[N-1]<<")"<<std::endl;
}

template <int N>
vec<N> operator*(float c, const vec<N>& v) {
    return v*c;
}

#endif //NEKO_LEARN_RAY_TRACING_VEC_H
