#ifndef REIMU_SCENE_ACCOUNTSCENE_H
#define REIMU_SCENE_ACCOUNTSCENE_H
#include "cocos2d.h"
#include "Data/DataEntityPool.h"
#include "System/SystemEntityPool.h"

/**���㳡��*/
class AccountScene:public cocos2d::Scene
{
public:
    /**��ȡ��Sceneʵ��
    @return Sceneʵ��
    */
	static cocos2d::Scene*  GetSceneInstance();
    static DataEntityPool* GetDataManage(){ return _dataManage; };
    static SystemEntityPool* GetSystemManage(){ return _systemManage; };

    virtual bool init() override;
    
    /**��ʾnode*/
    static  cocos2d::Node *node;
private:
    /**��̬scene ָ��*/
    static cocos2d::Scene* scene;


    static   DataEntityPool* _dataManage;
    static   SystemEntityPool* _systemManage;

    /**��ʱ���ص�����
    @param speed ����ʲô��
    */
    void Run_PerFrame(float speed);

    /**cocos2dx�Դ���̬Create��*/
    CREATE_FUNC(AccountScene);
};
#endif