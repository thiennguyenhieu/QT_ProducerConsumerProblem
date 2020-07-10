#include "domaineventmanager.h"
#include <QDebug>
#include "event.h"

DomainEventManager::DomainEventManager()
{
    qInfo() << "DomainEventManager is created";
}

DomainEventManager::~DomainEventManager()
{
    qInfo() << "DomainEventManager is destroyed";
}

void DomainEventManager::processEvent(Event *pEvent)
{
    if (pEvent == nullptr)
        return;

    qInfo() << "DomainEventManager is processing event " << pEvent->getEventID();
}

void DomainEventManager::destroyEvent(Event *pEvent)
{
    if (pEvent == nullptr)
        return;

    int *pIntData = nullptr;
    float *pFloatData = nullptr;

    switch (pEvent->getEventID())
    {
    case EVENT_DOMAIN_SELECT_PROGRAM:
        pIntData = static_cast<int*>(pEvent->getEventData());
        delete pIntData;
        break;

    case EVENT_DOMAIN_SET_OPT_VALUE:
        pFloatData = static_cast<float*>(pEvent->getEventData());
        delete pFloatData;
        break;

    default:
        break;
    }

    qInfo() << "DomainEventManager is destroying event " << pEvent->getEventID();

    delete pEvent;
}
