//
//  ShaderProgram.h
//  CookieEngine
//
//  Created by Amos Byon on 3/12/16.
//  Copyright (c) 2016 Amos Byon. All rights reserved.
//

#ifndef CookieEngine_ShaderProgram_h
#define CookieEngine_ShaderProgram_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace CookieEngine
{
    
enum class ShaderType
{
    Vertex,
    Fragment,
};
    
class ShaderProgram
{
private:
    GLuint mObject;
    bool mLinked;
    std::string mErrorLog;
public:
    // Constructor
    ShaderProgram();
    
    // Destructor
    virtual ~ShaderProgram();
    
    bool attachShaderFromFile(ShaderType type, const std::string& filename);
    bool attachShaderFromMemory(ShaderType type, const std::string& source);
    
    void use() const;
    bool isInUse() const;
    void stopUsing() const;
    
    bool link();
    bool isLinked();
    
    void bindAttributeLocation(GLuint location, const GLchar* name);
    
    GLint getUniformLocation(const GLchar* name);
    GLint getAttributeLocation(const GLchar* name);
    
    void setUniform(const GLchar* name, float x);
    void setUniform(const GLchar* name, float x, float y);
    void setUniform(const GLchar* name, float x, float y, float z);
    void setUniform(const GLchar* name, float x, float y, float z, float w);
    void setUniform(const GLchar* name, unsigned int x);
    void setUniform(const GLchar* name, int x);
    void setUniform(const GLchar* name, bool x);
    
    inline GLuint object() const { return mObject; }
    const std::string errorLog() const { return mErrorLog; }
};
    
} // namespace CookieEngine

#endif
