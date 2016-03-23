void input_init() {
}

void input_update(SDL_Event event) {
}

const char *input_event_type_to_string(unsigned int type) {
	switch(type) {
		case SDL_KEYDOWN:
			return "keydown";
		case SDL_KEYUP:
			return "keyup";
		case SDL_MOUSEMOTION:
			return "mousemove";
		case SDL_MOUSEBUTTONUP:
			return "mouseup";
		case SDL_MOUSEBUTTONDOWN:
			return "mousedown";
	}
	return "none";
}