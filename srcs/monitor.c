/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:03:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/30 17:22:49 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

static uint8_t	error_glfw(const char *err)
{
	dprintf(2, "Error : %s\n", err);
	return (0);
}

void	edit_rasterization(void)
{
	GLint polygon_mode;

	glGetIntegerv(GL_POLYGON_MODE, &polygon_mode);
	if (polygon_mode == GL_FILL)
		polygon_mode = GL_LINE;
	else if (polygon_mode == GL_LINE)
		polygon_mode = GL_POINT;
	else
		polygon_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);
}

void	key_callback(GLFWwindow *w, int key, int scancode, int act, int mods)
{
	t_monitor	*mon;

	(void)scancode;
	(void)mods;
	mon = (t_monitor *)glfwGetWindowUserPointer(w);
	if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS)
		glfwSetWindowShouldClose(w, GLFW_TRUE);
	else if (key == GLFW_KEY_R && act == GLFW_PRESS)
		edit_rasterization();
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

void	framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

uint8_t	init_monitor(t_monitor *monitor)
{
	if (!glfwInit())
		return (error_glfw("Error during initialization of GLFW"));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	monitor->win = glfwCreateWindow(WIDTH, HEIGHT, "Scop", NULL, NULL);
	if (!monitor->win)
	{
		glfwTerminate();
		return (error_glfw("Error while creating a window"));
	}
	glfwSetWindowUserPointer(monitor->win, (void *)monitor);
	glfwSetKeyCallback(monitor->win, key_callback);
	glEnable(GL_MULTISAMPLE);
	glfwMakeContextCurrent(monitor->win);
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(monitor->win, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);
	return (1);
}

void	destroy_monitor(t_monitor *monitor)
{
	glfwDestroyWindow(monitor->win);
	glfwTerminate();
}

void	clear_window(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

uint8_t	update_monitor(t_monitor *monitor)
{
	glfwSwapBuffers(monitor->win);
	glfwPollEvents();
	return (0);
}
