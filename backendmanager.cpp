#include "backendmanager.h"
#include <QDebug>
#include "guieventmanager.h"
#include "event.h"
#include "domainaccess.h"

BackendManager::BackendManager()
{
    qInfo() << "BackendManager is created";
    m_pGuiEventManager = new GuiEventManager();
    m_pDomainAccess = new DomainAccess();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    actionTest(GuiEventManager::EVENT_GUI_SELECT_PROGRAM, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    actionTest(GuiEventManager::EVENT_GUI_SET_OPT_VALUE, (float)1.1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    actionTest(GuiEventManager::EVENT_GUI_SELECT_PROGRAM, 2);
    actionTest(GuiEventManager::EVENT_GUI_SET_OPT_VALUE, (float)1.2);
}

BackendManager::~BackendManager()
{
    qInfo() << "BackendManager is destroyed";

    if (m_pGuiEventManager)
    {
        delete m_pGuiEventManager;
        m_pGuiEventManager = nullptr;
    }

    if (m_pDomainAccess)
    {
        delete m_pDomainAccess;
        m_pDomainAccess = nullptr;
    }
}

void BackendManager::actionTest(int nEventID, int val)
{
    if (m_pGuiEventManager == nullptr)
        return;

    m_pGuiEventManager->produceEvent(nEventID, val);
}

void BackendManager::actionTest(int nEventID, float val)
{
    if (m_pGuiEventManager == nullptr)
        return;

    m_pGuiEventManager->produceEvent(nEventID, val);
}
