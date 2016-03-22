#include "System/JudgeSystem.h"
#include "SimpleAudioEngine.h"
#include "Effect/PVEffectSprite.h"
#include "System/ScrollSystem.h"
#include "Static/PlayStatusStatic.h"
#include "Untils/RandomUntil.inl"

USING_NS_CC;

bool JudgeSystem::isLock = false;

void	JudgeSystem::initInterface()
{
	std::thread JudgeThread(&JudgeSystem::JudgeThreadExecute, this); // �˴��ɸ���Ϊ�༭�߳�
	JudgeThread.detach();
	if (_JudgeMode == JudgeStrength::Judge_Easy) //���ݹ����ٶȶ�̬�����ж�����
	{
		_judgeDistance.miss = -scrollSpeed*0.5;
		_judgeDistance.leftGood = -scrollSpeed*0.2;
		_judgeDistance.rightGood = scrollSpeed*1.0;
		_judgeDistance.leftPerfer = -scrollSpeed*0.15;
		_judgeDistance.rightPerfert = scrollSpeed*0.8;
	}
	else  if (_JudgeMode == JudgeStrength::Judge_Normal)
	{
		_judgeDistance.miss = -scrollSpeed*0.4;
		_judgeDistance.leftGood = -scrollSpeed*0.15;
		_judgeDistance.rightGood = scrollSpeed*0.8;
		_judgeDistance.leftPerfer = -scrollSpeed*0.12;
		_judgeDistance.rightPerfert = scrollSpeed*0.7;
	}
	else if (_JudgeMode == JudgeStrength::Judge_Hard)
	{
		_judgeDistance.miss = -20;
		_judgeDistance.leftGood = -20;
		_judgeDistance.rightGood = 40;
		_judgeDistance.leftPerfer = -10;
		_judgeDistance.rightPerfert = 30;
	}
	for (int i = 0; i < 10; ++i)
	{
		p_bezierSpriteStruct.BezierSpriteStatus_Vector.push_back(BezierSpriteStatus::Wait_Nothing);
	}

}

JudgeSystem::JudgeSystem(const JudgeStrength& judgeStrength)
{
	_JudgeMode = judgeStrength;
}


void JudgeSystem::JudgeThreadExecute()
{
	auto maxSurfaceSize = _surfaceEntity->GetSurfaceEntityVector()->size();//��ȡ�ĵ�����ֵ
	DrumSufaceStruct *_tempDrumStruct = nullptr;//��ʱ����ṹ����
	float distance = 0.0f;//����
	Node* CheckedNode = nullptr;
	bool  onesFlag = false;//��־���±�����һ��
	auto target = _mainLayer->_leftStateSprite->getChildByName("Target"); /**< ����Sprite,���ڼ���ˮƽ����*/
	_hitStatusArray = new HitStatus[DrumSurfaceLoader::PerDrumCount * 2];
	auto system = MainScene::GetSystemManage();
	std::mutex _mutex;/**<�̻߳���ṹ��*/

	//��ʼ��
	while (true)//ѭ����������ĵ����
	{
		if (!system->isSystemRuning)  break;
		onesFlag = true;
		for (int i = 0; i < DrumSurfaceLoader::PerDrumCount * 2; ++i)
		{
			CheckedNode = _nodeEntity->scrollBarSpriteVector.at(i);//���ݹĵ�����������Ӧ����ʾNode
			auto isVisible = false;
			if (_mutex.try_lock())
			{
				isLock = true;
				isVisible = CheckedNode->isVisible();
				isLock = false;
				_mutex.unlock();
			}
			else continue;

			if (!isVisible)
			{
				_hitStatusArray[i] = HitStatus::HIT_WAIT;
				continue;
			}
			distance = target->convertToNodeSpace(CheckedNode->convertToWorldSpace(Point(0, 0))).x;//������е���Ե�ˮƽ����
			if (distance > -100 && distance < _judgeDistance.miss)
			{
				_hitStatusArray[i] = HitStatus::HIT_MISS;
				if (onesFlag&&_progBarCount > 0)
				{
					onesFlag = false;
					--_progBarCount;
				}
				if (PlayStatusStatic::playStatus->nowHit > PlayStatusStatic::playStatus->maxHit)PlayStatusStatic::playStatus->maxHit = PlayStatusStatic::playStatus->nowHit;
				PlayStatusStatic::playStatus->nowHit = 0;
				++PlayStatusStatic::playStatus->missHit;
			}
			else if (distance < _judgeDistance.rightPerfert&&distance > _judgeDistance.leftPerfer)//����ƥ��Perfer
			{
				_hitStatusArray[i] = HitStatus::HIT_PERFER;
			}
			else if (distance < _judgeDistance.rightGood&&distance > _judgeDistance.leftGood)
			{
				_hitStatusArray[i] = HitStatus::HIT_GOOD;
			}
			else if (distance > _judgeDistance.rightPerfert)
			{
				_hitStatusArray[i] = HitStatus::HIT_WAIT;
			}
		}
	}
	CC_SAFE_DELETE_ARRAY(_hitStatusArray);
}



