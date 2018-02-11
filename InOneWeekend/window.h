//
// Created by Thierry Backes on 10/02/18.
//

#ifndef INONEWEEKEND_WINDOW_H
#define INONEWEEKEND_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int run(unsigned char *frame_buffer, int w, int h, GLFWwindow *window){
    glfwMakeContextCurrent(window);
    int wi, hi;
    glfwGetFramebufferSize(window, &wi, &hi); //due to retina display
    glViewport(0, 0, wi, hi);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    glewInit();
    glClearColor(1,1,1,1);

    Shader mainShader("shader.vert", "shader.frag");

    float vertices[] = {
            //position      //texture
            -1, 1,  0,      0,  0,      // top      left
            -1,-1,  0,      0,  1,      // bottom   left
             1, 1,  0,      1,  0,      // top      right
             1,-1,  0,      1,  1       // bottom   right
    };

    unsigned int indices[] = {
            0, 1, 2,
            1, 3, 2
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);
    //texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, frame_buffer);


    mainShader.use();
    //main update loop
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,w,h,GL_RGB,GL_UNSIGNED_BYTE,frame_buffer);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    std::cout << "[INFO]:\tWindow is closing" << std::endl;
    return 1;

}
void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "[INFO]:\tUser interrupt, closing window" << std::endl;
        glfwSetWindowShouldClose(window,true);
    }
}

#endif //INONEWEEKEND_WINDOW_H
