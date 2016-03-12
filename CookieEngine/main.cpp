//
//  main.cpp
//  CookieEngine
//
//  Created by Amos Byon on 1/14/16.
//  Copyright (c) 2016 Amos Byon. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vector3.h"
#include "Matrix4.h"

int main(int argc, const char * argv[]) {
    GLFWwindow* window;
    
    // initialize GLFW
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);                // 4x AA
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(1024, 768, "Cookie Engine", nullptr, nullptr);
    
    if(!window){
        std::cout << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    if(glewInit() != GLEW_OK){
        std::cout << "Failed to initialize GLEW\n";
        return -1;
    }
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    do{
        // Draw something here
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }while(!glfwWindowShouldClose(window));
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
