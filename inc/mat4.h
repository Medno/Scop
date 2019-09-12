#ifndef MAT4_H
# define MAT4_H

# define IDENTITY 1
# define  2

enum	e_mat
{
	IDENTITY,
	ZERO
};

typedef struct	s_mat4
{
	float	matrix[4][4];
}				t_mat4;

t_mat4	add_mat4(t_mat4 first, t_mat4 second);
t_mat4	sub_mat4(t_mat4 first, t_mat4 second);
t_mat4	mul_mat4(t_mat4 first, t_mat4 second);
#endif
