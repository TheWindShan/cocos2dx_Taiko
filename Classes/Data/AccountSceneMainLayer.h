#ifndef  REIMU_DATA_ACCOUNTSCENE_MAINLAYER_MAIN_H
#define  REIMU_DATA_ACCOUNTSCENE_MAINLAYER_MAIN_H
#include "cocos2d.h"
#include "Abstract/AbstractPollEntity.h"

/**@brief ��Ϸ��Ҫ��Layer,��������ˮƽ����Ĳ���,���������Լ���ص�״̬��ʾ
*/
class AccountSceneMainLayer : public AbstractPollEntity, public cocos2d::Layer
{
public:


protected:
    virtual void runInterface() override;
    virtual void initInterface() override;

};
#endif