#version 330 core
layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 in_TextureCoords;
layout (location = 2) in vec3 in_Normal;

out vec2 pass_TextureCoords;
out vec3 pass_Normal;

uniform float aspectRatio;

uniform float translateX, translateY;
uniform float cameraX, cameraY;
uniform float scaleX, scaleY;
void main(){
    float zoom = 1.5;
    float dist = 30;
    pass_TextureCoords = in_TextureCoords;
    pass_Normal = in_Normal;
    gl_Position = vec4(zoom*(scaleX*in_Position.x+translateX-cameraX)*aspectRatio, zoom*(scaleY*in_Position.y+translateY-cameraY), in_Position.z,dist+in_Position.z);
}
