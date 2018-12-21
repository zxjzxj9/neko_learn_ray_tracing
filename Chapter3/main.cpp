//
// Created by Victor Zhang on 2018/12/18.
//

#include "render.h"
#include "geometry.h"
#include "vec.h"

#include <iostream>
#include <vector>

#define NS 10

using vec3 = vec<3>;
const vec3 lt(-2.0, 1.0, -1.0);
const vec3 lb(-2.0, -1.0, -1.0);
const vec3 rt(2.0, 1.0, -1.0);
const vec3 rb(2.0, -1.0, -1.0);
const vec3 origin(0.0, 0.0, 0.0);
// const vec3 rc(0.0, 0.0, -2.0);

auto u = rt - lt;
auto v = lb - lt;

void background(Image& img) {
    for(auto pix = img.begin(); pix != img.end(); ++pix) {
        auto coord = pix.coord();
        auto vec = coord.first*u + coord.second*v + lt;
        auto unit = vec.unit();
        float t = 0.5*(unit[1] + 1.0);
        vec3 color_vec = (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
        pix.set( Color{color_vec[0], color_vec[1], color_vec[2]});
    }
    return;
}

Color color(const vec3& n) {
    return Color{n[0], n[1], n[2]};
}

void draw2(Image& img) {
    vec3 rc1(0.0, 0.0, -2.0);
    vec3 rc2(0.0, -100.8, -2.0);
    //sphere sp1(rc1, 1.0);
    //sphere sp2(rc2, 4.0);
    std::vector<geometry*> gs;
    gs.push_back(new sphere(rc1, 1.0, color));
    //gs.push_back(new sphere(rc1, 1.0));
    gs.push_back(new sphere(rc2, 100));

    auto htot = img.get_height();
    auto wtot = img.get_width();

    for(auto pix = img.begin(); pix != img.end(); ++pix) {
        vec3 avg_color{0,0,0};
        for(int ns=0; ns < NS; ns++) {
            auto coord = pix.coord(true);
            auto vec = coord.first*u + coord.second*v + lt;
            auto rt = ray(origin, vec);
            float tmp0 = std::numeric_limits<float>::infinity();

            Color s_color = pix.get();
            for(auto& g: gs) {
                float tmp1 = g->intercept(rt);
                //std::cout<<tmp1<<"  ";
                if(tmp1 > 0 && tmp1 < tmp0) {
                    tmp0 = tmp1;
                    auto p = rt.point(tmp1);
                    s_color = g->color(p);
                }
            }
            avg_color += vec3{s_color.r/(255.0*NS), s_color.g/(255.0*NS), s_color.b/(255.0*NS)};
        }
        pix.set(Color{avg_color[0], avg_color[1], avg_color[2]});
    }

}


int main() {
    int w = 800;
    int h = 400;
    Image img(h,w);
    background(img);
    draw2(img);
    ImageWriter ir("./test.ppm");
    ir.save(img);
    return 0;
}
