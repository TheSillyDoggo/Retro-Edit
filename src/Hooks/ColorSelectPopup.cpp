#include <Geode/modify/ColorSelectPopup.hpp>

#include "../Version.hpp"

using namespace geode::prelude;

class $modify (ColorSelectPopup)
{
    bool init(EffectGameObject* p0, cocos2d::CCArray* p1, ColorAction* p2)
    {
        if (!ColorSelectPopup::init(p0, p1, p2))
            return false;

        return true;
    }
};