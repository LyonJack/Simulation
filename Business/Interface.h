#ifndef INTERFACE_DEF_H
#define INTERFACE_DEF_H

#include <stdint.h>
#include <vector>

#pragma pack(1)

#define INTERFACE_VERSION	"1.1"
#define INTERFACE_PORT		(20000)

// ֡��ʽ��֡ͷ1(uint8_t), �����@e_nav_frame_info
//		  ֡ͷ2(uint8_t), �����@e_nav_frame_info
//		  ֡����(uint8_t), �����@e_nav_frame_core_type, @e_nav_frame_hmi_type
//		  ֡��Դ(uint8_t), �������@e_nav_frame_source
//		  ֡���ݳ���(uint16_t)
//		  ֡����(����ṹ�嶨��)
//		  У��(uint8_t) ֡���͵�֡����֮��������ֽڵ�����
//	      ֡β(uint8_t), �����@e_nav_frame_info


// ֡��Ϣ
enum e_nav_frame_info
{
    NFH_HEAD1 = 0xA5,								// ֡ͷ1
    NFH_HEAD2 = 0x5A,								// ֡ͷ2
    NFH_TAIL = 0xED,								// ֡β
};

// ֡��Դ
enum e_nav_frame_source
{
    NFS_CORE,										// ��̨�������
    NFS_HMI,										// HMIչʾ���
};

// ���������̨����֡����
enum e_nav_frame_core_type
{
    NFCT_INVALID,									// ��Ч
    NFCT_HMI_ACK,									// HMI��Ӧ֡, �յ�HMI֡����������, ����� @st_core_frame_ackinfo
    NFCT_NAV_INFO,									// ������Ϣ, ����� @st_core_frame_navinfo
    NFCT_NAV_ERROR,									// ���������Ϣ, ����� @st_core_frame_naverro
    NFCT_TRJ_INFO,									// �켣��Ϣ, ����� @st_core_frame_trjinfo
    NFCT_INER_INFO,									// ���Դ�������Ϣ, ����� @st_core_frame_inerinfo
    NFCT_BASE_INFO,									// ��׼Դ��������Ϣ, ����� @st_core_frame_baseinfo
    NFCT_CORR_INFO,									// У׼��Ϣ, ����� @st_core_frame_corrinfo
    NFCT_ASSE_INFO,									// ����������Ϣ, ����� @st_core_frame_assessinfo
    NFCT_DEV_STATUS,								// �豸״̬��Ϣ, ����� @st_core_frame_deviceinfo
    NFCT_SYS_STATUS,								// ����״̬��Ϣ, ����� @st_core_frame_sysinfo
};

// ����չʾ�������֡����
enum e_nav_frame_hmi_type
{
    NFHT_INVALID,									// ��Ч
    NFHT_NAV_ACK,									// ��̨��Ӧ֡, �յ������̨֡����������, ����� @st_hmi_frame_ackinfo
    NFHT_INI_PARA,									// ��ʼ����, ����� @st_hmi_frame_inipara
    NFHT_SYS_PARA,									// ϵͳ����, ����� @st_hmi_frame_syspara
    HFHT_INER_PARA,									// ���Դ���������, ����� @st_hmi_frame_inerpara
    NFHT_BASE_PRRA,									// ��׼Դ����������, ����� @st_hmi_frame_basepara
    HFHT_SYNC_PARA,									// ʱͳ����, ����� @st_hmi_frame_syncpara
    HFHT_FLOW_PARA,									// ���̲���, ����� @st_hmi_frame_flowpara
    HFHT_TRJ_PARA,									// �켣����, ����� @st_hmi_frame_trjpara
    HFHT_ASSE_PARA,									// ����������������, ����� @st_hmi_frame_assprara
    HFHT_COMMAND,									// ��������, ����� @st_hmi_frame_command
};

// ֡��Ӧ״̬
enum e_ack_status
{
    ACKS_OK,										// ����
    ACKS_ERR_DATA,									// ���ݴ���
};

// HMI��Ӧ֡
struct st_core_frame_ackinfo
{
    uint64_t timestamp;								// ϵͳʱ��(ms)
    e_nav_frame_hmi_type type;						// ���յ���HMI֡����
    e_ack_status status;							// ��Ӧ״̬
};

