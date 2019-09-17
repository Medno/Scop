/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:52:33 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/17 15:51:08 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <stdio.h>

typedef struct	s_monitor {
	GLFWwindow		*win;
}				t_monitor;

uint8_t	init_monitor(t_monitor *monitor);
void	destroy_monitor(t_monitor *monitor);
void	clear_window(float r, float g, float b, float a);

uint8_t	update_monitor(t_monitor monitor);

#endif
