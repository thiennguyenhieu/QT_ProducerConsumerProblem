#ifndef EVENT_H
#define EVENT_H

class Event
{
public:
    Event() {}
    virtual ~Event() {}

    void setEventID(int eventID)
    {
        m_nEventID = eventID;
    }

    int getEventID()
    {
        return m_nEventID;
    }

    void setEventData(void *pdata)
    {
        m_pData = pdata;
    }

    void* getEventData()
    {
        return m_pData;
    }

private:
    int m_nEventID;
    void *m_pData;

};

#endif // EVENT_H
