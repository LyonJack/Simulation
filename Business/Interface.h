#ifndef INTERFACE_DEF_H
#define INTERFACE_DEF_H

#include <stdint.h>
#include <vector>

#pragma pack(1)

#define INTERFACE_VERSION	"1.1"
#define INTERFACE_PORT		(20000)

// 帧格式：帧头1(uint8_t), 定义见@e_nav_frame_info
//		  帧头2(uint8_t), 定义见@e_nav_frame_info
//		  帧类型(uint8_t), 定义见@e_nav_frame_core_type, @e_nav_frame_hmi_type
//		  帧来源(uint8_t), 定义详见@e_nav_frame_source
//		  帧数据长度(uint16_t)
//		  帧内容(详见结构体定义)
//		  校验(uint8_t) 帧类型到帧内容之间的所有字节的异或和
//	      帧尾(uint8_t), 定义见@e_nav_frame_info


// 帧信息
enum e_nav_frame_info
{
    NFH_HEAD1 = 0xA5,								// 帧头1
    NFH_HEAD2 = 0x5A,								// 帧头2
    NFH_TAIL = 0xED,								// 帧尾
};

// 帧来源
enum e_nav_frame_source
{
    NFS_CORE,										// 后台仿真核心
    NFS_HMI,										// HMI展示软件
};

// 导航仿真后台发送帧类型
enum e_nav_frame_core_type
{
    NFCT_INVALID,									// 无效
    NFCT_HMI_ACK,									// HMI响应帧, 收到HMI帧后立即发送, 定义见 @st_core_frame_ackinfo
    NFCT_NAV_INFO,									// 导航信息, 定义见 @st_core_frame_navinfo
    NFCT_NAV_ERROR,									// 导航误差信息, 定义见 @st_core_frame_naverro
    NFCT_TRJ_INFO,									// 轨迹信息, 定义见 @st_core_frame_trjinfo
    NFCT_INER_INFO,									// 惯性传感器信息, 定义见 @st_core_frame_inerinfo
    NFCT_BASE_INFO,									// 基准源传感器信息, 定义见 @st_core_frame_baseinfo
    NFCT_CORR_INFO,									// 校准信息, 定义见 @st_core_frame_corrinfo
    NFCT_ASSE_INFO,									// 精度评定信息, 定义见 @st_core_frame_assessinfo
    NFCT_DEV_STATUS,								// 设备状态信息, 定义见 @st_core_frame_deviceinfo
    NFCT_SYS_STATUS,								// 仿真状态信息, 定义见 @st_core_frame_sysinfo
};

// 导航展示软件发送帧类型
enum e_nav_frame_hmi_type
{
    NFHT_INVALID,									// 无效
    NFHT_NAV_ACK,									// 后台响应帧, 收到仿真后台帧后立即发送, 定义见 @st_hmi_frame_ackinfo
    NFHT_INI_PARA,									// 初始参数, 定义见 @st_hmi_frame_inipara
    NFHT_SYS_PARA,									// 系统参数, 定义见 @st_hmi_frame_syspara
    HFHT_INER_PARA,									// 惯性传感器参数, 定义见 @st_hmi_frame_inerpara
    NFHT_BASE_PRRA,									// 基准源传感器参数, 定义见 @st_hmi_frame_basepara
    HFHT_SYNC_PARA,									// 时统参数, 定义见 @st_hmi_frame_syncpara
    HFHT_FLOW_PARA,									// 流程参数, 定义见 @st_hmi_frame_flowpara
    HFHT_TRJ_PARA,									// 轨迹参数, 定义见 @st_hmi_frame_trjpara
    HFHT_ASSE_PARA,									// 导航精度评定参数, 定义见 @st_hmi_frame_assprara
    HFHT_COMMAND,									// 仿真命令, 定义见 @st_hmi_frame_command
};

// 帧响应状态
enum e_ack_status
{
    ACKS_OK,										// 正常
    ACKS_ERR_DATA,									// 数据错误
};