//��̨��Ӧ֡
struct st_hmi_frame_ackinfo
{
    uint64_t timestamp;								// ϵͳʱ��(ms)
    e_nav_frame_hmi_type type;						// ���յ��ĺ�̨֡����
    e_ack_status status;							// ��Ӧ״̬
};

// �豸����
enum e_dev_type
{
    DT_INVALID,										// ��Ч�豸
    DT_I,											// �����豸
    DT_II,											// �����豸
    DT_III,											// �����豸
    DT_IV,											// �����豸
};

// ����״̬
enum e_nav_status
{
    NS_INVALID,										// ��Ч
    NS_READY,										// ����״̬
    NS_ALN_CORASE,									// �ֶ�׼״̬
    NS_ALN_PORT,									// ����������׼
    NS_ALN_SEA,										// ����������׼
    NS_NAV_NODAMP,									// �����Ե���״̬
    NS_NAV_LEVELDAMP,								// ˮƽ���ᵼ��״̬
    NS_INTEGATION,									// ���״̬
    NS_CORRECTION,									// У׼״̬
};

struct st_device
{
    e_dev_type type;								// �豸����,����� @e_dev_type
    uint32_t number;								// �豸���
};

// ������Ϣ֡���� 10Hz��Ƶ����
struct st_core_frame_navinfo
{
    st_device device;								// �豸����,����� @st_device
    uint64_t timestamp;								// ϵͳʱ��(ms)
    uint64_t timestamp_sync;						// ͬ��ʱ��(ms)
    uint64_t timestamp_status;						// ��ǰϵͳʱ��(ms)
    e_nav_status status;							// ����״̬,����� @e_nav_status
    double latitude;								// γ��(deg)
    double longitude;								// ����(deg)
    double altitude;								// ����(m)
    double velocity_east;							// �����ٶ�(kn)
    double velocity_north;							// �����ٶ�(kn)
    double velocity_upper;							// �����ٶ�(kn)
    double velocity;								// ���ٶ�(kn)
    double roll;									// ��ҡ��(deg)
    double pitch;									// ������(deg)
    double heading;									// �����(deg)
    double roll_rate;								// ��ҡ���ٶ�(deg/s)
    double pitch_rate;								// �������ٶ�(deg/s)
    double heading_rate;							// ������ٶ�(deg/s)
    double heave;									// ����λ��(m)
};

// �������֡���� 10Hz��Ƶ����
struct st_core_frame_naverro
{
    st_device device;								// �豸����,����� @st_device
    uint64_t timestamp;								// ϵͳʱ��(ms)
    uint64_t timestamp_sync;						// ͬ��ʱ��(ms)
    e_nav_status status;							// ����״̬,����� @e_nav_status
    double e_latitude;								// γ��(deg)
    double e_longitude;								// ����(deg)
    double e_altitude;								// ����(m)
    double e_velocity_east;							// �����ٶ�(kn)
    double e_velocity_north;						// �����ٶ�(kn)
    double e_velocity_upper;						// �����ٶ�(kn)
    double e_roll;									// ��ҡ��(deg)
    double e_pitch;									// ������(deg)
    double e_heading;								// �����(deg)
};

// �켣��Ϣ֡���� 10Hz��Ƶ����
struct st_core_frame_trjinfo
{
    st_device device;								// �豸����,����� @st_device
    uint64_t timestamp;								// ϵͳʱ��(ms)
    uint64_t timestamp_sync;						// ͬ��ʱ��(ms)
    uint32_t seg_all;								// ������
    uint32_t seg_cur;								// ��ǰ�����
    uint32_t time_seg_cur;							// ��ǰ������ʱ��
    uint32_t time_seg;								// ��ǰ����ʱ��
    uint64_t time_total;							// ��ʱ��
    double latitude;								// γ��(deg)
    double longitude;								// ����(deg)
    double altitude;								// ����(m)
    double velocity_east;							// �����ٶ�(kn)
    double velocity_north;							// �����ٶ�(kn)
    double velocity_upper;							// �����ٶ�(kn)
    double roll;									// ��ҡ��(deg)
    double pitch;									// ������(deg)
    double heading;									// �����(deg)
};

