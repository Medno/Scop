/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_updates.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:23:40 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 15:41:29 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

void	edit_front(t_camera *camera, float xoffset, float yoffset)
{
	t_vec3	new_front;
	float	xpos;
	float	ypos;
	float	sensibility;

	xpos = xoffset + camera->last_x;
	ypos = yoffset + camera->last_y;
	camera->last_x = xpos;
	camera->last_y = ypos;
	sensibility = 0.05f;
	xoffset *= sensibility;
	yoffset *= sensibility;
	camera->yaw += xoffset;
	camera->pitch += yoffset;
	if (camera->pitch > 89.0f)
		camera->pitch = 89.0f;
	if (camera->pitch < -89.0f)
		camera->pitch = -89.0f;
	new_front.x = cos(degree_to_radian(camera->yaw))
		* cos(degree_to_radian(camera->pitch));
	new_front.y = sin(degree_to_radian(camera->pitch));
	new_front.z = sin(degree_to_radian(camera->yaw))
		* cos(degree_to_radian(camera->pitch));
	camera->front = new_front;
}

void	mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	t_monitor	*mon;
	float		xoffset;
	float		yoffset;

	mon = (t_monitor *)glfwGetWindowUserPointer(window);
	if (!mon->enable_mouse)
		return ;
	xoffset = xpos - mon->camera->last_x;
	yoffset = ypos - mon->camera->last_y;
	edit_front(mon->camera, xoffset, yoffset);
}

void	handle_camera_view(t_monitor *mon, int key, int act)
{
	if (key == GLFW_KEY_UP && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->camera)
		edit_front(mon->camera, 0.0f, 10.0f);
	else if (key == GLFW_KEY_LEFT && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->camera)
		edit_front(mon->camera, -10.0f, 0.0f);
	else if (key == GLFW_KEY_DOWN && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->camera)
		edit_front(mon->camera, 0.0f, -10.0f);
	else if (key == GLFW_KEY_RIGHT && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->camera)
		edit_front(mon->camera, 10.0f, 0.0f);
}

void	handle_camera_position(t_monitor *mon, int key, int act)
{
	if (key == GLFW_KEY_W && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->camera)
		mon->camera->position = vec3_add(mon->camera->position,
			vec3_mul_scalar(mon->camera->front, mon->camera->speed));
	else if (key == GLFW_KEY_S && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->camera)
		mon->camera->position = vec3_sub(mon->camera->position,
			vec3_mul_scalar(mon->camera->front, mon->camera->speed));
	else if (key == GLFW_KEY_A && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->camera)
		mon->camera->position = vec3_sub(mon->camera->position,
			vec3_mul_scalar(vec3_normalize(vec3_cross(mon->camera->front,
				mon->camera->up)), mon->camera->speed));
	else if (key == GLFW_KEY_D && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->camera)
		mon->camera->position = vec3_add(mon->camera->position,
			vec3_mul_scalar(vec3_normalize(vec3_cross(mon->camera->front,
				mon->camera->up)), mon->camera->speed));
}
