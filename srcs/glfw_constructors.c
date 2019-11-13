/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_constructors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:09:48 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 16:04:13 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

static uint8_t	error_glfw(const char *err)
{
	dprintf(2, "Error : %s\n", err);
	return (0);
}

static void		framebuffer_size_callback(GLFWwindow *w, int width, int height)
{
	(void)w;
	glViewport(0, 0, width, height);
}

uint8_t			init_glfw_config(t_monitor *monitor)
{
	if (!glfwInit())
		return (error_glfw("Error during initialization of GLFW"));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	monitor->win = glfwCreateWindow(WIDTH, HEIGHT, "Scop", NULL, NULL);
	if (!monitor->win)
	{
		glfwTerminate();
		return (error_glfw("Error while creating a window"));
	}
	glfwSetWindowUserPointer(monitor->win, (void *)monitor);
	glfwSetKeyCallback(monitor->win, key_callback);
	glfwSetCursorPosCallback(monitor->win, mouse_callback);
	glfwSetScrollCallback(monitor->win, scroll_callback);
	glfwMakeContextCurrent(monitor->win);
	glfwSetFramebufferSizeCallback(monitor->win, framebuffer_size_callback);
	return (1);
}

uint8_t			destroy_glfw_config(t_monitor *monitor)
{
	glfwDestroyWindow(monitor->win);
	glfwTerminate();
	return (0);
}