void JudgeSystem::addHit()
{
	++PlayStatusStatic::playStatus->nowHit;
	ss.clear();
	ss.str("");
	ss << PlayStatusStatic::playStatus->nowHit;
	static_cast<Label*>(_mainLayer->_leftStateSprite->getChildByName("HitCharMap"))->setString(ss.str());
	static_cast<Label*>(_mainLayer->_leftStateSprite->getChildByName("HitCharMap"))->runAction(Sequence::create(
		ScaleTo::create(0.1f, 1.0f, 1.3f),
		ScaleTo::create(0.1f, 1.0f, 1.0f),
		NULL));//��������Ч��
}


void JudgeSystem::OnTouchJudgeMent(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	for (const auto &item : touches)
	{
		_touchPos = item->getLocation(); //��ȡOpengl����
		_isHitScreen = true;
		_delay = 3;
	}
}


void JudgeSystem::runInterface()
{
	ss.clear();
	ss.str("");
	ss << PlayStatusStatic::playStatus->nowHit;
	static_cast<Label*>(_mainLayer->_leftStateSprite->getChildByName("HitCharMap"))->setString(ss.str());

	if (!_IsAuto&&!_isHitScreen) return; //ֻ���ֶ�ģʽ�ſ�ִ�������ж�

	for (int i = 0; i < 2 * DrumSurfaceLoader::PerDrumCount; ++i)
	{
		_hitStatus = _hitStatusArray[i];
		if (_hitStatus == HitStatus::HIT_PERFER || (!_IsAuto&&_hitStatus == HitStatus::HIT_GOOD))
		{
			displayHit(i);
			break;
		}
	}
	_isHitScreen = (--_delay < 0) ? false : _isHitScreen;
}


void JudgeSystem::addTotalMark(const unsigned int &mark)
{
	ss.clear();
	ss.str("");
	PlayStatusStatic::playStatus->Mark += (mark + PlayStatusStatic::playStatus->nowHit * 10);
	ss << PlayStatusStatic::playStatus->Mark;
	auto totalMarkcharMap = _uiLayer->totalMarkcharMap;
	totalMarkcharMap->setString(ss.str());
	totalMarkcharMap->stopAllActions();
	totalMarkcharMap->setScale(0.9f);
	totalMarkcharMap->setOpacity(255);
	totalMarkcharMap->runAction(Spawn::create(ScaleTo::create(0.6f, 1.1f), FadeOut::create(2.0f), NULL));
}




void JudgeSystem::displayHit(const int hitNum)
{
	auto CheckedNode = _nodeEntity->scrollBarSpriteVector.at(hitNum);
	CheckedNode->setVisible(false);
	auto   tag = CheckedNode->getTag();
	CheckedNode->stopAllActions();
	addHit();

#pragma region ����Ķ����߼�(����UI���������2�����߼���)
	auto bezierNodeVector = _mainLayer->_leftStateSprite->getChildByName("Target")->getChildByName("BezierVector")->getChildren();
	bool onlyOne = false; /**< ÿֻ֡����һ����������*/
	for (int i = 0; i < 10; ++i)
	{
		auto& bezierDisplaySpriteStatus = p_bezierSpriteStruct.BezierSpriteStatus_Vector.at(i);//ֱ������
		if ((bezierDisplaySpriteStatus&BezierSpriteStatus::Working) == BezierSpriteStatus::Working) continue;
		auto  bezierDisplaySprite = static_cast<Sprite*>(bezierNodeVector.at(i));//��Ϊ��ָ��,����Ҫauto &
		bezierDisplaySprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("redGu.png"));
		if (!onlyOne)
		{
			if ((bezierDisplaySpriteStatus&BezierSpriteStatus::Wait_Nothing) == BezierSpriteStatus::Wait_Nothing)
			{
				bezierDisplaySprite->setVisible(true);
				bezierDisplaySprite->setOpacity(255);
				bezierDisplaySprite->setPosition(Vec2::ZERO);
				bezierDisplaySpriteStatus = BezierSpriteStatus::Wait_FIRST_Bezier;
				onlyOne = true;
			}
		}
		if ((bezierDisplaySpriteStatus&BezierSpriteStatus::Wait_SENCOND_Bezier) != BezierSpriteStatus::Wait_SENCOND_Bezier && (bezierDisplaySpriteStatus&BezierSpriteStatus::Wait_FIRST_Bezier) == BezierSpriteStatus::Wait_FIRST_Bezier)
		{
			ccBezierConfig config1{ Vec2(0, RandomUntil::fgRangeRand(70, 100)), Vec2(RandomUntil::fgRangeRand(-50, -30), 90), Vec2(50, 110) }; /**< �������������*/
			if (tag == 1)    //���������ڵ�����
			{
				_nodeEntity->scrollBar_Background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sfieldflash_red.png"));
				bezierDisplaySprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("redGu.png"));
			}
			else
			{
				_nodeEntity->scrollBar_Background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sfieldflash_blue.png"));
				bezierDisplaySprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blueGu.png"));
			}
			bezierDisplaySprite->runAction(Sequence::create(BezierBy::create(1.5, config1),
				CallFunc::create([=](){
				ccBezierConfig config2{ Vec2(585, 0), Vec2(100, 30), Vec2(450, -80) };
				bezierDisplaySprite->runAction(Sequence::create(Spawn::create(BezierBy::create(1.5, config2), FadeOut::create(1.5f), NULL), Hide::create(),
					CallFunc::create([=](){// ��ֵ���ݲ����ⲿ������ľֲ�����,���ܻ��е���ʧ��(���浱ǰ�ֲ�״̬,��Ȼֻ��Ҫһ������)
					p_bezierSpriteStruct.BezierSpriteStatus_Vector.at(i) = BezierSpriteStatus::Wait_Nothing;
				}), NULL));
				p_bezierSpriteStruct.BezierSpriteStatus_Vector.at(i) = BezierSpriteStatus::Wait_SENCOND_Bezier;
			}), NULL));
			bezierDisplaySpriteStatus = (BezierSpriteStatus)(bezierDisplaySpriteStatus | BezierSpriteStatus::Working);
		}
	}

