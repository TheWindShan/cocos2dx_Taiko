#ifndef REIMU_SYSTEM_SYSTEMMANAGE_H
#define REIMU_SYSTEM_SYSTEMMANAGE_H

#include "Data/DataEntityPool.h"
#include <vector>
#include "GameDefine.h"
#include "GameConst.h"
#include "Abstract/AbstractPollManager.inl"
#include "Abstract/AbstractEventDispatcher.inl"



class SystemEntityPool:public AbstractPollManager<AbstractPollEntity>
{
 
public:

    virtual ~SystemEntityPool(){};

    /**���ݳ�����ʼ��ͬ��System
    @param type ����ö����
    */
    void init(const SceneType  &type);


    /**��д���з���*/
    inline void  run()    override
    {
        for (const auto &system : _vect)
        {         
            system->runInterface();
            if (!isSystemRuning) break;
        }
        if (!isSystemRuning) destory();
    }

    /**���н���,ִ�з����������ó������ͷ�
    @warning ��ʱֻ�����Ҫ��Ϸ����
    */
    void destory();

public:
    bool isSystemRuning = true; /**ϵͳ���б�ʶ*/
    SceneType _sceneType;
};
#endif