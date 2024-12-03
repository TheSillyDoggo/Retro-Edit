#pragma once

namespace VersionUtils
{
    std::string getVersionSimulating();

    cocos2d::CCArray* getObjectsForVersion(std::string version, int rows, int columns, EditorUI* ui, int category);
    std::vector<CCMenuItemToggler*> getTabs(std::string version);
};