#pragma endregion ����Ķ����߼�

#pragma region ����UI�Լ����Ͳ۶����߼�

	auto position = _uiLayer->heartNode->getPosition();

	//����������
	ccBezierConfig config{ position, Vec2(position.x - 200, position.y + 20), Vec2(position.x - 50, position.y + 50) };

	auto StarUINode = _uiLayer->_StarUINode;/**< ��ȡ����UI�ܽ�� */

	auto touchstarNodeVector = StarUINode->getChildByName("StarDisplayVector")->getChildren();
	auto  touchstarNode = static_cast<Sprite*>(touchstarNodeVector.at(_StarCount));
	touchstarNode->setVisible(true);
	touchstarNode->setPosition(_touchPos);

	auto touchStreakNodeVector = StarUINode->getChildByName("StreakNodeVector")->getChildren();
	auto   touchStreakNode = static_cast<MotionStreak*>(touchStreakNodeVector.at(_StarCount));
	touchStreakNode->setVisible(true);
	touchStreakNode->setPosition(_touchPos);
	touchstarNode->stopAllActions();
	touchStreakNode->stopAllActions();
	//��ʼ��������Ϣ
	touchstarNode->setOpacity(0);
	touchstarNode->runAction(Sequence::create(Spawn::create(BezierTo::create(1.0, config), RotateBy::create(1.0, 1080), FadeIn::create(1.0f), NULL)
		, Hide::create(), NULL));
	touchStreakNode->setVisible(true);
	touchStreakNode->runAction(Sequence::create(BezierTo::create(1.0, config), Hide::create(), NULL));

	_StarCount = (++_StarCount >= 10) ? 0 : _StarCount;
	(static_cast<MotionStreak*>(touchStreakNodeVector.at(_StarCount)))->reset();

	/**< ÿ�λ�����ȷ���β�����0.5���� */
	_uiLayer->heartNode->getChildByName("heartin")->setPositionY(_uiLayer->heartNode->getChildByName("heartin")->getPositionY() + 0.5f);
#pragma endregion ����UI�����߼�(����~~)

#pragma region ����Ч��

	//��ʾ��������Ч��
	_nodeEntity->touchparticle->resetSystem();
	_nodeEntity->touchparticle->setPosition(_touchPos);
#pragma endregion ����Ч��



#pragma region �ж����仯�Ķ����߼�
	if (PlayStatusStatic::playStatus->nowHit / 100 > 0 && PlayStatusStatic::playStatus->nowHit % 100 < 50)    _mainLayer->_leftStateSprite->getChildByName("upDisplay")->setVisible(true); //���Ĺ�����ʾ
	else    _mainLayer->_leftStateSprite->getChildByName("upDisplay")->setVisible(false);

	if (PlayStatusStatic::playStatus->nowHit > 100)  static_cast<Label*>(_mainLayer->_leftStateSprite->getChildByName("HitCharMap"))->setCharMap("combonumber_l.png", 25, 38, '0'); //���Ĺ�������
	else      static_cast<Label*>(_mainLayer->_leftStateSprite->getChildByName("HitCharMap"))->setCharMap("combonumber_balloon.png", 20, 24, '0');
