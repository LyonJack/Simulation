#pragma once
#include "IEventSubscription.h"
#include "SynchronizationContext.h"
#include <vector>
#include <map>
#include <mutex>

namespace events
{
    /**
     * @brief �¼�����
     * 
     */
    class EventBase
    {
    public:
        SynchronizationContext* lpSynchronizationContext;
        /**
         * @brief ȡ������
         * 
         * @param token 
         */
        virtual void Unsubscribe(SubscriptionToken* token)
        {
            std::lock_guard<std::mutex> m(g_mutex);
            if (Subscriptions.find(token) != Subscriptions.end())
            {
                Subscriptions.erase(token);
            }
        }
        /**
         * @brief �Ƿ����
         * 
         * @param token 
         * @return true 
         * @return false 
         */
        virtual bool Contains(SubscriptionToken* token)
        {
            return Subscriptions.find(token) != Subscriptions.end();
        }
        /**
         * @brief ���
         * 
         */
        void Clear()
        {
            Subscriptions.clear();
        }

    protected:
        std::map<SubscriptionToken*, IEventSubscription*> Subscriptions;

        /**
         * @brief �ڲ�����
         * 
         * @param eventSubscription 
         * @return SubscriptionToken* 
         */
        virtual SubscriptionToken* InternalSubscribe(IEventSubscription* eventSubscription)
        {
            if (eventSubscription == nullptr)
            {
                return nullptr;
            }
            eventSubscription->subscriptionToken = new SubscriptionToken([&](SubscriptionToken* token) {Unsubscribe(token); });
            std::lock_guard<std::mutex> m(g_mutex);
            Prune();
            Subscriptions.insert(std::make_pair(eventSubscription->subscriptionToken, eventSubscription));

            return eventSubscription->subscriptionToken;
        }
        /**
         * @brief �ڲ�����
         * 
         * @param arguments 
         */
        virtual void InternalPublish(void* arguments)
        {
            auto actions = PruneAndReturnStrategies();
            for (auto& action : actions)
            {
                action(arguments);
            }
        }
    private:
        std::mutex g_mutex;
        /**
         * @brief �޼�
         * 
         */
        void Prune()
        {
            for (auto& subscription : Subscriptions)
            {
                if (subscription.second->IsActionNull())
                {
                    Subscriptions.erase(subscription.first);
                }
            }
        }
        /**
         * @brief �޼����˻�����
         * 
         * @return std::vector<std::function<void(void*)>> 
         */
        std::vector<std::function<void(void*)>> PruneAndReturnStrategies()
        {
            std::lock_guard<std::mutex> m(g_mutex);
            Prune();
            std::vector<std::function<void(void*)>> vct;
            for (auto& sub : Subscriptions)
            {
                vct.push_back(sub.second->GetExecutionStrategy());
            }
            return vct;
        }
    };
}