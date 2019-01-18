//
// Created by Victor Zhang on 2018/12/24.
//

#include "render.h"
#include "geometry.h"
#include "vec.h"

#include <iostream>
#include <vector>

#define NS 1000

using vec3 = vec<3>;
const vec3 lt({-2.0, 1.0, -1.0});
const vec3 lb({-2.0, -1.0, -1.0});
const vec3 rt({2.0, 1.0, -1.0});
const vec3 rb({2.0, -1.0, -1.0});
const vec3 origin({0.0, 0.0, 0.0});
// const vec3 rc(0.0, 0.0, -2.0);

auto u = rt - lt;
auto v = lb - lt;

void background(Image& img) {
    for(auto pix = img.begin(); pix != img.end(); ++pix) {
        auto coord = pix.coord();
        auto vec = coord.first*u + coord.second*v + lt;
        auto unit = vec.unit();
        float t = 0.5*(unit[1] + 1.0);
        vec3 color_vec = (1.0-t)*vec3({1.0, 1.0, 1.0}) + t*vec3({0.5, 0.7, 1.0});
        pix.set(Color{color_vec[0], color_vec[1], color_vec[2]});
    }
    return;
}

Color color(const vec3& n) {
    float t = (n[1]+1.0f)/2.0f;
    return Color{t, t, t};
}

Color color2(const vec3& n) {
    float t = 0.5*(n[1] + 1.0);
    vec3 color_vec = (1.0-t)*vec3({1.0, 1.0, 1.0}) + t*vec3({0.5, 0.7, 1.0});
    return Color{color_vec[0], color_vec[1], color_vec[2]};
}

void draw2(Image& img) {
    vec3 rc1({1.5, 0.0, -2.0});
    vec3 rc2({-1.5, 0.0, -2.0});
    MaterialTrait mt1{METAL, 0.9f, 0.0f, 0.0f, 1.0f};
    MaterialTrait mt2{GLASS, 0.2f, 0.0f, 0.9f, 1.5f};
    vec3 rc0({0.0, -100.8, -2.0});
    //sphere sp1(rc1, 1.0);
    //sphere sp2(rc2, 4.0);
    std::vector<geometry*> gs;
    gs.push_back(new sphere(rc0, 100));
    gs.push_back(new sphere(rc1, 1.0, color, &mt1));
    gs.push_back(new sphere(rc2, 1.0, color2, &mt2));
    //gs.push_back(new sphere(rc1, 1.0));

    auto htot = img.get_height();
    auto wtot = img.get_width();

    world wd{gs};

    for(auto pix = img.begin(); pix != img.end(); ++pix) {
        vec3 avg_color({0.0f,0.0f,0.0f});
        for(int ns=0; ns < NS; ns++) {
            auto coord = pix.coord(true);
            auto vec = coord.first*u + coord.second*v + lt;
            auto rt = ray(origin, vec);
            Color s_color = pix.get();

            auto ret = wd.hit(rt);
            if(ret.second) {
                s_color = ret.second -> brdf(rt.dv(), ret.first, wd, 10);
            }

            avg_color += vec3{s_color.r/(255.0*NS), s_color.g/(255.0*NS), s_color.b/(255.0*NS)};
        }
        pix.set(Color{pow(avg_color[0],  1.0f), pow(avg_color[1], 1.0f), pow(avg_color[2], 1.0f)});
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
