#include "parser.h"


int main(int argc, char **argv) {
	if (argc != 2)
		return (1);
	if (!parse_obj_file(argv[1]))
		return (1);
	return (0);
}

