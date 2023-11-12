#ifndef __IMPORT_CALLBACK_DEFS_H__
#define __IMPORT_CALLBACK_DEFS_H__

#include "s63defs.h"

typedef enum
{
    ENCL_STEP_READ_CALALOG=0,
    ENCL_STEP_CHECK_DATASETINTEGRITY,
    ENCL_STEP_GET_CORRESPONDINGPERMIT,
    ENCL_STEP_CHECK_CERTIFICATE,
    ENCL_STEP_DECRYPT_S63ENC,
    ENCL_STEP_CONVERT_TOSENC,
    ENCL_STEP_DONE,
}EnclImportStep;

typedef enum
{
    ENCL_IMPORT_MENC=0,
    ENCL_IMPORT_S63,
    ENCL_IMPORT_S57,
}EnclImportType;

//! ��ͼ������̻ص�����
/*!
*	type�� �������ͣ�����s57 �� s63 ����
*	step: ��ǰ������������׶�
*	pszChartName�� ��ǰ�����ļ�����·��
*	iCurChart: ��ǰ�ļ�����
*	totalChartCnt: Ҫ�����ļ�����
*	progress: ��ǰ����(0~1)
*	usrData: �û�����ָ�룬���ս����ݸ��ص�����
*/
typedef void (*ImportProcCallback)(EnclImportType type, EnclImportStep step,
	const char* pszChartName, int iCurChart, int totalChartCnt, float progress, 
	void * usrData );

//! ��ͼ���������Ϣ�ص�����
/*!
*	type�� �������ͣ�����s57 �� s63 ����
*	step: ��ǰ������������׶�
*	pszChartName�� ��ǰ�����ļ�����·��
*	errorCode: �������
*	usrData: �û�����ָ�룬���ս����ݸ��ص�����
*/
typedef bool (*EnclSENCInstallErrCallBack)(EnclImportType type, EnclImportStep step,
	int errorCode, const char* chartno, const char *ds, void *usrdata);
typedef bool (*EnclSENCImportErrCallBack)(EnclImportType type, EnclImportStep step,
	int errorCode, const char* chartno, EnclErrCellPermitCallbackData *data);

typedef bool (*EnclS63PermitCallback)(EnclS63CellPermitInfo *, bool formatFlag, void *);

#endif