// HMI响应帧
struct st_core_frame_ackinfo
{
    uint64_t timestamp;								// 系统时间(ms)
    e_nav_frame_hmi_type type;						// 接收到的HMI帧类型
    e_ack_status status;							// 响应状态
};

//后台响应帧
struct st_hmi_frame_ackinfo
{
    uint64_t timestamp;								// 系统时间(ms)
    e_nav_frame_hmi_type type;						// 接收到的后台帧类型
    e_ack_status status;							// 响应状态
};

// 设备类型
enum e_dev_type
{
    DT_INVALID,										// 无效设备
    DT_I,											// Ⅰ型设备
    DT_II,											// Ⅱ型设备
    DT_III,											// Ⅲ型设备
    DT_IV,											// Ⅳ型设备
};

// 导航状态
enum e_nav_status
{
    NS_INVALID,										// 无效
    NS_READY,										// 待机状态
    NS_ALN_CORASE,									// 粗对准状态
    NS_ALN_PORT,									// 静基座精对准
    NS_ALN_SEA,										// 动基座精对准
    NS_NAV_NODAMP,									// 纯惯性导航状态
    NS_NAV_LEVELDAMP,								// 水平阻尼导航状态
    NS_INTEGATION,									// 组合状态
    NS_CORRECTION,									// 校准状态
};

struct st_device
{
    e_dev_type type;								// 设备类型,定义见 @e_dev_type
    uint32_t number;								// 设备编号
};

// 导航信息帧定义 10Hz定频发送
struct st_core_frame_navinfo
{
    st_device device;								// 设备类型,定义见 @st_device
    uint64_t timestamp;								// 系统时间(ms)
    uint64_t timestamp_sync;						// 同步时间(ms)
    uint64_t timestamp_status;						// 当前系统时间(ms)
    e_nav_status status;							// 导航状态,定义见 @e_nav_status
    double latitude;								// 纬度(deg)
    double longitude;								// 经度(deg)
    double altitude;								// 海拔(m)
    double velocity_east;							// 东向速度(kn)
    double velocity_north;							// 北向速度(kn)
    double velocity_upper;							// 垂向速度(kn)
    double velocity;								// 合速度(kn)
    double roll;									// 横摇角(deg)
    double pitch;									// 俯仰角(deg)
    double heading;									// 航向角(deg)
    double roll_rate;								// 横摇角速度(deg/s)
    double pitch_rate;								// 俯仰角速度(deg/s)
    double heading_rate;							// 航向角速度(deg/s)
    double heave;									// 升沉位移(m)
};

// 导航误差帧定义 10Hz定频发送
struct st_core_frame_naverro
{
    st_device device;								// 设备类型,定义见 @st_device
    uint64_t timestamp;								// 系统时间(ms)
    uint64_t timestamp_sync;						// 同步时间(ms)
    e_nav_status status;							// 导航状态,定义见 @e_nav_status
    double e_latitude;								// 纬度(deg)
    double e_longitude;								// 经度(deg)
    double e_altitude;								// 海拔(m)
    double e_velocity_east;							// 东向速度(kn)
    double e_velocity_north;						// 北向速度(kn)
    double e_velocity_upper;						// 垂向速度(kn)
    double e_roll;									// 横摇角(deg)
    double e_pitch;									// 俯仰角(deg)
    double e_heading;								// 航向角(deg)
};

// 轨迹信息帧定义 10Hz定频发送
struct st_core_frame_trjinfo
{
    st_device device;								// 设备类型,定义见 @st_device
    uint64_t timestamp;								// 系统时间(ms)
    uint64_t timestamp_sync;						// 同步时间(ms)
    uint32_t seg_all;								// 段数量
    uint32_t seg_cur;								// 当前段序号
    uint32_t time_seg_cur;							// 当前段运行时间
    uint32_t time_seg;								// 当前段总时间
    uint64_t time_total;							// 总时间
    double latitude;								// 纬度(deg)
    double longitude;								// 经度(deg)
    double altitude;								// 海拔(m)
    double velocity_east;							// 东向速度(kn)
    double velocity_north;							// 北向速度(kn)
    double velocity_upper;							// 垂向速度(kn)
    double roll;									// 横摇角(deg)
    double pitch;									// 俯仰角(deg)
    double heading;									// 航向角(deg)
};