// ���Դ�������Ϣ֡���� 10Hz��Ƶ����
struct st_core_frame_inerinfo
{
    st_device device;								// �豸����,����� @st_device
    uint64_t timestamp;								// ϵͳʱ��(ms)
    uint64_t timestamp_sync;						// ͬ��ʱ��(ms)
    double gyro_val_x;								// X������ֵ(deg/h)
    double gyro_val_y;								// Y������ֵ(deg/h)
    double gyro_val_z;								// Z������ֵ(deg/h)
    double gyro_err_x;								// X���������ֵ(deg/h)
    double gyro_err_y;								// Y���������ֵ(deg/h)
    double gyro_err_z;								// Z���������ֵ(deg/h)
    double acce_val_x;								// X����ٶȼ�ֵ(m/s^2)
    double acce_val_y;								// Y����ٶȼ�ֵ(m/s^2)
    double acce_val_z;								// Z����ٶȼ�ֵ(m/s^2)
    double acce_err_x;								// X����ٶȼ����ֵ(m/s^2)
    double acce_err_y;								// Y����ٶȼ����ֵ(m/s^2)
    double acce_err_z;								// Z����ٶȼ����ֵ(m/s^2)
};

// ��׼Դ������ֵ 10Hz��Ƶ����
struct st_core_frame_baseinfo
{
    st_device device;								// �豸����,����� @st_device
    uint64_t timestamp;								// ϵͳʱ��(ms)
    uint64_t timestamp_sync;						// ͬ��ʱ��(ms)
    double gnss_lat;								// ������λγ��ֵ(deg)
    double gnss_lon;								// ������λ����ֵ(deg)
    double gnss_alt;								// ������λ�߶�ֵ(m)
    double gnss_ve;									// ������λ�����ٶ�ֵ(m/s)
    double gnss_vn;									// ������λ�����ٶ�ֵ(m/s)
    double gnss_vu;									// ������λ�����ٶ�ֵ(m/s)
    double gnss_vh;									// ������λˮƽ�ٶ�ֵ(m/s)
    double log_vx;									// �����ռƳ���x���ٶ�ֵ(m/s)
    double log_vy;									// �����ռƳ���y���ٶ�ֵ(m/s)
    double log_vz;									// �����ռƳ���z���ٶ�ֵ(m/s)
};

// У׼���Ͷ���
enum e_correction_type
{
    NCT_INVALID,									// ��Ч����
    NCT_SINGLE_POINT,								// ����У׼
    NCT_TWO_POINTS,									// ����У׼
    NCT_CONTINUOUS,									// ����У׼
};

// У׼״̬����
enum e_nav_correct_status
{
    NCS_INVALID,									// ��Ч״̬
    NCS_COR_ING,									// У׼��
    NCS_COR_NOT_ING,								// δУ׼
};

// У׼��Ϣ֡  10Hz��Ƶ����
struct st_core_frame_corrinfo
{
    st_device device;								// �豸����,����� @st_device
    uint64_t timestamp;								// ϵͳʱ��(ms)
    uint64_t timestamp_sync;						// ͬ��ʱ��(ms)
    e_nav_correct_status status;					// У׼״̬,�����@e_nav_correct_status
    e_correction_type type;							// У׼״̬,�����@e_correction_type
    double corr_lat;								// γ��У׼��(nmile)
    double corr_lon;								// ����У׼��(nmile)
    double corr_pos;								// ˮƽλ��У׼��(nmile)
    double corr_ve;									// �����ٶ�У׼��(kn)
    double corr_vn;									// �����ٶ�У׼��(kn)
    double corr_vu;									// �����ٶ�У׼��(kn)
    double corr_roll;								// �����У׼��(��)
    double corr_pitch;								// ������У׼��(��)
    double corr_heading;							// �����У׼��(��)
    double corr_gx_bias;							// x����Ư��У׼��(deg/h)
    double corr_gy_bias;							// y����Ư��У׼��(deg/h)
    double corr_gz_bias;							// z����Ư��У׼��(deg/h)
    double corr_ax_bias;							// x���ٶȼ�Ư��У׼��(ug)
    double corr_ay_bias;							// y���ٶȼ�Ư��У׼��(ug)
    double corr_az_bias;							// z���ٶȼ�Ư��У׼��(ug)
};

