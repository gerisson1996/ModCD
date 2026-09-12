#include "gameTileView.hpp"

#include <front/styles/colors.hpp>
#include <utils/localization.hpp>
#include <utils/utils.hpp>

namespace front {
GameTileView::GameTileView(const core::Game& aGame, const bool aSupported, const bool aNoMods)
    : game(aGame), supported(aSupported), noMods(aNoMods) {
    this->setPadding(0.0f, 0.0f, 0.0f, 0.0f);
    this->setMaxWidth(370);
    this->setMinWidth(370);
    this->setMaxHeight(430);
    this->setMinHeight(430);

    brls::Box* root = new brls::Box(brls::Axis::COLUMN);

    brls::Image* icon = new brls::Image();
    if (game.icon) {
        icon->setImageFromMem(game.icon.get(), GAME_ICON_SIZE);  // @TODO Does need save game.icon?
    }
    icon->setMargins(10.0f, 0.0f, 0.0f, 0.0f);
    icon->setWidth(320);
    icon->setHeight(320);
    root->addView(icon);

    brls::Box* labelsContainer = new brls::Box(brls::Axis::COLUMN);

    std::string gameNameString = game.name;
    std::string versionString = "GameTileView.Version";

    NVGcolor labelColor = MCDWhite;
    NVGcolor versionColor = MCDWhite;

    if (!this->supported) {
        if (this->noMods) {
            gameNameString = "[NO MODS] " + gameNameString;
            labelColor = MCDRed;
            versionColor = MCDRed;
        } else {
            versionString = "GameTileView.UnsupportedVersion";
            versionColor = MCDRed;
        }
    }

    brls::Label* gameName = new brls::Label();
    utils::trimLabelText(gameNameString, gameName, 320);
    gameName->setTextColor(labelColor);
    gameName->setMargins(10.0f, 0.0f, 0.0f, 0.0f);
    labelsContainer->addView(gameName);

    brls::Label* gameTitleId = new brls::Label();
    gameTitleId->setText(
        utils::Localization::getInterpolated("GameTileView.TitleID", {{"id", game.titleIDToString()}}));
    gameTitleId->setTextColor(labelColor);
    gameTitleId->setMargins(5.0f, 0.0f, 0.0f, 0.0f);
    labelsContainer->addView(gameTitleId);

    brls::Label* gameVersion = new brls::Label();
    gameVersion->setText(
        utils::Localization::getInterpolated(versionString, {{"version", std::to_string(game.version)}}));
    gameVersion->setTextColor(versionColor);
    gameVersion->setMargins(5.0f, 0.0f, 0.0f, 0.0f);
    labelsContainer->addView(gameVersion);
    root->addView(labelsContainer);

    addView(root);
}
}  // namespace front
