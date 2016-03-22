#ifndef   REIMU_DATA_DRUMSURFACELOADER_H
#define  REIMU_DATA_DRUMSURFACELOADER_H

#include "Data/DataEntityPool.h"
#include "Abstract/AbstractPollEntity.h"
#include <regex>


/**
�ĵ����ݽṹ��
*/
struct DrumSufaceStruct
{
    short type = 0;/** 0��ʾ�հ�,1Ϊ���,2Ϊ���� */
};

/**�ĵ����ݶ�ȡ��*/
class DrumSurfaceLoader :public AbstractPollEntity
{
public:
    /**��ȡ������������
    @return �ĵ���������Vector������
    */
    inline  std::vector<DrumSufaceStruct*>* GetSurfaceEntityVector()   { return &DrumSurfaceEntityVector; };
    
    static  unsigned short PerDrumCount;/**< ÿ������Ĺ���*/
    static  unsigned short BPM;/**< �ø��BPM*/
    static  int PlayDelay;/**< �ø��BPM*/

    void  loadDrumData(const std::string & filename);


protected:

    /**��������*/
    ~DrumSurfaceLoader();;

protected:
    std::vector<DrumSufaceStruct*> DrumSurfaceEntityVector;/**�ĵ���������Vector*/
	inline std::vector<std::string> getLineScript(const std::string& scriptString, const std::string& pattern);
	inline std::string& trim(std::string& text);
    virtual void runInterface() override  final {};
    virtual void initInterface() override  final;

    /**@brief ����������ʽѰ�Ҷ�Ӧ���ַ���
       *@param content ��Ѱ������
       *@param _regex ������ʽ
       */
    std::string  findString(const std::string  &content, const std::string &_regex);

    bool _isDirty = false; /**< �Ƿ���������*/
    bool _isEditMode = false; /**< �Ƿ�Ϊ�༭ģʽ*/

};

#endif