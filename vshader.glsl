attribute highp vec3 vertex;
attribute lowp vec4 sourceColor;
uniform highp mat4 matrix;
varying mediump vec4 color;

void main()
{
  color = sourceColor;
  gl_Position = matrix * vec4(vertex, 1.0);
}
