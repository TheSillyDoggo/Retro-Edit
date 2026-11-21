#include <Geode/Geode.hpp>
#include <Geode/modify/GameObject.hpp>
#include "Version.hpp"

using namespace geode::prelude;
using namespace cocos2d;

template <typename T, typename U>
inline T as(U ptr) {
    return static_cast<T>(ptr);
}

std::string VersionUtils::getVersionSimulating()
{
    return Mod::get()->getSettingValue<std::string>("version");
}

bool isGameobjectCreateWithKeyFix = false;

class $modify (GameObject)
{
    static GameObject* createWithKey(int key)
    {
        auto pRet = GameObject::createWithKey(key);

        isGameobjectCreateWithKeyFix = true;

        if (!pRet && isGameobjectCreateWithKeyFix)
        {
            if (key == 104)
            {
                pRet = GameObject::createWithKey(899);
                pRet->m_objectID = 104;
                pRet->m_objectType = GameObjectType::Modifier;
                pRet->m_unk390 = as<int>(GameObjectType::Modifier);

                if (CCSprite* newSpr = CCSprite::create("alphalaneous.old_color_triggers/edit_eTintLBtn_001.png"))
                {
                    pRet->setTexture(newSpr->getTexture());
                    pRet->setTextureRect(newSpr->getTextureRect());
                }
            }

            if (key == 221)
            {
                pRet = GameObject::createWithKey(899);
                pRet->m_objectID = 221;
                pRet->m_objectType = GameObjectType::Modifier;
                pRet->m_unk390 = as<int>(GameObjectType::Modifier);

                if (CCSprite* newSpr = CCSprite::createWithSpriteFrameName("edit_eTintCol01Btn_001.png"))
                {
                    pRet->setTexture(newSpr->getTexture());
                    pRet->setTextureRect(newSpr->getTextureRect());
                }
            }

            if (key == 717 || key == 718 || key == 743)
            {
                pRet = GameObject::createWithKey(899);
                pRet->m_objectID = key;
                pRet->m_objectType = GameObjectType::Modifier;
                pRet->m_unk390 = as<int>(GameObjectType::Modifier);

                if (CCSprite* newSpr = CCSprite::createWithSpriteFrameName("edit_eTintCol01Btn_001.png"))
                {
                    pRet->setTexture(newSpr->getTexture());
                    pRet->setTextureRect(newSpr->getTextureRect());
                }
            }
            if (!pRet)
                pRet = GameObject::createWithKey(1);
        }

        return pRet;
    }
};

#define EDITOR_BUTTON(__objid__) \
if (__objid__ == -1) \
    btn = as<CCMenuItemSpriteExtra*>(CCNode::create()); \
else \
{ \
    btn = ui->getCreateBtn(__objid__, 4); \
    btn->setTarget(ui, menu_selector(EditorUI::onCreateButton)); \
    spr = CCSprite::create(); \
    if (btn->getNormalImage()->getChildByType<GameObject>(0)) \
        spr->setColor(btn->getNormalImage()->getChildByType<GameObject>(0)->getColor()); \
    spr->setID("colour"_spr); \
    spr->setVisible(false); \
    btn->addChild(spr); \
} \
btn->setTag(__objid__); \
array->addObject(btn);

#define EDITOR_BUTTON2(__objid__, __colour__) \
if (__objid__ == -1) \
    btn = as<CCMenuItemSpriteExtra*>(CCNode::create()); \
else \
{ \
    btn = ui->getCreateBtn(__objid__, __colour__); \
    btn->setTarget(ui, menu_selector(EditorUI::onCreateButton)); \
    spr = CCSprite::create(); \
    if (btn->getNormalImage()->getChildByType<GameObject>(0)) \
        spr->setColor(btn->getNormalImage()->getChildByType<GameObject>(0)->getColor()); \
    spr->setID("colour"_spr); \
    spr->setVisible(false); \
    btn->addChild(spr); \
} \
btn->setTag(__objid__); \
array->addObject(btn);

#define REPEATED_EDITOR_BUTTON(__objid__, __count__) \
for (int i = 0; i < __count__; i++) \
{ \
    EDITOR_BUTTON(__objid__); \
}

#define REPEATED_INCREASED_EDITOR_BUTTON(__objid__, __count__) \
start = __objid__; \
for (int i = 0; i < __count__; i++) \
{ \
    EDITOR_BUTTON(start + i); \
}

#define REPEATED_INCREASED_EDITOR_BUTTON2(__objid__, __count__, __colour__) \
start = __objid__; \
for (int i = 0; i < __count__; i++) \
{ \
    EDITOR_BUTTON2(start + i, __colour__); \
}

// There is a better way to do this, Too bad!

