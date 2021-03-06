//
// Created by arroganz on 7/30/18.
//


#pragma once

#include <fengin-core/include/events.hpp>
#include <json/Json.hpp>
#include <GameObjects/Game/Tile.hpp>
#include <fengin-base/src/Entities/Camera.hpp>

namespace orias::scenes {
    class Game: public fengin::System {
        int state{0};
        void init();
        std::vector<orias::game::Tile *> tiles;
        fengin::entities::Camera *cam;
        fengin::entities::Window *win;
    public:
        explicit Game(fengin::entities::Camera *cam, fengin::entities::Window *win) : cam(cam), win(win) {
            name = "Game";
            afterBuild = [this, cam]() {
                addReaction<fengin::events::Shutdown>([this](futils::IMediatorPacket &) {
                    entityManager->removeSystem(name);
                });
            };
        }

        virtual void run(float) final;
    };
}