// 惯性传感器信息帧定义 10Hz定频发送
struct st_core_frame_inerinfo
{
    st_device device;								// 设备类型,定义见 @st_device
    uint64_t timestamp;								// 系统时间(ms)
    uint64_t timestamp_sync;						// 同步时间(ms)
    double gyro_val_x;								// X轴陀螺值(deg/h)
    double gyro_val_y;								// Y轴陀螺值(deg/h)
    double gyro_val_z;								// Z轴陀螺值(deg/h)
    double gyro_err_x;								// X轴陀螺误差值(deg/h)
    double gyro_err_y;								// Y轴陀螺误差值(deg/h)
    double gyro_err_z;								// Z轴陀螺误差值(deg/h)
    double acce_val_x;								// X轴加速度计值(m/s^2)
    double acce_val_y;								// Y轴加速度计值(m/s^2)
    double acce_val_z;								// Z轴加速度计值(m/s^2)
    double acce_err_x;								// X轴加速度计误差值(m/s^2)
    double acce_err_y;								// Y轴加速度计误差值(m/s^2)
    double acce_err_z;								// Z轴加速度计误差值(m/s^2)
};

// 基准源传感器值 10Hz定频发送
struct st_core_frame_baseinfo
{
    st_device device;								// 设备类型,定义见 @st_device
    uint64_t timestamp;								// 系统时间(ms)
    uint64_t timestamp_sync;						// 同步时间(ms)
    double gnss_lat;								// 北斗定位纬度值(deg)
    double gnss_lon;								// 北斗定位经度值(deg)
    double gnss_alt;								// 北斗定位高度值(m)
    double gnss_ve;									// 北斗定位东向速度值(m/s)
    double gnss_vn;									// 北斗定位北向速度值(m/s)
    double gnss_vu;									// 北斗定位垂向速度值(m/s)
    double gnss_vh;									// 北斗定位水平速度值(m/s)
    double log_vx;									// 多普勒计程仪x轴速度值(m/s)
    double log_vy;									// 多普勒计程仪y轴速度值(m/s)
    double log_vz;									// 多普勒计程仪z轴速度值(m/s)
};

// 校准类型定义
enum e_correction_type
{
    NCT_INVALID,									// 无效类型
    NCT_SINGLE_POINT,								// 单点校准
    NCT_TWO_POINTS,									// 两点校准
    NCT_CONTINUOUS,									// 连续校准
};

// 校准状态定义
enum e_nav_correct_status
{
    NCS_INVALID,									// 无效状态
    NCS_COR_ING,									// 校准中
    NCS_COR_NOT_ING,								// 未校准
};

// 校准信息帧  10Hz定频发送
struct st_core_frame_corrinfo
{
    st_device device;								// 设备类型,定义见 @st_device
    uint64_t timestamp;								// 系统时间(ms)
    uint64_t timestamp_sync;						// 同步时间(ms)
    e_nav_correct_status status;					// 校准状态,定义见@e_nav_correct_status
    e_correction_type type;							// 校准状态,定义见@e_correction_type
    double corr_lat;								// 纬度校准量(nmile)
    double corr_lon;								// 经度校准量(nmile)
    double corr_pos;								// 水平位置校准量(nmile)
    double corr_ve;									// 东向速度校准量(kn)
    double corr_vn;									// 北向速度校准量(kn)
    double corr_vu;									// 垂向速度校准量(kn)
    double corr_roll;								// 横滚角校准量(′)
    double corr_pitch;								// 俯仰角校准量(′)
    double corr_heading;							// 航向角校准量(′)
    double corr_gx_bias;							// x陀螺漂移校准量(deg/h)
    double corr_gy_bias;							// y陀螺漂移校准量(deg/h)
    double corr_gz_bias;							// z陀螺漂移校准量(deg/h)
    double corr_ax_bias;							// x加速度计漂移校准量(ug)
    double corr_ay_bias;							// y加速度计漂移校准量(ug)
    double corr_az_bias;							// z加速度计漂移校准量(ug)
};

