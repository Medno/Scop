/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:15:38 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 11:12:32 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERS_H
# define SHADERS_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <stdio.h>
# include "libft.h"
# include "mat4.h"
# include "view.h"
# include "read_file.h"

# define NUM_SHADERS 2

enum
{
	MODEL_U,
	VIEW_U,
	PROJECTION_U,
	ALPHA_U,
	LIGHT_COLOR_U,

	NUM_UNIFORMS
};

typedef struct	s_shader
{
	GLuint	program;
	GLuint	id_so[NUM_SHADERS];
	GLuint	uniforms[NUM_UNIFORMS];
	GLfloat	alpha;
}				t_shader;

t_shader		*construct_shader(const char *file);
t_shader		*delete_shader(t_shader *shader);
void			use_shader(t_shader *shader);

char			*read_shader_file(const char *filename);

#endif
