#ifndef _REIMU_DATA_DATAMANAGE_H
#define _REIMU_DATA_DATAMANAGE_H

#include "vector"
#include "GameDefine.h"
#include "Abstract/AbstractPollManager.inl"
#include "GameConst.h"


/**���ݹ�����*/
class DataEntityPool :public AbstractPollManager<AbstractPollEntity>
{
 
public:
    /**��������*/
    virtual ~DataEntityPool(){};

    /**��ʼ������*/
    void  init(const SceneType &);

};
#endif 