#pragma once

#include "Interface.h"

#define DEFINEBACK(type) virtual void on_##type(const type* info) = 0;

// 回调接口
class ICallBack
{
public:
    // HMI响应帧
    DEFINEBACK(st_core_frame_ackinfo)
    // 后台响应帧
    DEFINEBACK(st_hmi_frame_ackinfo)
    // 导航信息帧定义 10Hz定频发送
    DEFINEBACK(st_core_frame_navinfo)
    // 导航误差帧定义 10Hz定频发送
    DEFINEBACK(st_core_frame_naverro)
    // 轨迹信息帧定义 10Hz定频发送
    DEFINEBACK(st_core_frame_trjinfo)
    // 惯性传感器信息帧定义 10Hz定频发送
    DEFINEBACK(st_core_frame_inerinfo)
    // 基准源传感器值 10Hz定频发送
    DEFINEBACK(st_core_frame_baseinfo)
    // 校准信息帧 10Hz定频发送
    DEFINEBACK(st_core_frame_corrinfo)
    // 精度评定信息  1Hz定频发送
    DEFINEBACK(st_core_frame_assessinfo)
    // 设备状态信息  1Hz定频发送
    DEFINEBACK(st_core_frame_deviceinfo)
    // 仿真状态信息 1Hz定频发送
    DEFINEBACK(st_core_frame_sysinfo)
    // 系统参数
    DEFINEBACK(st_hmi_frame_syspara)
    // 惯性传感器误差特性参数
    DEFINEBACK(st_hmi_frame_inerpara)
    // 基准源传感器误差特性参数
    DEFINEBACK(st_hmi_frame_basepara)
    // 时统参数
    DEFINEBACK(st_hmi_frame_syncpara)
};