// 精度评定方法
enum e_nav_assessment_means
{
    NAM_INVALID,									// 无效方法
    NAM_TRUE_ERR,									// 真值误差
    NAM_MEAN,										// 均值
    NAM_VAR,										// 方差
    NAM_STD,										// 标准差
    NAM_CEP_SIGMA1,									// 圆概率误差1σ
    NAM_CEP_SIGMA3,									// 圆概率误差3σ
    NAM_SEP_SIGMA1,									// 球概率误差1σ
    NAM_SEP_SIGMA3,									// 球概率误差3σ
    NAM_TMRMS,										// 时间均方误差
    NAM_TRRMS,										// 真均方根误差
    NAM_RMS,										// 均方根误差
    NAM_DOA,										// 对准度
    NAM_VAR_ALLAN,									// 阿伦方差
};

// 精度评定量
enum e_nav_assessment_var
{
    NASV_INVALID,									// 无效参量
    NASV_LAT,										// 纬度
    NASV_LON,										// 经度
    NASV_ALT,										// 高度
    NAVS_POS2D,										// 水平位置
    NAVS_POS3D,										// 空间位置
    NAVS_VE,										// 东向速度
    NAVS_VN,										// 北向速度
    NAVS_VU,										// 垂向速度
    NAVS_VEL,										// 合速度
    NAVS_ROLL,										// 横摇角
    NAVS_PITCH,										// 俯仰角
    NAVS_HEADING									// 航向角
};

struct st_assessment_item
{
    e_nav_assessment_var var;   					// 评定量,定义见@e_nav_assessment_var
    e_nav_assessment_means meas;					// 评定方法,定义见@e_nav_assessment_means
    double value;									// 评定结果
};

// 评定信息头
struct st_core_frame_assess_header
{
    st_device device;								// 设备类型,定义见 @st_device
    uint64_t timestamp;								// 系统时间(ms)
    uint64_t timestamp_sync;						// 同步时间(ms)
    uint32_t assess_number;							// assessment 向量个数
};

// 精度评定信息  1Hz定频发送
struct st_core_frame_assessinfo
{
    st_core_frame_assess_header header;				// 评定信息头, 定义见 @st_core_frame_assess_header
    std::vector<st_assessment_item> assessment; 	// 评定信息
};


// 设备状态定义
enum e_device_status
{
    DS_NORMAL,										// 正常仿真
    DS_ERR_TRJ		= 0x0001,						// 轨迹生成错误发生
    DS_ERR_INER		= 0x0002,						// 惯性传感器仿真错误
    DS_ERR_BASE		= 0x0004,						// 基准源传感器仿真错误
    DS_ERR_NAV		= 0x0008,						// 惯导算法仿真错误
    DS_ERR_COR		= 0x0010,						// 校准仿真错误
    DS_ERR_ASS		= 0x0020,						// 精度评定错误
};

// 设备状态信息  1Hz定频发送
struct st_core_frame_deviceinfo
{
    st_device device;								// 设备类型,定义见 @st_device
    uint64_t timestamp;								// 系统时间(ms)
    uint32_t status;								// 设备状态,定义见 @e_device_status
};

// 仿真状态定义
enum e_simulation_status
{
    SS_NORMAL,										// 正常仿真
    SS_ERR_SYNC		= 0x0001,						// 时间模块错误
    SS_ERR_TASK		= 0x0002,						// 任务模块错误
    SS_ERR_DATA		= 0x0004,						// 数据模块错误
};

// 版本号定义
struct st_version
{
    uint32_t major;									// 主
    uint32_t minor;									// 次
};

