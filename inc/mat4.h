/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:14:54 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 19:18:10 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_H
# define MAT4_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# include "vec3.h"

enum	e_mat
{
	IDENTITY,
	ZEROS
};

typedef struct	s_mat4
{
	float	matrix[4][4];
}				t_mat4;

t_mat4			mat4_new(enum e_mat type);

t_mat4			mat4_add(t_mat4 first, t_mat4 second);
t_mat4			mat4_sub(t_mat4 first, t_mat4 second);
t_mat4			mat4_mul(t_mat4 first, t_mat4 second);

t_mat4			mat4_add_vec3(t_mat4 mat, t_vec3 vect, uint8_t coord);
void			mat4_print(t_mat4 m);

#endif
