/****************************************************************************
 *
 * Copyrig_ht (c) 2001-2006
 *     Institute of Computing Tech.
 *     Chinese Academy of Sciences
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Institute of Computing_ Tech. and the posession or use of this file requires 
 * a written license from the author.
 * Filename: 
 * Abstract:
 *            ICTCLAS30.h: definition of the ICTCLAS30
 * Author:   Kevin Zhang_ 
 *          (zhang_hp@software.ict.ac.cn)
 * Date:     2005-12-27
 *
 * Notes:
 *                
 ****************************************************************************/
#if !defined(__ICTCLAS_LIB_INCLUDED__)
#define __ICTCLAS_LIB_INCLUDED__

#ifdef OS_LINUX
	#define ICTCLAS_API 
#else
	#ifdef ICTCLAS_EXPORTS
		#ifdef CSHARP_API
			#define ICTCLAS_API extern "C" __declspec(dllexport)
		#else
			#define ICTCLAS_API __declspec(dllexport)
		#endif
	#else
		#define ICTCLAS_API 
	#endif
#endif

struct result_t{
  int start; //start position,��������������еĿ�ʼλ��
  int length; //length,����ĳ���
  int POS_id;//word type������IDֵ�����Կ��ٵĻ�ȡ���Ա�
  int word_ID; //�����δ��¼�ʣ����0����-1
 };
/*********************************************************************
 *
 *  Func Name  : Init
 *
 *  Description: Init ICTCLAS30
 *              The function must be invoked before any operation listed as following
 *
 *  Parameters : const char * sInitDirPath=NULL
 *       sInitDirPath: Initial Directory Path, where file Configure.xml and Data directory stored.
 * the default value is NULL, it indicates the initial directory is current working directory path
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2002-8-6
 *********************************************************************/
ICTCLAS_API bool ICTCLAS_Init(const char * sInitDirPath=0);
/*********************************************************************
 *
 *  Func Name  : ICTCLAS_Exit
 *
 *  Description: Exist ICTCLAS30 and free related buffer
 *              Exit the program and free memory
 *The function must be invoked while you needn't any lexical anlysis
 *
 *  Parameters : None
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2002-8-6
 *********************************************************************/
ICTCLAS_API bool ICTCLAS_Exit();
/*********************************************************************
 *
 *  Func Name  : ImportUserDict
 *
 *  Description: Import User-defined dictionary
 *  Parameters : Text filename for user dictionary 
 *  Returns    : The  number of  lexical entry imported successfully
 *  Author     : Kevin Zhang
 *  History    : 
 *              1.create 2003-11-28
 *********************************************************************/
ICTCLAS_API unsigned int ICTCLAS_ImportUserDict(const char *sFilename);

/*********************************************************************
 *
 *  Func Name  : ParagraphProcessing
 *
 *  Description: Process a paragraph
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               sResult: The result
 *				 bPOStagged:Judge whether need POS tagging, 0 for no tag;default:1
 *  i.e.  �Ż�ƽ��1978��3��9�ճ����ڽ���ʡ�����ء�
 *        Result: ��/nr  ��ƽ/nr  ��/p  1978��/t  3��/t  9��/t  ������/v  ����ʡ/ns  ������/ns  ��/w   
 *  Returns    : the result buffer pointer 
 *
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2003-12-22
 *********************************************************************/
ICTCLAS_API const char * ICTCLAS_ParagraphProcess(const char *sParagraph,int bPOStagged=1);
/*********************************************************************
 *
 *  Func Name  : ParagraphProcessingA
 *
 *  Description: Process a paragraph
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               pResultCount: pointer to result vector size
 *  Returns    : the pointer of result vector, it is managed by system,user cannot alloc and free it 
 *  Author     :  
 *  History    : 
 *              1.create 2006-10-26
 *********************************************************************/
ICTCLAS_API const result_t * ICTCLAS_ParagraphProcessA(const char *sParagraph,int *pResultCount);
/*********************************************************************
 *
 *  Func Name  : ICTCLAS_GetParagraphProcessAWordCount
 *
 *  Description: Get ProcessAWordCount, API for C#
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               pResultCount: pointer to result vector size
 *  Returns    : the pointer of result vector, it is managed by system,user cannot alloc and free it 
 *  Author     :  
 *  History    : 
 *              1.create 2007-3-15
 *********************************************************************/
ICTCLAS_API int ICTCLAS_GetParagraphProcessAWordCount(const char *sParagraph);
/*********************************************************************
 *
 *  Func Name  : ICTCLAS_ParagraphProcessAW
 *
 *  Description: Process a paragraph, API for C#
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               pResultCount: pointer to result vector size
 *  Returns    : the pointer of result vector, it is managed by system,user cannot alloc and free it 
 *  Author     :  
 *  History    : 
 *              1.create 2007-3-15
 *********************************************************************/
ICTCLAS_API void ICTCLAS_ParagraphProcessAW(int nCount,result_t * result);

/*********************************************************************
 *
 *  Func Name  : ICTCLAS_FileProcess
 *
 *  Description: Process a text file
 *    
 *
 *  Parameters : sSourceFilename: The source file name  
 *               sResultFilename: The result file name 
 *				 bPOStagged:Judge whether need POS tagging, 0 for no tag;default:1
 *  i.e. FileProcess("E:\\Sample\\Corpus_NewPOS\\199802_Org.txt","E:\\Sample\\Corpus_NewPOS\\199802_Org_cla.txt");
 *  Returns    : success: 
 *               fail: 
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2005-11-22
 *********************************************************************/
ICTCLAS_API double ICTCLAS_FileProcess(const char *sSourceFilename,const char *sResultFilename,int bPOStagged=1);
/*********************************************************************
 *
 *  Func Name  : ICTCLAS_FileProcessEx
 *
 *  Description: Process a text file
 *               (string,frequency) sort by frequency
 *
 *  Parameters : sSourceFilename: The source file name  
 *               sResultFilename: The result file name 
 *  i.e. FileProcess("E:\\Sample\\Corpus_NewPOS\\199802_Org.txt","E:\\Sample\\Corpus_NewPOS\\199802_Org_cla.txt");
 *  Returns    : success: 
 *               fail: 
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2007-04-07
 *********************************************************************/
ICTCLAS_API double ICTCLAS_FileProcessEx(const char *sSourceFilename,const char *sResultFilename);

/*********************************************************************
 *
 *  class CICTCLAS30
 *   ������
 *		   ICTCLAS30 �࣬ʹ��֮ǰ�������ICTCLAS_Init(),�˳��������ICTCLAS_Exit
 *		   ��ʹ�ù����п���ʹ�ö��CICTCLAS30��֧�ֶ��̷ִ߳ʴ���
 *
 *  History    : 
 *              1.create 2005-11-10
 *********************************************************************/
#ifdef OS_LINUX
class  CICTCLAS30 {
#else
class  __declspec(dllexport) CICTCLAS30 {
#endif
	public:
		CICTCLAS30();
		~CICTCLAS30();
		bool FileProcess(const char *sSourceFilename,const char *sResultFilename,int bPOStagged=1);
		//Process a file��������C�µ�ICTCLAS_FileProcess
		const char * ParagraphProcess(const char *sLine,int bPOStagged=1); 
		//Process a file��������C�µ�ICTCLAS_FileProcess
	private:
		unsigned int m_nHandle;//�ó�Ա��Ϊ�����Handleֵ����ϵͳ�Զ����䣬�û������޸�
};

#endif//#define __ICTCLAS_LIB_INCLUDED__
