#include "eventmanager.h"
#include "event.h"
#include <QDebug>
#include <memory>

EventManager::EventManager()
    : m_bKeepThreadRunning(true)
{
    qInfo() << "EventManager is created";

    m_pEventConsumer = new std::thread(&EventManager::runConsumer, this);
}

EventManager::~EventManager()
{
    m_bKeepThreadRunning = false;

    if (m_pEventConsumer)
    {
        m_condConsumer.notify_one();
        m_pEventConsumer->join();
        delete m_pEventConsumer;
        m_pEventConsumer = nullptr;
    }

    clearEventQueue();

    qInfo() << "EventManager is destroyed";
}

void EventManager::runConsumer()
{
    qInfo() << "consumer is running ";

    while (true)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_queueEvent.empty())
        {
            qInfo() << "consumer is waiting";
            m_condConsumer.wait(lock);
        }

        if (!m_bKeepThreadRunning)
        {
            qInfo() << "consumer is exiting";
            return;
        }

        qInfo() << "consumer is resuming";
        Event *ptrEvent = m_queueEvent.front();

        m_queueEvent.pop();
        lock.unlock();

        if (ptrEvent)
        {
            qInfo() << "consumer is consuming event" << ptrEvent->getEventID();

            processEvent(ptrEvent);
            destroyEvent(ptrEvent);
        }
    }
}

void EventManager::clearEventQueue()
{
    qInfo() << "clearEventQueue " << m_queueEvent.size();

    while(!m_queueEvent.empty())
    {
        Event *ptrEvent = m_queueEvent.front();
        destroyEvent(ptrEvent);
        m_queueEvent.pop();
    }
}

void EventManager::produceEvent(unsigned int uEventID, int val)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        Event *pEvent = new Event();
        pEvent->setEventID(uEventID);
        pEvent->setEventData(new int(val));

        qInfo() << "addEvent " << pEvent->getEventID();
        m_queueEvent.push(pEvent);
    }
    m_condConsumer.notify_one();
}

void EventManager::produceEvent(unsigned int uEventID, float val)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        Event *pEvent = new Event();
        pEvent->setEventID(uEventID);
        pEvent->setEventData(new float(val));

        qInfo() << "addEvent " << pEvent->getEventID();
        m_queueEvent.push(pEvent);
    }
    m_condConsumer.notify_one();
}
