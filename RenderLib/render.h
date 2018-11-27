//
// Created by Victor Zhang on 2018/11/27.
//

#ifndef NEKO_LEARN_RAY_TRACING_RENDER_H
#define NEKO_LEARN_RAY_TRACING_RENDER_H

#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <cstring>
// r, g, b 0~255

struct Color {
    char r;
    char g;
    char b;
};

class Image {
public:
    Image(int h, int w);
    ~Image();
    // x -> w, y -> h
    void set_pixel(int x, int y, Color c);
    Color get_pixel (int x, int y) const;
    friend class ImageWriter;

private:
    int h;
    int w;
    std::unique_ptr<char[]> img;
};

class ImageWriter {
public:
    ImageWriter(const std::string path);
    void save(const Image& img) const;

private:
    std::string path;

};
#endif //NEKO_LEARN_RAY_TRACING_RENDER_H
