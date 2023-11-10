#pragma once
#include "EventSubscription.h"
#include "pool.h"

namespace events
{
    /**
     * @brief 后台事件订阅
     * 
     * @tparam TPayload 
     */
    template<class TPayload>
    class BackgroundEventSubscription :public EventSubscription<TPayload>
    {
    public:
        BackgroundEventSubscription(std::function<void(TPayload)>& action, std::function<bool(TPayload)> filter);
        ~BackgroundEventSubscription();
        virtual void InvokeAction(std::function<void(TPayload)>* action, TPayload& argument) override
        {
            if (action)
            {
                pool::getInstance()->commit(*action, argument);
            }
        }
    private:
    };
    template<class TPayload>
    inline BackgroundEventSubscription<TPayload>::BackgroundEventSubscription(std::function<void(TPayload)>& action, std::function<bool(TPayload)> filter) :EventSubscription<TPayload>(action, filter) {}
    template<class TPayload>
    inline BackgroundEventSubscription<TPayload>::~BackgroundEventSubscription()
    {
    }
}