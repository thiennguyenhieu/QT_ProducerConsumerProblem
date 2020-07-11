#include "domaineventmanager.h"
#include "loguru.hpp"
#include "event.h"

DomainEventManager::DomainEventManager()
{
    LOG_F(INFO, "DomainEventManager is created");
}

DomainEventManager::~DomainEventManager()
{
    LOG_F(INFO, "DomainEventManager is destroyed");
}

void DomainEventManager::processEvent(Event *pEvent)
{
    if (pEvent == nullptr)
        return;

    LOG_F(INFO, "DomainEventManager is processing event %d", pEvent->getEventID());
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

    LOG_F(INFO, "DomainEventManager is destroying event %d", pEvent->getEventID());

    delete pEvent;
}
