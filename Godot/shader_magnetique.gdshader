shader_type canvas_item;

uniform float param1; 
uniform float param2;
uniform float param3;
uniform float max_c3;
uniform float max_c1;
uniform float max_c2;

uniform sampler2D noise1;

bool is_at_circle_range(vec2 UV_val,float r, vec2 c,float thickness)
{
	if (distance(UV_val,c) < r+ thickness && distance(UV_val,c) > r - thickness)
	{
		return true;
	}
	else return false;
}

bool is_at_grid_range(vec2 UV_val, float h, float w ,vec2 c, float thickness)
{
	if (UV_val.x < c.x + w/2. + thickness && UV_val.x > c.x + w/2. - thickness  )
	{
		return true;
	}
	if (UV_val.x < c.x - w/2. + thickness && UV_val.x > c.x - w/2. - thickness  )
	{
		return true;
	}
	else if (UV_val.y < c.y + h/2. + thickness && UV_val.y > c.y + h/2. - thickness  )
	{
		return true;
	}
	else if (UV_val.y < c.y - h/2. + thickness && UV_val.y > c.y - h/2. - thickness  )
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void fragment() {
	vec3 base_color = vec3(param3/max_c3,.05*param3,param3/2.*max_c3);
	COLOR.rgb = base_color;
	
	if (is_at_circle_range(UV,log(abs(param1))/max_c1,vec2(.5,.5),.01))
	{
		COLOR.rgb = vec3(1.,1.,1.);
	}
	
	else if (is_at_grid_range(UV,log(abs(param2))/max_c2,log(param2)/max_c2,vec2(.5,.5),.01))
	{
		COLOR.rgb = vec3(1.,1.,1.);
	}
	
	
}
