#include "vec3.h"

t_vec3	create_vec3(float x, float y, float z)
{
	t_vec3	new_vec3;

	new_vec3.x = x;
	new_vec3.y = y;
	new_vec3.z = z;
	return (new_vec3);
}

t_vec3	add_vec3(t_vec3 first, t_vec3 second)
{
	return (create_vec3(first.x + second.x, first.y + second.y,
		first.z + second.y));
}

t_vec3	sub_vec3(t_vec3 first, t_vec3 second)
{
	return (create_vec3(first.x - second.x, first.y - second.y,
		first.z - second.y));
}
