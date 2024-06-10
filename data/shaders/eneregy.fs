uniform vec4 u_color;
uniform float energy_charged;

varying vec2 v_uv;

void main()
{
	vec4 my_color = u_color;
	float n_energy = float(energy_charged)/50.0;
	if(v_uv.x>n_energy)
		my_color = my_color*0.2;

	gl_FragColor = my_color;
}
