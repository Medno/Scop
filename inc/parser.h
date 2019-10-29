#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "vec3.h"
# include "read_file.h"
# include "errno.h"
# include <string.h>

enum	e_face_type
{
	V_1,
	V_2,
	V_3
};

typedef struct	s_parse_obj
{
	t_vec3				*vertices;
	t_vec3				*vertices_normal;
	t_vec3				*vertices_texture;
	int					*indices;
	enum e_face_type	face_type;
	size_t				len_vertices;
	size_t				len_vertices_normal;
	size_t				len_vertices_texture;
	size_t				len_faces;
	size_t				index_vertices;
	size_t				index_vertices_normal;
	size_t				index_vertices_texture;
}				t_parse_obj;

enum	e_token_obj
{
	VERTEX,
	TEXTURE,
	N_VERTEX,
	FACES,
	NAME,
	GROUP,
	MATERIAL,
	COMMENT
};

uint8_t	check_float(const char *str, float *fl);

#endif
