#ifndef REIMU_STATIC_ACCOUNTSYSTEM_H
#define REIMU_STATIC_ACCOUNTSYSTEM_H

#include "Abstract/AbstractPollEntity.h"
#include "Data/AccountSceneMainLayer.h"
#include "Scene/AccountScene.h"


/**��������ϵͳ*/
class AccountSystem :public AbstractPollEntity
{
protected:
    virtual void runInterface() override;
    virtual void initInterface() override;
    AccountSceneMainLayer* _mainLayer = static_cast<AccountSceneMainLayer*>(AccountScene::GetDataManage()->getEntity("AccountSceneMainLayer"));
    bool _isShake = false; /**< ������������ */
    cocos2d::Vec2 _originPostion = cocos2d::Vec2::ZERO;/**< ����ԭʼ��ַ,�Ա㻹ԭ */
    short _shakeTime = 0;/**<  ��������ʱ�� */
    /**@brief ���ɷ�Χ�ڵ������
        @param min ��Сֵ
        @param max ���ֵ
        */
   unsigned short _tempMaxHit = 0;
   unsigned short _tempPerferHit = 0;
   unsigned short _tempGoodHit = 0;
   unsigned int _tempMark = 0;
   std::stringstream ss;
};
#endif
