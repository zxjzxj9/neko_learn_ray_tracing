//
// Created by Victor Zhang on 2018/11/27.
//

#include "render.h"

Image::Image(int h, int w): h(h), w(w) {
    int tot = 3*h*w;
    img = std::unique_ptr<char[]>(new char[tot]);
};

void Image::set_pixel(int x, int y, Color c) {
    int offset = 3*(y*w + x);
    if(offset + 3 > 3*h*w) throw std::out_of_range("Image index out of bound!");
    img[offset] = c.r;
    img[offset+1] = c.r;
    img[offset+2] = c.r;
}

Color Image::get_pixel(int x, int y) const {
    int offset = 3*(y*w + x);
    if(offset + 3 > 3*h*w) throw std::out_of_range("Image index out of bound!");
    return Color{img[offset], img[offset+1], img[offset+2]};
}

ImageWriter::ImageWriter(const std::string path):path(path){

}

void ImageWriter::save(const Image& img) const{
    std::ofstream fout(path, std::ios_base::binary);
    // do some reinterpret_cast
    std::string header{"P6\n#sample image\n"};
    fout.write(header.c_str(), header.size());
    std::stringstream buf;
    buf<<img.h<<" "<<img.w<<std::endl;
    auto tmps = buf.str();
    fout.write(tmps.c_str(), tmps.size());

    for(int i=0; i<img.h; i++) {
        for(int j=0; j<img.w; j++) {
            Color c = img.get_pixel(i, j);
            fout.write(reinterpret_cast<char*>(&c), sizeof(Color));
        }
        fout.write("\n", sizeof(char));
    }
}