// ������������
enum e_nav_assessment_means
{
    NAM_INVALID,									// ��Ч����
    NAM_TRUE_ERR,									// ��ֵ���
    NAM_MEAN,										// ��ֵ
    NAM_VAR,										// ����
    NAM_STD,										// ��׼��
    NAM_CEP_SIGMA1,									// Բ�������1��
    NAM_CEP_SIGMA3,									// Բ�������3��
    NAM_SEP_SIGMA1,									// ��������1��
    NAM_SEP_SIGMA3,									// ��������3��
    NAM_TMRMS,										// ʱ��������
    NAM_TRRMS,										// ����������
    NAM_RMS,										// ���������
    NAM_DOA,										// ��׼��
    NAM_VAR_ALLAN,									// ���׷���
};

// ����������
enum e_nav_assessment_var
{
    NASV_INVALID,									// ��Ч����
    NASV_LAT,										// γ��
    NASV_LON,										// ����
    NASV_ALT,										// �߶�
    NAVS_POS2D,										// ˮƽλ��
    NAVS_POS3D,										// �ռ�λ��
    NAVS_VE,										// �����ٶ�
    NAVS_VN,										// �����ٶ�
    NAVS_VU,										// �����ٶ�
    NAVS_VEL,										// ���ٶ�
    NAVS_ROLL,										// ��ҡ��
    NAVS_PITCH,										// ������
    NAVS_HEADING									// �����
};

struct st_assessment_item
{
    e_nav_assessment_var var;   					// ������,�����@e_nav_assessment_var
    e_nav_assessment_means meas;					// ��������,�����@e_nav_assessment_means
    double value;									// �������
};

// ������Ϣͷ
struct st_core_frame_assess_header
{
    st_device device;								// �豸����,����� @st_device
    uint64_t timestamp;								// ϵͳʱ��(ms)
    uint64_t timestamp_sync;						// ͬ��ʱ��(ms)
    uint32_t assess_number;							// assessment ��������
};

// ����������Ϣ  1Hz��Ƶ����
struct st_core_frame_assessinfo
{
    st_core_frame_assess_header header;				// ������Ϣͷ, ����� @st_core_frame_assess_header
    std::vector<st_assessment_item> assessment; 	// ������Ϣ
};


// �豸״̬����
enum e_device_status
{
    DS_NORMAL,										// ��������
    DS_ERR_TRJ		= 0x0001,						// �켣���ɴ�����
    DS_ERR_INER		= 0x0002,						// ���Դ������������
    DS_ERR_BASE		= 0x0004,						// ��׼Դ�������������
    DS_ERR_NAV		= 0x0008,						// �ߵ��㷨�������
    DS_ERR_COR		= 0x0010,						// У׼�������
    DS_ERR_ASS		= 0x0020,						// ������������
};

// �豸״̬��Ϣ  1Hz��Ƶ����
struct st_core_frame_deviceinfo
{
    st_device device;								// �豸����,����� @st_device
    uint64_t timestamp;								// ϵͳʱ��(ms)
    uint32_t status;								// �豸״̬,����� @e_device_status
};

// ����״̬����
enum e_simulation_status
{
    SS_NORMAL,										// ��������
    SS_ERR_SYNC		= 0x0001,						// ʱ��ģ�����
    SS_ERR_TASK		= 0x0002,						// ����ģ�����
    SS_ERR_DATA		= 0x0004,						// ����ģ�����
};

// �汾�Ŷ���
struct st_version
{
    uint32_t major;									// ��
    uint32_t minor;									// ��
};