// 仿真状态信息 1Hz定频发送
struct st_core_frame_sysinfo
{
    uint64_t timestamp;								// 系统时间(ms)
    uint32_t status;								// 仿真状态,定义见 @e_simulation_status
    uint32_t memory_useage;							// 内存使用百分比
    uint32_t process_useage;						// 进程CPU使用百分比
    uint32_t sim_process;							// 仿真进度百分比
    uint32_t task_id;								// 仿真任务ID
    st_version core;								// 内核版本号
    st_version interface;							// 接口版本号
};

// 仿真数据源头
enum e_trjactory_source
{
    TRJS_INNER,										// 内部模型
    TRJS_EXTERN,									// 外部模型
};

// 系统参数
struct st_hmi_frame_syspara
{
    uint32_t number_I;								// I型设备数量
    uint32_t number_II;								// Ⅱ型设备数量
    uint32_t number_III;							// Ⅲ型设备数量
    uint32_t number_IV;								// Ⅳ型设备数量
    e_trjactory_source trj_src;						// 轨迹生成源
    uint32_t sim_speed;								// 仿真倍率
    double sim_step;								// 仿真步长
    uint32_t task_id;								// 仿真任务ID
};

// 初始参数
struct st_hmi_frame_inipara
{
    st_device device;								// 设备类型,定义见 @st_device
    double latitude;								// 纬度(deg)
    double longitude;								// 经度(deg)
    double altitude;								// 海拔(m)
    double velocity_east;							// 东向速度(kn)
    double velocity_north;							// 北向速度(kn)
    double velocity_upper;							// 垂向速度(kn)
    double roll;									// 横摇角(deg)
    double pitch;									// 俯仰角(deg)
    double heading;									// 航向角(deg)
};

// 陀螺误差特性参数
struct st_gyro_para
{
    double bias_x;									// x陀螺常值漂移(deg/h)
    double bias_y;									// y陀螺常值漂移(deg/h)
    double bias_z;									// z陀螺常值漂移(deg/h)
    double angle_walk_x;							// x陀螺角度随机游走(deg/√h)
    double angle_walk_y;							// y陀螺角度随机游走deg/√h)
    double angle_walk_z;							// z陀螺角度随机游走(deg/√h)
    double arate_walk_x;							// x陀螺角速度随机游走(deg/√hh)
    double arate_walk_y;							// y陀螺角速度随机游走(deg/√hh)
    double arate_walk_z;							// z陀螺角速度随机游走(deg/√hh)
    double scale_x;									// x陀螺标度因数非线性度(ppm)
    double scale_y;									// y陀螺标度因数非线性度(ppm)
    double scale_z;									// z陀螺标度因数非线性度(ppm)
    double g_x;										// x陀螺g相关性(deg/h/g)
    double g_y;										// y陀螺g相关性(deg/h/g)
    double g_z;										// z陀螺g相关性(deg/h/g)
    double mis_xy;									// 陀螺失准角误差(x-y)(arcmin)
    double mis_xz;									// 陀螺失准角误差(x-z)(arcmin)
    double mis_yx;									// 陀螺失准角误差(y-x)(arcmin)
    double mis_yz;									// 陀螺失准角误差(y-z)(arcmin)
    double mis_zy;									// 陀螺失准角误差(z-x)(arcmin)
    double mis_zx;									// 陀螺失准角误差(z-y)(arcmin)
    double noise_std_x;								// x陀螺扰动噪声标准差(deg/h)
    double noise_std_y;								// y陀螺扰动噪声标准差(deg/h)
    double noise_std_z;								// z陀螺扰动噪声标准差(deg/h)
};

// 加表误差特性参数
struct st_acce_para
{
    double bias_x;									// x加计常值漂移(deg/h)
    double bias_y;									// y加计常值漂移(deg/h)
    double bias_z;									// z加计常值漂移(deg/h)
    double scale_x;									// x加计标度因数非线性度(ppm)
    double scale_y;									// y加计标度因数非线性度(ppm)
    double scale_z;									// z加计标度因数非线性度(ppm)
    double mis_xy;									// 加计失准角误差(x-y)(arcmin)
    double mis_xz;									// 加计失准角误差(x-z)(arcmin)
    double mis_yx;									// 加计失准角误差(y-x)(arcmin)
    double mis_yz;									// 加计失准角误差(y-z)(arcmin)
    double mis_zy;									// 加计失准角误差(z-x)(arcmin)
    double mis_zx;									// 加计失准角误差(z-y)(arcmin)
    double noise_std_x;								// x加计扰动噪声标准差(deg/h)
    double noise_std_y;								// y加计扰动噪声标准差(deg/h)
    double noise_std_z;								// z加计扰动噪声标准差(deg/h)
};

