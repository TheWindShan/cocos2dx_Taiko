#ifndef REIMU_SCENE_MAINTSCENE_H
#define REIMU_SCENE_MAINTSCENE_H

#include "cocos2d.h"
#include "Data/DataEntityPool.h"
#include "System/SystemEntityPool.h"

/**��Ҫ��Ϸ����*/
class MainScene : public cocos2d::Scene
{

public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer

    static Scene* GetSceneInstance();
    static DataEntityPool* GetDataManage(){ return _dataManage; };
    static SystemEntityPool* GetSystemManage(){ return _systemManage; };
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init() override;

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);

private:
    /**��ʱ���ص�����
    @param speed ����ʲô��
    */
    inline void Run_PerFrame(float speed);

    static   DataEntityPool* _dataManage;
    static   SystemEntityPool* _systemManage;

    /**���̴�����Ӧ����
    @param keyCode ������
    @param event cocos2dx�Դ��¼�
    */
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    static Scene* scene;/**��sceneָ��*/
};
#endif 
