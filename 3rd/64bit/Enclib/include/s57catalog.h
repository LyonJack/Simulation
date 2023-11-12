#ifndef __S57_CATALOG_H__ 
#define __S57_CATALOG_H__

//! Catalog �ļ��е��ļ�·����Ϣ
typedef struct
{
	char RCNM[3];	/**<��¼����ֵȷ��Ϊ"CD"*/
	int RCID; 		/**<��¼ID*/
	char* FILE;		/**<���ļ���*/
	char* LFIL;		/**<���ļ���*/
	char* VOLM;		/**<�ļ������̷�*/
	char IMPL[4];	/**<�ļ����ͣ�ASC���ı��ļ���BIN���������ļ�*/
	double SLAT;	/**<��ͼ���Ƿ�Χ������γ��*/
	double WLON;	/**<��ͼ���Ƿ�Χ�������*/
	double NLAT;	/**<��ͼ���Ƿ�Χ���γ��*/
	double ELON;	/**<��ͼ���Ƿ�Χ����������*/
	char* CRCS;		/**<CRCУ���*/
	char* COMT; 	/**<������Ϣ*/
}S57CatalogDirectory;

//! Catalog�ļ��еĽ���������Ϣ
typedef struct
{
	char RCNM[3];	/**<��¼����ֵȷ��Ϊ"CR":Cross Reference*/
	int RCID;		/**<��¼ID*/
	char* NAM1;		/**<Name 1*/
	char* NAM2;		/**<Name 2*/
	char* COMT;		/**<������Ϣ*/
}S57CatalogCrossReference;

//! ���ݼ� Catalogue��Ϣ
typedef struct
{
	int nCatalogDirectories; 					/**<�ļ�·����¼����*/
	S57CatalogDirectory** catalogdirectories;	/**<�ļ�·����¼*/
	int nCatalogCrossReferences;				/**<�������ü�¼����*/
	S57CatalogCrossReference** crossreferences;	/**<�������ü�¼*/
}S57DatasetCatalogueInfo;

#endif
