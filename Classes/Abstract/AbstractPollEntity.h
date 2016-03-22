#ifndef REIMU_ABSTRACT_ABSTRACTEVENTPOLLENTITY_H
#define REIMU_ABSTRACT_ABSTRACTEVENTPOLLENTITY_H
#include "Abstract/AbstractPollEntity.h"

class AbstractPollEntity
{
public:
    /**��������*/
    virtual ~AbstractPollEntity(){};

    /**���нӿ�*/
    virtual void runInterface() = 0;

    /**��ʼ���ӿ�*/
    virtual void initInterface() = 0;
};
#endif