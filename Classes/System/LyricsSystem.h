#ifndef REIMU_SYSTEM_LYRICSSYSTEM_H
#define REIMU_SYSTEM_LYRICSSYSTEM_H
#include "Data/LyricslableLoader.h"
#include "Data/BackGroundLayer.h"
#include "Abstract/AbstractEventDispatcher.inl"
#include "Scene/MainScene.h"

class LyricsSystem :public AbstractPollEntity
{
public:

    /**����BGM
    @param fileName  �ļ���
    */
    void playBGM(const std::string & fileName);

    unsigned int _playTime = 0;/**< �Ѳ���ʱ��*/

protected:
	virtual void runInterface() override final;
    virtual void initInterface() override final;

private:
    LyricslableLoader *_lyricsEntity = static_cast<LyricslableLoader*>(MainScene::GetDataManage()->getEntity("lyricslable"));/**�������ʵ��*/
    BackGroundLayer* _nodeEntity = static_cast<BackGroundLayer*>(MainScene::GetDataManage()->getEntity("BackGroundLayer"));/**��������ʵ��*/
    bool _isPlay = false;/**< ���ű�ʶ*/
    unsigned int _playNum = 0;/**< �������*/
    unsigned short _playSN = 0;/**< ��ʹ����ʾ�������(��ǰ�ܼ���5�������ʾ���)*/
    unsigned short _playBGMDelay = 0;/**< ����BGM���ӳ�*/
};
#endif