#pragma endregion �ж����仯�Ķ����߼�

#pragma region �����������߼�
	if (_progBarCount < 100)
	{
		++_progBarCount;
		auto to = ProgressTo::create(1.0f, _progBarCount);
		_nodeEntity->soulProgBar->runAction(to);
	}
#pragma endregion �����������߼�

#pragma region �������Ķ�����ʾ

	auto targetJadgeFontSprite = static_cast<Sprite*>(_mainLayer->_leftStateSprite->getChildByName("Target")->getChildByName("JadgeFont"));/**< ���ĵ��Ϸ��ж����� */
	if (_hitStatus == HitStatus::HIT_PERFER)
	{
		targetJadgeFontSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("judgement_perfer.png"));
		++PlayStatusStatic::playStatus->perferHit;
		addTotalMark(200);
	}
	else if (_hitStatus == HitStatus::HIT_GOOD)
	{
		targetJadgeFontSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("judgement_good.png"));
		++PlayStatusStatic::playStatus->goodHit;
		addTotalMark(100);
	}
	targetJadgeFontSprite->setVisible(true);	/**< ��\�е���Ծ����*/
	targetJadgeFontSprite->runAction(Sequence::create(JumpBy::create(0.15f, Vec2(0, 0), 10, 1), Hide::create(), NULL));

	/**< �����ϲ㶯����ʾ */
	auto  targetUpDisplaySprite = static_cast<Sprite*>(_mainLayer->_leftStateSprite->getChildByName("Target")->getChildByName("TargetUpDisplay"));/**< ���ĵĶ�����ʾ���� */
	targetUpDisplaySprite->setVisible(true);
	targetUpDisplaySprite->runAction(Sequence::create(ScaleTo::create(0.05f, 1.1f),
		FadeIn::create(0.05f),
		ScaleTo::create(0.05f, 1.0f),
		FadeOut::create(0.05f),
		NULL));
#pragma endregion �������Ķ�����ʾ

#pragma region ����������(��|��)��صĶ����߼�

	if (tag == 1)    //���������ڵ�����
	{
		_nodeEntity->scrollBar_Background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sfieldflash_red.png"));
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("musiceffect/dong.wav");
	}
	else
	{
		_nodeEntity->scrollBar_Background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sfieldflash_blue.png"));
		   CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("musiceffect/ka.wav");
	}
#pragma endregion ����������(��|��)��صĶ����߼�

#pragma region ��������صĶ����߼�
	auto backgroundFadeAction = FadeIn::create(0.15f);
	_nodeEntity->scrollBar_Background->runAction(Sequence::create(backgroundFadeAction,
		backgroundFadeAction->reverse(),
		CallFunc::create([&](){
		_nodeEntity->scrollBar_Background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sfieldbg.png"));
	}), NULL));
#pragma endregion ��������صĶ����߼�
}

void JudgeSystem::setGameMode()
{
	_IsAuto = !_IsAuto;
}


void JudgeSystem::EditThreadExecute()
{
	auto& BPM = (static_cast<ScrollSystem*>(MainScene::GetSystemManage()->getEntity("scrollSystem")))->BPMCount;
	float distance = 0.0f;//����
	Node* CheckedNode = nullptr;
	bool  onesFlag = false;//��־���±�����һ��
	auto  target = _mainLayer->_leftStateSprite->getChildByName("Target"); /**< ����Sprite,���ڼ���ˮƽ����*/
	auto durmDataVector = (static_cast<DrumSurfaceLoader*>(MainScene::GetDataManage()->getEntity("drumSurface")))->GetSurfaceEntityVector();/**< ��ȡ�հ�����*/

	auto distanceArray = new DrumSortStruct[DrumSurfaceLoader::PerDrumCount * 2];
	//��ʼ��
	while (true)//ѭ����������ĵ����
	{
		for (int i = 0; i < DrumSurfaceLoader::PerDrumCount * 2; ++i)
		{
			CheckedNode = _nodeEntity->scrollBarSpriteVector.at(i);//���ݹĵ�����������Ӧ����ʾNode
			distanceArray[i].DrumSN = i;
			distanceArray[i].distance = abs(target->convertToNodeSpace(CheckedNode->convertToWorldSpace(Point(0, 0))).x);
			std::sort(distanceArray, distanceArray + DrumSurfaceLoader::PerDrumCount * 2, [](const DrumSortStruct &m1, const DrumSortStruct &m2){
				return  m1.distance < m2.distance;
			});
		}
		printf("��ǰ��BPMΪ:%d ,�������Ϊ %f ,������Ϊ %d \n", BPM, distanceArray[0].distance, distanceArray[0].DrumSN);
	}
	CC_SAFE_DELETE_ARRAY(distanceArray);
}
