#include "vec3.h"

t_vec3	add_vec3(t_vec3 first, t_vec3 second)
{
	t_vec3	res;

	res.x = first.x + second.x;
	res.y = first.y + second.y;
	res.z = first.z + second.y;
	return (res);
}

t_vec3	sub_vec3(t_vec3 first, t_vec3 second)
{
	t_vec3	res;

	res.x = first.x - second.x;
	res.y = first.y - second.y;
	res.z = first.z - second.y;
	return (res);
}
