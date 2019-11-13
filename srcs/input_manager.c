/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:30:28 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 17:11:27 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

void	edit_rasterization(int key, int act)
{
	GLint polygon_mode;

	if (key == GLFW_KEY_P && act == GLFW_PRESS)
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
		mon->enable_texture ^= 1;
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

void	edit_rotation_activation(t_monitor *mon, int key, int act)
{
	if (key == GLFW_KEY_R && act == GLFW_PRESS)
		mon->enable_rotation ^= 1;
}
