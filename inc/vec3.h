/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:19:16 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 12:36:34 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>
# include <stdlib.h>

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef enum	e_vec3_coordinate
{
	COORD_X,
	COORD_Y,
	COORD_Z
}				t_v3_coord;

t_vec3			vec3_new(float x, float y, float z);
t_vec3			*vec3_array(size_t size);

t_vec3			vec3_add(t_vec3 first, t_vec3 second);
t_vec3			vec3_sub(t_vec3 first, t_vec3 second);
t_vec3			vec3_mul_scalar(t_vec3 first, float scalar);

float			vec3_magnitude(t_vec3 vect);
t_vec3			vec3_normalize(t_vec3 vect);
t_vec3			vec3_cross(t_vec3 first, t_vec3 second);

float			*vec3_assign_coord(t_vec3 *vec, t_v3_coord coord);
#endif
