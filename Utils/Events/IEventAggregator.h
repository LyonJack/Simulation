#pragma once
#include <typeinfo>
#include <functional>
#include "EventBase.h"

namespace events
{
    /**
     * @brief �¼��ۺ����ӿ�
     *
     */
    class IEventAggregator
    {
    protected:
        /**
         * @brief ��ȡ�¼�
         *
         * @param typeName
         * @return void*
         */
        virtual EventBase* _GetEvent(const char* typeName, std::function<EventBase* ()> createEB) = 0;
    public:
        /**
         * @brief ��ȡ�¼�
         *
         * @tparam TEventType �¼�����
         * @return TEventType* �¼�ָ��
         */
        template<class TEventType>
        TEventType* GetEvent()
        {
            return (TEventType*)_GetEvent(typeid(TEventType).name(), [&]() { return new TEventType(); });
        }
        /**
         * @brief ���
         */
        virtual void Clear() = 0;
    };
}