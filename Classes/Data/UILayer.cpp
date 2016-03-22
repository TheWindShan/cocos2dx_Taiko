#include "Data/UILayer.h"
#include "Scene/MainScene.h"
#include "Effect/DoorEffectSprite.h"

USING_NS_CC;

void UILayer::initInterface()
{
    this->setName("UILayer");
    MainScene::GetSceneInstance()->addChild(this);
#pragma region �Ʒ�������
    totalMarkcharMap = Label::createWithCharMap("totalMark.png", 26, 35, '0');  //��ʼ���ܼƷ����
    totalMarkcharMap->setAnchorPoint(Vec2(1, 0));
    totalMarkcharMap->setString("0");// ��ʼ��Ϊ0��
    totalMarkcharMap->setPosition(Vec2(940, 520));
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
    /**< �������Ч�� */
    auto clippingNode = ClippingNode::create(); //�����Ʒ����Ϊһ�����ý��
    clippingNode->setPosition(Vec2(0, 0));
    auto spark = Sprite::create("spark.png"); //��������ͼƬ
    spark->setPosition(940 - totalMarkcharMap->getContentSize().width, 520);
    spark->setAnchorPoint(Vec2(1, 0));
    auto moveBackAction = MoveTo::create(2.0f, Vec2(930 - totalMarkcharMap->getContentSize().width * 2 - 10, 520));
    auto moveAction = MoveTo::create(2.0f, Vec2(930 + totalMarkcharMap->getContentSize().width * 2 + 10, 520));
    spark->runAction(RepeatForever::create(Sequence::create(moveAction, moveBackAction, NULL)));
    clippingNode->setAlphaThreshold(0.05f); //����alphaբֵ
    clippingNode->setStencil(totalMarkcharMap);
    clippingNode->addChild(totalMarkcharMap, 1);
    clippingNode->addChild(spark, 2);
    this->addChild(clippingNode);
#else
    mainScene->addChild(totalMarkcharMap);
#endif
#pragma endregion �Ʒ�������
#pragma region ����������UI
    _StarUINode = Node::create();
    _StarUINode->ignoreAnchorPointForPosition(true);
    this->addChild(_StarUINode);
    // ��ʼ���������ǵ���β���
    auto streakNodeVector = Node::create();
    streakNodeVector->setName("StreakNodeVector");/**< ��β��㼯��*/
    for (int i = 0; i < 10; ++i) /**< ���10����β�����Ϊ�˽��1���޷���1����ʾ���� */
    {
        auto  streak = MotionStreak::create(1.0f, 2, 10, Color3B(251, 4, 132), SpriteFrameCache::getInstance()->getSpriteFrameByName("test1.png")->getTexture());/**< �ֱ������βЧ��*/
        streak->setVisible(false);
        streakNodeVector->addChild(streak);
    }
    _StarUINode->addChild(streakNodeVector);
    // ��ʼ���������ǽ��
    auto  touchStarNode = Node::create();
    touchStarNode->setName("StarDisplayVector");/**< ��β���ǰ�˵�������ʾ*/
    for (int i = 0; i < 10; ++i) /**< ͬ���������Ӧ */
    {
        auto  touchStar = Sprite::create("Star_1.png");
        touchStar->setVisible(false);
        touchStarNode->addChild(touchStar);
    }
    _StarUINode->addChild(touchStarNode);
    //���ͼ�����
    heartNode = ClippingNode::create(); //�����Ʒ����Ϊһ�����ý��
    auto heartIn = Sprite::create("heart_in.png"); //��������ͼƬ
    heartIn->setScale(0.6f);
    heartIn->setName("heartin");
    auto heart = Sprite::create("heart.png");
    heart->setScale(0.6f);
    heartNode->setAlphaThreshold(0.05f); //����alphaբֵ
    heartNode->setStencil(heart);
    heartNode->addChild(heart, 1);
    heartNode->addChild(heartIn, 2);
    heartNode->setPosition(Vec2(880, 270));
    heartIn->setPosition(Vec2(0, -100));
    this->addChild(heartNode);

    auto heartNodeParticle = ParticleSystemQuad::create("particle/progress_2.plist"); /**<  ���͵�����Ч��*/
    heartNodeParticle->setPosition(heartNode->getPosition());
    this->addChild(heartNodeParticle);
#pragma endregion ����UI
#pragma region �ȴ��������
    auto waitingPage = DoorEffectSprite::create("waiting.png");
    waitingPage->setGlobalZOrder(2);
    waitingPage->setAnchorPoint(Vec2(0, 0));
    waitingPage->setScaleY(1.1f);
    waitingPage->setName("WaitingPage");
    waitingPage->retain();
    this->addChild(waitingPage);

    auto waitingFont = Label::create(); /**< �ȴ�˵������*/
    waitingFont->setString("Loading...");
    waitingFont->setPosition(Vec2(850, 100));
    waitingFont->setColor(Color3B{ 250, 3, 235 });
    waitingFont->retain();
    waitingFont->setGlobalZOrder(4);
    waitingFont->runAction(Sequence::create(Blink::create(5.0, 5),Hide::create(),NULL));
    waitingPage->addChild(waitingFont);
#pragma endregion 


}



void UILayer::runInterface()
{

}
