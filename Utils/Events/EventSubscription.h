#pragma once
#include "func_compare.h"
#include "IEventSubscription.h"
#include <functional>

namespace events
{
    /**
     * @brief �¼�����
     * 
     * @tparam TPayload 
     */
    template<class TPayload>
    class EventSubscription :public IEventSubscription
    {
    public:
        EventSubscription(std::function<void(TPayload)>& action, std::function<bool(TPayload)> filter);
        ~EventSubscription();

        virtual void InvokeAction(std::function<void(TPayload)>* action, TPayload& argument)
        {
            if (action)
            {
                (*action)(argument);
            }
        }
        /**
         * @brief �Ƿ���ͬί��
         * 
         * @param _action 
         * @return true 
         * @return false 
         */
        virtual bool IsAction(std::function<void(TPayload)>& _action)
        {
            return is_std_func_equal(*action, _action);
        }
    protected:
        std::function<void(TPayload)>* action = nullptr;
        std::function<bool(TPayload)> filter = nullptr;

        // ͨ�� IEventSubscription �̳�
        virtual std::function<void(void*)> GetExecutionStrategy() override
        {
            if (action)
            {
                return [=](void* arg)
                {
                    TPayload _arg = *(TPayload*)(char*)arg;
                    if (filter == nullptr || filter(_arg))
                    {
                        InvokeAction(action, _arg);
                    }
                };
            }
            return nullptr;
        }

        // ͨ�� IEventSubscription �̳�
        virtual bool IsActionNull() override
        {
            return action == nullptr;
        }
    };
    template<class TPayload>
    inline EventSubscription<TPayload>::EventSubscription(std::function<void(TPayload)>& _action, std::function<bool(TPayload)> _filter)
    {
        action = &_action;
        filter = _filter;
    }
    template<class TPayload>
    inline EventSubscription<TPayload>::~EventSubscription()
    {
    }
}