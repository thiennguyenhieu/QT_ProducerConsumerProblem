#include "domainaccess.h"
#include "event.h"
#include <QDebug>
#include "domaineventmanager.h"

DomainAccess::DomainAccess()
{
    qInfo() << "DomainAccess is created";

    m_pDomainEventManager = new DomainEventManager();

    /*std::this_thread::sleep_for(std::chrono::milliseconds(1));
    callbackTest(DomainEventManager::EVENT_DOMAIN_SELECT_PROGRAM, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    callbackTest(DomainEventManager::EVENT_DOMAIN_SET_OPT_VALUE, (float)1.1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    callbackTest(DomainEventManager::EVENT_DOMAIN_SELECT_PROGRAM, 2);
    callbackTest(DomainEventManager::EVENT_DOMAIN_SET_OPT_VALUE, (float)1.2);*/
}

DomainAccess::~DomainAccess()
{
    qInfo() << "DomainAccess is destroyed";

    if (m_pDomainEventManager)
    {
        delete m_pDomainEventManager;
        m_pDomainEventManager = nullptr;
    }
}

void DomainAccess::callbackTest(int nEventID, int val)
{
    if (m_pDomainEventManager == nullptr)
        return;

    m_pDomainEventManager->produceEvent(nEventID, val);
}

void DomainAccess::callbackTest(int nEventID, float val)
{
    if (m_pDomainEventManager == nullptr)
        return;

    m_pDomainEventManager->produceEvent(nEventID, val);
}

