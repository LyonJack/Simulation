#pragma once
#include "EventAggregator.h"
#include "PubSubEvent.h"
#include "ThreadOption.h"
#include <functional>

namespace events
{
    class MessageCenter
    {
    public:
        /**
         * @brief ������Ϣ
         *
         * @tparam T
         * @param action ����
         * @param threadOption �߳�ѡ��
         */
        template <class T>
        static void SubMsg(std::function<void(T)>& action, ThreadOption threadOption = ThreadOption::PublisherThread)
        {
            PubSubEvent<T>* lpEvent = eventAggregator->GetEvent<PubSubEvent<T>>();
            lpEvent->Subscribe(action, threadOption);
        }
        /**
         * @brief ������Ϣ
         *
         * @tparam T
         * @param msg ��Ϣ
         */
        template <class T>
        static void PubMsg(T msg)
        {
            PubSubEvent<T>* lpEvent = eventAggregator->GetEvent<PubSubEvent<T>>();
            lpEvent->Publish(msg);
        }
        /**
         * @brief ȡ������
         *
         * @tparam T
         * @param action ����
         */
        template <class T>
        static void UnSub(std::function<void(T)>& action)
        {
            PubSubEvent<T>* lpEvent = eventAggregator->GetEvent<PubSubEvent<T>>();
            lpEvent->Unsubscribe(action);
        }
        /**
         * @brief ���
         *
         */
        static void Clear()
        {
            eventAggregator->Clear();
        }

    private:
        static EventAggregator* eventAggregator;
    };
}