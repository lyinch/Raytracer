#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "camera.h"
#include "material.h"
#include "sphere.h"
#include "hitable_list.h"
#include <fstream>


hitable *random_scene(){
    int n = 500;
    hitable **list = new hitable*[n+1];
    list[0] = new sphere(vec3(0,-100,0),1000,new lambertian(vec3(0.5,0.5,0.5)));
    int i = 1;
    for (int a = -11; a  < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
        float choose_mat = drand48();
            vec3 center(a+0.9*drand48(),0.2,b+0.9*drand48());
            if((center-vec3(4,0.2,0)).length() > 0.9){
                if(choose_mat < 0.8) { //we chose diffuse material
                    list[i++] = new sphere(center,0.2,new lambertian(vec3(drand48()*drand48(),drand48()*drand48(),drand48()*drand48())));
                }else if(choose_mat < 0.95){ //metal
                    //list[i++] = new sphere(center,0.2,new metal();
                }else{ //glass

                }
            }
        } 
    }
    return new hitable_list(list,i);
}

vec3 color(const ray& r, hitable *world,int depth){
    hit_record rec;
    if(world -> hit(r,0.001f,MAXFLOAT,rec)){
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered))
            return attenuation*color(scattered,world,depth+1);
        else{
            return {0,0,0};
        }
    }else {
        vec3 direction = normalized(r.direction());
        float t = 0.5f * (direction.y() + 1.f);
        //linear interpolation of white and blue depending on the y coordinate
        return (1.f - t) * vec3(1.f, 1.f, 1.f) + t * vec3(0.5f, 0.7f, 1.f);
    }
}




int main() {
    std::ofstream file;
    file.open("out.ppm");

    int nx = 200;
    int ny = 100;
    int ns = 100;
    file << "P3\n" << nx << " " << ny << "\n255\n";

    /*
    hitable *list[4];
    list[0] = new sphere(vec3(0,0,-1),0.5,new lambertian(vec3(0.8,0.3,0.3)));
    list[1] = new sphere(vec3(0,-100.5f,-1),100,new lambertian(vec3(0.8,0.8,0.0)));
    list[2] = new sphere(vec3(1,0,-1.5f),0.5,new metal(vec3(0.8,0.6,0.2),0.4f));
    list[3] = new sphere(vec3(-1,0,-1),0.5f,new dielectric(1.5)); //left */

    //hitable *world = new hitable_list(list,4);
    hitable *scene = random_scene();

    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    //float dist_to_focus = (lookfrom-lookat).length();
    float dist_to_focus = 10;
    float aperture = .1f;
    camera cam(lookfrom,lookat,vec3(0,1,0),20 ,(float)nx/(float)ny,aperture,dist_to_focus);
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = ny-1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            vec3 col(0,0,0);
            for (int s = 0; s < ns; ++s) {
                float u = (float)(i+drand48())/(float)nx;
                float v = (float)(j+drand48())/(float)ny;
                ray r = cam.get_ray(u,v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r,scene,0);
            }

            col /= float(ns);
            //gamma correction
            col = vec3(sqrtf(col[0]),sqrtf(col[1]),sqrtf(col[2]));
            auto ir = int(255.99f*col[0]);
            auto ig = int(255.99f*col[1]);
            auto ib = int(255.99f*col[2]);
            file << ir << " " << ig << " " << ib << "\n";
        }
        printf("\r%f",((float)(ny-j)/(float)ny)*100);
        fflush(stdout);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    printf("\nRendering took %0.1f seconds.\n", diff.count());


    file.close();

    //free(list[3]);
    //free(list[2]);
    //free(list[1]);
    //free(list[0]);
    //free(world);

    return 0;
}