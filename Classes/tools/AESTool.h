#include "aes.h"

/**AES���ܹ���
@warning ò�Ʋ���ô�ȶ�
 */
class AESTool
{
public:
     void  encodeString(char *string, char* password, unsigned char*outString);
     void decodeString(unsigned char *string, char* password);
private:
      char code[8192*2*2];
};