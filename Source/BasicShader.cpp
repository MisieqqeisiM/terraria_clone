#include"BasicShader.h"
#include<iostream>
#include<GL/glew.h>
#include<glm/glm.hpp>
BasicShader::BasicShader(const char*vertexPath, const char* fragmentPath){
    loadFromFiles(vertexPath, fragmentPath);
    link();
    aspect_ratio_uniform_location = glGetUniformLocation(programID, "aspectRatio");
    cam_x_uniform_location = glGetUniformLocation(programID, "cameraX");
    cam_y_uniform_location = glGetUniformLocation(programID, "cameraY");
    trans_x_uniform_location = glGetUniformLocation(programID, "translateX");
    trans_y_uniform_location = glGetUniformLocation(programID, "translateY");
    scale_x_uniform_location = glGetUniformLocation(programID, "scaleX");
    scale_y_uniform_location = glGetUniformLocation(programID, "scaleY");
};
void BasicShader::setScale(float x, float y){
    use();
    glUniform1f(scale_x_uniform_location, x);
    glUniform1f(scale_y_uniform_location, y);
};

void BasicShader::loadCameraPosition(float x, float y){
    use();
    glUniform1f(cam_x_uniform_location, x);
    glUniform1f(cam_y_uniform_location, y);
};
void BasicShader::setTranslation(float x, float y){
    use();
    glUniform1f(trans_x_uniform_location, x);
    glUniform1f(trans_y_uniform_location, y);
};

void BasicShader::loadAspectRatio(float aspectRatio){
    use();
    glUniform1f(aspect_ratio_uniform_location, aspectRatio);
};
