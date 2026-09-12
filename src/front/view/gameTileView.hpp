#pragma once

#include <borealis.hpp>
#include <core/game.hpp>

namespace front {
class GameTileView : public brls::Button {
   public:
    const core::Game& game;
    const bool supported;
    const bool noMods;
    GameTileView(const core::Game& aGame, const bool aSupported, const bool aNoMods);
};
}  // namespace front
