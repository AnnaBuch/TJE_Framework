
varying vec3 v_position;
varying vec3 v_world_position;
varying vec3 v_normal;
varying vec2 v_uv;
varying vec4 v_color;

uniform vec3 u_camera_pos;
uniform vec4 u_color;
uniform float u_time;
uniform samplerCube u_texture;


void main()
{
	vec3 V = normalize( u_camera_pos - v_world_position );
	gl_FragColor = u_color * textureCube( u_texture, V );
}
