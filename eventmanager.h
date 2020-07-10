#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>

class Event;

class EventManager
{
public:
    EventManager();
    virtual ~EventManager();

    void produceEvent(unsigned int uEventID, int val);
    void produceEvent(unsigned int uEventID, float val);

protected:
    virtual void processEvent(Event *pEvent) = 0;
    virtual void destroyEvent(Event *pEvent) = 0;

private:
    std::thread *m_pEventConsumer;
    std::queue <Event*> m_queueEvent;
    std::condition_variable m_condConsumer;
    std::mutex m_mutex;
    bool m_bKeepThreadRunning;

    void runConsumer();
    void clearEventQueue();
};

#endif // EVENTMANAGER_H