// ����״̬��Ϣ 1Hz��Ƶ����
struct st_core_frame_sysinfo
{
    uint64_t timestamp;								// ϵͳʱ��(ms)
    uint32_t status;								// ����״̬,����� @e_simulation_status
    uint32_t memory_useage;							// �ڴ�ʹ�ðٷֱ�
    uint32_t process_useage;						// ����CPUʹ�ðٷֱ�
    uint32_t sim_process;							// ������Ȱٷֱ�
    uint32_t task_id;								// ��������ID
    st_version core;								// �ں˰汾��
    st_version interface;							// �ӿڰ汾��
};

// ��������Դͷ
enum e_trjactory_source
{
    TRJS_INNER,										// �ڲ�ģ��
    TRJS_EXTERN,									// �ⲿģ��
};

// ϵͳ����
struct st_hmi_frame_syspara
{
    uint32_t number_I;								// I���豸����
    uint32_t number_II;								// �����豸����
    uint32_t number_III;							// �����豸����
    uint32_t number_IV;								// �����豸����
    e_trjactory_source trj_src;						// �켣����Դ
    uint32_t sim_speed;								// ���汶��
    double sim_step;								// ���沽��
    uint32_t task_id;								// ��������ID
};

// ��ʼ����
struct st_hmi_frame_inipara
{
    st_device device;								// �豸����,����� @st_device
    double latitude;								// γ��(deg)
    double longitude;								// ����(deg)
    double altitude;								// ����(m)
    double velocity_east;							// �����ٶ�(kn)
    double velocity_north;							// �����ٶ�(kn)
    double velocity_upper;							// �����ٶ�(kn)
    double roll;									// ��ҡ��(deg)
    double pitch;									// ������(deg)
    double heading;									// �����(deg)
};

// ����������Բ���
struct st_gyro_para
{
    double bias_x;									// x���ݳ�ֵƯ��(deg/h)
    double bias_y;									// y���ݳ�ֵƯ��(deg/h)
    double bias_z;									// z���ݳ�ֵƯ��(deg/h)
    double angle_walk_x;							// x���ݽǶ��������(deg/��h)
    double angle_walk_y;							// y���ݽǶ��������deg/��h)
    double angle_walk_z;							// z���ݽǶ��������(deg/��h)
    double arate_walk_x;							// x���ݽ��ٶ��������(deg/��hh)
    double arate_walk_y;							// y���ݽ��ٶ��������(deg/��hh)
    double arate_walk_z;							// z���ݽ��ٶ��������(deg/��hh)
    double scale_x;									// x���ݱ�����������Զ�(ppm)
    double scale_y;									// y���ݱ�����������Զ�(ppm)
    double scale_z;									// z���ݱ�����������Զ�(ppm)
    double g_x;										// x����g�����(deg/h/g)
    double g_y;										// y����g�����(deg/h/g)
    double g_z;										// z����g�����(deg/h/g)
    double mis_xy;									// ����ʧ׼�����(x-y)(arcmin)
    double mis_xz;									// ����ʧ׼�����(x-z)(arcmin)
    double mis_yx;									// ����ʧ׼�����(y-x)(arcmin)
    double mis_yz;									// ����ʧ׼�����(y-z)(arcmin)
    double mis_zy;									// ����ʧ׼�����(z-x)(arcmin)
    double mis_zx;									// ����ʧ׼�����(z-y)(arcmin)
    double noise_std_x;								// x�����Ŷ�������׼��(deg/h)
    double noise_std_y;								// y�����Ŷ�������׼��(deg/h)
    double noise_std_z;								// z�����Ŷ�������׼��(deg/h)
};

// �ӱ�������Բ���
struct st_acce_para
{
    double bias_x;									// x�ӼƳ�ֵƯ��(deg/h)
    double bias_y;									// y�ӼƳ�ֵƯ��(deg/h)
    double bias_z;									// z�ӼƳ�ֵƯ��(deg/h)
    double scale_x;									// x�ӼƱ�����������Զ�(ppm)
    double scale_y;									// y�ӼƱ�����������Զ�(ppm)
    double scale_z;									// z�ӼƱ�����������Զ�(ppm)
    double mis_xy;									// �Ӽ�ʧ׼�����(x-y)(arcmin)
    double mis_xz;									// �Ӽ�ʧ׼�����(x-z)(arcmin)
    double mis_yx;									// �Ӽ�ʧ׼�����(y-x)(arcmin)
    double mis_yz;									// �Ӽ�ʧ׼�����(y-z)(arcmin)
    double mis_zy;									// �Ӽ�ʧ׼�����(z-x)(arcmin)
    double mis_zx;									// �Ӽ�ʧ׼�����(z-y)(arcmin)
    double noise_std_x;								// x�Ӽ��Ŷ�������׼��(deg/h)
    double noise_std_y;								// y�Ӽ��Ŷ�������׼��(deg/h)
    double noise_std_z;								// z�Ӽ��Ŷ�������׼��(deg/h)
};

