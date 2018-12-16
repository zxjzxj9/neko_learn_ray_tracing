//
// Created by Victor Zhang on 2018/12/10.
//

#include <vector>
#include <numeric>
#include "render.h"
#include "vec.h"
#include "geometry.h"

using vec3 = vec<3>;
const vec3 lt(-2.0, 1.0, -1.0);
const vec3 lb(-2.0, -1.0, -1.0);
const vec3 rt(2.0, 1.0, -1.0);
const vec3 rb(2.0, -1.0, -1.0);
const vec3 origin(0.0, 0.0, 0.0);
// const vec3 rc(0.0, 0.0, -2.0);

auto u = rt - lt;
auto v = lb - lt;

// functions to set bg color
void background(Image& img) {

    auto htot = img.get_height();
    auto wtot = img.get_width();

    for(int i=0; i<htot; i++) {
        for(int j=0; j<wtot; j++){
            float y = static_cast<float>(i)/htot;
            float x = static_cast<float>(j)/wtot;
            auto vec = x*u + y*v + lt;
            auto unit = vec.unit();
            float t = 0.5*(unit[1] + 1.0);
            vec3 color_vec = (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
            img.set_pixel(j, i, Color{color_vec[0], color_vec[1], color_vec[2]});
        }
    }
    return;
}

void draw(Image& img) {

    vec3 rc(0.0, 0.0, -2.0);
    sphere sp(rc, 1.0);

    auto htot = img.get_height();
    auto wtot = img.get_width();

    for(int i=0; i<htot; i++) {
        for(int j=0; j<wtot; j++){
            float y = static_cast<float>(i)/htot;
            float x = static_cast<float>(j)/wtot;
            auto vec = x*u + y*v + lt;
            auto rt = ray(origin, vec);
            float tmp = sp.intercept(rt);
            if(tmp > 0) {
                vec3 nvec = (rt.point(tmp) - rc).unit();
                Color s_color{static_cast<float>((nvec[0] + 1.0)/2.0),
                              static_cast<float>((nvec[1] + 1.0)/2.0),
                              static_cast<float>((nvec[2] + 1.0)/2.0)};
                img.set_pixel(j, i, s_color);
            } else continue;
        }
    }
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

    for(int i=0; i<htot; i++) {
        for(int j=0; j<wtot; j++){

            float y = static_cast<float>(i)/htot;
            float x = static_cast<float>(j)/wtot;
            auto vec = x*u + y*v + lt;
            auto rt = ray(origin, vec);
            float tmp0 = std::numeric_limits<float>::infinity();
            Color s_color = img.get_pixel(j, i);
            for(auto& g: gs) {
                float tmp1 = g->intercept(rt);
                //std::cout<<tmp1<<"  ";
                if(tmp1 > 0 && tmp1 < tmp0) {
                    tmp0 = tmp1;
                    auto p = rt.point(tmp1);
                    s_color = g->color(p);
                }
            }
            //std::cout<<std::endl;
            img.set_pixel(j, i, s_color);
        }
    }
}

int main() {

    int w = 800;
    int h = 400;
    Image img(h,w);
    background(img);
    //draw(img);
    draw2(img);
    ImageWriter ir("./test.ppm");
    ir.save(img);
    return 0;
}
