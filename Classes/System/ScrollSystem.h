#ifndef REIMU_SYSTEM_SCROLLSYSTEM_H
#define REIMU_SYSTEM_SCROLLSYSTEM_H
#include "Effect/PVEffectSprite.h"
#include "System/SystemEntityPool.h"
#include "Data/DrumSurfaceLoader.h"
#include "Data/BackGroundLayer.h"
#include "Scene/MainScene.h"
#include "Data/UILayer.h"



class ScrollSystem :public AbstractPollEntity
{
public:
    short BPMCount = 0;/**< BPM����*/

protected:
    float _scrollSpeed = 0.0f; /**< �����������ٶ�*/
    float  _srollBarPostionX = 0.0f;/**< ������λ��*/
    float  criticalPoint = 0;/**< ��ͼ�����ٽ��(�������ٽ����˵����һͼ�Ѿ���ʾ���,��ʼ�ڶ�����ͼ���ĳ�ʼ���ͼ���)*/
    float  mapSetPoint = 0;/**< ��ͼ�趨�ٽ��*/
    bool scrollLock = false; /**< �����ж���*/
   
protected:
    virtual void initInterface() override final;
    virtual void runInterface() override final;

private:
    BackGroundLayer* _nodeEntity = static_cast<BackGroundLayer*>(MainScene::GetDataManage()->getEntity("BackGroundLayer"));/**< ��������ʵ�� ֱ�Ӵ�Scene��ͨ��getChild��ȡLayerҲ��һ����,��ͬһ������*/
    DrumSurfaceLoader* _surfaceEntity = static_cast<DrumSurfaceLoader*>(MainScene::GetDataManage()->getEntity("drumSurface"));/**< ��������ʵ��*/
    UILayer* _uiLayer = static_cast<UILayer*>(MainScene::GetDataManage()->getEntity("UILayer"));/**��������ʵ��*/


    unsigned short _SrollState = 0x111;/**��������״̬*/
    std::stringstream ss; /**stringת����*/

    /**����״̬���
    �ж��Ƿ���Ҫ��ʼ��,���г�ʼ��,Ȼ�����Է�����,1�����,��ʼ��2��
    */
    inline  void CheckSroll()
    {
        _SrollState = (_SrollState | 0x000) == 0x000 ? 0x111 : _SrollState;
    }

    /**���г�ʼ��,Ȼ�����Է�����,2�����,��ʼ��1��*/
    inline void CheckSrollClone()
    {
        _SrollState = (_SrollState & 0x110) == 0x100 ? 0x010 : _SrollState;
    }

    inline bool  IsSrollChange() const
    {
        return (_SrollState & 0x010) == 0x010;
    }

    inline bool IsSrollInit() const
    {
        return (_SrollState & 0x001) == 0x000;
    }

    inline void SetInitOver()
    {
        _SrollState = _SrollState & 0x101;
    }

private:
    inline void addBPMCount();/** < ��ʾ��ǰ��BPM��,����������*/
};
#endif

///**
//**����״̬˵��
//**/
//typedef struct _DrumSrollState
//{
//	enum {
//		SrollInit = 0x000, //1���ʼ��
//		SrollCloneInit = 0x100, //2���ʼ��
//		SrollOverInit = 0x111,//1���ѳ�ʼ��
//		SrollCloneOverInit = 0x010//2���ѳ�ʼ��
//	};
//}DrumSrollState;