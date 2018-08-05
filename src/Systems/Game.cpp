//
// Created by arroganz on 7/30/18.
//

#include "Game.hpp"

namespace orias::scenes {
    void Game::run(float) {
        switch (state) {
            case 0: return this->init();
            case 1: return;
        }
    }

    void Game::init() {
        state++;
        auto addTile = [this](float x, float y, float z){
            fengin::vec3f pos;
            pos.x = x;
            pos.y = y;
            pos.z = z;
            auto *t = &entityManager->smartCreate<orias::game::Tile>(pos, fengin::vec3f(1, 1, 1));
            events->send<fengin::components::Transform>(t->get<fengin::components::Transform>());
            this->tiles.push_back(t);
        };
        addTile(0, 0, 1.5);
        addTile(1, 0, 1);
        addTile(0, 1, 1);
        addTile(0, -1, 1);
        addTile(-1, 0, 1);
        const auto move = [this](float x, float y) {
            this->cam->setPosition(this->cam->getPosition().x + x, this->cam->getPosition().y + y);
            events->send<std::string>(
                    "Position: " +
                    std::to_string(this->cam->getPosition().x)
                    + ", "
                    + std::to_string(this->cam->getPosition().y)
            );
        };
        addReaction<futils::Keys>([this, move](futils::IMediatorPacket &pkg){
            const auto &key = futils::Mediator::rebuild<futils::Keys>(pkg);
            std::cout << "Received key" << std::endl;
            if (key == futils::Keys::ArrowLeft)
                move(1, -1);
            if (key == futils::Keys::ArrowRight)
                move(-1, 1);
            if (key == futils::Keys::ArrowUp)
                move(1, 1);
            if (key == futils::Keys::ArrowDown)
                move(-1, -1);
        });
        std::cout << "Initialized" << std::endl;
    }
}