/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:28:52 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 16:04:53 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

void	edit_rasterization(int key, int act)
{
	GLint polygon_mode;

	if (key == GLFW_KEY_R && act == GLFW_PRESS)
	{
		glGetIntegerv(GL_POLYGON_MODE, &polygon_mode);
		if (polygon_mode == GL_FILL)
			polygon_mode = GL_LINE;
		else if (polygon_mode == GL_LINE)
			polygon_mode = GL_POINT;
		else
			polygon_mode = GL_FILL;
		glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);
	}
}

void	edit_texture(t_monitor *mon, int key, int act)
{
	if (key == GLFW_KEY_T && act == GLFW_PRESS)
	{
		if (mon->enable_texture)
			mon->enable_texture = 0;
		else
			mon->enable_texture = 1;
	}
}

void	edit_mouse_activation(t_monitor *mon, int key, int act)
{
	if (key == GLFW_KEY_M && act == GLFW_PRESS)
	{
		if (!mon->enable_mouse)
			glfwSetInputMode(mon->win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(mon->win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		mon->enable_mouse ^= 1;
	}
}

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

void	key_callback(GLFWwindow *w, int key, int scancode, int act, int mods)
{
	t_monitor	*mon;

	(void)scancode;
	(void)mods;
	mon = (t_monitor *)glfwGetWindowUserPointer(w);
	handle_camera_view(mon, key, act);
	handle_camera_position(mon, key, act);
	edit_mouse_activation(mon, key, act);
	edit_rasterization(key, act);
	edit_texture(mon, key, act);
	if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS)
		glfwSetWindowShouldClose(w, GLFW_TRUE);
	else if (key == GLFW_KEY_K && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->transformation)
		mon->transformation->rotation.y -= 0.01f;
	else if (key == GLFW_KEY_L && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->transformation)
		mon->transformation->rotation.y += 0.01f;
	else if (key == GLFW_KEY_O && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->transformation)
		mon->transformation->position.y += 0.01f;
	else if (key == GLFW_KEY_PERIOD && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->transformation)
		mon->transformation->position.y -= 0.01f;
}
