/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:03:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/17 15:57:59 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

/*
** Initialize SDL window
** Double buffering for OpenGL
** Creation of a window
** Creation of a OpenGL context
*/

/*
static void	set_attributes_sdl(void)
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
int maj;
SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &maj);
int min;
SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &min);
printf("SDL maj : %d, min : %d\n", maj, min);
}
*/
static uint8_t	error_glfw(const char *err)
{
	dprintf(2, "Error : %s\n", err);
	return (0);
}

void	key_callback(GLFWwindow *w, int key, int scancode, int act, int mods)
{
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS)
		glfwSetWindowShouldClose(w, GLFW_TRUE);
}

uint8_t	init_monitor(t_monitor *monitor)
{
	if (!glfwInit())
		return error_glfw("Error during initialization of GLFW");
	monitor->win = glfwCreateWindow(800, 600, "Scop", NULL, NULL);
	if (!monitor->win)
	{
		glfwTerminate();
		return error_glfw("Error while creating a window");
	}
	glfwSetKeyCallback(monitor->win, key_callback);
	glfwMakeContextCurrent(monitor->win);

	return (1);

/*
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	set_attributes_sdl();
	monitor->win = SDL_CreateWindow("Scop", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (!monitor->win)
	monitor->context = SDL_GL_CreateContext(monitor->win);
	if (!monitor->context)
		return error_sdl(monitor, "", 1);
	glewExperimental = GL_TRUE;
	GLenum status = glewInit();
	if (status != GLEW_OK)
		dprintf(2, "Glew failed to initialize\n");
	return (status == GLEW_OK ? 1 : 0);
*/
}

void	destroy_monitor(t_monitor *monitor)
{
	glfwDestroyWindow(monitor->win);
	glfwTerminate();
/*
	SDL_GL_DeleteContext(monitor->context);
	SDL_DestroyWindow(monitor->win);
	SDL_Quit();
	*/
}

void	clear_window(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

uint8_t	update_monitor(t_monitor monitor)
{
	glfwSwapBuffers(monitor.win);
	glfwPollEvents();
	return (0);
}
