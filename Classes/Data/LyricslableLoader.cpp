#include "Data/LyricslableLoader.h"
#include <regex>
#include "cocos2d.h"

USING_NS_CC;

void LyricslableLoader::initInterface()
{
	auto txt_vec = FileUtils::getInstance()->getValueVectorFromFile("Song/wenchengLyrics.dat");
	for (const auto& e : txt_vec)
	{
		auto txt_map = e.asValueMap();//����ֵת����Map��ʽ������txt_map��  
		auto lyricsEntity = new LyricsEntityStruct();
		lyricsEntity->lyricsStratTime = txt_map.at("time").asInt();
		lyricsEntity->displaySpeed = txt_map.at("speed").asFloat();
	  	lyricsEntity->lyricsContent = txt_map.at("contant").asString();
		LyricsEntityVector.push_back(lyricsEntity);
	}
    //�ؼ���ʱ����
    for (auto &lyricsEntity : LyricsEntityVector)
    {
        lyricsEntity->lyricsStratTime = lyricsEntity->lyricsStratTime / 60 * 50;
    }
}

LyricslableLoader::~LyricslableLoader()
{
    for (auto &leStruct : LyricsEntityVector)
    {
        CC_SAFE_DELETE(leStruct);
    }
    LyricsEntityVector.clear();
}