// ���Դ�����������Բ���
struct st_hmi_frame_inerpara
{
    st_device device;								// �豸����,����� @st_device
    st_gyro_para gyro;								// ���ݲ���,����� @st_gyro_para
    st_acce_para acce;								// �ӱ����,����� @st_acce_para
};

// �������ջ�������Բ���
struct st_bd_para
{
    double lat_std;									// ����γ�ȱ�׼ƫ��(m)
    double lon_std;									// �������ȱ�׼ƫ��(m)
    double alt_std;									// �����߶ȱ�׼ƫ��(m)
    double ve_std;									// ���������ٶȱ�׼ƫ��(m/s)
    double vn_std;									// ���������ٶȱ�׼ƫ��(m/s)
    double vu_std;									// ���������ٶȱ�׼ƫ��(m/s)
    double recv_terr;								// �������ջ��Ӳ�(ns)
    double pos_noise_std;							// ����λ�����������׼��(m)
    double vel_noise_std;							// �����ٶ����������׼��(m/s)
};

// �����ռƳ��ǻ�������Բ���
struct st_log_para
{
    double bias_x;									// �Ƴ���x���ٶȳ�ֵ���(kn)
    double bias_y;									// �Ƴ���y���ٶȳ�ֵ���(kn)
    double bias_z;									// �Ƴ���z���ٶȳ�ֵ���(kn)
    double scale;									// �Ƴ��ǿ̶�ϵ�������Զ�(ppm)
    double mis_x;									// �Ƴ���x��ʧ׼�����(arcmin)
    double mis_y;									// �Ƴ���y��ʧ׼�����(arcmin)
    double mis_z;									// �Ƴ���z��ʧ׼�����(arcmin)
    double noise_std;								// �Ƴ����ٶ����������׼��(kn)
};

// ��׼Դ������������Բ���
struct st_hmi_frame_basepara
{
    st_bd_para bd;
    st_log_para log;
};

// ��ʱʱ��ģ������������Ͷ���
enum e_clock_module_type
{
    CMT_MARKOV1,
    CMT_MARKOV2,
};

// ʱͳģ�Ͳ�������
struct st_clock_module_para
{
    e_clock_module_type inert;						// ���Դ�������ʱģ�������������, �����@e_clock_modle_type
    double inert_corr_time;							// ���Դ�������ʱģ������������ʱ��(t)
    double inert_std;								// ���Դ�������ʱģ��������̱�׼��(ns)
};

// ʱͳ����
struct st_hmi_frame_syncpara
{
    st_device device;								// �豸����,����� @st_device
    st_clock_module_para inert;						// ���Դ�������ʱģ�Ͳ���,����� @st_clock_module_para
    st_clock_module_para nav;						// �����������ʱģ�Ͳ���,����� @st_clock_module_para
    st_clock_module_para bd;						// �������ջ���ʱģ�Ͳ���,����� @st_clock_module_para
    st_clock_module_para log;						// �����ռƳ�����ʱģ�Ͳ���,����� @st_clock_module_para
};

// ��׼����
enum e_alignment_type
{
    ALNT_INVALID,									// ��Ч����
    ALNT_FINE_PORT,									// �������Զ�׼
    ALNT_FILE_SEA,									// �������Զ�׼
    ALNT_TRANS,										// ���ݶ�׼
};

// ��׼���̲���
struct st_alignment_flowpara
{
    e_alignment_type type;							// ��׼����,�����@e_alignment_type
    uint32_t duration;								// ����ʱ��(s)
    uint32_t time;									// ��׼ʱ��(s)
};

