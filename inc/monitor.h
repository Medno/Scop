/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:52:33 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 16:42:29 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <stdio.h>
# include "model.h"
# include "view.h"
# include "mesh.h"

# define WIDTH 800
# define HEIGHT 600

typedef struct	s_monitor {
	GLFWwindow	*win;
	t_transform	*transformation;
	t_camera	*camera;
	t_mesh		*mesh;
	uint8_t		enable_texture;
	uint8_t		enable_mouse;
	uint8_t		enable_rotation;
}				t_monitor;

uint8_t			init_glfw_config(t_monitor *monitor);
uint8_t			destroy_glfw_config(t_monitor *monitor);

uint8_t			init_monitor(t_monitor *monitor);
void			destroy_monitor(t_monitor monitor);
void			clear_window(float r, float g, float b, float a);

uint8_t			update_monitor(t_monitor *monitor);

void			key_callback(GLFWwindow *w, int key, int s, int act, int mods);
void			scroll_callback(GLFWwindow *w, double xoffset, double yoffset);
void			mouse_callback(GLFWwindow *window, double xpos, double ypos);

void			handle_camera_view(t_monitor *mon, int key, int act);
void			handle_camera_position(t_monitor *mon, int key, int act);

void			edit_rasterization(int key, int act);
void			edit_texture(t_monitor *mon, int key, int act);
void			edit_mouse_activation(t_monitor *mon, int key, int act);
void			edit_rotation_activation(t_monitor *mon, int key, int act);
#endif
