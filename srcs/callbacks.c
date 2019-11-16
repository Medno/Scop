/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:28:52 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 18:54:02 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

void	scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	t_monitor	*mon;

	(void)xoffset;
	mon = (t_monitor *)glfwGetWindowUserPointer(window);
	if (!mon->enable_mouse)
		return ;
	if (mon->camera->fov >= 1.0f && mon->camera->fov <= 45.0f)
		mon->camera->fov -= yoffset;
	if (mon->camera->fov <= 1.0f)
		mon->camera->fov = 1.0f;
	if (mon->camera->fov >= 45.0f)
		mon->camera->fov = 45.0f;
}

void	move_obj(t_monitor *mon, int key, int act)
{
	t_transform	*trans;

	trans = (mon->mode == LIGHT_MODE && mon->light_trans)
		? mon->light_trans : mon->transformation;
	if (key == GLFW_KEY_Y && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& trans)
		trans->position.x -= 0.02f;
	else if (key == GLFW_KEY_U && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& trans)
		trans->position.x += 0.02f;
	else if (key == GLFW_KEY_H && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& trans)
		trans->position.y += 0.02f;
	else if (key == GLFW_KEY_J && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& trans)
		trans->position.y -= 0.02f;
	else if (key == GLFW_KEY_B && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& trans)
		trans->position.z += 0.02f;
	else if (key == GLFW_KEY_N && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& trans)
		trans->position.z -= 0.02f;
}

void	key_callback(GLFWwindow *w, int key, int scancode, int act, int mods)
{
	t_monitor	*mon;

	(void)scancode;
	(void)mods;
	mon = (t_monitor *)glfwGetWindowUserPointer(w);
	if (mon)
	{
		handle_camera_view(mon, key, act);
		handle_camera_position(mon, key, act);
		edit_mouse_activation(mon, key, act);
		edit_rasterization(key, act);
		edit_texture(mon, key, act);
		edit_rotation_activation(mon, key, act);
		edit_speed(mon, key, act);
		edit_light_activation(mon, key, act);
		edit_mode(mon, key, act);
		edit_color_display(mon, key, act);
		move_obj(mon, key, act);
	}
	if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS)
		glfwSetWindowShouldClose(w, GLFW_TRUE);
}
