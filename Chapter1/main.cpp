#include "render.h"
#include "vec.h"



int main(int argc, char** argv) {
    int w = 800;
    int h = 400;

    using vec3 = vec<3>;

    Image img(h,w);

    vec3 lt(-2.0, 1.0, -1.0);
    vec3 lb(-2.0, -1.0, -1.0);
    vec3 rt(2.0, 1.0, -1.0);
    vec3 rb(2.0, -1.0, -1.0);

    vec3 origin(0.0, 0.0, 0.0);

    auto u = rt - lt;
    auto v = lb - lt;

    for(int i=0; i<h; i++) {
        for(int j=0; j<w; j++) {
            float y = static_cast<float>(i)/h;
            float x = static_cast<float>(j)/w;

            auto vec = x*u + y*v;
            auto unit = vec.unit();
            float t = 0.5*(unit[1] + 1.0);
            vec3 color_vec = (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
            img.set_pixel(j, i, Color{color_vec[0], color_vec[1], color_vec[2]});
            // vec<3> vec3(x, y, 0.2);
        }
    }

    ImageWriter ir("./test.ppm");
    ir.save(img);

    return 0;
}