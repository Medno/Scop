#include "vec3.h"

t_vec3	vec3_add(t_vec3 first, t_vec3 second)
{
	return (vec3_new(first.x + second.x, first.y + second.y,
		first.z + second.z));
}

t_vec3	vec3_sub(t_vec3 first, t_vec3 second)
{
	return (vec3_new(first.x - second.x, first.y - second.y,
		first.z - second.z));
}

t_vec3	vec3_mul_scalar(t_vec3 vect, float scalar)
{
	return (vec3_new(vect.x * scalar, vect.y * scalar, vect.z * scalar));
}
