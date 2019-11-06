/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_constructors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:40:35 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/06 13:40:37 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

t_camer	*init_camera(void)
{
	t_camera	*camera;

	if (!(camera = (t_camera *)malloc(sizeof(t_camera))))
		return (NULL);
	camera->position = vec3_new(0.0f, 0.0f, 3.0f);
	camera->front = vec3_new(0.0f, 0.0f, -1.0f);
	camera->up = vec3_new(0.0f, 1.0f, 0.0f);
	camera->speed = 0.05f;
	camera->delta_time = 0.0f;
	camera->last_frame = 0.0f;
	camera->last_x = WIDTH / 2;
	camera->last_y = HEIGHT / 2;
	camera->yaw = -90.0f;
	camera->pitch = 0.0f;
	return (camera);
}

void	update_delta_time(t_camera *camera)
{
	float	current_frame;

	current_frame = glfwGetTime();
	camera->delta_time = current_frame - camera->last_frame;
	camera->last_frame = current_frame;
}

t_mat4	create_new_axes(t_vec3 position, t_vec3 target, t_vec3 upspace)
{
	t_mat4	result;
	t_vec3	direction;
	t_vec3	right;
	t_vec3	up;

	direction = vec3_normalize(vec3_sub(position, target));
	right = vec3_normalize(vec3_cross(upspace, direction));
	up = vec3_cross(direction, right);
	result = mat4_new(IDENTITY);
	result = mat4_add_vec3(result, right, 0);
	result = mat4_add_vec3(result, up, 1);
	result = mat4_add_vec3(result, direction, 2);
	return (result);
}

t_mat4	view_look_at(t_vec3 position, t_vec3 target, t_vec3 up)
{
	t_mat4	perpendicular_axes;
	t_mat4	opposite_direction;

	perpendicular_axes = create_new_axes(position, target, up);
	opposite_direction = mat4_new(IDENTITY);
	opposite_direction.matrix[0][3] = -1 * position.x;
	opposite_direction.matrix[1][3] = -1 * position.y;
	opposite_direction.matrix[2][3] = -1 * position.z;
	return (mat4_mul(perpendicular_axes, opposite_direction));
}
