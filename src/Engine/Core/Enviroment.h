#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include "../../Editor/QT/mainwindow.h"

namespace Engine
{
    void Tick(std::vector<std::function<void()>>& tick_functions);

    template<class TickerType>
    void AddTickFunction(std::vector<std::function<void()>>& tick_functions, TickerType& ticker, std::function<void()> tick_function)
    {
        tick_functions.push_back(std::bind(&TickerType::tick_function, &ticker));
    };
}
#endif