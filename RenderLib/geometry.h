//
// Created by Victor Zhang on 2018/12/5.
//

#ifndef NEKO_LEARN_RAY_TRACING_GEOMETRY_H
#define NEKO_LEARN_RAY_TRACING_GEOMETRY_H

#include <math.h>
#include "vec.h"
#include "ray.h"

using vec3 = vec<3>;

class sphere {
public:

    sphere(vec3 rc, float radius): rc(rc), radius(radius) {

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
        // dummy return
        return 0.0;
    }

private:
    vec3 rc;
    float radius;

};


#endif //NEKO_LEARN_RAY_TRACING_GEOMETRY_H
