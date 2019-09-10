/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:03:00 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/10 18:27:58 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

/*
** Initialize SDL window
** Double buffering for OpenGL
** Creation of a window
** Creation of a OpenGL context
*/

uint8_t	init_monitor(t_monitor *monitor)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_printf("Error during initialization of SDL : %s\n", SDL_GetError());
		SDL_Quit();
		return (0);
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	monitor->win = SDL_CreateWindow("Scop", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!monitor->win)
	{
		ft_printf("Error while creating a window : %s\n", SDL_GetError());
		SDL_Quit();
		return (0);
	}
	monitor->context = SDL_GL_CreateContext(monitor->win);
	if (!monitor->context)
	{
		ft_printf("%s\n", SDL_GetError());
		SDL_DestroyWindow(monitor->win);
		SDL_Quit();
		return (0);
	}
	return (1);
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