// 惯性传感器误差特性参数
struct st_hmi_frame_inerpara
{
    st_device device;								// 设备类型,定义见 @st_device
    st_gyro_para gyro;								// 陀螺参数,定义见 @st_gyro_para
    st_acce_para acce;								// 加表参数,定义见 @st_acce_para
};

// 北斗接收机误差特性参数
struct st_bd_para
{
    double lat_std;									// 北斗纬度标准偏差(m)
    double lon_std;									// 北斗经度标准偏差(m)
    double alt_std;									// 北斗高度标准偏差(m)
    double ve_std;									// 北斗东向速度标准偏差(m/s)
    double vn_std;									// 北斗北向速度标准偏差(m/s)
    double vu_std;									// 北斗天向速度标准偏差(m/s)
    double recv_terr;								// 北斗接收机钟差(ns)
    double pos_noise_std;							// 北斗位置随机噪声标准差(m)
    double vel_noise_std;							// 北斗速度随机噪声标准差(m/s)
};

// 多普勒计程仪机误差特性参数
struct st_log_para
{
    double bias_x;									// 计程仪x轴速度常值误差(kn)
    double bias_y;									// 计程仪y轴速度常值误差(kn)
    double bias_z;									// 计程仪z轴速度常值误差(kn)
    double scale;									// 计程仪刻度系数非线性度(ppm)
    double mis_x;									// 计程仪x轴失准角误差(arcmin)
    double mis_y;									// 计程仪y轴失准角误差(arcmin)
    double mis_z;									// 计程仪z轴失准角误差(arcmin)
    double noise_std;								// 计程仪速度随机噪声标准差(kn)
};

// 基准源传感器误差特性参数
struct st_hmi_frame_basepara
{
    st_bd_para bd;
    st_log_para log;
};

// 守时时钟模型随机过程类型定义
enum e_clock_module_type
{
    CMT_MARKOV1,
    CMT_MARKOV2,
};

// 时统模型参数定义
struct st_clock_module_para
{
    e_clock_module_type inert;						// 惯性传感器守时模型随机过程类型, 定义见@e_clock_modle_type
    double inert_corr_time;							// 惯性传感器守时模型随机过程相关时间(t)
    double inert_std;								// 惯性传感器守时模型随机过程标准差(ns)
};

// 时统参数
struct st_hmi_frame_syncpara
{
    st_device device;								// 设备类型,定义见 @st_device
    st_clock_module_para inert;						// 惯性传感器守时模型参数,定义见 @st_clock_module_para
    st_clock_module_para nav;						// 导航计算机守时模型参数,定义见 @st_clock_module_para
    st_clock_module_para bd;						// 北斗接收机守时模型参数,定义见 @st_clock_module_para
    st_clock_module_para log;						// 多普勒计程仪守时模型参数,定义见 @st_clock_module_para
};

// 对准类型
enum e_alignment_type
{
    ALNT_INVALID,									// 无效类型
    ALNT_FINE_PORT,									// 静基座自对准
    ALNT_FILE_SEA,									// 动基座自对准
    ALNT_TRANS,										// 传递对准
};

// 对准流程参数
struct st_alignment_flowpara
{
    e_alignment_type type;							// 对准类型,定义见@e_alignment_type
    uint32_t duration;								// 持续时间(s)
    uint32_t time;									// 对准时刻(s)
};

// 导航类型
enum e_navigation_type
{
    NAVT_INVALID,									// 无效类型
    NAVT_NODAMP,									// 无阻尼导航
    NAVT_LEVELDAMP,									// 水平阻尼导航
    NAVT_INTEGATION,								// 组合导航
};

