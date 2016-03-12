//
//  ShaderProgram.cpp
//  CookieEngine
//
//  Created by Amos Byon on 3/12/16.
//  Copyright (c) 2016 Amos Byon. All rights reserved.
//

#include "ShaderProgram.h"
#include <fstream>

namespace CookieEngine
{
    std::string stringFromFile(const std::string& filename)
    {
        std::ifstream file;
        file.open(filename.c_str(), std::ios::in | std::ios::binary);
        
        std::string output;
        std::string line;
        if(!file.is_open())
        {
            std::runtime_error(std::string("Failed to open file: ") + filename);
        }
        else
        {
            while(file.good())
            {
                getline(file, line);
                
                output.append(line + "\n");
            }
        }
        
        file.close();
        return output;
    }
    
    // Constructor
    ShaderProgram::ShaderProgram() : mObject(0), mLinked(false), mErrorLog()
    {
        mObject = glCreateProgram();
    }
    
    // Destructor
    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(mObject);
    }
    
    bool ShaderProgram::attachShaderFromFile(ShaderType type, const std::string& filename)
    {
        std::string source = stringFromFile(filename);
        return attachShaderFromMemory(type, source);
    }
    
    bool ShaderProgram::attachShaderFromMemory(ShaderType type, const std::string& source)
    {
        const char* shaderSource = source.c_str();
        
        GLuint shader;
        if(type == ShaderType::Vertex)
        {
            shader = glCreateShader(GL_VERTEX_SHADER);
        }
        else if(type == ShaderType::Fragment)
        {
            shader = glCreateShader(GL_FRAGMENT_SHADER);
        }
        
        glShaderSource(shader, 1, &shaderSource, nullptr);
        glCompileShader(shader);
        
        glAttachShader(mObject, shader);
        
        return true;
    }
    
    void ShaderProgram::use() const
    {
        if(!isInUse())
        {
            glUseProgram(mObject);
        }
    }
    
    bool ShaderProgram::isInUse() const
    {
        GLint currProgram = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
        
        return (currProgram == (GLint)mObject);
    }
    
    void ShaderProgram::stopUsing() const
    {
        if(isInUse())
        {
            glUseProgram(0);
        }
    }
    
    bool ShaderProgram::link()
    {
        if(!isLinked())
        {
            glLinkProgram(mObject);
            
            mLinked = true;
        }
        
        return mLinked;
    }
    
    bool ShaderProgram::isLinked()
    {
        return mLinked;
    }
    
    void ShaderProgram::bindAttributeLocation(GLuint location, const GLchar* name)
    {
        glBindAttribLocation(mObject, location, name);
    }
    
    GLint ShaderProgram::getUniformLocation(const GLchar* name)
    {
        return glGetUniformLocation(mObject, name);
    }
    
    GLint ShaderProgram::getAttributeLocation(const GLchar* name)
    {
        return glGetAttribLocation(mObject, name);
    }
    
    void ShaderProgram::setUniform(const GLchar* name, float x)
    {
        if(!isInUse())
        {
            use();
        }
        glUniform1f(getUniformLocation(name), x);
    }
    
    void ShaderProgram::setUniform(const GLchar* name, float x, float y)
    {
        if(!isInUse())
        {
            use();
        }
        glUniform2f(getUniformLocation(name), x, y);
    }
    
    void ShaderProgram::setUniform(const GLchar* name, float x, float y, float z)
    {
        if(!isInUse())
        {
            use();
        }
        glUniform3f(getUniformLocation(name), x, y, z);
    }
    
    void ShaderProgram::setUniform(const GLchar* name, float x, float y, float z, float w)
    {
        if(!isInUse())
        {
            use();
        }
        glUniform4f(getUniformLocation(name), x, y, z, w);
    }
    
    void ShaderProgram::setUniform(const GLchar* name, unsigned int x)
    {
        if(!isInUse())
        {
            use();
        }
        glUniform1ui(getUniformLocation(name), x);
    }
    
    void ShaderProgram::setUniform(const GLchar* name, int x)
    {
        if(!isInUse())
        {
            use();
        }
        glUniform1i(getUniformLocation(name), x);
    }
    
    void ShaderProgram::setUniform(const GLchar* name, bool x)
    {
        if(!isInUse())
        {
            use();
        }
        glUniform1i(getUniformLocation(name), (int)x);
    }
} // namespace CookieEngine
