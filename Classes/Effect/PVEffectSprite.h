#ifndef REIMU_EFFECT_PVEFFECTSPRITE_H
#define REIMU_EFFECT_PVEFFECTSPRITE_H

#include "cocos2d.h"


class PVEffectSprite :public cocos2d::Sprite
{
public:
    /**���캯��*/
	PVEffectSprite();

    /**����Shader����(��Ҫ��Uniform����)
    @param progressNow ��ʾ����(0~100)
    @param temp  �����ڸ�Effect����ʾ����
    */
    int updateShader(const float progressNow, Sprite * const temp);

    /**��ʼ��Shader
    @warning  ����ʾ����
    */
	void InitShader();

private:
    float PVcount = 0.0f;/**���Ȼ������*/
	float progress = 1.0f; /**alpha����*/
	float region = 0.0f; /**PV��ȡ����*/
	float x_offset = 0.0f; /**x����ƫ��*/
	float y_offset = 0.0f; /**y����ƫ��*/
	unsigned short status= 0;/**0Ϊ��ͨ״̬ 1λ�Գ�״̬  2ΪPV״̬ 3Ϊ����״̬*/
};
#endif 