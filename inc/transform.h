#ifndef TRANSFORM_H
# define TRANSFORM_H

#include "vec3.h"
#include "mat4.h"

enum e_axis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};

typedef struct	s_transform
{
	t_vec3	position;
	t_vec3	rotation;
	t_vec3	scale;
}				t_transform;

t_transform	create_transform(void);
t_mat4		get_model(t_transform t);

#endif
