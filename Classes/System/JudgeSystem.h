#ifndef REIMU_SYSTEM_JUDGESYSTEM_H
#define  REIMU_SYSTEM_JUDGESYSTEM_H
#include "GameDefine.h"
#include "Data/BackGroundLayer.h"
#include "Data/UILayer.h"
#include "Data/DrumSurfaceLoader.h"
#include "Data/MainLayer.h"
#include "cocos2d.h"
#include "Scene/MainScene.h"
#include "Abstract/AbstractEventDispatcher.inl"


/**�ж��Ѷ�ö����*/
enum class JudgeStrength
{
    Judge_Easy,/**����*/
    Judge_Normal,/**һ��*/
    Judge_Hard/**����*/
};


/**���״̬ö����*/
enum class HitStatus
{
    HIT_PERFER,/**����*/
    HIT_GOOD,/**����*/
    HIT_MISS,/**�Ѿ�Miss*/
    HIT_WAIT,/**�ȴ��ж�*/
};

/**����ʹ�ýṹ��*/
typedef struct _drumSortStruct
{
    unsigned short DrumSN = 0;
    float distance = 0.0f;
}DrumSortStruct;



/**�����ж�ϵͳ*/
class JudgeSystem :public AbstractPollEntity
{
public:
    /**���캯��
    @param judgeStrength �Ѷ�ѡ��
    */
    explicit JudgeSystem(const JudgeStrength& judgeStrength);

    virtual void	initInterface() override;

    /**�����ж�*/
    void   OnTouchJudgeMent(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

    static bool isLock;/**< ������*/
   
    /** @brief �ı���Ϸģʽ*/
    void setGameMode();

private:
    BackGroundLayer* _nodeEntity = static_cast<BackGroundLayer*>(MainScene::GetDataManage()->getEntity("BackGroundLayer"));
    UILayer* _uiLayer = static_cast<UILayer*>(MainScene::GetDataManage()->getEntity("UILayer"));
    MainLayer* _mainLayer = static_cast<MainLayer*>(MainScene::GetDataManage()->getEntity("MainLayer"));
    DrumSurfaceLoader* _surfaceEntity = static_cast<DrumSurfaceLoader*>(MainScene::GetDataManage()->getEntity("drumSurface"));/**��������ʵ��*/

    bool _IsAuto = true;/**< �Զ�ģʽ*/
    std::stringstream ss; /**< stringת����*/
    const float _halfScreenPostionX = cocos2d::Director::getInstance()->getVisibleSize().width / 2.0;/**��������ж���*/
    bool _isHitScreen = false;/**< �Ƿ����������Ļ����*/

protected:
    virtual	void   runInterface() override;

private:
#pragma region �ṹ��
    /**�������(target)�ľ���ṹ��*/
    struct  JudgeDistance
    {
        float miss = 0; /**Miss���ھ���*/
        float  leftGood = 0;/**�������ж�(��)*/
        float  rightGood = 0;/**�������ж�(��)*/
        float  leftPerfer = 0;/**�������ж�(��)*/
        float  rightPerfert = 0;/**�������ж�(��)*/
    }_judgeDistance;
#pragma endregion

    /**����Hit��*/
    inline  void addHit(); 
    /**�����ܷ�*/
    inline  void addTotalMark(const unsigned int &mark);


    void	 JudgeThreadExecute();    /**< �����ж�������ĺ���*/

    void	 EditThreadExecute();   /**< �༭ģʽ�ж�����*/

    JudgeStrength _JudgeMode;  /**< �����ж�������ĺ���*/

    HitStatus *_hitStatusArray;/**< ����״̬����*/

    /**ִ�л��к���߼�
    @param num ����״̬������
    */
    void displayHit(const int num);

    int _delay = 3; /**����״̬�ӳ�֡��*/

    enum  BezierSpriteStatus
    {
        Wait_FIRST_Bezier = 0x01,
        Wait_SENCOND_Bezier=0x02,
        Wait_Nothing=0x0F,
        Working = 0x10,
    };

    struct  BezierSpriteStruct /**< �����������˶��ľ���״̬*/
    {
        unsigned short _BezierSpriteCount = 0; /**< ���������ʹ�ü���(�ܼ�ʹ����10�����)*/
        std::vector<BezierSpriteStatus> BezierSpriteStatus_Vector;
    }p_bezierSpriteStruct;

    unsigned short _StarCount = 0; /**�������ǽ�����(�ܼ�ʹ��10�����)*/

    unsigned short _progBarCount = 0;/**����������*/

    HitStatus _hitStatus = HitStatus::HIT_MISS;/**< ����Ĵ��״̬*/

    cocos2d::Vec2 _touchPos = cocos2d::Vec2::ZERO;/**�������ʱ������*/

    float scrollSpeed = 0.0f;/**���������ٶ�*/
};


#endif