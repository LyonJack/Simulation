#pragma once
#include "EventBase.h"
#include "IEventAggregator.h"
#include "SynchronizationContext.h"
#include <map>
#include <mutex>
#include <string>

namespace events
{
    /**
     * @brief 事件聚合器
     *
     */
    class EventAggregator :public IEventAggregator
    {
    public:
        EventAggregator()
        {
            lpSyncContext = new SynchronizationContext();
        }

        // 通过 IEventAggregator 继承
        virtual void Clear() override;
    private:
        std::map<std::string, EventBase*> events;
        SynchronizationContext* lpSyncContext;
        std::mutex g_mutex;
        // 通过 IEventAggregator 继承
        virtual EventBase* _GetEvent(const char* typeName, std::function<EventBase* ()> createEB) override;
    };
}