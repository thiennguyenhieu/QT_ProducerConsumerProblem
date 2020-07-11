#include "domainaccess.h"
#include "event.h"
#include "loguru.hpp"
#include "domaineventmanager.h"

DomainAccess::DomainAccess()
{
    LOG_F(INFO, "DomainAccess is created");

    m_pDomainEventManager = new DomainEventManager();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    callbackTest(DomainEventManager::EVENT_DOMAIN_SELECT_PROGRAM, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    callbackTest(DomainEventManager::EVENT_DOMAIN_SET_OPT_VALUE, static_cast<float>(1.1));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    callbackTest(DomainEventManager::EVENT_DOMAIN_SELECT_PROGRAM, 2);
    callbackTest(DomainEventManager::EVENT_DOMAIN_SET_OPT_VALUE, static_cast<float>(1.2));
}

DomainAccess::~DomainAccess()
{
    LOG_F(INFO, "DomainAccess is destroyed");

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

