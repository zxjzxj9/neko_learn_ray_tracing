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
#include "render.h"

template <int N>
class vec {
public:
    const int dim = N;
    // Sadly va_list not support float
    vec(double a1, ...) {
        data = std::unique_ptr<float []>(new float[N]);
        va_list args;
        va_start(args, a1);
        data[0] = static_cast<float>(a1);
        for(int i=1; i<N; i++) {
            data[i] = static_cast<float>(va_arg(args, double));
        }
        va_end(args);
    }

    vec(Color c, double a1, ...): c(c) {
        data = std::unique_ptr<float []>(new float[N]);
        va_list args;
        va_start(args, a1);
        data[0] = static_cast<float>(a1);
        for(int i=1; i<N; i++) {
            data[i] = static_cast<float>(va_arg(args, double));
        }
        va_end(args);
    }

    vec() {
        data = std::unique_ptr<float []>(new float[N]);
    }

    vec(const vec& v) {
        data = std::unique_ptr<float []>(new float[N]);
        for(int i=0; i<N; i++) {
            data[i] = v.data[i];
        }
    }

    vec(const vec&& v) {
        data = std::move(v.data);
    }

    inline vec& operator+(const vec& v) const{
        assert(this->dim == v.dim);
        auto ret = new vec<N>();
        for(int i=0; i<N; i++) {
            ret->data[i] = this->data[i] + v.data[i];
        }
        return *ret;
    }

    inline vec<N>& operator-(const vec& v) const{
        assert(this->dim == v.dim);
        auto ret = new vec<N>();
        for(int i=0; i<N; i++) {
            ret->data[i] = this->data[i] - v.data[i];
        }
        return *ret;
    }

    inline vec<N>& operator-() const {
        auto ret = new vec<N>(*this);
        for(int i=0; i<N; i++) ret->data[i] = -ret->data[i];
        return *ret;
    }

    inline vec<N>& operator*(const vec& v) const{
        assert(this->dim == v.dim);
        auto ret = new vec<N>();
        for(int i=0; i<N; i++) {
            ret->data[i] = this->data[i] * v.data[i];
        }
        return *ret;
    }

    inline vec<N>&operator*(const float c) const {
        auto ret = new vec<N>();
        for(int i=0; i<N; i++) {
            ret->data[i] = this->data[i] * c;
        }
        return *ret;

    }

    inline vec<N>& operator/(const vec& v) const{
        assert(this->dim == v.dim);
        auto ret = new vec<N>();
        for(int i=0; i<N; i++) {
            ret->data[i] = this->data[i] / v.data[i];
        }
        return *ret;
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
        auto ret = new vec();
        ret->data[0] = this->data[1]*v.data[2] - this->data[2]*v.data[1];
        ret->data[1] = this->data[2]*v.data[0] - this->data[0]*v.data[2];
        ret->data[2] = this->data[0]*v.data[1] - this->data[1]*v.data[0];
        return *ret;
    }

    inline float norm() const {
        return sqrt(this->dot(*this));
    }

    void print();

    void setColor(const Color& c) {
        this -> c = c;
    }

    vec<N>& unit() {
        auto ret = new vec<N>(*this);
        auto norm = ret->norm();
        for(int i=0; i<dim; i++) {
            ret->data[i] /= norm;
        }
        return *ret;
    }

    Color getColor() {return this -> c;}

    float operator[](int i) const {
        return data[i];
    }

private:
    std::unique_ptr<float []> data;
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
vec<N>& operator*(float c, const vec<N>& v) {
    return v*c;
}

#endif //NEKO_LEARN_RAY_TRACING_VEC_H
