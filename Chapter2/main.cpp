//
// Created by Victor Zhang on 2018/12/10.
//

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
        for(int j=0; j<img.wtot; j++){
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


int main() {

    int w = 800;
    int h = 400;
    Image img(h,w);
    background(img);

    return 0;
}
