#ifndef  REIMU_DATA_MAINSCNEN_LAYER_UI_H
#define  REIMU_DATA_MAINSCNEN_LAYER_UI_H
#include "cocos2d.h"
#include "Abstract/AbstractPollEntity.h"


/**@brief UI��,���ø�������Ӿ������Ĳ���,����Ʒ��밴ť�ȵ�
*/
class UILayer : public AbstractPollEntity, public cocos2d::Layer
{
 
public:
    cocos2d::Label  * totalMarkcharMap = nullptr; /**< �Ʒ����  */
    cocos2d::ClippingNode *heartNode = nullptr;/**< ���ͽ��*/
    cocos2d::Node  *_StarUINode = nullptr; /**< ����UI��� */

protected:
    virtual void runInterface() override;
    virtual void initInterface() override;
};
#endif