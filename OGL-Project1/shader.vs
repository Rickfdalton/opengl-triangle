#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
out vec4 ourColor;
uniform float offset; 
void main()
{	
   vec3 offset_pos=vec3(offset,offset,offset);
   gl_Position= vec4(aPos+offset_pos,1.0f);
   ourColor= vec4(aCol,1.0f);
}s