#include "guieventmanager.h"
#include "event.h"
#include <QDebug>

GuiEventManager::GuiEventManager()
{
    qInfo() << "GuiEventManager is created";
}

GuiEventManager::~GuiEventManager()
{
    qInfo() << "GuiEventManager is destroyed";
}

void GuiEventManager::processEvent(Event *pEvent)
{
    if (pEvent == nullptr)
        return;

    qInfo() << "GuiEventManager is processing event " << pEvent->getEventID();

    int *pIntData = nullptr;
    float *pFloatData = nullptr;

    switch (pEvent->getEventID())
    {
    case EVENT_GUI_SELECT_PROGRAM:
        pIntData = static_cast<int*>(pEvent->getEventData());
        qInfo() << "val " << *pIntData;
        break;

    case EVENT_GUI_SET_OPT_VALUE:
        pFloatData = static_cast<float*>(pEvent->getEventData());
        qInfo() << "val " << *pFloatData;
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

    qInfo() << "GuiEventManager is destroying event " << pEvent->getEventID();

    delete pEvent;
}