CCArray* VersionUtils::getObjectsForVersion(std::string version, int rows, int columns, EditorUI* ui, int category)
{
    auto array = CCArray::create();

    isGameobjectCreateWithKeyFix = true;

    CCMenuItemSpriteExtra* btn;
    CCSprite* spr;
    int start = 0;

    if (version == "1.0" || version == "1.1" || version == "1.2")
    {
        REPEATED_INCREASED_EDITOR_BUTTON(1, 8);
        EDITOR_BUTTON(39);
        EDITOR_BUTTON(9);
        EDITOR_BUTTON(40);
        REPEATED_INCREASED_EDITOR_BUTTON(35, 2);
        REPEATED_INCREASED_EDITOR_BUTTON(10, 4);

        int _11offset = 1;

        if (version == "1.1" || version == "1.2")
        {
            _11offset += (version == "1.2" ? 3 : 2);

            REPEATED_INCREASED_EDITOR_BUTTON(45, (version == "1.2" ? 3 : 2));
        }

        REPEATED_INCREASED_EDITOR_BUTTON(15, 7);
        EDITOR_BUTTON(41);

        REPEATED_EDITOR_BUTTON(-1, rows * columns - _11offset);

        EDITOR_BUTTON(22);
        EDITOR_BUTTON(24);
        EDITOR_BUTTON(23);
        REPEATED_INCREASED_EDITOR_BUTTON(25, 3);
        REPEATED_INCREASED_EDITOR_BUTTON(29, 3);
        EDITOR_BUTTON(33);
        EDITOR_BUTTON(32);
    }
    else if (version == "1.3" || version == "1.4" || version == "1.5" || version == "1.6")
    {
        EDITOR_BUTTON(1);
        EDITOR_BUTTON(83);
        REPEATED_INCREASED_EDITOR_BUTTON(2, 7);
        EDITOR_BUTTON(39);

        if (version == "1.4" || version == "1.5" || version == "1.6")
        {
            EDITOR_BUTTON(103);
        }

        EDITOR_BUTTON(9);
        EDITOR_BUTTON(61);
        EDITOR_BUTTON(40);
        EDITOR_BUTTON(62);
        EDITOR_BUTTON(66);
        EDITOR_BUTTON(65);
        EDITOR_BUTTON(68);
        EDITOR_BUTTON(35);

        if (version == "1.5" || version == "1.6")
        {
            EDITOR_BUTTON(140);
        }

        EDITOR_BUTTON(67);
        EDITOR_BUTTON(36);

        if (version == "1.5" || version == "1.6")
        {
            EDITOR_BUTTON(141);
        }

        EDITOR_BUTTON(84);
        REPEATED_INCREASED_EDITOR_BUTTON(10, 4);
        REPEATED_INCREASED_EDITOR_BUTTON(45, 3);

        if (version == "1.4" || version == "1.5" || version == "1.6")
        {
            EDITOR_BUTTON(99);
            EDITOR_BUTTON(101);

            if (version == "1.5" || version == "1.6")
            {
                EDITOR_BUTTON(111);
            }
        }

        REPEATED_INCREASED_EDITOR_BUTTON(15, 7);
        EDITOR_BUTTON(41);

        if (version == "1.5" || version == "1.6")
        {
            EDITOR_BUTTON(110);
            REPEATED_INCREASED_EDITOR_BUTTON(106, 2);
        }

        if (version == "1.5" || version == "1.6")
        {
            REPEATED_INCREASED_EDITOR_BUTTON(48, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(129, 2);

            if (version == "1.6")
            {
                EDITOR_BUTTON(131);
            }

            REPEATED_INCREASED_EDITOR_BUTTON(113, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(50, 5);
        }
        else
        {
            REPEATED_INCREASED_EDITOR_BUTTON(48, 7);
        }

        EDITOR_BUTTON(60);

        if (version == "1.6")
        {
            REPEATED_INCREASED_EDITOR_BUTTON(148, 2);
        }

        if (version == "1.4" || version == "1.5" || version == "1.6")
        {
            REPEATED_INCREASED_EDITOR_BUTTON(85, 3);
            EDITOR_BUTTON(97);

            if (version == "1.5" || version == "1.6")
            {
                REPEATED_INCREASED_EDITOR_BUTTON(137, 3);
            }

            REPEATED_INCREASED_EDITOR_BUTTON(88, 2);
            EDITOR_BUTTON(98);
        }

        REPEATED_INCREASED_EDITOR_BUTTON(69, 7);

        if (version == "1.4" || version == "1.5" || version == "1.6")
        {
            REPEATED_INCREASED_EDITOR_BUTTON(76, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(80, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(90, 7);

            if (version == "1.5" || version == "1.6")
            {
                REPEATED_INCREASED_EDITOR_BUTTON(116, 7);

                if (version == "1.6")
                {
                    REPEATED_INCREASED_EDITOR_BUTTON(160, 10);
                    EDITOR_BUTTON(193);

                    REPEATED_INCREASED_EDITOR_BUTTON(170, 3);
                    EDITOR_BUTTON(192);

                    EDITOR_BUTTON(173);
                    EDITOR_BUTTON(194);
                    REPEATED_INCREASED_EDITOR_BUTTON(174, 3);
                    EDITOR_BUTTON(197);
                }

                EDITOR_BUTTON(135);

                EDITOR_BUTTON(128);

                REPEATED_INCREASED_EDITOR_BUTTON(123, 5);

                REPEATED_INCREASED_EDITOR_BUTTON(132, 2);
                EDITOR_BUTTON(136);

                if (version == "1.6")
                {
                    EDITOR_BUTTON(150);
                    EDITOR_BUTTON(143);
                    EDITOR_BUTTON(146);
                    EDITOR_BUTTON(147);
                    EDITOR_BUTTON(144);
                    EDITOR_BUTTON(145);

                    EDITOR_BUTTON(134);
                    EDITOR_BUTTON(190);
                    EDITOR_BUTTON(151);
                    EDITOR_BUTTON(152);
                    EDITOR_BUTTON(153);
                    EDITOR_BUTTON(154);
                    EDITOR_BUTTON(155);
                    EDITOR_BUTTON(156);
                    EDITOR_BUTTON(157);
                    EDITOR_BUTTON(158);
                    EDITOR_BUTTON(159);

                    EDITOR_BUTTON(177);
                    EDITOR_BUTTON(178);
                    EDITOR_BUTTON(179);

                    EDITOR_BUTTON(180);
                    EDITOR_BUTTON(181);
                    EDITOR_BUTTON(182);
                    EDITOR_BUTTON(182);
                    EDITOR_BUTTON(184);
                    EDITOR_BUTTON(185);
                    EDITOR_BUTTON(186);
                    EDITOR_BUTTON(187);
                    EDITOR_BUTTON(188);

                    EDITOR_BUTTON(191);
                    EDITOR_BUTTON(198);
                    EDITOR_BUTTON(199);

                    EDITOR_BUTTON(195);
                    EDITOR_BUTTON(196);

                    REPEATED_EDITOR_BUTTON(-1, 2);
                }
            }
        }

        if (version == "1.5" || version == "1.6")
        {
            REPEATED_EDITOR_BUTTON(-1, rows * columns - 10);
        }
        else
        {
            REPEATED_EDITOR_BUTTON(-1, rows * columns - 3);
        }

        if (version == "1.4" || version == "1.5" || version == "1.6")
        {
            EDITOR_BUTTON(-1);
        }

        EDITOR_BUTTON(22);
        EDITOR_BUTTON(24);
        EDITOR_BUTTON(23);
        REPEATED_INCREASED_EDITOR_BUTTON(25, 4);
        REPEATED_INCREASED_EDITOR_BUTTON(56, 4);
        
        EDITOR_BUTTON(-1);

        if (version == "1.4" || version == "1.5" || version == "1.6")
        {
            REPEATED_INCREASED_EDITOR_BUTTON(29, 2);

            EDITOR_BUTTON(104);

            if (version == "1.5" || version == "1.6")
            {
                EDITOR_BUTTON(105);
            }

            EDITOR_BUTTON(31);
        }
        else
        {
            REPEATED_INCREASED_EDITOR_BUTTON(29, 3);
        }

        EDITOR_BUTTON(33);
        EDITOR_BUTTON(32);
    }
    else if (version == "1.7")
    {
        if (category == 0)
        {
            EDITOR_BUTTON(1);
            EDITOR_BUTTON(83);
            REPEATED_INCREASED_EDITOR_BUTTON(2, 6);

            REPEATED_INCREASED_EDITOR_BUTTON(69, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(76, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(80, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(90, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(116, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(160, 10);
            EDITOR_BUTTON(193);

            REPEATED_INCREASED_EDITOR_BUTTON(207, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(247, 8);

            REPEATED_INCREASED_EDITOR_BUTTON(255, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(263, 6);
            
            REPEATED_INCREASED_EDITOR_BUTTON(269, 7);
        }

        if (category == 1)
        {
            EDITOR_BUTTON(40);
            REPEATED_INCREASED_EDITOR_BUTTON(195, 2);

            EDITOR_BUTTON(215);
            EDITOR_BUTTON(220);
            EDITOR_BUTTON(219);

            REPEATED_INCREASED_EDITOR_BUTTON(146, 2);
            EDITOR_BUTTON(206);
            EDITOR_BUTTON(204);

            EDITOR_BUTTON(62);
            EDITOR_BUTTON(66);
            EDITOR_BUTTON(65);
            EDITOR_BUTTON(68);

            REPEATED_INCREASED_EDITOR_BUTTON(170, 3);
            EDITOR_BUTTON(192);

            EDITOR_BUTTON(173);
            EDITOR_BUTTON(194);
            REPEATED_INCREASED_EDITOR_BUTTON(174, 3);
            EDITOR_BUTTON(197);

            EDITOR_BUTTON(143);
        }

        if (category == 2)
        {
            EDITOR_BUTTON(8);
            EDITOR_BUTTON(39);
            EDITOR_BUTTON(103);
            
            REPEATED_INCREASED_EDITOR_BUTTON(216, 3);

            EDITOR_BUTTON(144);
            EDITOR_BUTTON(205);
            EDITOR_BUTTON(145);

            REPEATED_INCREASED_EDITOR_BUTTON(177, 3);

            EDITOR_BUTTON(191);
            REPEATED_INCREASED_EDITOR_BUTTON(198, 2);

            EDITOR_BUTTON(9);
            EDITOR_BUTTON(61);
            REPEATED_INCREASED_EDITOR_BUTTON(243, 2);
            EDITOR_BUTTON(135);
        }

        if (category == 3)
        {
            EDITOR_BUTTON(35);
            EDITOR_BUTTON(140);
            EDITOR_BUTTON(67);

            EDITOR_BUTTON(36);
            EDITOR_BUTTON(141);
            EDITOR_BUTTON(84);

            REPEATED_INCREASED_EDITOR_BUTTON(10, 4);
            EDITOR_BUTTON(47);
            EDITOR_BUTTON(111);

            REPEATED_INCREASED_EDITOR_BUTTON(45, 2);

            EDITOR_BUTTON(99);
            EDITOR_BUTTON(101);

            REPEATED_INCREASED_EDITOR_BUTTON(200, 4);
        }

        if (category == 4)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(18, 4);
            REPEATED_INCREASED_EDITOR_BUTTON(48, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(113, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(157, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(227, 2);
            EDITOR_BUTTON(242);
        }

        if (category == 5)
        {
            EDITOR_BUTTON(41);
            EDITOR_BUTTON(110);
            REPEATED_INCREASED_EDITOR_BUTTON(106, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(129, 3);

            EDITOR_BUTTON(128);
            REPEATED_INCREASED_EDITOR_BUTTON(123, 5);

            EDITOR_BUTTON(134);
            EDITOR_BUTTON(190);

            REPEATED_INCREASED_EDITOR_BUTTON(151, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(225, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(229, 2);

            REPEATED_INCREASED_EDITOR_BUTTON(237, 5);

            REPEATED_INCREASED_EDITOR_BUTTON(231, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(283, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(279, 2);
            EDITOR_BUTTON(233);
            REPEATED_INCREASED_EDITOR_BUTTON(281, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(234, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(277, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(245, 2);
        }

        if (category == 6)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(15, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(50, 5);
            EDITOR_BUTTON(60);
            REPEATED_INCREASED_EDITOR_BUTTON(148, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(132, 2);
            EDITOR_BUTTON(136);
            EDITOR_BUTTON(150);
            EDITOR_BUTTON(236);
        }

        if (category == 7)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(88, 2);
            EDITOR_BUTTON(98);

            REPEATED_INCREASED_EDITOR_BUTTON(186, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(183, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(85, 3);
            EDITOR_BUTTON(97);

            REPEATED_INCREASED_EDITOR_BUTTON(137, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(154, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(180, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(222, 3);
        }

        if (category == 8)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(29, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(104, 2);
            EDITOR_BUTTON(221);
            EDITOR_BUTTON(31);
            EDITOR_BUTTON(33);
            EDITOR_BUTTON(32);

            REPEATED_EDITOR_BUTTON(-1, 4);

            EDITOR_BUTTON(22);
            EDITOR_BUTTON(24);
            EDITOR_BUTTON(23);
            REPEATED_INCREASED_EDITOR_BUTTON(25, 4);
            REPEATED_INCREASED_EDITOR_BUTTON(56, 4);
        }
    }
    else if (version == "1.8")
    {
        if (category == 0)
        {
            EDITOR_BUTTON(1);
            EDITOR_BUTTON(83);
            REPEATED_INCREASED_EDITOR_BUTTON(2, 4);
            EDITOR_BUTTON(502);
            REPEATED_INCREASED_EDITOR_BUTTON(6, 2);

            REPEATED_INCREASED_EDITOR_BUTTON(69, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(76, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(80, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(90, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(116, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(160, 10);
            EDITOR_BUTTON(193);

            REPEATED_INCREASED_EDITOR_BUTTON(207, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(247, 8);

            REPEATED_INCREASED_EDITOR_BUTTON(255, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(263, 6);
            
            REPEATED_INCREASED_EDITOR_BUTTON(269, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(476, 7);
            REPEATED_INCREASED_EDITOR_BUTTON(485, 7);
        }

        if (category == 1)
        {
            EDITOR_BUTTON(40);
            EDITOR_BUTTON(369);
            EDITOR_BUTTON(370);
            REPEATED_INCREASED_EDITOR_BUTTON(195, 2);

            EDITOR_BUTTON(215);
            EDITOR_BUTTON(220);
            EDITOR_BUTTON(219);

            REPEATED_INCREASED_EDITOR_BUTTON(146, 2);
            EDITOR_BUTTON(206);
            EDITOR_BUTTON(204);

            EDITOR_BUTTON(62);
            EDITOR_BUTTON(66);
            EDITOR_BUTTON(65);
            EDITOR_BUTTON(68);
            EDITOR_BUTTON(63);
            EDITOR_BUTTON(64);

            REPEATED_INCREASED_EDITOR_BUTTON(170, 3);
            EDITOR_BUTTON(192);

            EDITOR_BUTTON(173);
            EDITOR_BUTTON(194);
            REPEATED_INCREASED_EDITOR_BUTTON(174, 3);
            EDITOR_BUTTON(197);

            EDITOR_BUTTON(143);
        }

        if (category == 2)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(467, 9);
        }

        if (category == 3)
        {
            EDITOR_BUTTON(289);
            EDITOR_BUTTON(291);
            EDITOR_BUTTON(299);
            EDITOR_BUTTON(301);
            EDITOR_BUTTON(305);
            EDITOR_BUTTON(307);
            EDITOR_BUTTON(309);
            EDITOR_BUTTON(311);
            EDITOR_BUTTON(315);
            EDITOR_BUTTON(317);
            EDITOR_BUTTON(321);
            REPEATED_INCREASED_EDITOR_BUTTON(323, 3);
            EDITOR_BUTTON(358);

            REPEATED_INCREASED_EDITOR_BUTTON(294, 4);
            REPEATED_INCREASED_EDITOR_BUTTON(326, 4);

            EDITOR_BUTTON(331);
            EDITOR_BUTTON(333);
            EDITOR_BUTTON(337);
            EDITOR_BUTTON(339);
            EDITOR_BUTTON(343);
            EDITOR_BUTTON(345);
            EDITOR_BUTTON(349);
            EDITOR_BUTTON(351);
            EDITOR_BUTTON(353);
            EDITOR_BUTTON(355);
            REPEATED_INCREASED_EDITOR_BUTTON(483, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(492, 2);
        }

        if (category == 4)
        {
            EDITOR_BUTTON(8);
            EDITOR_BUTTON(39);
            EDITOR_BUTTON(103);
            EDITOR_BUTTON(392);
            
            REPEATED_INCREASED_EDITOR_BUTTON(216, 3);
            EDITOR_BUTTON(458);

            EDITOR_BUTTON(144);
            EDITOR_BUTTON(205);
            EDITOR_BUTTON(145);
            EDITOR_BUTTON(459);

            REPEATED_INCREASED_EDITOR_BUTTON(177, 3);

            EDITOR_BUTTON(191);
            REPEATED_INCREASED_EDITOR_BUTTON(198, 2);

            EDITOR_BUTTON(393);

            EDITOR_BUTTON(9);
            EDITOR_BUTTON(61);
            REPEATED_INCREASED_EDITOR_BUTTON(243, 2);
            EDITOR_BUTTON(135);

            REPEATED_INCREASED_EDITOR_BUTTON(363, 6);
            REPEATED_INCREASED_EDITOR_BUTTON(446, 2);
        }

        if (category == 5)
        {
            EDITOR_BUTTON(35);
            EDITOR_BUTTON(140);
            EDITOR_BUTTON(67);

            EDITOR_BUTTON(36);
            EDITOR_BUTTON(141);
            EDITOR_BUTTON(84);

            REPEATED_INCREASED_EDITOR_BUTTON(10, 4);
            EDITOR_BUTTON(47);
            EDITOR_BUTTON(111);

            REPEATED_INCREASED_EDITOR_BUTTON(45, 2);

            EDITOR_BUTTON(99);
            EDITOR_BUTTON(101);

            REPEATED_INCREASED_EDITOR_BUTTON(286, 2);

            REPEATED_INCREASED_EDITOR_BUTTON(200, 4);
        }

        if (category == 6)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(18, 4);
            REPEATED_INCREASED_EDITOR_BUTTON(48, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(113, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(157, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(227, 2);
            EDITOR_BUTTON(242);

            REPEATED_INCREASED_EDITOR_BUTTON(448, 5);
            REPEATED_INCREASED_EDITOR_BUTTON2(503, 3, 5);
        }

        if (category == 7)
        {
            EDITOR_BUTTON(41);
            EDITOR_BUTTON(110);
            REPEATED_INCREASED_EDITOR_BUTTON(106, 2);

            REPEATED_INCREASED_EDITOR_BUTTON2(498, 2, 5)

            REPEATED_INCREASED_EDITOR_BUTTON(129, 3);

            EDITOR_BUTTON(128);
            REPEATED_INCREASED_EDITOR_BUTTON(123, 5);

            EDITOR_BUTTON2(466, 5);
            REPEATED_INCREASED_EDITOR_BUTTON2(461, 5, 5);

            EDITOR_BUTTON(134);
            EDITOR_BUTTON(190);

            REPEATED_INCREASED_EDITOR_BUTTON(151, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(225, 2);

            REPEATED_INCREASED_EDITOR_BUTTON2(500, 2, 5);

            REPEATED_INCREASED_EDITOR_BUTTON(229, 2);

            REPEATED_INCREASED_EDITOR_BUTTON(237, 5);

            REPEATED_INCREASED_EDITOR_BUTTON(231, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(283, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(279, 2);
            EDITOR_BUTTON(233);
            REPEATED_INCREASED_EDITOR_BUTTON(281, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(234, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(277, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(245, 2);
            
            REPEATED_INCREASED_EDITOR_BUTTON(409, 5);
            REPEATED_INCREASED_EDITOR_BUTTON(453, 5);
        }

        if (category == 8)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(15, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(50, 5);
            EDITOR_BUTTON(60);
            REPEATED_INCREASED_EDITOR_BUTTON(148, 2);
            EDITOR_BUTTON(405);
            EDITOR_BUTTON(132);
            EDITOR_BUTTON(460);
            EDITOR_BUTTON(494);
            EDITOR_BUTTON(133);
            EDITOR_BUTTON(136);
            EDITOR_BUTTON(150);
            EDITOR_BUTTON(236);
            EDITOR_BUTTON(497);
            REPEATED_INCREASED_EDITOR_BUTTON(495, 2);
        }

        if (category == 9)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(88, 2);
            EDITOR_BUTTON(98);

            REPEATED_INCREASED_EDITOR_BUTTON(397, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(186, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(183, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(85, 3);
            EDITOR_BUTTON(97);

            REPEATED_INCREASED_EDITOR_BUTTON(137, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(154, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(180, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(222, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(375, 4);

            REPEATED_INCREASED_EDITOR_BUTTON(394, 3);
        }

        if (category == 10)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(29, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(104, 2);
            EDITOR_BUTTON(221);
            EDITOR_BUTTON(31);
            EDITOR_BUTTON(33);
            EDITOR_BUTTON(32);

            REPEATED_EDITOR_BUTTON(-1, 4);

            EDITOR_BUTTON(22);
            EDITOR_BUTTON(24);
            EDITOR_BUTTON(23);
            REPEATED_INCREASED_EDITOR_BUTTON(25, 4);
            REPEATED_INCREASED_EDITOR_BUTTON(56, 4);
        }
    }
    else if (version == "1.9")
    {
        if (category == 0)
        {
            EDITOR_BUTTON(1);
            EDITOR_BUTTON(83);
            REPEATED_INCREASED_EDITOR_BUTTON(2, 4);
            EDITOR_BUTTON(502);
            REPEATED_INCREASED_EDITOR_BUTTON(6, 2);

            REPEATED_INCREASED_EDITOR_BUTTON(69, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(76, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(80, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(90, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(116, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(160, 8);
            EDITOR_BUTTON(737);
            REPEATED_INCREASED_EDITOR_BUTTON(168, 2);
            EDITOR_BUTTON(193);

            REPEATED_INCREASED_EDITOR_BUTTON(207, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(247, 8);

            REPEATED_INCREASED_EDITOR_BUTTON(255, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(263, 6);
            
            REPEATED_INCREASED_EDITOR_BUTTON(269, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(476, 7);
            REPEATED_INCREASED_EDITOR_BUTTON(485, 7);

            REPEATED_INCREASED_EDITOR_BUTTON(641, 8);
            EDITOR_BUTTON(739);
            REPEATED_INCREASED_EDITOR_BUTTON(649, 2);

            EDITOR_BUTTON(658);
            EDITOR_BUTTON(722);
            EDITOR_BUTTON(659);
            EDITOR_BUTTON(734);
        }

        if (category == 1)
        {
            EDITOR_BUTTON(40);
            EDITOR_BUTTON(369);
            EDITOR_BUTTON(370);
            REPEATED_INCREASED_EDITOR_BUTTON(195, 2);

            EDITOR_BUTTON(215);
            EDITOR_BUTTON(220);
            EDITOR_BUTTON(219);

            REPEATED_INCREASED_EDITOR_BUTTON2(146, 2, 5);
            EDITOR_BUTTON2(206, 5);
            EDITOR_BUTTON2(204, 5);
            REPEATED_INCREASED_EDITOR_BUTTON2(673, 2, 5);

            EDITOR_BUTTON(62);
            EDITOR_BUTTON(66);
            EDITOR_BUTTON(65);
            EDITOR_BUTTON(68);
            EDITOR_BUTTON(63);
            EDITOR_BUTTON(64);

            REPEATED_INCREASED_EDITOR_BUTTON(170, 3);
            EDITOR_BUTTON(192);

            EDITOR_BUTTON(173);
            EDITOR_BUTTON(194);
            REPEATED_INCREASED_EDITOR_BUTTON(174, 3);
            EDITOR_BUTTON(197);

            EDITOR_BUTTON(143);

            EDITOR_BUTTON(653);
            EDITOR_BUTTON(724);
            EDITOR_BUTTON(654);
            EDITOR_BUTTON(736);

            EDITOR_BUTTON(657);
            EDITOR_BUTTON(656);
            EDITOR_BUTTON(655);
            EDITOR_BUTTON(723);
            EDITOR_BUTTON(735);
        }

        if (category == 2)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(467, 9);
            REPEATED_INCREASED_EDITOR_BUTTON(661, 6);
        }

        if (category == 3)
        {
            EDITOR_BUTTON(289);
            EDITOR_BUTTON(291);
            EDITOR_BUTTON(299);
            EDITOR_BUTTON(301);
            EDITOR_BUTTON(305);
            EDITOR_BUTTON(307);
            EDITOR_BUTTON(309);
            EDITOR_BUTTON(311);
            EDITOR_BUTTON(315);
            EDITOR_BUTTON(317);
            EDITOR_BUTTON(321);
            REPEATED_INCREASED_EDITOR_BUTTON(323, 3);
            EDITOR_BUTTON(358);

            REPEATED_INCREASED_EDITOR_BUTTON(294, 4);
            REPEATED_INCREASED_EDITOR_BUTTON(326, 4);

            EDITOR_BUTTON(331);
            EDITOR_BUTTON(333);
            EDITOR_BUTTON(337);
            EDITOR_BUTTON(339);
            EDITOR_BUTTON(343);
            EDITOR_BUTTON(345);
            EDITOR_BUTTON(349);
            EDITOR_BUTTON(351);
            EDITOR_BUTTON(353);
            EDITOR_BUTTON(355);
            REPEATED_INCREASED_EDITOR_BUTTON(483, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(492, 2);

            REPEATED_INCREASED_EDITOR_BUTTON(651, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(709, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(726, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(711, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(728, 2);

            EDITOR_BUTTON(-1);

            REPEATED_INCREASED_EDITOR_BUTTON(681, 28);

            REPEATED_INCREASED_EDITOR_BUTTON(713, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(730, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(715, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(732, 2);
        }

        if (category == 4)
        {
            EDITOR_BUTTON(8);
            EDITOR_BUTTON(39);
            EDITOR_BUTTON(103);
            EDITOR_BUTTON(392);
            
            REPEATED_INCREASED_EDITOR_BUTTON(216, 3);
            EDITOR_BUTTON(458);

            EDITOR_BUTTON2(144, 5);
            EDITOR_BUTTON2(205, 5);
            EDITOR_BUTTON2(145, 5);
            EDITOR_BUTTON2(459, 5);

            REPEATED_INCREASED_EDITOR_BUTTON(177, 3);

            EDITOR_BUTTON(191);
            REPEATED_INCREASED_EDITOR_BUTTON(198, 2);

            EDITOR_BUTTON(393);

            EDITOR_BUTTON(9);
            EDITOR_BUTTON(61);
            REPEATED_INCREASED_EDITOR_BUTTON(243, 2);
            EDITOR_BUTTON(135);

            REPEATED_INCREASED_EDITOR_BUTTON(363, 6);
            REPEATED_INCREASED_EDITOR_BUTTON(446, 2);

            EDITOR_BUTTON(667);
            EDITOR_BUTTON(720);
        }

        if (category == 5)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(506, 135);
        }

        if (category == 6)
        {
            EDITOR_BUTTON(35);
            EDITOR_BUTTON(140);
            EDITOR_BUTTON(67);

            EDITOR_BUTTON(36);
            EDITOR_BUTTON(141);
            EDITOR_BUTTON(84);

            REPEATED_INCREASED_EDITOR_BUTTON(10, 4);
            EDITOR_BUTTON(47);
            EDITOR_BUTTON(111);

            EDITOR_BUTTON(660);
            REPEATED_INCREASED_EDITOR_BUTTON(45, 2);

            EDITOR_BUTTON(99);
            EDITOR_BUTTON(101);

            REPEATED_INCREASED_EDITOR_BUTTON(286, 2);

            REPEATED_INCREASED_EDITOR_BUTTON(200, 4);
        }

        if (category == 7)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(18, 4);
            REPEATED_INCREASED_EDITOR_BUTTON(48, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(113, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(157, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(227, 2);
            EDITOR_BUTTON(242);

            REPEATED_INCREASED_EDITOR_BUTTON(448, 5);
            REPEATED_INCREASED_EDITOR_BUTTON2(503, 3, 5);
        }

        if (category == 8)
        {
            EDITOR_BUTTON(41);
            EDITOR_BUTTON(110);
            REPEATED_INCREASED_EDITOR_BUTTON(106, 2);

            REPEATED_INCREASED_EDITOR_BUTTON2(498, 2, 5)

            REPEATED_INCREASED_EDITOR_BUTTON(129, 3);

            EDITOR_BUTTON(466);
            REPEATED_INCREASED_EDITOR_BUTTON(461, 5);

            EDITOR_BUTTON(134);
            EDITOR_BUTTON(190);

            REPEATED_INCREASED_EDITOR_BUTTON(151, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(225, 2);

            REPEATED_INCREASED_EDITOR_BUTTON2(500, 2, 5);

            REPEATED_INCREASED_EDITOR_BUTTON(229, 2);

            REPEATED_INCREASED_EDITOR_BUTTON(237, 5);

            REPEATED_INCREASED_EDITOR_BUTTON(231, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(283, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(279, 2);
            EDITOR_BUTTON(233);
            REPEATED_INCREASED_EDITOR_BUTTON(281, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(234, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(277, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(245, 2);
            
            REPEATED_INCREASED_EDITOR_BUTTON(409, 5);
            REPEATED_INCREASED_EDITOR_BUTTON(453, 5);

            REPEATED_INCREASED_EDITOR_BUTTON(668, 5);
            EDITOR_BUTTON(738);

            EDITOR_BUTTON2(719, 5);
            EDITOR_BUTTON2(721, 5);
        }

        if (category == 9)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(15, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(50, 5);
            EDITOR_BUTTON(60);
            REPEATED_INCREASED_EDITOR_BUTTON(148, 2);
            EDITOR_BUTTON(405);
            EDITOR_BUTTON(132);
            EDITOR_BUTTON(460);
            EDITOR_BUTTON(494);
            EDITOR_BUTTON(133);
            EDITOR_BUTTON(136);
            EDITOR_BUTTON(150);
            EDITOR_BUTTON(236);
            EDITOR_BUTTON(497);
            REPEATED_INCREASED_EDITOR_BUTTON(495, 2);
        }

        if (category == 10)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(88, 2);
            EDITOR_BUTTON(98);

            REPEATED_INCREASED_EDITOR_BUTTON(397, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(675, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(186, 3);

            REPEATED_INCREASED_EDITOR_BUTTON2(740, 3, 5);

            REPEATED_INCREASED_EDITOR_BUTTON(678, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(183, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(85, 3);
            EDITOR_BUTTON(97);

            REPEATED_INCREASED_EDITOR_BUTTON(137, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(154, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(180, 3);
            REPEATED_INCREASED_EDITOR_BUTTON(222, 3);

            REPEATED_INCREASED_EDITOR_BUTTON(375, 4);

            REPEATED_INCREASED_EDITOR_BUTTON(394, 3);
        }

        if (category == 11)
        {
            REPEATED_INCREASED_EDITOR_BUTTON(29, 2);
            REPEATED_INCREASED_EDITOR_BUTTON(104, 2);
            EDITOR_BUTTON(744);
            EDITOR_BUTTON(221);
            EDITOR_BUTTON(717);
            EDITOR_BUTTON(718);
            EDITOR_BUTTON(743);

            EDITOR_BUTTON(31);
            EDITOR_BUTTON(33);
            EDITOR_BUTTON(32);

            EDITOR_BUTTON(22);
            EDITOR_BUTTON(24);
            EDITOR_BUTTON(23);
            REPEATED_INCREASED_EDITOR_BUTTON(25, 4);
            REPEATED_INCREASED_EDITOR_BUTTON(56, 4);
        }
    }

    isGameobjectCreateWithKeyFix = false;

    return array;
}

#define TAB_SPRITE(spr) \
toggle = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("GJ_tabOff_001.png"), CCSprite::createWithSpriteFrameName("GJ_tabOn_001.png"), nullptr, nullptr); \
spr1 = spr; \
spr1->setOpacity(150); \
spr1->setPosition(toggle->m_offButton->getNormalImage()->getContentSize() / 2); \
spr1->setPositionY(7.5f); \
spr1->setID("spr1"_spr); \
limitNodeSize(spr1, ccp(25, 14), 0.55f, 0); \
as<CCSprite*>(toggle->m_offButton->getNormalImage())->setOpacity(150); \
toggle->m_offButton->getNormalImage()->addChild(spr1); \
spr2 = spr; \
spr2->setPosition(toggle->m_offButton->getNormalImage()->getContentSize() / 2); \
spr2->setPositionY(7.5f); \
spr2->setID("spr2"_spr); \
limitNodeSize(spr2, ccp(25, 14), 0.55f, 0); \
toggle->m_onButton->getNormalImage()->addChild(spr2); \
tabs.push_back(toggle);

std::vector<CCMenuItemToggler*> VersionUtils::getTabs(std::string version)
{
    if (version == "1.0" || version == "1.1" || version == "1.2" || version == "1.3" || version == "1.4" || version == "1.5" || version == "1.6")
        return { as<CCMenuItemToggler*>(CCNode::create()) };

    std::vector<CCMenuItemToggler*> tabs;
    CCSprite* spr1;
    CCSprite* spr2;
    CCSprite* sprSlab1 = CCSprite::createWithSpriteFrameName("plank_01_color_001.png");
    sprSlab1->setZOrder(-1);
    sprSlab1->setColor(ccBLACK);
    sprSlab1->setOpacity(150);
    CCSprite* sprSlab2 = CCSprite::createWithSpriteFrameName("plank_01_color_001.png");
    sprSlab2->setZOrder(-1);
    sprSlab2->setColor(ccBLACK);

    auto slope1 = CCSprite::createWithSpriteFrameName("triangle_a_02_001.png");
    slope1->setZOrder(-1);
    slope1->setOpacity(150);
    auto slope2 = CCSprite::createWithSpriteFrameName("triangle_a_02_001.png");
    slope2->setZOrder(-1);

    CCMenuItemToggler* toggle;

    TAB_SPRITE(GameObject::createWithKey(1));
    TAB_SPRITE(GameObject::createWithKey(40));

    as<GameObject*>(spr1)->addChildAtPosition(sprSlab1, Anchor::Center);
    as<GameObject*>(spr2)->addChildAtPosition(sprSlab2, Anchor::Center);

    if (version == "1.8" || version == "1.9")
    {
        TAB_SPRITE(GameObject::createWithKey(467));
        TAB_SPRITE(GameObject::createWithKey(289));

        as<GameObject*>(spr1)->addChildAtPosition(slope1, Anchor::Center);
        as<GameObject*>(spr2)->addChildAtPosition(slope2, Anchor::Center);
    }

    TAB_SPRITE(GameObject::createWithKey(8));

    if (version == "1.9")
    {
        TAB_SPRITE(GameObject::createWithKey(506));
    }

    TAB_SPRITE(GameObject::createWithKey(36));
    TAB_SPRITE(GameObject::createWithKey(18));
    TAB_SPRITE(GameObject::createWithKey(41));
    TAB_SPRITE(GameObject::createWithKey(50));
    TAB_SPRITE(CCSprite::createWithSpriteFrameName("sawblade_02_001.png"));

    spr1->setColor(ccBLACK);
    spr2->setColor(ccBLACK);

    TAB_SPRITE(CCSprite::create("alphalaneous.old_color_triggers/edit_eTintBGBtn_001.png"));

    return tabs;
}
