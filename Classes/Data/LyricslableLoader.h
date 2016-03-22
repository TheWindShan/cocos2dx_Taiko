#ifndef   REIMU_DATA_LYRICSLABLELOADER_H
#define  REIMU_DATA_LYRICSLABLELOADER_H
#include "Data/DataEntityPool.h"
#include "Abstract/AbstractPollEntity.h"


/**������ݽṹ��*/
struct LyricsEntityStruct
{
    unsigned int lyricsStratTime; /**��ʿ�ʼʱ��(��֡��ͳ��)*/
    float displaySpeed;/**�����ʾʱ��*/
    std::string lyricsContent;/**�������*/
};


/**������ݶ�ȡ��*/
class LyricslableLoader : public AbstractPollEntity
{
public:
    /**��������*/
    ~LyricslableLoader();

    /**��ȡ�������
    @return �����������Vector
    */
    inline  std::vector<LyricsEntityStruct*>* GetLyricsEntityVector()  { return &LyricsEntityVector; };

protected:
    virtual void runInterface() override  final {};
    virtual void initInterface() override  final;
    std::vector<LyricsEntityStruct*>LyricsEntityVector;/**������ݼ���*/
};
#endif