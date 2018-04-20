
Ray- Pathtracer Collection
===

Collection of Ray- and Pathtracer implementations from different sources, tutorials and books.

### InOneWeekend
Implementation from the *trilogy* **Raytracing in one weekend**, **Raytracing the next week** and **Raytracing the rest of your life** from Peter Shirley.
CPU single-threaded renderer which currently only supports diffuse materials and spheres. openGL runs in a second thread to have a realtime renderer. Output is saved in a [PPM](http://netpbm.sourceforge.net/doc/ppm.html) file. Next versions include more materials, multithreading, .obj loading and spatial accelerating data structures.

### InAWeekend
Reference implementation of **Raytracing in one weekend**. 

### ScratchPixel
Implementation from [ScratchPixel](www.scratchpixel.com.com). Currently only Whitted style raytracing. Next steps are an .obj loader, rendering of meshes, lights, correct shading (pathtracer), accelerating datastructure (BVH), implicit surfaces and multithreading. A possible extension is an interactive renderer with an openGL context. 