/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:14:15 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 16:14:16 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_H
# define VIEW_H

# include <GLFW/glfw3.h>
# include "mat4.h"
# include "vec3.h"
# define WIDTH 800
# define HEIGHT 600

typedef struct	s_camera
{
	t_vec3	position;
	t_vec3	front;
	t_vec3	up;
	float	speed;
	float	delta_time;
	float	last_frame;
	float	last_x;
	float	last_y;
	float	fov;
	float	yaw;
	float	pitch;
}				t_camera;

t_camera		*init_camera(void);
t_mat4			view_look_at(t_vec3 position, t_vec3 target, t_vec3 up);

void			update_delta_time(t_camera *camera);

#endif
