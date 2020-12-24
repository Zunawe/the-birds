#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 modelViewProjection;

void main(){
	gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
