/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:52:33 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/10 18:07:00 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

#include <SDL.h>
#include <GL/glew.h>
#include <OpenGL/gl.h>

typedef struct	s_monitor {
	SDL_Window*		win;
	SDL_GLContext	context;
	SDL_Event		event;
}				t_monitor;

uint8_t	init_monitor(t_monitor *monitor);
void	destroy_monitor(t_monitor *monitor);
void	clear_window(float r, float g, float b, float a);

uint8_t	update_monitor(t_monitor monitor);

#endif
