#ifndef REIMU_ABSTRACT_ABSTRACTEVENTLISTENER_H
#define REIMU_ABSTRACT_ABSTRACTEVENTLISTENER_H
#include"Abstract\AbstractEvent.h"
#include <functional>
#include <map>
#include <vector>
#include "cocos2d.h"


/**�¼�������
*@brief ִ�зַ��������������
*/
class AbstractEventListener
{
public:
    /**��������*/
    virtual ~AbstractEventListener(){
		_eventMap.clear();
		for (auto &event : _eventList)
		{
			CC_SAFE_DELETE(event); 
		}
		_eventList.clear();
	};

    /**ִ���¼�
     @param eventID  �¼�ID�ṹ
     @param parmIN ����ṹָ��
    */
	inline virtual void*  execEvent(const EVENT_KEY_TYPE& event, void *parmIN)
    {
		auto& iter = _eventMap.find(event);
		if (iter != _eventMap.end())
		{
			auto& method = iter->second;
			return  method(parmIN);
		}
		else return nullptr;
    };

	/*
	*@brief ע���������
	* @param event  �¼��ṹ
	*@param method �ص�����ָ��
	*/
	virtual  void registerEvent(AbstractEvent * const event, std::function<void*(void*)> method)
	{
		_eventList.push_back(event);
		_eventMap.insert(std::pair<EVENT_KEY_TYPE, std::function<void*(void*)>>(event->getEventName(), method));
	}

protected:
	std::string _listenName;/**< ������*/
	std::map<EVENT_KEY_TYPE, std::function<void*(void*)>> _eventMap; /**< �����¼���--��������*/
	std::vector<AbstractEvent*> _eventList;/**< �����¼�ָ��,����ͳһ�ͷ�*/
};
#endif