/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_constructors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:07:08 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 19:07:21 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

t_transform	create_transform(void)
{
	t_transform	new_t;

	new_t.position = vec3_new(0.0f, 0.0f, 0.0f);
	new_t.rotation = vec3_new(0.0f, 0.0f, 0.0f);
	new_t.scale = vec3_new(1.0f, 1.0f, 1.0f);
	return (new_t);
}

t_mat4		get_model(t_transform t)
{
	t_mat4	pos_matrix;
	t_mat4	rot_matrix;
	t_mat4	scale_matrix;
	t_mat4	final_matrix;

	pos_matrix = translate(mat4_new(IDENTITY), t.position);
	rot_matrix = rotate(t);
	scale_matrix = scale(t);
	final_matrix = mat4_mul(pos_matrix, mat4_mul(rot_matrix, scale_matrix));
	return (final_matrix);
}
