#include "DrumSurfaceLoader.h"
#include <regex>
#include "cocos2d.h"

USING_NS_CC;



unsigned short DrumSurfaceLoader::PerDrumCount = 0;
unsigned short DrumSurfaceLoader::BPM = 0;
int DrumSurfaceLoader::PlayDelay = 0;

void  DrumSurfaceLoader::initInterface()
{
    if (!_isEditMode)
    {
        loadDrumData("Song/wencheng.dat");
    }
    else
    {
        for (int i = 0; i < 30000;++i) /**<��̬��ë�ߣ�*/
        {
            auto endPosition = new  DrumSufaceStruct();
            endPosition->type = 0;
            DrumSurfaceEntityVector.push_back(endPosition);
        }    
    }
}

std::string DrumSurfaceLoader::findString(const std::string &content, const std::string &_regex)
{
    //ʹ��������ʽ
    std::regex regExpress(_regex);//����������Ҫ����

    // ������ҵĽ��     
    std::smatch ms;

    std::string main; /**<  ���ת��ΪString*/

    if (std::regex_search(content, ms, regExpress))
    {
        for (size_t i = 0; i < ms.size(); ++i)
        {
            main = ms.str(i);
        }
    }
    return std::move(main);/**< ʹ��move���������ʱ�������������*/
}

DrumSurfaceLoader::~DrumSurfaceLoader()
{
    for (auto &drStruct : DrumSurfaceEntityVector)
    {
        CC_SAFE_DELETE(drStruct);
    }
    DrumSurfaceEntityVector.clear();
}

void DrumSurfaceLoader::loadDrumData(const std::string & filename)
{
    if (_isDirty)
    {
        for (auto &drStruct : DrumSurfaceEntityVector)
        {
            CC_SAFE_DELETE(drStruct);
        }
        DrumSurfaceEntityVector.clear();
    }
#pragma region ��ȡ�����ļ�
    std::string fileContent = FileUtils::getInstance()->getStringFromFile(filename);

    std::string main = findString(fileContent, "MAIN:[a-zA-Z0-9\\r\\n]+(?=MAINEND)"); /**<  ���ת��ΪString*/

    CCASSERT(main.size() != 0, "Have no mainString.");

    std::string perLengthString = findString(fileContent, "PERSIZE:[0-9\\s]+(?=END)");

    CCASSERT(perLengthString.size() != 0, "Have no lengthString.");

    perLengthString = perLengthString.substr(perLengthString.find(":") + 1, perLengthString.size() - perLengthString.find(":"));/**< ���Բ��ùܿո���,���Զ������� */

    std::stringstream ss;
    ss.clear();
    ss.str("");
    ss << perLengthString;
    ss >> DrumSurfaceLoader::PerDrumCount;

    std::string BPMString = findString(fileContent, "BPM:[0-9\\s]+(?=END)"); /**< �ø��BPM*/

    CCASSERT(BPMString.size() != 0, "Have no lengthString.");

    BPMString = BPMString.substr(BPMString.find(":") + 1, BPMString.size() - BPMString.find(":"));/**< ���Բ��ùܿո���,���Զ������� */

    ss.clear();
    ss.str("");
    ss << BPMString;
    ss >> DrumSurfaceLoader::BPM;

    CCASSERT(DrumSurfaceLoader::PerDrumCount != 0, "Have no BPM.");

    std::string playDelayString = findString(fileContent, "PlAYDELAY:[0-9\\s]+(?=END)"); /**< �ø��BPM*/

    CCASSERT(playDelayString.size() != 0, "Have no lengthString.");

    playDelayString = playDelayString.substr(playDelayString.find(":") + 1, playDelayString.size() - playDelayString.find(":"));/**< ���Բ��ùܿո���,���Զ������� */

    ss.clear();
    ss.str("");
    ss << playDelayString;
    ss >> DrumSurfaceLoader::PlayDelay;

    CCASSERT(DrumSurfaceLoader::PlayDelay != 0, "Have no PlayDelay.");

    //��ȡ��������
    int startPosition = 0;
    int endPosition = 0;

    //��ȡÿ������
    std::vector<std::string> dataVector=getLineScript(main,"\r\n");  //�����������к��vector
	dataVector.erase(dataVector.begin());//ɾ����һ�еı�ǩ

    //����ת��Ϊint����
    int *data_int = (int*)malloc(sizeof(int)*dataVector.size() * DrumSurfaceLoader::PerDrumCount);
    int positionx = -1;

    for (auto &itor : dataVector)
    {
        for (size_t i = 0; i < itor.size(); ++i)
        {
            ss.clear();
            ss.str("");
            ss << itor.at(i);
            ss >> data_int[++positionx];
        }
    }
#pragma endregion ��ȡ�����ļ�
#pragma region ��ʼ��Ϸ����
    //��ʼ����
    for (int i = 0; i < (int)dataVector.size() * DrumSurfaceLoader::PerDrumCount; ++i)
    {
        auto endPosition = new  DrumSufaceStruct();
        endPosition->type = data_int[i]; //�ж����ݸ�ֵ
        DrumSurfaceEntityVector.push_back(endPosition);
    }
    free(data_int);
    dataVector.clear();
#pragma endregion
    _isDirty = true;
}


inline   std::vector<std::string> DrumSurfaceLoader::getLineScript(const std::string& scriptString,const std::string& pattern)
{
	std::string tempReslut;
	std::string::size_type  pos;
	std::vector<std::string> stringVector;
	for (size_t i = 0; i<scriptString.length(); ++i)
	{
		pos = scriptString.find(pattern, i);
		if (pos == std::string::npos) break;
		tempReslut = trim(scriptString.substr(i, pos - i));
		if (tempReslut.size()<=0)  continue;
		stringVector.push_back(tempReslut);
		i = pos + std::string(pattern).size() - 1;
		tempReslut.clear();
	}
	return std::move(stringVector);
};

inline  std::string& DrumSurfaceLoader::trim(std::string& text)
{
	if (!text.empty())
	{
		text.erase(0, text.find_first_not_of(" \n\r\t"));
		text.erase(text.find_last_not_of(" \n\r\t") + 1);
	}
	return text;
};










