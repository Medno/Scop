/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:08:55 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 19:17:46 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_H
# define MODEL_H

# include "vec3.h"
# include "mat4.h"

enum	e_axis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};

typedef struct	s_transform
{
	t_vec3	position;
	t_vec3	rotation;
	t_vec3	scale;
}				t_transform;

t_transform		create_transform(void);
t_mat4			get_model(t_transform t);

t_mat4			translate(t_mat4 mat4, t_vec3 vec3);
t_mat4			projection_mat4(float angle, float rat, float near, float far);
t_mat4			scale(t_transform t);
t_mat4			rotate(t_transform t);

#endif
