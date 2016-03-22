#ifndef REIMU_ABSTRACT_ABSTRACTEVENTPOLLMANAGER_H
#define REIMU_ABSTRACT_ABSTRACTEVENTPOLLMANAGER_H
#include "Abstract/AbstractPollEntity.h"
#include <vector>
#include "cocos2d.h"

template<class T> class AbstractPollManager
{
public:
    /**��������
      @warning ��Ҫdelete����Ż�ִ��
      */
    virtual ~AbstractPollManager()
    {  
        _vect.clear();
		_entityMap.clear(); /**< ��ѯ���������е�ָ����destory()���������ͷ�*/
    };

    /**ע����ѯ����
    @param _system ��ѯ����
    */
    inline virtual void registe(T *const _system)//ע��Sysyem
    {
        _vect.push_back(_system);
    };

    /**ע����ѯ����
    @param _system ��ѯ����
    @param entityName �����ʶ
    */
    inline virtual void registe(T *const _system, const std::string & entityName)//ע��Sysyem
    {
        registe(_system);
        if (entityName == "") return;
        CCASSERT(_entityMap.find(entityName) == _entityMap.end(), "the entity map had one which could be repeat.");
        _entityMap.insert(std::pair<std::string, T*>(entityName, _system));
    };

    /**ע��ָ�����
    */
    inline virtual void registePoint(const std::string & pointName, void *_point)
    {
        if (pointName == "") return;
        CCASSERT(_pointMap.find(pointName) == _pointMap.end(), "the point map had one which could be repeat.");
        _pointMap.insert(std::pair<std::string, void*>(pointName, _point));
    };

    /**��ȡָ�����
    */
    inline virtual void* getPoint(const std::string & pointName)
    {
        auto 	iter = _pointMap.find(pointName);
        if (iter != _pointMap.end())
        {
            return iter->second;
        }
        else
        {
            CCASSERT(1 == 0, "the point map hasn't  one.");
            return nullptr;
        }
    };


    /**����ʵ��*/
    virtual inline void destory()
    {
        for (auto &system : _vect)
        {
            if (!dynamic_cast<cocos2d::Layer*>(system)) CC_SAFE_DELETE(system); /**< Layer�����Դ��cocos2dx�ͷ�*/
        }
        _vect.clear();
        _entityMap.clear();
    };

    /**��ȡ��ѯ����
    @param entityName �����ʶ
    */
    virtual  inline T* getEntity(const std::string & entityName) const
    {
        auto& iter = _entityMap.find(entityName);
        if (iter != _entityMap.end())
        {
            return iter->second;
        }
        else
        {
            CCASSERT(1 == 0, "the entity map hasn't  one.");
            return nullptr;
        }
    };

    /**ִ�з���*/
    virtual  inline void  run() 
    {
        for (const auto &system : _vect)
        {
            system->runInterface();
        }
    }

    /**��ʼ������*/
    virtual void  init() const
    {
        for (const auto &system : _vect)
        {
            system->initInterface();
        }
    }

protected:
    std::vector<T*> _vect; /**��ѯ��������Vector(���ڸ�Ч��ִ��)*/
    std::map<std::string, T*> _entityMap; /**��ѯ��������Map(���ڸ��ݱ�ʶ��ȡ����)*/
    std::map<std::string, void*> _pointMap;//ָ��map
};
#endif