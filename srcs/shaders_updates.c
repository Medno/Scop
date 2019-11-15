/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders_updates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:51:43 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/15 19:43:52 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

void			use_shader(t_shader *shader)
{
	glUseProgram(shader->program);
}

/*
** Send matrices (MVP) to the vertex shader
*/

void			update_obj_shader(t_monitor *m)
{
	t_mat4	model;
	t_mat4	view;
	t_mat4	projection;
	float	ratio;

	model = get_model(*(m->transformation));
	glUniformMatrix4fv(
			m->obj_shader->uniforms[MODEL_U], 1, GL_TRUE, &model.matrix[0][0]);
	view = view_look_at(m->camera->position,
		vec3_add(m->camera->position, m->camera->front), m->camera->up);
	glUniformMatrix4fv(m->obj_shader->uniforms[VIEW_U], 1, GL_TRUE,
			&view.matrix[0][0]);
	ratio = (float)WIDTH / (float)HEIGHT;
	projection = projection_mat4(
			degree_to_radian(m->camera->fov), ratio, 0.01f, 100.0f);
	glUniformMatrix4fv(m->obj_shader->uniforms[PROJECTION_U], 1, GL_TRUE,
			&projection.matrix[0][0]);
	if (m->enable_texture && m->obj_shader->alpha < 1.0)
		m->obj_shader->alpha += 0.001;
	else if (!m->enable_texture && m->obj_shader->alpha > 0.0)
		m->obj_shader->alpha -= 0.001;
	glUniform1f(m->obj_shader->uniforms[ALPHA_U], m->obj_shader->alpha);
}

void			set_light_uniforms(t_shader *shader)
{
	
}

void			update_light_shader(t_monitor *m)
{

}
