/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:15:38 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 19:21:10 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERS_H
# define SHADERS_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <stdio.h>
# include "libft.h"
# include "model.h"
# include "monitor.h"
# include "mat4.h"

# define NUM_SHADERS 2

enum
{
	MODEL_U,
	VIEW_U,
	PROJECTION_U,

	NUM_UNIFORMS
};

typedef struct	s_shader
{
	GLuint	program;
	GLuint	id_so[NUM_SHADERS];
	GLuint	uniforms[NUM_UNIFORMS];
}				t_shader;

uint8_t			construct_shader(const char *file, t_shader *new_shader);
void			delete_shader(t_shader shader);
void			use_shader(t_shader shader);

void			update_shader(t_shader s, t_transform t);

char			*read_shader_file(const char *filename);

#endif
