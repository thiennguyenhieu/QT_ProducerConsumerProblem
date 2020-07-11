#include "guieventmanager.h"
#include "event.h"
#include "loguru.hpp"

GuiEventManager::GuiEventManager()
{
    LOG_F(INFO, "GuiEventManager is created");
}

GuiEventManager::~GuiEventManager()
{
    LOG_F(INFO, "GuiEventManager is destroyed");
}

void GuiEventManager::processEvent(Event *pEvent)
{
    if (pEvent == nullptr)
        return;

    LOG_F(INFO, "GuiEventManager is processing event %d", pEvent->getEventID());

    int *pIntData = nullptr;
    float *pFloatData = nullptr;

    switch (pEvent->getEventID())
    {
    case EVENT_GUI_SELECT_PROGRAM:
        pIntData = static_cast<int*>(pEvent->getEventData());
        LOG_F(INFO, "val %d", *pIntData);
        break;

    case EVENT_GUI_SET_OPT_VALUE:
        pFloatData = static_cast<float*>(pEvent->getEventData());
        LOG_F(INFO, "val %f", *pFloatData);
        break;

    default:
        break;
    }
}

void GuiEventManager::destroyEvent(Event *pEvent)
{
    if (pEvent == nullptr)
        return;

    int *pIntData = nullptr;
    float *pFloatData = nullptr;

    switch (pEvent->getEventID())
    {
    case EVENT_GUI_SELECT_PROGRAM:
        pIntData = static_cast<int*>(pEvent->getEventData());
        delete pIntData;
        break;

    case EVENT_GUI_SET_OPT_VALUE:
        pFloatData = static_cast<float*>(pEvent->getEventData());
        delete pFloatData;
        break;

    default:
        break;
    }

    LOG_F(INFO, "GuiEventManager is destroying event %d", pEvent->getEventID());

    delete pEvent;
}
