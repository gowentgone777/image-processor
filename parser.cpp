#include "parser.h"
#include "./filters/crop.h"
#include "./filters/grayscale.h"
#include "./filters/negative.h"
#include "./filters/sharpen.h"
#include "./filters/edge.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

Parser::Parser(int argc, const char** argv) : argc_(argc), argv_(argv) {
    commands_["-crop"] = [&]() { ParseCrop(); };
    commands_["-gs"] = [&]() { ParseGrayscale(); };
    commands_["-neg"] = [&]() { ParseNegative(); };
    commands_["-sharp"] = [&]() { ParseSharpening(); };
    commands_["-edge"] = [&]() { ParseEdge(); };
}

void Parser::Read() {
    std::string command_name = argv_[pos_];
    auto it = commands_.find(command_name);
    if (it != commands_.end()) {
        it->second();
    } else {
        throw std::invalid_argument("expected filter flag, got " + std::string(argv_[pos_]));
    }
    ++pos_;
}

void Parser::Parse() {
    if (argc_ < 3) {
        throw std::invalid_argument("usage: <file1> <file2> ...");
    }
    file_read_ = argv_[1];
    file_write_ = argv_[2];
    pos_ = 1;
    pos_ += 2;
    while (pos_ < argc_) {
        Read();
    }
}

void Parser::ParseCrop() {
    pos_ += 2;
    if (pos_ > argc_) {
        throw std::out_of_range("usage: -crop <width> <height>");
    }
    int32_t width = 0;
    int32_t height = 0;
    try {
        width = std::stoi(argv_[pos_ - 1]);
        height = std::stoi(argv_[pos_]);
        if (width <= 0 || height <= 0) {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        throw std::invalid_argument("width and height arguments must be positive integers");
    }
    filters_.push_back(std::make_unique<Crop>(width, height));
}

void Parser::ParseGrayscale() {
    filters_.push_back(std::make_unique<Grayscale>());
}

void Parser::ParseNegative() {
    filters_.push_back(std::make_unique<Negative>());
}

void Parser::ParseSharpening() {
    filters_.push_back(std::make_unique<Sharpening>());
}

void Parser::ParseEdge() {
    ++pos_;
    if (pos_ > argc_) {
        throw std::out_of_range("usage: -edge <threshold>");
    }
    float threshold = 0;
    try {
        threshold = static_cast<float>(std::stod(argv_[pos_]));
        if (threshold < 0 || 1 < threshold) {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        throw std::invalid_argument("threshold argument must be a real number from 0 to 1");
    }
    filters_.push_back(std::make_unique<Edge>(threshold));
}

const char* Parser::GetFileForReading() const {
    return file_read_;
}
const char* Parser::GetFileForWriting() const {
    return file_write_;
}

std::vector<std::unique_ptr<Filter> >& Parser::GetFilters() {
    return filters_;
}