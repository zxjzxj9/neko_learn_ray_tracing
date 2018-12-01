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

    vec() {
        data = std::unique_ptr<float []>(new float[N]);
    }

    vec(vec& v) {
        data = std::unique_ptr<float []>(new float[N]);
        for(int i=0; i<N; i++) {
            data[i] = v.data[i];
        }
    }

    vec(vec&& v) {
        data = std::move(v.data);
    }

    vec& operator+(const vec& v) const{
        auto ret = new vec();
        for(int i=0; i<N; i++) {
            ret[i] = this->data[i] + v.data[i];
        }
    }

    vec& operator-(const vec& v) const{
        auto ret = new vec();
        for(int i=0; i<N; i++) {
            ret[i] = this->data[i] - v.data[i];
        }
    }

    vec& operator*(const vec& v) const{
        auto ret = new vec();
        for(int i=0; i<N; i++) {
            ret[i] = this->data[i] * v.data[i];
        }
    }

    vec& operator/(const vec& v) const{
        auto ret = new vec();
        for(int i=0; i<N; i++) {
            ret[i] = this->data[i] / v.data[i];
        }
    }

    vec& operator+=(const vec& v) {
        for(int i=0; i<N; i++) {
            this->data[i] += v.data[i];
        }
        return *this;
    }

    vec& operator-=(const vec& v) {
        for(int i=0; i<N; i++) {
            this->data[i] -= v.data[i];
        }
        return *this;
    }

    vec& operator*=(const vec& v) {
        for(int i=0; i<N; i++) {
            this->data[i] *= v.data[i];
        }
        return *this;
    }

    vec& operator/=(const vec& v) {
        for(int i=0; i<N; i++) {
            this->data[i] /= v.data[i];
        }
        return *this;
    }

    float dot(const vec& v) const {
        float sum = 0;
        for(int i=0; i<N; i++) {
            sum += this->data[i]*v.data[i];
        }
        return sum;
    }

    float norm() const {
        return sqrt(this->dot(*this));
    }

    void print();

private:
    std::unique_ptr<float []> data;

};

template <int N>
void vec<N>::print() {
    std::cout<<"vector "<<N<<": (";
    for(int i=0; i<N-1; i++) {
        std::cout<<data[i]<<", ";
    }
    std::cout<<data[N-1]<<")"<<std::endl;
}

#endif //NEKO_LEARN_RAY_TRACING_VEC_H
