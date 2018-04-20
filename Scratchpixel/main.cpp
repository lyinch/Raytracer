#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include "Vec3.h"
#include "Ray.h"
#include "Matrix.h"
#include "Vec2.h"
#include "Sphere.h"
#include "MathUtils.h"
#include "Light.h"
#include "IO.h"
#include "Triangle.h"

const float kInfinity = std::numeric_limits<float>::max();

//we initialize a prng
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);



/*
struct Options
{
    uint32_t width;
    uint32_t height;
    float fov;
    Matrix44f cameraToWorld;
};
*/

bool trace(const Vec3f &orig, const Vec3f &dir, const std::vector<std::unique_ptr<Object>> &objects, float &tNear, const Object *&hitObject){
    tNear = kInfinity;
    for (const auto &object : objects) {
        float t = kInfinity;
        if (object->intersect(orig, dir, t) && t < tNear) {
            hitObject = object.get();
            tNear = t;
        }
    }

    return (hitObject != nullptr);
}

Vec3f castRay(const Vec3f &orig, const Vec3f &dir,
              const std::vector<std::unique_ptr<Object>> &objects,
              const std::vector<std::unique_ptr<Light>> &lights,
              const Options &options,
              uint32_t depth)
{
    Vec3f hitColor;
    const Object *hitObject = nullptr; //hit object
    float t; //distance from ray origin to hit point
    if(trace(orig,dir,objects,t,hitObject)){

        Vec3f Phit = orig + dir * t;
        Vec3f Nhit;
        Vec2f tex;
        hitObject->getSurfaceData(Phit, Nhit, tex);
        float scale = 4;
        float pattern = (fmodf(tex.x * scale, 1) > 0.5) ^ (fmodf(tex.y * scale, 1) > 0.5);
        hitColor = std::max(0.f, Nhit.dot(-dir)) * mix(hitObject->color, hitObject->color * 0.8, pattern);
        hitColor = Vec3f(0.9,0.2,0.3);
    }
    return hitColor;
}




void render(const Options &options,
            const std::vector<std::unique_ptr<Object>> &objects,
            const std::vector<std::unique_ptr<Light>> &lights)
{

    auto *framebuffer = new Vec3f[options.width * options.height];

    Vec3f *pix = framebuffer;

    //scales the sides of our image plane according to our FOV
    float scale = static_cast<float>(std::tan(deg2rad(static_cast<const float &>(options.fov * 0.5))));
    float imageAspectRatio = options.width / (float)options.height;

    Vec3f orig;

    //We translate our camera origin currently at (0,0,0) to it's new position
    options.cameraToWorld.multVecMatrix(Vec3f(0), orig);

    for (int j = 0; j < options.height; ++j) {
        for (int i = 0; i < options.width; ++i) {
            auto x = static_cast<float>((2 * (i + 0.5) / (float)options.width - 1) * scale);
            auto y = static_cast<float>((1 - 2 * (j + 0.5) / (float)options.height) * scale * 1 / imageAspectRatio);
            Vec3f dir;
            //We translate and rotate the direction vector of the ray to the new camera position
            options.cameraToWorld.multDirMatrix(Vec3f(x, y, -1), dir);
            dir.normalize();
            *(pix++) = castRay(orig, dir, objects, lights, options, 0);
        }
    }

    writeToFile("out.ppm",options,framebuffer);

    delete[](framebuffer);
}

int main() {



    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Light>> lights;

    uint32_t numSpheres = 32;
    gen.seed(0);
    for (uint32_t i = 0; i < numSpheres; ++i) {
        Vec3f randPos(static_cast<float>((0.5 - dis(gen)) * 10), static_cast<float>((0.5 - dis(gen)) * 10),
                      static_cast<float>(0.5 + dis(gen) * 10));
        auto randRadius = static_cast<float>(0.5 + dis(gen) * 0.5);
        objects.push_back(std::unique_ptr<Object>(new Sphere(randPos, randRadius)));
    }


    objects.push_back(std::unique_ptr<Object>(new Triangle(Vec3f(-1, -1, -5),Vec3f( 1, -1, -5),Vec3f(0,  1, -5))));

    struct Options options{};
    options.width = 640;
    options.height = 480;
    options.fov = 51.2;
    options.cameraToWorld = Matrix44f(0.945519, 0, -0.325569, 0, -0.179534, 0.834209,
                                      -0.521403, 0, 0.271593, 0.551447, 0.78876, 0, 4.208271, 8.374532, 17.932925, 1);
    //options.cameraToWorld = Matrix44f();
    std::cout << "Starting rendering" << std::endl;
    render(options,objects,lights);
    std::cout << "Rendering done" << std::endl;
    return 0;
}