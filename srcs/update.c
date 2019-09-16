#include "monitor.h"

uint8_t	update_monitor(t_monitor monitor)
{
	SDL_Event	e;

	SDL_GL_SwapWindow(monitor.win);
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT)
			return (1);
	return (0);
}
