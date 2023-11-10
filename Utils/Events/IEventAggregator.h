#pragma once
#include <typeinfo>
#include <functional>
#include "EventBase.h"

namespace events
{
    /**
     * @brief 事件聚合器接口
     *
     */
    class IEventAggregator
    {
    protected:
        /**
         * @brief 获取事件
         *
         * @param typeName
         * @return void*
         */
        virtual EventBase* _GetEvent(const char* typeName, std::function<EventBase* ()> createEB) = 0;
    public:
        /**
         * @brief 获取事件
         *
         * @tparam TEventType 事件类型
         * @return TEventType* 事件指针
         */
        template<class TEventType>
        TEventType* GetEvent()
        {
            return (TEventType*)_GetEvent(typeid(TEventType).name(), [&]() { return new TEventType(); });
        }
        /**
         * @brief 清空
         */
        virtual void Clear() = 0;
    };
}