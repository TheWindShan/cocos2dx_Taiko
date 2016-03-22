#ifndef REIMU_EFFECT_DOOREFFECTSPRITE_H
#define REIMU_EFFECT_DOOREFFECTSPRITE_H

#include "cocos2d.h"


class DoorEffectSprite :public cocos2d::Sprite
{
public:

    /**����Shader����(��Ҫ��Uniform����)
    @param progressNow ��ʾ����(0~100)
    */
    void updateShader(const float progress);

    /**��ʼ��Shader
    @warning  ����ʾ����
    */
    void InitShader();

    void endMainScene();

private:
    float iGlobalTime = 0.0f;
    bool _isFirst = true;
    int _waitTime = 10;
    bool _isEnd = false;
};
#endif 