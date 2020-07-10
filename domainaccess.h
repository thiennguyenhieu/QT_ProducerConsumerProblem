#ifndef DOMAINACCESS_H
#define DOMAINACCESS_H

#include "eventmanager.h"

class DomainEventManager;

class DomainAccess
{
public:
    DomainAccess();
    virtual ~DomainAccess();

private:
    DomainEventManager *m_pDomainEventManager;

    void callbackTest(int nEventID, int val);
    void callbackTest(int nEventID, float val);
};

#endif // DOMAINACCESS_H
