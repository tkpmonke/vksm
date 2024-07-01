#version 450
#vert
vec2 positions[3] = vec2[](
   vec2(0.0, -0.5),
   vec2(0.5, 0.5),
   vec2(-0.5, 0.5)
);

void main() 
{
   gl_Position = vec4(positions[gl_VertexIndex]), 0.0, 1.0);
}

~
#frag

layout(location = 0) out vec4 oColor;

void main() 
{
   oColor = vec4(1,0,0,1);
}