// 导航流程参数
struct st_navigaiton_flowpara
{
    e_navigation_type type;							// 导航类型,定义详见e_navigation_type
    uint32_t time;									// 切换时刻(s)
};

// 校准流程参数
struct st_correction_flowpara
{
    e_correction_type type;							// 校准类型,定义详见e_correction_type
    uint32_t time;									// 校准时刻(s)
    uint32_t interval;								// 两点校准间隔(s)
    uint32_t duration;								// 连续校准持续时间(s)
};

// 流程参数头定义
struct st_hmi_frame_flowpara_header
{
    st_device device;								// 设备类型,定义见 @st_device
    uint32_t aln_segs;								// 对准流程参数条目数,即aln中向量个数
    uint32_t nav_segs;								// 导航流程参数条目数,即nav中向量个数
    uint32_t cor_segs;								// 校准流程参数条目数,即cor中向量个数
};

// 流程参数
struct st_hmi_frame_flowpara
{
    st_hmi_frame_flowpara_header header;			// 流程参数头,定义见 @st_hmi_frame_flowpara_header
    std::vector<st_alignment_flowpara> aln;  		// 对准流程参数,定义见 @st_alignment_flowpara>
    std::vector<st_navigaiton_flowpara> nav; 		// 对准流程参数,定义见 @st_navigaiton_flowpara
    std::vector<st_correction_flowpara> cor; 		// 对准流程参数,定义见 @st_correction_flowpara
};

// 轨迹类型
enum e_trajectory_type
{
    TRJT_INVALID,									// 无效类型
    TRJT_KEEP,										// 保持
    TRJT_ACC,										// 加速
    TRJT_DCC,										// 减速
    TRJT_TURNLEFT,									// 左转
    TRJT_TURNRIGHT,									// 右转
    TRJT_HEADUP,									// 抬头
    TRJT_HEADDOWN,									// 低头
    TRJT_ROLLLEFT,									// 左滚
    TRJT_ROLLRIGHT,									// 右滚
};

// 轨迹片段
struct st_trajectory_segment
{
    uint32_t index;									// 编码
    e_trajectory_type type;							// 轨迹片段类型,详见@e_trajectory_type
    uint32_t duartion;								// 持续时间(s)
};

// 轨迹参数头定义
struct st_hmi_frame_trjpara_header
{
    st_device device;								// 设备类型,定义见 @st_device
    uint32_t segs;									// 片段数目,即trjs中向量个数
};
// 轨迹参数
struct st_hmi_frame_trjpara
{
    st_hmi_frame_trjpara_header header;		 		// 轨迹描述头, 定义见st_hmi_frame_trjpara_header
    std::vector<st_trajectory_segment> trjs; 		// 轨迹,定义见 @st_hmi_frame_trjpara
};

// 样本处理方法
enum e_sample_calc_means
{
    SCM_MEAN,										// 均值
    SCM_MIDDLE,										// 中值
};

// 精度评定参数
struct st_hmi_frame_assprara
{
    uint32_t samples_time;							// 样本时间(s)
    e_sample_calc_means mean;						// 样本处理办法,定义见@st_hmi_frame_assprara
};

// 仿真命令类型
enum e_sim_command_type
{
    SCT_INVALID,									// 无效命令
    SCT_START,										// 仿真开始
    SCT_PAUSE,										// 暂停仿真
    SCT_STOP,										// 仿真结束
    SCT_INQUIRE										// 查询参数, 接收到此命令后, core将按定义的HMI参数结构体进行回传
};

// 仿真命令
struct st_hmi_frame_command
{
    st_device device;								// 设备类型, 定义见 @st_device
    e_sim_command_type cmd;							// 仿真类型, 定义详见 @e_sim_command_type
    e_nav_frame_hmi_type type;						// 仅用于 SCT_INQUIRE, 查询参数类型, 定义详见 @e_nav_frame_hmi_type
};

#pragma pack()

#endif //NAVOCRE_INTERFACE_H
