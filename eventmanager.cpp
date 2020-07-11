#include "eventmanager.h"
#include "event.h"
#include "loguru.hpp"
#include <memory>

EventManager::EventManager()
    : m_bKeepThreadRunning(true)
{
    LOG_F(INFO, "EventManager is created");

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

    LOG_F(INFO, "EventManager is destroyed");
}

void EventManager::runConsumer()
{
    LOG_F(INFO, "consumer is running");

    while (true)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_queueEvent.empty())
        {
            LOG_F(INFO, "consumer is waiting");
            m_condConsumer.wait(lock);
        }

        if (!m_bKeepThreadRunning)
        {
            LOG_F(INFO, "consumer is exiting");
            return;
        }

        LOG_F(INFO, "consumer is resuming");
        Event *ptrEvent = m_queueEvent.front();

        m_queueEvent.pop();
        lock.unlock();

        if (ptrEvent)
        {
            LOG_F(INFO, "consumer is consuming event %d", ptrEvent->getEventID());

            processEvent(ptrEvent);
            destroyEvent(ptrEvent);
        }
    }
}

void EventManager::clearEventQueue()
{
    LOG_F(INFO, "clearEventQueue %d", m_queueEvent.size());

    while(!m_queueEvent.empty())
    {
        Event *ptrEvent = m_queueEvent.front();
        destroyEvent(ptrEvent);
        m_queueEvent.pop();
    }
}

void EventManager::produceEvent(int uEventID, int val)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        Event *pEvent = new Event();
        pEvent->setEventID(uEventID);
        pEvent->setEventData(new int(val));

        LOG_F(INFO, "addEvent %d", pEvent->getEventID());
        m_queueEvent.push(pEvent);
    }
    m_condConsumer.notify_one();
}

void EventManager::produceEvent(int uEventID, float val)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        Event *pEvent = new Event();
        pEvent->setEventID(uEventID);
        pEvent->setEventData(new float(val));

        LOG_F(INFO, "addEvent %d", pEvent->getEventID());
        m_queueEvent.push(pEvent);
    }
    m_condConsumer.notify_one();
}
