//
// Created by Victor Zhang on 2018/12/5.
//

#ifndef NEKO_LEARN_RAY_TRACING_GEOMETRY_H
#define NEKO_LEARN_RAY_TRACING_GEOMETRY_H

#include <math.h>
#include <vector>
#include <random>
#include "vec.h"
#include "ray.h"

using vec3 = vec<3>;

Color green(const vec3& t) {
    return Color(0.0f, 1.0f, 0.0f);
}

class world;

class geometry {
public:
    virtual float intercept(const ray&) = 0;
    virtual Color color(const vec3&) = 0;
    virtual ~geometry(){}
    // Define BRDF function to decide color
    virtual Color brdf(const vec3& hitp, const world&, int) = 0;
    // return norm vector given the surface point
    virtual vec3 normvec(const vec3& p) = 0;
};

// world class, containing all geometry objects
class world {
public:
    world(std::vector<geometry*>& gs): gs(gs) {

    }

    // return the hit point in a world
    std::pair<vec3, geometry*> hit(const ray& r) const {

        float tmp = std::numeric_limits<float>::infinity();
        geometry* retg = nullptr;

        for(auto g: gs) {
            float tmp1 = g->intercept(r);
            if(tmp1 > 0 && tmp1 < tmp) {
                tmp = tmp1;
                retg = g;
            }
        }
        if(retg) {
            return std::pair<vec3, geometry*> {r.point(tmp), retg};
        } else {
            return std::pair<vec3, geometry*> {vec3{tmp, tmp, tmp}, retg};
        }
    }

private:
   std::vector<geometry*>& gs;
};

enum Material {
    DIFFUSE,
    METAL,
};


class sphere: public geometry {
public:

    sphere(vec3 rc, float radius, Color(*cfunc)(const vec3&) = green, Material material=DIFFUSE):
            rc(rc), radius(radius), cfunc(cfunc), material(material) {
    }

    ~sphere(){};
    // return parameters
    float intercept(const ray& r) {
        vec3 dv = r.dv();
        vec3 dv2 = r.start() - rc;
        float proj = dv.dot(dv2);
        float delta = proj*proj - (dv2.normsq()-radius*radius);
        if(delta<0) {
            // dummy value
            return -1.0;
        } else {
            return -proj - sqrt(delta) > 0? -proj - sqrt(delta) :  -proj + sqrt(delta) ;
        }
    }

    Color color(const vec3& t) {
        vec3 nvec = (t - rc).unit();
        vec3 nvec2{
            (nvec[0] + 1.0)/2.0,
            (nvec[1] + 1.0)/2.0,
            (nvec[2] + 1.0)/2.0
        };
        return cfunc(nvec2);
    }


    Color brdf(const vec3& hitp, const world& w, int rec=10) {
        // Select material and return the corresponding color
        switch (material) {
            case DIFFUSE:
                return diffuse(hitp, w, rec);
            default:
                return Color{0.0f, 0.0f, 0.0f};
        }
    }


    // hit_p : hit point
    // in_vec : input vector
    // rec: recursive depth
    Color diffuse(const vec3& hitp, const world& w, int rec=10) {

        auto nvec = this -> normvec(hitp);

        // if max hit number
        if(rec == 0) {
            return color(nvec);
        }

        // if not exceed max hit number
        vec3 randvec{dist(rg), dist(rg), dist(rg)};
        randvec = (randvec.dot(nvec)*randvec).unit();
        ray outr(hitp, hitp + randvec);
        auto retp = w.hit(outr);

        if(retp.second) {
            //vec3 nvec = retp.second -> normvec(retp.first);
            //ray outr(retp.first, retp.first + randvec);
            //auto c = retp.second->brdf(outr, w, rec - 1);
            //return color({1.0 - sqrt(c.r/255.0f), 1.0 - sqrt(c.g/255.0f), 1.0 - sqrt(c.b/255.0f)});
            return 0.5*retp.second->brdf(retp.first, w, rec - 1);
        } else {
            return color(nvec);
        }

    }


    vec3 normvec(const vec3& v) {
         return (v-rc).unit();
    }

private:
    vec3 rc;
    float radius;
    Color (*cfunc)(const vec3&);
    std::mt19937 rg{std::random_device{}()};
    std::uniform_real_distribution<float> dist{0.0, 1.0};
    Material material;
};


#endif //NEKO_LEARN_RAY_TRACING_GEOMETRY_H
