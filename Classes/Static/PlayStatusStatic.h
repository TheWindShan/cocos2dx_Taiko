#ifndef REIMU_STATIC_PLAYSTATUS_H
#define  REIMU_STATIC_PLAYSTATUS_H

/**< ����ͳ�ƽṹ��*/
 typedef struct  _PlayStatus
{
    unsigned short nowHit = 0; /**��ǰHit��*/
    unsigned short maxHit = 0;/**���Hit��*/
    unsigned int Mark = 0;/**�ܷ�*/
    unsigned short perferHit = 0;/**����perfer����*/
    unsigned short goodHit = 0;/**����good����*/
    unsigned short missHit = 0;/**miss����*/
 }PlayStatus;


class PlayStatusStatic
{
public:
      static  PlayStatus  *playStatus;
      PlayStatusStatic();
};
#endif
