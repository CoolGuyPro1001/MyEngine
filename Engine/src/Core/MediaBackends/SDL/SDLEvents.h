#ifndef SDLEVENTS_H
#define SDLEVENTS_H

static std::vector<SDL_Event>& SDLEventList();

void UpdateSDLEventList();

std::vector<SDL_Event> RetrieveSDLEvents(uint event_type_from, uint event_type_to);








#endif
