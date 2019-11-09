/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:03:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/09 13:40:21 by pchadeni         ###   ########.fr       */
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

float	degree_to_radian(float degree)
{
	return (degree * M_PI / 180.0);
}

void	edit_front(t_camera *camera, float xoffset, float yoffset)
{
	float xpos = xoffset + camera->last_x;
	float ypos = yoffset + camera->last_y;
	camera->last_x = xpos;
	camera->last_y = ypos;

	float sensibility = 0.05f;
	xoffset *= sensibility;
	yoffset *= sensibility;

	camera->yaw += xoffset;
	camera->pitch += yoffset;

	if (camera->pitch > 89.0f)
		camera->pitch = 89.0f;
	if (camera->pitch < -89.0f)
		camera->pitch = -89.0f;
	t_vec3	new_front;

	new_front.x = cos(degree_to_radian(camera->yaw)) * cos(degree_to_radian(camera->pitch));
	new_front.y = sin(degree_to_radian(camera->pitch));
	new_front.z = sin(degree_to_radian(camera->yaw)) * cos(degree_to_radian(camera->pitch));
	camera->front = new_front;
}

void	edit_texture(t_monitor *mon)
{
printf("Edit texture alpha");
	if (mon->enable_texture)
		mon->enable_texture = 0;
	else
		mon->enable_texture = 1;
}

void	key_callback(GLFWwindow *w, int key, int scancode, int act, int mods)
{
	t_monitor	*mon;

	(void)scancode;
	(void)mods;
	mon = (t_monitor *)glfwGetWindowUserPointer(w);
//	mon->camera->speed = mon->camera->delta_time * 5.5f;
	if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS)
		glfwSetWindowShouldClose(w, GLFW_TRUE);
	else if (key == GLFW_KEY_R && act == GLFW_PRESS)
		edit_rasterization();

	else if (key == GLFW_KEY_UP && (act == GLFW_PRESS || act == GLFW_REPEAT)
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


	else if (key == GLFW_KEY_T && act == GLFW_PRESS)
		edit_texture(mon);

	else if (key == GLFW_KEY_W && (act == GLFW_PRESS || act == GLFW_REPEAT)
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
			vec3_mul_scalar(vec3_normalize(vec3_cross(mon->camera->front, mon->camera->up)), mon->camera->speed));
	else if (key == GLFW_KEY_D && (act == GLFW_PRESS || act == GLFW_REPEAT)
		&& mon && mon->camera)
		mon->camera->position = vec3_add(mon->camera->position,
			vec3_mul_scalar(vec3_normalize(vec3_cross(mon->camera->front, mon->camera->up)), mon->camera->speed));



// TO delete
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
	glfwMakeContextCurrent(monitor->win);
	glfwSetFramebufferSizeCallback(monitor->win, framebuffer_size_callback);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	monitor->camera = init_camera();
	monitor->enable_texture = 0;
	return (1);
}

/*
** Clear the screen from the previous iteration
*/

void	clear_window(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*
** Render loop.
** glfwSwapBuffers will swap the color buffer that has been used to
** draw in during this iteration and show it as output to the screen
** glfwPollEvents checks any events are triggered.
*/

uint8_t	update_monitor(t_monitor *monitor)
{
	glfwSwapBuffers(monitor->win);
	glfwPollEvents();
	return (0);
}

void	destroy_monitor(t_monitor monitor)
{
	glfwDestroyWindow(monitor.win);
	glfwTerminate();
	free(monitor.camera);
}
