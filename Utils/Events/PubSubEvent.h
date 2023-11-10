#pragma once
#include "EventBase.h"
#include "EventSubscription.h"
#include "IEventSubscription.h"
#include "SubscriptionToken.h"
#include "BackgroundEventSubscription.h"
#include "ThreadOption.h"
#include <functional>

namespace events
{
    /**
     * @brief 发布订阅事件
     *
     * @tparam TPayload
     */
    template<class TPayload>
    class PubSubEvent :public EventBase
    {
    public:
        PubSubEvent() {};
        ~PubSubEvent() {};
        /**
         * @brief 订阅
         *
         * @param action 方法
         * @param threadOption 线程选项
         * @param keepSubscriberReferenceAlive 保持订阅引用有效
         * @param filter 筛选器
         * @return SubscriptionToken*
         */
        SubscriptionToken* Subscribe(std::function<void(TPayload)>& action, ThreadOption threadOption = PublisherThread, bool keepSubscriberReferenceAlive = false, std::function<bool(TPayload)> filter = nullptr)
        {
            IEventSubscription* eventSubscription = nullptr;
            switch (threadOption)
            {
            case BackgroundThread:
                eventSubscription = new BackgroundEventSubscription<TPayload>(action, filter);
                break;
            default:
                eventSubscription = new EventSubscription<TPayload>(action, filter);
                break;
            }
            return InternalSubscribe(eventSubscription);
        }
        /**
         * @brief 发布
         *
         * @param payload
         */
        void Publish(TPayload& payload)
        {
            InternalPublish((void*)&payload);
        }
        /**
         * @brief 取消订阅
         *
         * @param subscriber
         */
        virtual void Unsubscribe(std::function<void(TPayload)>& subscriber)
        {
            for (auto sub = Subscriptions.begin(); sub != Subscriptions.end();)
            {
                if (((EventSubscription<TPayload>*)sub->second)->IsAction(subscriber))
                {
                    Subscriptions.erase(sub++);
                }
                else
                {
                    sub++;
                }
            }
        }
    };
}