//
// Created by arroganz on 7/30/18.
//


#pragma once

#include <fengin-core/include/events.hpp>
#include <utils/ecs.hpp>
#include <json/Json.hpp>
#include <GameObjects/Game/Tile.hpp>
#include <fengin-base/src/Entities/Camera.hpp>

namespace orias::scenes {
    class Game: public futils::ISystem {
        int state{0};
        void init();
        std::vector<orias::game::Tile *> tiles;
        fengin::entities::Camera *cam;
    public:
        explicit Game(fengin::entities::Camera *cam) : cam(cam) {
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

