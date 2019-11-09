/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders_updates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:51:43 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/09 13:32:02 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

void			use_shader(t_shader shader)
{
	glUseProgram(shader.program);
}

/*
** Send matrices (MVP) to the vertex shader
*/

void			update_shader(t_shader *s, t_monitor *m)
{
	t_mat4	model;
	t_mat4	view;
	t_mat4	projection;
	float	ratio;

	model = get_model(*(m->transformation));
	glUniformMatrix4fv(
			s->uniforms[MODEL_U], 1, GL_TRUE, &model.matrix[0][0]);
	view = view_look_at(m->camera->position,
		vec3_add(m->camera->position, m->camera->front), m->camera->up);
	glUniformMatrix4fv(
			s->uniforms[VIEW_U], 1, GL_TRUE, &view.matrix[0][0]);
	ratio = (float)WIDTH / (float)HEIGHT;
	projection = projection_mat4(45.0f, ratio, 0.01f, 100.0f);
	glUniformMatrix4fv(
			s->uniforms[PROJECTION_U], 1, GL_TRUE, &projection.matrix[0][0]);
	if (m->enable_texture && s->alpha < 1.0)
	{
		s->alpha += 0.001;
	printf("s->alpha = %f\n", s->alpha);
	}
	else if (!m->enable_texture && s->alpha > 0.0)
	{
		s->alpha -= 0.001;
	printf("s->alpha = %f\n", s->alpha);
	}
	glUniform1f(s->uniforms[ALPHA_U], s->alpha);
}
