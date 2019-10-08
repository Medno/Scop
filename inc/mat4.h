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
# include "vec3.h"
# include <stdio.h>

enum	e_mat
{
	IDENTITY,
	ZEROS
};

typedef struct	s_mat4
{
	float	matrix[4][4];
}				t_mat4;

t_mat4			new_mat4(enum e_mat type);

t_mat4			add_mat4(t_mat4 first, t_mat4 second);
t_mat4			sub_mat4(t_mat4 first, t_mat4 second);
t_mat4			mul_mat4(t_mat4 first, t_mat4 second);

void			print_mat4(t_mat4 m);

#endif
