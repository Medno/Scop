#ifndef VIEW_H
# define VIEW_H

# include "mat4.h"
# include "vec3.h"

typedef struct	s_camera
{
	t_vec3	position;
	t_vec3	front;
	t_vec3	up;
	float	speed;
}				t_camera;

t_camera		*init_camera(void);
t_mat4			view_look_at(t_vec3 position, t_vec3 target, t_vec3 up);

#endif