// ��������
enum e_navigation_type
{
    NAVT_INVALID,									// ��Ч����
    NAVT_NODAMP,									// �����ᵼ��
    NAVT_LEVELDAMP,									// ˮƽ���ᵼ��
    NAVT_INTEGATION,								// ��ϵ���
};

// �������̲���
struct st_navigaiton_flowpara
{
    e_navigation_type type;							// ��������,�������e_navigation_type
    uint32_t time;									// �л�ʱ��(s)
};

// У׼���̲���
struct st_correction_flowpara
{
    e_correction_type type;							// У׼����,�������e_correction_type
    uint32_t time;									// У׼ʱ��(s)
    uint32_t interval;								// ����У׼���(s)
    uint32_t duration;								// ����У׼����ʱ��(s)
};

// ���̲���ͷ����
struct st_hmi_frame_flowpara_header
{
    st_device device;								// �豸����,����� @st_device
    uint32_t aln_segs;								// ��׼���̲�����Ŀ��,��aln����������
    uint32_t nav_segs;								// �������̲�����Ŀ��,��nav����������
    uint32_t cor_segs;								// У׼���̲�����Ŀ��,��cor����������
};

// ���̲���
struct st_hmi_frame_flowpara
{
    st_hmi_frame_flowpara_header header;			// ���̲���ͷ,����� @st_hmi_frame_flowpara_header
    std::vector<st_alignment_flowpara> aln;  		// ��׼���̲���,����� @st_alignment_flowpara>
    std::vector<st_navigaiton_flowpara> nav; 		// ��׼���̲���,����� @st_navigaiton_flowpara
    std::vector<st_correction_flowpara> cor; 		// ��׼���̲���,����� @st_correction_flowpara
};

// �켣����
enum e_trajectory_type
{
    TRJT_INVALID,									// ��Ч����
    TRJT_KEEP,										// ����
    TRJT_ACC,										// ����
    TRJT_DCC,										// ����
    TRJT_TURNLEFT,									// ��ת
    TRJT_TURNRIGHT,									// ��ת
    TRJT_HEADUP,									// ̧ͷ
    TRJT_HEADDOWN,									// ��ͷ
    TRJT_ROLLLEFT,									// ���
    TRJT_ROLLRIGHT,									// �ҹ�
};

// �켣Ƭ��
struct st_trajectory_segment
{
    uint32_t index;									// ����
    e_trajectory_type type;							// �켣Ƭ������,���@e_trajectory_type
    uint32_t duartion;								// ����ʱ��(s)
};

// �켣����ͷ����
struct st_hmi_frame_trjpara_header
{
    st_device device;								// �豸����,����� @st_device
    uint32_t segs;									// Ƭ����Ŀ,��trjs����������
};
// �켣����
struct st_hmi_frame_trjpara
{
    st_hmi_frame_trjpara_header header;		 		// �켣����ͷ, �����st_hmi_frame_trjpara_header
    std::vector<st_trajectory_segment> trjs; 		// �켣,����� @st_hmi_frame_trjpara
};

// ����������
enum e_sample_calc_means
{
    SCM_MEAN,										// ��ֵ
    SCM_MIDDLE,										// ��ֵ
};

// ������������
struct st_hmi_frame_assprara
{
    uint32_t samples_time;							// ����ʱ��(s)
    e_sample_calc_means mean;						// ��������취,�����@st_hmi_frame_assprara
};

// ������������
enum e_sim_command_type
{
    SCT_INVALID,									// ��Ч����
    SCT_START,										// ���濪ʼ
    SCT_PAUSE,										// ��ͣ����
    SCT_STOP,										// �������
    SCT_INQUIRE										// ��ѯ����, ���յ��������, core���������HMI�����ṹ����лش�
};

// ��������
struct st_hmi_frame_command
{
    st_device device;								// �豸����, ����� @st_device
    e_sim_command_type cmd;							// ��������, ������� @e_sim_command_type
    e_nav_frame_hmi_type type;						// ������ SCT_INQUIRE, ��ѯ��������, ������� @e_nav_frame_hmi_type
};

#pragma pack()

#endif //NAVOCRE_INTERFACE_H
