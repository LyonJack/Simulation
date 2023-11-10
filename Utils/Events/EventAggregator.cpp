#include "EventAggregator.h"

namespace events
{
    EventBase* EventAggregator::_GetEvent(const char* typeName, std::function<EventBase* ()> createEB)
    {
        std::lock_guard<std::mutex> m(g_mutex);//互斥量包装程序
        EventBase* value = nullptr;
        if (events.find(typeName) == events.end())
        {
            value = createEB();
            value->lpSynchronizationContext = lpSyncContext;
            events[typeName] = value;
        }
        else
        {
            value = events[typeName];
        }
        return value;
    }
    void EventAggregator::Clear()
    {
        for (auto& _event : events)
        {
            _event.second->Clear();
        }
        events.clear();
    }
}
