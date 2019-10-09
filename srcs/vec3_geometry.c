#include "vec3.h"

float	vec3_magnitude(t_vec3 vect)
{
	return (sqrtf((vect.x * vect.x) + (vect.y * vect.y) + (vect.z * vect.z)));
}

t_vec3	vec3_normalize(t_vec3 vect)
{
	t_vec3	normalized;
	float	magnitude;

	magnitude = vec3_magnitude(vect);
	normalized = vect;
	normalized.x /= magnitude;
	normalized.y /= magnitude;
	normalized.z /= magnitude;
	return (normalized);
}

t_vec3			vec3_cross(t_vec3 first, t_vec3 second)
{
	return (vec3_new(
		(first.y * second.z) - (second.y * first.z),
		(first.z * second.x) - (second.z * first.x),
		(first.x * second.y) - (second.x * first.y)));
}
