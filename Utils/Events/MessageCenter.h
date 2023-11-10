#pragma once
#include "EventAggregator.h"
#include "PubSubEvent.h"
#include "ThreadOption.h"
#include <functional>

namespace events
{
    class MessageCenter
    {
    public:
        /**
         * @brief 订阅消息
         *
         * @tparam T
         * @param action 方法
         * @param threadOption 线程选项
         */
        template <class T>
        static void SubMsg(std::function<void(T)>& action, ThreadOption threadOption = ThreadOption::PublisherThread)
        {
            PubSubEvent<T>* lpEvent = eventAggregator->GetEvent<PubSubEvent<T>>();
            lpEvent->Subscribe(action, threadOption);
        }
        /**
         * @brief 发布消息
         *
         * @tparam T
         * @param msg 消息
         */
        template <class T>
        static void PubMsg(T msg)
        {
            PubSubEvent<T>* lpEvent = eventAggregator->GetEvent<PubSubEvent<T>>();
            lpEvent->Publish(msg);
        }
        /**
         * @brief 取消订阅
         *
         * @tparam T
         * @param action 方法
         */
        template <class T>
        static void UnSub(std::function<void(T)>& action)
        {
            PubSubEvent<T>* lpEvent = eventAggregator->GetEvent<PubSubEvent<T>>();
            lpEvent->Unsubscribe(action);
        }
        /**
         * @brief 清空
         *
         */
        static void Clear()
        {
            eventAggregator->Clear();
        }

    private:
        static EventAggregator* eventAggregator;
    };
}