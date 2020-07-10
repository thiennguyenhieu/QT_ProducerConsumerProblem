#ifndef GUIEVENTMANAGER_H
#define GUIEVENTMANAGER_H

#include "eventmanager.h"

class GuiEventManager : public EventManager
{
public:
    enum ASYNC_GUI_EVENT
    {
        EVENT_GUI_SELECT_PROGRAM,
        EVENT_GUI_SET_OPT_VALUE
    };

    GuiEventManager();
    virtual ~GuiEventManager();

protected:
    void processEvent(Event *pEvent) override;
    void destroyEvent(Event *pEvent) override;
};

#endif // GUIEVENTMANAGER_H
