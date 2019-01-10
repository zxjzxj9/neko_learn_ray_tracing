//
// Created by Victor Zhang on 2018/11/28.
//


#include "render.h"
#include "vec.h"

//#include "gtest/gtest.h"

int main() {

    // For image write test
    Image img(256, 256);
    for(int i=0; i<img.get_height(); i++) {
        for(int j=0; j<img.get_width(); j++) {
            float x = static_cast<float>(j)/img.get_height();
            float y = static_cast<float>(i)/img.get_width();
            if((x-0.5)*(x-0.5) + (y-0.5)*(y-0.5) < 0.10) {
                img.set_pixel(i, j, Color{static_cast<unsigned char>(x*255), static_cast<unsigned char>(y*255), 122});
            } else {
                img.set_pixel(i, j, Color{122, static_cast<unsigned char>(x*255), static_cast<unsigned char>(y*255)});
            }
        }
    }
    ImageWriter ir("./test.ppm");
    ir.save(img);


    vec<3> data({1.0,2.0,3.0});
    data.print();


    return 0;
}
