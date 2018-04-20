//
// Created by Thierry Backes on 19/04/18.
//

#ifndef SCRATCHPIXEL_IO_H
#define SCRATCHPIXEL_IO_H

#include <fstream>
#include "MathUtils.h"
#include "Matrix.h"


struct Options
{
    uint32_t width;
    uint32_t height;
    float fov;
    Matrix44f cameraToWorld;
};

/**
 * Writes the framebuffer to a ppm file.
 */
void writeToFile(const std::string &fileName, const Options &options, const Vec3f * framebuffer){
    std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
    ofs << "P6\n" << options.width << " " << options.height << "\n255\n";
    for (uint32_t i = 0; i < options.height * options.width; ++i) {
        char r = static_cast<char>(255 * clamp(0, 1, framebuffer[i].x));
        char g = static_cast<char>(255 * clamp(0, 1, framebuffer[i].y));
        char b = static_cast<char>(255 * clamp(0, 1, framebuffer[i].z));
        ofs << r << g << b;
    }
    ofs.close();
}
#endif //SCRATCHPIXEL_IO_H
