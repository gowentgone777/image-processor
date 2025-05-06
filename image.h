#pragma once

#include <cstdint>
#include <vector>
#include <fstream>

static const int FILE_HEADER_SIZE = 14;
static const int INFO_HEADER_SIZE = 40;

struct Color {
    float red_;
    float green_;
    float blue_;

    Color();
    ~Color();
    Color(float red, float green, float blue);
    Color(const Color& color);
    Color& operator=(const Color& color);
};

class Image {
public:
    Image();
    Image(int32_t height, int32_t weidth);
    ~Image();

    void SetColor(int32_t x, int32_t y, const Color& color);
    Color GetColor(int32_t x, int32_t y) const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;

    friend void SaveFile(const char* path, Image& image);
    void Read(const char* path);
    void Save(const char* path);

private:
    int32_t height_;
    int32_t width_;
    std::vector<std::vector<Color> > pixels_;
};