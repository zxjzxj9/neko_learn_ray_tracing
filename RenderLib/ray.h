//
// Created by Victor Zhang on 2018/12/4.
//

#ifndef NEKO_LEARN_RAY_TRACING_RAY_H
#define NEKO_LEARN_RAY_TRACING_RAY_H
#include "vec.h"

using vec3 = vec<3>;

class ray {
public:
    ray(){}
    ray(vec3 s, vec3 e): s(s), e(e) {
        auto dtn = (e - s).unit();
    }
    vec3 start() const {return s;};
    vec3 end() const {return e;};
    vec3 dv() const {return dtn;}
    vec3 point(float c) {return c*dtn + s;}

private:
    vec3 dtn;
    vec3 s;
    vec3 e;
};


#endif //NEKO_LEARN_RAY_TRACING_RAY_H
