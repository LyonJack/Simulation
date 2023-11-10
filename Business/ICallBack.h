#pragma once

#include "Interface.h"

#define DEFINEBACK(type) virtual void on_##type(const type* info) = 0;

// �ص��ӿ�
class ICallBack
{
public:
    // HMI��Ӧ֡
    DEFINEBACK(st_core_frame_ackinfo)
    // ��̨��Ӧ֡
    DEFINEBACK(st_hmi_frame_ackinfo)
    // ������Ϣ֡���� 10Hz��Ƶ����
    DEFINEBACK(st_core_frame_navinfo)
    // �������֡���� 10Hz��Ƶ����
    DEFINEBACK(st_core_frame_naverro)
    // �켣��Ϣ֡���� 10Hz��Ƶ����
    DEFINEBACK(st_core_frame_trjinfo)
    // ���Դ�������Ϣ֡���� 10Hz��Ƶ����
    DEFINEBACK(st_core_frame_inerinfo)
    // ��׼Դ������ֵ 10Hz��Ƶ����
    DEFINEBACK(st_core_frame_baseinfo)
    // У׼��Ϣ֡ 10Hz��Ƶ����
    DEFINEBACK(st_core_frame_corrinfo)
    // ����������Ϣ  1Hz��Ƶ����
    DEFINEBACK(st_core_frame_assessinfo)
    // �豸״̬��Ϣ  1Hz��Ƶ����
    DEFINEBACK(st_core_frame_deviceinfo)
    // ����״̬��Ϣ 1Hz��Ƶ����
    DEFINEBACK(st_core_frame_sysinfo)
    // ϵͳ����
    DEFINEBACK(st_hmi_frame_syspara)
    // ���Դ�����������Բ���
    DEFINEBACK(st_hmi_frame_inerpara)
    // ��׼Դ������������Բ���
    DEFINEBACK(st_hmi_frame_basepara)
    // ʱͳ����
    DEFINEBACK(st_hmi_frame_syncpara)
};
