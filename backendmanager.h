#ifndef BACKENDMANAGER_H
#define BACKENDMANAGER_H

#include <QObject>

class GuiEventManager;
class DomainAccess;

class BackendManager : public QObject
{
public:
    BackendManager();
    virtual ~BackendManager();

private:
    GuiEventManager *m_pGuiEventManager;
    DomainAccess *m_pDomainAccess;

    void actionTest(int nEventID, int val);
    void actionTest(int nEventID, float val);
};

#endif // BACKENDMANAGER_H
