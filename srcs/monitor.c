/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:03:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/11 11:32:28 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

/*
** Initialize SDL window
** Double buffering for OpenGL
** Creation of a window
** Creation of a OpenGL context
*/

static void	set_attributes_sdl(void)
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

static uint8_t	error_sdl(t_monitor *m, const char *err, uint8_t destr)
{
	dprintf(2, "%s%s\n", err, SDL_GetError());
	if (destr)
		SDL_DestroyWindow(m->win);
	SDL_Quit();
	return (0);
}

uint8_t	init_monitor(t_monitor *monitor)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return error_sdl(monitor, "Error during initialization of SDL : ", 0);
	set_attributes_sdl();
	monitor->win = SDL_CreateWindow("Scop", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (!monitor->win)
		return error_sdl(monitor, "Error while creating a window : ", 0);
	monitor->context = SDL_GL_CreateContext(monitor->win);
	if (!monitor->context)
		return error_sdl(monitor, "", 1);
	glewExperimental = GL_TRUE;
	GLenum status = glewInit();
	if (status != GLEW_OK)
		dprintf(2, "Glew failed to initialize\n");
	return (status == GLEW_OK ? 1 : 0);
}

/*
** // Version d'OpenGL
** SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
** SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
*/

void	destroy_monitor(t_monitor *monitor)
{
	SDL_GL_DeleteContext(monitor->context);
	SDL_DestroyWindow(monitor->win);
	SDL_Quit();
}

void	clear_window(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
