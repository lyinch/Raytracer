//
// Created by Thierry Backes on 19/04/18.
//

#ifndef SCRATCHPIXEL_IO_H
#define SCRATCHPIXEL_IO_H

#include <fstream>
#include "MathUtils.h"
#include "Matrix.h"
#include "Triangle.h"
#include <sstream>

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


void readObj(const std::string &fileName,std::vector<std::shared_ptr<Object>> &triangles){
    std::ifstream file(fileName);
    std::string str;
    std::vector<Vec3f> vertices;
    //std::vector<Triangle> triangles;
    while(std::getline(file,str)){
        std::istringstream iss(str);
        //tokenize the string by whitespace
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                        std::istream_iterator<std::string>{}};
        if(tokens[0] == "v"){
            vertices.push_back(Vec3f(std::stof(tokens[1]),std::stof(tokens[2]),std::stof(tokens[3])));
        }else if(tokens[0] == "f"){
            //f has the format x/y/z where x: vertex index, y: texture index, z: vertex normal
            unsigned long dela = tokens[1].find_first_of("/");
            unsigned long delb = tokens[2].find_first_of("/");
            unsigned long delc = tokens[3].find_first_of("/");
            //obj indexes at 1 but std::vector starts at 0
            triangles.push_back(std::shared_ptr<Object>(new Triangle(vertices[std::stof(tokens[1].substr(0,dela))-1],
                                vertices[std::stof(tokens[2].substr(0,delb))-1],
                                vertices[std::stof(tokens[3].substr(0,delc))-1])));
        }
    }
}
#endif //SCRATCHPIXEL_IO_H
