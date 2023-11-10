#pragma once
#include "SubscriptionToken.h"
#include <functional>
#include <vector>

namespace events
{
    class IEventSubscription
    {
    public:
        /**
         * @brief 订阅令牌
         *
         */
        SubscriptionToken* subscriptionToken = nullptr;
        /**
         * @brief 获取执行策略
         *
         * @return std::function<void(std::vector<void*>)>
         */
        virtual std::function<void(void*)> GetExecutionStrategy() = 0;
        /**
         * @brief 是否委托为空
         * 
         * @return true 
         * @return false 
         */
        virtual bool IsActionNull() = 0;
    };
}