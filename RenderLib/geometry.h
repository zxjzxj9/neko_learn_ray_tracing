//
// Created by Victor Zhang on 2018/12/5.
//

#ifndef NEKO_LEARN_RAY_TRACING_GEOMETRY_H
#define NEKO_LEARN_RAY_TRACING_GEOMETRY_H

#include <math.h>
#include "vec.h"
#include "ray.h"

using vec3 = vec<3>;

Color green(vec3 t) {
    return Color(0.0f, 0.0f, 0.0f);
}

class geometry {
public:
    virtual float intercept(ray) = 0;
    virtual Color color(vec3) = 0;
};

class sphere: public geometry {
public:

    sphere(vec3 rc, float radius, Color(*cfunc)(vec3) = green): rc(rc), radius(radius), cfunc(cfunc) {
    }

    // return parameters
    float intercept(ray r) {
        vec3 dv = r.dv();
        vec3 dv2 = r.start() - rc;
        float proj = dv.dot(dv2);
        float delta = proj*proj - (dv2.normsq()-radius*radius);
        if(delta<0) {
            // dummy value
            return -1.0;
        } else {
            return -proj - sqrt(delta);
        }
    }

    Color color(vec3 t) {
        return cfunc(t);
    }

private:
    vec3 rc;
    float radius;
    Color (*cfunc)(vec3);
};


#endif //NEKO_LEARN_RAY_TRACING_GEOMETRY_H
