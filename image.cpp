#include "image.h"

#include <cstdint>
#include <vector>

Color::Color() : red_(0), green_(0), blue_(0){};

Color::~Color() {
}

Color::Color(float red, float green, float blue) : red_(red), green_(green), blue_(blue){};

Color::Color(const Color &rgb) : red_(rgb.red_), green_(rgb.green_), blue_(rgb.blue_){};

Color &Color::operator=(const Color &rgb) {
    red_ = rgb.red_;
    green_ = rgb.green_;
    blue_ = rgb.blue_;
    return *this;
}

Image::Image() : height_(0), width_(0) {
}

Image::~Image() {
}

Image::Image(int32_t height, int32_t width)
    : height_(height), width_(width), pixels_(height_, std::vector<Color>(width_, Color())) {
}

int Image::GetWidth() const {
    return width_;
}

int Image::GetHeight() const {
    return height_;
}

Color Image::GetColor(int32_t x, int32_t y) const {
    return pixels_[y][x];
}

void Image::SetColor(int32_t x, int32_t y, const Color &color) {
    pixels_[y][x] = color;
}

void CreateHeader(unsigned char *file_header, const int file_size) {
    file_header[0] = 'B';
    file_header[1] = 'M';
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;
    for (int i = 6; i < 14; ++i) {
        if (i == 10) {
            file_header[i] = FILE_HEADER_SIZE + INFO_HEADER_SIZE;
            continue;
        }
        file_header[i] = 0;
    }
}

void CreateInfo(unsigned char *info_header, const int width, const int height) {
    info_header[0] = INFO_HEADER_SIZE;
    info_header[1] = 0;
    info_header[2] = 0;
    info_header[3] = 0;

    info_header[4] = width;
    info_header[5] = width >> 8;
    info_header[6] = width >> 16;
    info_header[7] = width >> 24;

    info_header[8] = height;
    info_header[9] = height >> 8;
    info_header[10] = height >> 16;
    info_header[11] = height >> 24;

    info_header[12] = 0;
    info_header[13] = 0;

    info_header[14] = 24;
    for (int i = 15; i < INFO_HEADER_SIZE; ++i) {
        info_header[i] = 0;
    }
}

void Image::Save(const char *path) {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("File is not writeable");
    }
    unsigned char padding[3] = {0, 0, 0};
    const int count_paddings = ((4 - (width_ * 3) % 4) % 4);
    const int file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + width_ * height_ * 3 + count_paddings * height_;
    unsigned char file_header[FILE_HEADER_SIZE];
    unsigned char info_header[INFO_HEADER_SIZE];
    CreateHeader(file_header, file_size);
    CreateInfo(info_header, width_, height_);
    file.write(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);
    file.write(reinterpret_cast<char *>(info_header), INFO_HEADER_SIZE);
    Color tmp;
    const float max_color = 255.0f;
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            tmp = pixels_[y][x];
            unsigned char pixel_r = static_cast<unsigned char>(tmp.red_ * max_color);
            unsigned char pixel_g = static_cast<unsigned char>(tmp.green_ * max_color);
            unsigned char pixel_b = static_cast<unsigned char>(tmp.blue_ * max_color);
            unsigned char pixel_color[3] = {pixel_b, pixel_g, pixel_r};
            file.write(reinterpret_cast<char *>(pixel_color), 3);
        }
        file.write(reinterpret_cast<char *>(padding), count_paddings);
    }
    file.close();
}

void Image::Read(const char *path) {
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("File is not readable");
    }
    unsigned char file_header[FILE_HEADER_SIZE];
    unsigned char info_header[INFO_HEADER_SIZE];
    file.read(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);
    file.read(reinterpret_cast<char *>(info_header), INFO_HEADER_SIZE);
    if (file_header[0] != 'B' || file_header[1] != 'M') {
        throw std::runtime_error("File is not a BMP file");
    }
    width_ = (info_header[4]) + (info_header[5] << 8) + (info_header[6] << 16) + (info_header[7] << 24);
    height_ = (info_header[8]) + (info_header[9] << 8) + (info_header[10] << 16) + (info_header[11] << 24);
    pixels_.resize(height_);
    for (auto &row : pixels_) {
        row.resize(width_);
    }
    const float max_color = 255.0f;
    const int count_paddings = ((4 - (width_ * 3) % 4) % 4);
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            unsigned char pixel_color[3];
            file.read(reinterpret_cast<char *>(pixel_color), 3);
            pixels_[y][x].red_ = static_cast<float>(pixel_color[2]) / max_color;
            pixels_[y][x].green_ = static_cast<float>(pixel_color[1]) / max_color;
            pixels_[y][x].blue_ = static_cast<float>(pixel_color[0]) / max_color;
        }
        file.ignore(count_paddings);
    }
    file.close();
}