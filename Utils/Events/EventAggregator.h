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
     * @brief �¼��ۺ���
     *
     */
    class EventAggregator :public IEventAggregator
    {
    public:
        EventAggregator()
        {
            lpSyncContext = new SynchronizationContext();
        }

        // ͨ�� IEventAggregator �̳�
        virtual void Clear() override;
    private:
        std::map<std::string, EventBase*> events;
        SynchronizationContext* lpSyncContext;
        std::mutex g_mutex;
        // ͨ�� IEventAggregator �̳�
        virtual EventBase* _GetEvent(const char* typeName, std::function<EventBase* ()> createEB) override;
    };
}