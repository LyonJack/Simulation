#pragma once
#include "IEventSubscription.h"
#include "SynchronizationContext.h"
#include <vector>
#include <map>
#include <mutex>

namespace events
{
    /**
     * @brief 事件基础
     * 
     */
    class EventBase
    {
    public:
        SynchronizationContext* lpSynchronizationContext;
        /**
         * @brief 取消订阅
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
         * @brief 是否包含
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
         * @brief 清空
         * 
         */
        void Clear()
        {
            Subscriptions.clear();
        }

    protected:
        std::map<SubscriptionToken*, IEventSubscription*> Subscriptions;

        /**
         * @brief 内部订阅
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
         * @brief 内部发布
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
         * @brief 修剪
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
         * @brief 修剪和退货策略
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