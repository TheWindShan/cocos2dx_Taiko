#ifndef  REIMU_DATA_LAYER_MAINSCENE_BACKGROUND_H
#define  REIMU_DATA_LAYER_MAINSCENE_BACKGROUND_H
#include "cocos2d.h"
#include "Abstract/AbstractPollEntity.h"

/**@brief ������,��Ҫ������Ծ�ֹ�Ĳ���,�綥��ѭ��ͼ��
    @attention �����ʾ����Ҳ�����
*/
class BackGroundLayer : public AbstractPollEntity, public cocos2d::Layer
{
public:
    virtual void runInterface() override;
    virtual void initInterface() override;
    ~BackGroundLayer();

 public:

    cocos2d::Sprite *buttomBG = nullptr;//�ױ���(PV����)

    //���沼��
    cocos2d::Label  * GUcharMap = nullptr;//��������������
    cocos2d::Label  * GUcharMapClone = nullptr;//��������������
    cocos2d::Sprite  *guDisplayBlue = nullptr;//������ɫȦ
    cocos2d::Sprite   *guDisplay = nullptr;//������ʾ��
    cocos2d::Label    * charMap = nullptr;//��������������1

    //�����沼��
    cocos2d::Sprite  *scrollBar_Background = nullptr;//��������
    cocos2d::Node  *scrollBar = nullptr;
    cocos2d::Node  *scrollBarClone = nullptr;
    cocos2d::Sprite  *spirteCache = nullptr; //����Spite
    cocos2d::Vector<cocos2d::Node*>   scrollBarSpriteVector;//�ܵĹĵ㾫�鼯��
    cocos2d::Sprite *gu = nullptr;

    //�겼��
    cocos2d::Sprite *soul = nullptr;
    cocos2d::ProgressTimer *soulProgBar = nullptr;//�������
	cocos2d::ParticleSystemQuad  *touchparticle = nullptr; /**<  ��������Ч��*/

  
protected:
    cocos2d::Sprite *topBG = nullptr;/**< ������ ������lamba�ص� */
    cocos2d::Sprite *topBGclone = nullptr;/**< ������Clone ������lamba�ص� */

    void  LoadSpriteCache(); /**<��Ԥ������֡*/
    void  LoadNode();
    void LoadAnimationCache();
};
#endif