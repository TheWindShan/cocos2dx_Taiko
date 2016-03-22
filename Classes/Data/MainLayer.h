#ifndef  REIMU_DATA_MAINSCENE_LAYER_MAIN_H
#define  REIMU_DATA_MAINSCENE_LAYER_MAIN_H
#include "cocos2d.h"
#include "Abstract/AbstractPollEntity.h"

/**@brief ��Ϸ��Ҫ��Layer,��������ˮƽ����Ĳ���,���������Լ���ص�״̬��ʾ
*/
class MainLayer : public AbstractPollEntity, public cocos2d::Layer
{
public:
    cocos2d::Sprite *_leftStateSprite = nullptr; /**< �����ʾ״̬����(��ǰ����ʾһ����) */

protected:
    virtual void runInterface() override;
    virtual void initInterface() override;
};
#endif