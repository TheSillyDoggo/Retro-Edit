#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/EditButtonBar.hpp>

#include "../Version.hpp"

using namespace geode::prelude;

class $modify (RetroEditorUI, EditorUI)
{
    struct Fields
    {
        std::vector<EditButtonBar*> bars;
        CCMenu* tabsMenu;
        std::vector<CCMenuItemToggler*> tabs;
        Ref<CCArray> objs;
        int selectedTab = 0;
    };

    bool init(LevelEditorLayer* editorLayer)
    {
        if (!EditorUI::init(editorLayer))
            return false;

        int rows = 6;
        int columns = 2;

        auto tabs = VersionUtils::getTabs(VersionUtils::getVersionSimulating());
        m_fields->tabs = tabs;

        auto tabsMenu = CCMenu::create();
        tabsMenu->setLayout(RowLayout::create()->setGap(2.0f)->setCrossAxisLineAlignment(AxisAlignment::Start));
        tabsMenu->setPosition(m_tabsMenu->getPosition());
        tabsMenu->setZOrder(69);
        tabsMenu->setID("tabs-menu"_spr);
        m_fields->tabsMenu = tabsMenu;

        int i = 0;
        for (auto tab : tabs)
        {
            tabsMenu->addChild(tab);

            if (!typeinfo_cast<CCMenuItemToggler*>(tab))
                continue;

            tab->setTarget(this, menu_selector(RetroEditorUI::onChangeTab));
            tab->setTag(i);

            i++;
        }

        tabsMenu->updateLayout();

        auto objs = CCArray::create();
        m_fields->objs = objs;

        for (size_t i = 0; i < tabs.size(); i++)
        {
            auto objs2 = VersionUtils::getObjectsForVersion(VersionUtils::getVersionSimulating(), rows, columns, this, i);

            for (auto obj : CCArrayExt<CCMenuItemSpriteExtra*>(objs2))
            {
                objs->addObject(obj);
            }

            auto editBar = EditButtonBar::create(objs2, ccp(CCDirector::get()->getWinSize().width / 2 - 5, 86), 69, false, rows, columns);
            editBar->setZOrder(10);
            editBar->setID("edit-bar"_spr);
            m_fields->bars.push_back(editBar);

            this->addChild(editBar, 5 + i);
        }

        selectTab(0);

        this->addChild(tabsMenu);
        return true;
    }

    void setupCreateMenu()
    {
        EditorUI::setupCreateMenu();

        if (auto tabs = m_tabsMenu)
        {
            tabs->setScale(0);
        }

        for (auto tab : CCArrayExt<CCNode*>(m_createButtonBars))
        {
            tab->setScale(0);
        }

        Loader::get()->queueInMainThread([this]
        {
            for (auto tab : CCArrayExt<CCNode*>(m_createButtonBars))
            {
                tab->setScale(0);
            }
        });
    }

    void selectTab(int index)
    {
        if (m_fields->tabs.size() <= 1)
            return;

        m_fields->selectedTab = index;

        for (size_t i = 0; i < m_fields->tabs.size(); i++)
        {
            m_fields->tabs[i]->toggle(i == index);
            m_fields->tabs[i]->setEnabled(i != index);
            m_fields->tabs[i]->m_offButton->setScale(1);
            m_fields->tabs[i]->m_onButton->setScale(1);
            m_fields->tabs[i]->m_offButton->stopAllActions();
            m_fields->tabs[i]->m_onButton->stopAllActions();
        }

        updateCustomTabs();
    }

    void onChangeTab(CCObject* sender)
    {
        selectTab(sender->getTag());

        updateCustomTabs();
    }

    void updateCustomTabs()
    {
        if (!m_fields->tabsMenu)
            return;

        for (size_t i = 0; i < m_fields->bars.size(); i++)
        {
            m_fields->bars[i]->setVisible(m_tabsMenu->isVisible() && i == m_fields->selectedTab);
        }

        m_fields->tabsMenu->setVisible(m_tabsMenu->isVisible());
    }

    void resetUI()
    {
        EditorUI::resetUI();

        updateCustomTabs();
    }

    void updateCreateMenu(bool p0)
    {
        EditorUI::updateCreateMenu(p0);

        for (auto btn : CCArrayExt<CCNode*>(m_fields->objs))
        {
            if (auto tbtn = typeinfo_cast<CreateMenuItem*>(btn))
            {
                if (auto btnSpr = typeinfo_cast<ButtonSprite*>(tbtn->getNormalImage()))
                {
                    auto col = btn->getTag() == m_selectedObjectIndex ? ccc3(127, 127, 127) : ccWHITE;
                    if (btnSpr->m_subBGSprite)
                    {
                        btnSpr->m_subBGSprite->setColor(col);
                    }
                }
            }
        }
    }
};
