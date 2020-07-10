#ifndef DOMAINEVENTMANAGER_H
#define DOMAINEVENTMANAGER_H

#include "eventmanager.h"

class DomainEventManager  : public EventManager
{
public:
    enum ASYNC_DOMAIN_EVENT
    {
        EVENT_DOMAIN_SELECT_PROGRAM,
        EVENT_DOMAIN_SET_OPT_VALUE
    };

    DomainEventManager();
    virtual ~DomainEventManager();

protected:
    void processEvent(Event *pEvent) override;
    void destroyEvent(Event *pEvent) override;
};

#endif // DOMAINEVENTMANAGER_H
