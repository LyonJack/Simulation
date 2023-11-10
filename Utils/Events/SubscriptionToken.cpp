#include "SubscriptionToken.h"

namespace events
{
    SubscriptionToken::SubscriptionToken()
    {
    }

    SubscriptionToken::SubscriptionToken(std::function<void(SubscriptionToken*)> unsubscribeAction)
    {
        _unsubscribeAction = unsubscribeAction;
    }

    SubscriptionToken::~SubscriptionToken()
    {
    }
}