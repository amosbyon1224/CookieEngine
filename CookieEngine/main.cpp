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
#include "CookieMath.h"
#include "ShaderProgram.h"

int main(int argc, const char * argv[]) {
    GLFWwindow* window;
    
    // initialize GLFW
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);    // 4x AA
    
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
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    float vertices[] = {
        +0.0f, +0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        +0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    };
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    CookieEngine::ShaderProgram shaderProgram;
    shaderProgram.attachShaderFromFile(CookieEngine::ShaderType::Vertex, "shaders/default.vert");
    shaderProgram.attachShaderFromFile(CookieEngine::ShaderType::Fragment, "shaders/default.frag");
    
    shaderProgram.bindAttributeLocation(0, "vertPosition");
    shaderProgram.bindAttributeLocation(1, "vertColor");
    shaderProgram.link();
    shaderProgram.use();
    
    do
    {
        glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // DRAW STUFF HERE
        {
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const GLvoid*)(2*sizeof(float)));
            
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
        }
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }while(!glfwWindowShouldClose(window));
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
