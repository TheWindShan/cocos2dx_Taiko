#ifndef REIMU_ABSTRACT_ABSTRACTEVENTDISPATCHER_H
#define REIMU_ABSTRACT_ABSTRACTEVENTDISPATCHER_H
#include "Abstract/AbstractEventListener.h"
#include <map>
#include <string>



/**< �����¼��ַ���*/ 
class AbstractEventDispatcher
{
public:
    /**��������*/
    virtual ~AbstractEventDispatcher(){
		auto& it = m_listeners.begin();
		while (it != m_listeners.end())
		{
			CC_SAFE_DELETE(it->second);
			m_listeners.erase(it++);
		}
		m_listeners.clear();
	};

    /**�ַ��¼�
    @param  listenName ��������
    @param  eventKey �¼�Key�����ṹ
    @param  paramIn ����ṹָ��
    */
	inline void* dispatchEvent(const std::string &listenName, const EVENT_KEY_TYPE & eventKey, void *paramIn) const
    {
        auto& iter = m_listeners.find(listenName);
        if (iter != m_listeners.end())
        {
            auto method = iter->second;
			return method->execEvent(eventKey, paramIn);
        }
		else  return nullptr;
    }

    /**ע�������
	  @param  listenName �����߱�ʶ
      @param  listener ������
      */
	inline void addListener(const std::string &listenName, AbstractEventListener  *listener)
	{
		m_listeners.insert(std::pair<std::string, AbstractEventListener*>(listenName, listener));
	}

    /**�Ƴ�������
    @param  listenName �����߱�ʶ
    */
    inline void removeListener(const std::string &listenName)  //ɾ���������¼�
    {
        m_listeners.erase(listenName);
    }

protected:
	std::map<EVENT_KEY_TYPE, AbstractEventListener*> m_listeners; /**< ������Map����*/
    unsigned int _listenCount = 0; /**< ������ID����*/
};
#endif