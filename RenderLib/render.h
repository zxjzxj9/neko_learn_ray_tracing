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
    Color() {
        this -> r = 0xFF;
        this -> g = 0xFF;
        this -> b = 0xFF;
    }
    // 0 ~ 255
    Color(unsigned char r, unsigned char g, unsigned char b) {
        this -> r = r;
        this -> g = g;
        this -> b = b;
    }

    // r, g, b between 0,1
    Color(float r, float g, float b) {
        this->r = static_cast<unsigned char>(255.0*r);
        this->g = static_cast<unsigned char>(255.0*g);
        this->b = static_cast<unsigned char>(255.0*b);
    }
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

class Image {
public:
    Image(int h, int w);
    ~Image(){};
    // x -> w, y -> h
    void set_pixel(int x, int y, const Color& c);
    Color get_pixel (int x, int y) const;
    int get_height() {return h;}
    int get_width() {return w;}
    friend class ImageWriter;

    class Iterator {
    public:
        Iterator(Image& img, int i=0, int j=0): img(img), i(i), j(j) {

        }

        std::pair<float, float> coord() {
            return std::pair<float, float>(static_cast<float>(i)/img.h, static_cast<float>(j)/img.w);
        };

        void set(const Color& c) {
            img.set_pixel(j, i, c);
        }

        Iterator& operator++() {
            j++;
            i += j/img.w;
            j %= img.w;
            return *this;
        }

        bool operator==(const Iterator& iter) {
            return (this->i == iter.i) && (this->j == iter.j);
        }

    private:
        Image& img;
        unsigned char* r;
        unsigned char* g;
        unsigned char* b;
        int i, j;

    };

    Iterator begin() {
        return Iterator(*this, 0, 0);
    }

    Iterator end() {
        return Iterator(*this, h+1, 0);
    }


private:
    int h;
    int w;
    std::unique_ptr<unsigned char[]> img;
};

class ImageWriter {
public:
    ImageWriter(const std::string path);
    void save(const Image& img) const;

private:
    std::string path;

};
#endif //NEKO_LEARN_RAY_TRACING_RENDER_H
