#include "Data/MainLayer.h"
#include "Scene/MainScene.h"

USING_NS_CC;


void MainLayer::runInterface()
{

}

void MainLayer::initInterface()
{
#pragma region ��߾������

    this->setName("MainLayer");
    MainScene::GetSceneInstance()->addChild(this);

    _leftStateSprite = Sprite::create();	//��ʼ������
    _leftStateSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mtaiko.png"));
    _leftStateSprite->setPosition(Vec2(46.90f, 463.08f));
    _leftStateSprite->setScaleY(1.2517f);
    _leftStateSprite->setLocalZOrder(2);//�������ֲ�
    this->addChild(_leftStateSprite);

    auto upDisplay = Sprite::create(); /**< _leftStateSprite�Ķ���ʾ�� */
    upDisplay->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mtaikoflower.png"));
    upDisplay->setName("upDisplay");
    upDisplay->setPosition(Vec2(50,50));
    upDisplay->setVisible(false);
    _leftStateSprite->addChild(upDisplay);



    auto target = Sprite::create(); /**<���ĸ������*/
    target->setName("Target");/**<����*/
    target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("target.png"));
    target->setPosition(Vec2(180, 40));
    _leftStateSprite->addChild(target);
	auto hitEffect = ParticleSystemQuad::create("particle/ring.plist"); /**< ������Ч����Ч��*/
    hitEffect->setLocalZOrder(1);
    hitEffect->setPosition(Vec2(22,20));
    target->addChild(hitEffect);


    auto hitCharMap = Label::createWithCharMap(SpriteFrameCache::getInstance()->getSpriteFrameByName("combonumber_balloon.png")->getTexture(), 20, 24, '0'); //��ʼ�������������
   hitCharMap->setAnchorPoint(Vec2(0.5, 0.5));
   hitCharMap->setString("0");// ��ʼ��Ϊ0��
   hitCharMap->setPosition(Vec2(50, 55));
   hitCharMap->setName("HitCharMap");
   _leftStateSprite->addChild(hitCharMap);
#pragma endregion ��߾������
   
#pragma region ��������ؾ���
    auto bezierVector = Node::create(); /**<������ı��������*/
    bezierVector->setAnchorPoint(Vec2(0, 0));
    bezierVector->ignoreAnchorPointForPosition(true);
    bezierVector->setName("BezierVector");
    target->addChild(bezierVector);

    for (int i = 0; i < 10; ++i) /**< ��ʼ����� 10�� */
    {
        auto bezierSpite = Sprite::create();
        auto hitEffect = ParticleSystemQuad::create("particle/trail.plist");/**<���ĸ���������Ч��*/
        hitEffect->setLocalZOrder(1);
        hitEffect->setPosition(Vec2(200,0));
        bezierSpite->addChild(hitEffect);
        bezierSpite->setVisible(false);
        bezierSpite->setAnchorPoint(Vec2(0, 0));
        bezierSpite->ignoreAnchorPointForPosition(true);
        bezierVector->addChild(bezierSpite);
    }

    auto targetJadgeFont = Sprite::create();/**< �����Ϸ����ж�������ʾ */
    targetJadgeFont->setPosition(Vec2(23, 70));
    targetJadgeFont->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("target_good_small.png"));
    targetJadgeFont->setVisible(false);
    targetJadgeFont->setName("JadgeFont");
    target->addChild(targetJadgeFont);

    auto targetUpDisplay = Sprite::create();/**< ���ĵĶ���ʾ�� */
    targetUpDisplay->setPosition(Vec2(25 ,25));
    targetUpDisplay->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("target_flash.png"));
    targetUpDisplay->setVisible(false);
    targetUpDisplay->setName("TargetUpDisplay");
    target->addChild(targetUpDisplay);
#pragma endregion ��������ؾ���
}

