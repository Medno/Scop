#include "transform.h"

t_transform	create_transform(void)
{
	t_transform	new_t;

	new_t.position = create_vec3(0.0f, 0.0f, 0.0f);
	new_t.rotation = create_vec3(0.0f, 0.0f, 0.0f);
	new_t.scale = create_vec3(1.0f, 1.0f, 1.0f);
	return (new_t);
}

t_mat4	scale(t_transform t)
{
	t_mat4	scaled;

	scaled = new_mat4(IDENTITY);
	scaled.matrix[0][0] *= t.scale.x;
	scaled.matrix[1][1] *= t.scale.y;
	scaled.matrix[2][2] *= t.scale.z;
	return (scaled);
}

t_mat4	rotate_axis(t_transform t, enum e_axis axis)
{
	t_mat4	n_mat4;
	int		i;
	int		j;
	float	angle;

	n_mat4 = new_mat4(IDENTITY);
	i = (axis == X_AXIS) ? 1 : 0;
	j = (axis == Y_AXIS) ? i + 2 : i + 1;
	if (axis == X_AXIS)
		angle = t.rotation.x;
	else if (axis == Y_AXIS)
		angle = t.rotation.y;
	else
		angle = t.rotation.z;
	n_mat4.matrix[i][i] = cosf(angle);
	n_mat4.matrix[i][j] = (axis == Y_AXIS) ? sinf(angle) : -sinf(angle);
	n_mat4.matrix[j][i] = (axis == Y_AXIS) ? -sinf(angle) : sinf(angle);
	i = j;
	n_mat4.matrix[i][i] = cosf(angle);
	return (n_mat4);
}

t_mat4	rotate(t_transform t)
{
	t_mat4	rotX_matrix;
	t_mat4	rotY_matrix;
	t_mat4	rotZ_matrix;

	rotX_matrix = rotate_axis(t, X_AXIS);
	rotY_matrix = rotate_axis(t, Y_AXIS);
	rotZ_matrix = rotate_axis(t, Z_AXIS);
	return (mul_mat4(rotX_matrix, mul_mat4(rotY_matrix, rotZ_matrix)));
}

t_mat4	get_model(t_transform t)
{
	t_mat4	pos_matrix;
	t_mat4	rot_matrix;
	t_mat4	scale_matrix;
	t_mat4	final_matrix;

	pos_matrix = translate(new_mat4(IDENTITY), t.position);
	rot_matrix = rotate(t);
	scale_matrix = scale(t);
	final_matrix = mul_mat4(pos_matrix, mul_mat4(rot_matrix, scale_matrix));
print_mat4(final_matrix);
	return (final_matrix);
}
