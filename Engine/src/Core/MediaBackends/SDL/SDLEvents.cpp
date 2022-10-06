#include "SDLEvents.h"

std::vector<SDL_Event>& SDLEventList()
{
    static std::vector<SDL_Event> event_list;
    event_list.reserve(20);
    return event_list;
}

void UpdateSDLEventList()
{
    std::vector<SDL_Event>& event_list = SDLEventList();
    event_list.clear();

    while(SDL_PollEvent(&event_list.emplace_back()))

    //Sort Events By Type (Which Is An Enum)
    std::sort(event_list.begin(), event_list.end(), [](SDL_Event a, SDL_Event b)
    {
        return a.type < b.type;
    });
}

std::vector<SDL_Event> RetrieveSDLEvents(uint event_type_from, uint event_type_to)
{
    std::vector<SDL_Event>& event_list = SDLEventList();

    auto begin_it = std::lower_bound(event_list.begin(), event_list.end(), event_type_from, [](SDL_Event a, uint value)
    {
        return a.type < value;
    });

    auto end_it = std::upper_bound(event_list.begin(), event_list.end(), event_type_to, [](uint value, SDL_Event a)
    {
        return a.type > value;
    });

    std::vector<SDL_Event> event_group(begin_it, end_it);
    return event_group;
}
