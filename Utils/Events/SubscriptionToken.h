#pragma once
#include "SubscriptionToken.h"
#include <functional>
#include "MessageId.h"

namespace events
{
    /**
     * @brief 订阅令牌
     *
     */
    class SubscriptionToken
    {
    public:
        SubscriptionToken();
        SubscriptionToken(std::function<void(SubscriptionToken*)> unsubscribeAction);
        ~SubscriptionToken();

    private:
        std::function<void(SubscriptionToken*)> _unsubscribeAction;
        MessageId _message_id;
    };
}