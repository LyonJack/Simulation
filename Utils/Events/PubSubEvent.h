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
     * @brief ���������¼�
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
         * @brief ����
         *
         * @param action ����
         * @param threadOption �߳�ѡ��
         * @param keepSubscriberReferenceAlive ���ֶ���������Ч
         * @param filter ɸѡ��
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
         * @brief ����
         *
         * @param payload
         */
        void Publish(TPayload& payload)
        {
            InternalPublish((void*)&payload);
        }
        /**
         * @brief ȡ������
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