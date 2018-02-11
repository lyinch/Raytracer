
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "shader.h"
#include "window.h"


static const std::string FILENAME = "out.ppm";
static const char* WINDOW_TITLE = "Pathtracer"; //glew needs char* instead of std::string

static const int SAMPLES_PER_PIXEL = 300;
static const Vec3 bg_color(0.5f, 0.7f, 1.f);
static const int width = 800*2;
static const int height = 400*2;

/**
 * Normalizes value in given min/max range
 * https://stats.stackexchange.com/questions/70801/how-to-normalize-data-to-0-1-range
 */
float normalize(float in,float min, float max){
    return (in-min)/(max-min);
}


// http://mathworld.wolfram.com/SpherePointPicking.html
Vec3 random_point_on_unit_sphere(){
    auto phi = static_cast<float>(drand48() * 2 * M_PI);
    auto u = static_cast<float>(drand48() * 2 - 1);
    float t = sqrtf(1-u*u);
    return {t*cosf(phi),t*sinf(phi),u};
}
/*
Vec3 random_point_on_unit_sphere(){
    Vec3 p;
    do{
        p = 2.0f*Vec3(drand48(),drand48(),drand48())-Vec3(1,1,1);
    }while (p.squared_length() >= 1.0);

    return  p;

}
*/

/*
 * right hand coordinate system (+z is out of monitor): camera is at (0,0,0) and looks to a screen centered at (0,0,-1)
 * Screen has edges at (w/h ratio) top left:(-2,1,-1), top right: (2,1,-1) and symmetric down.
 */
Vec3 color(const ray& r, hitable *world){
    //sphere
    hit_record rec;
    if(world->hit(r,0.0001f,MAXFLOAT,rec)) {
        Vec3 target = rec.p + rec.normal + random_point_on_unit_sphere();
        return 0.5 * color(ray(rec.p,target-rec.p),world);
        //return 0.5 * Vec3(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1);
    }

    //background
    //y of the direction vector ganges from ca. 0.4 to ca. 0.8 The 1.8 is arbitrary to get a good looking background
    //We don't get a linear gradient, because we don't look at the intersection of the direction vector and the plane
    //but solely at the y coordinate of the direction vector. It looks good :)
    float t = normalize(r.getDirection().y,-1,1);
    //std::cout << r.getDirection().y << std::endl;
    return (1-t)*Vec3(1.f,1.f,1.f)+(t)*bg_color; //lerp of default color
}


GLFWwindow* initGLFW(){
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //needed on OSX
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return glfwCreateWindow(width,height,WINDOW_TITLE, nullptr,nullptr);
}


void render(camera cam, unsigned char* frame_buffer, std::ofstream &file, hitable *world){
    srand(static_cast<unsigned int>(time(nullptr)));

    int buffer_index = 0;
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {

            Vec3 col(0,0,0);
            for (int k = 0; k < SAMPLES_PER_PIXEL; ++k) {
                float u = (float) (i+drand48()) / (float) width;
                float v = (float) (j+drand48()) / (float) height;
                ray r = cam.get_ray(u,v);
                col += color(r,world);
            }

            col /= SAMPLES_PER_PIXEL;

            col = sqrtvec(col); //Gamma correction

            //col is in range 0-1 but we want RGB in range 0-255
            int ir = uint8_t(255 * col.x);
            int ig = uint8_t(255 * col.y);
            int ib = uint8_t(255 * col.z);

            frame_buffer[buffer_index] = ir;
            frame_buffer[buffer_index+1] = ig;
            frame_buffer[buffer_index+2] = ib;
            buffer_index += 3;
            file << ir << " " << ig << " " << ib << "\n";

            //glfw needs to be in the main thread
            glfwPollEvents();
        }
        std::cout << "\r[Info]:\tProgress: " << (((float)j)/((float)height))*100 << "%";
    }
    std::cout << std::endl;//flush and add newline
}


int main() {
    auto *frame_buffer = (unsigned char*) calloc(width*height*3,sizeof(unsigned char*));
    if(frame_buffer == nullptr){
        fprintf(stderr, "Failed to allocate memory for frame buffer\n");
        exit(-1);
    }

    GLFWwindow *window = initGLFW();
    if(window == nullptr){
        fprintf(stderr, "Failed to create GLFW window\n");
        exit(-1);
    }

    std::ofstream file;
    file.open(FILENAME);
    if(!file){
        fprintf(stderr, "Failed to open file\n");
        exit(-1);
    }

    //PPM Header: P3 is the magic number for ppm in ASCII format, followed by width and height, followed by 255, the max value for each colour
    file << "P3\n" << width << " " << height << "\n255\n";


    hitable *list[2];
    list[0] = new sphere(Vec3(0,0,-1),0.5f);
    list[1] = new sphere(Vec3(0,-100.5f,-1),100);
    hitable *world = new hitable_list(list,2);

    camera cam;

    std::cout << "[INFO]:\tInitialization successful, start rendering" << std::endl;

    //we start the opengl thread
    std::thread window_thread(run,frame_buffer,width,height,window);

    //main render loop
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    render(cam,frame_buffer,file,world);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    std::cout << "[INFO]:\tRendering finished in " <<  std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count() << "s" << std::endl;

    free(list[0]);
    free(list[1]);
    free(world);

    file.close();
    std::cout << "[INFO]:\tFile written" << std::endl;

    //glfwSetWindowShouldClose(window,true);
    window_thread.join();
    glfwTerminate();


    return 0;
}
