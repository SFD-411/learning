#Shader Vertex
#version 420 core

layout(location = 0) in vec3 aPos;

out vec4 vertColor;
uniform mat4 transform;

void main(){
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertColor = vec4(0.5, 0.71, 1.0, 1.0);
};

#Shader Fragment
#version 420 core

in vec4 vertColor;
out vec4 fragColor;

void main(){
  fragColor = vertColor;
};
