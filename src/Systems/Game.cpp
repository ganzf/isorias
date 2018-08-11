//
// Created by arroganz on 7/30/18.
//

#include <GameObjects/UI/Button.hpp>
#include <Entities/Window.hpp>
#include "Game.hpp"
#include "Components/rigidBody.hpp"
#include "Components/Billboard.hpp"

namespace orias::scenes {
    void Game::run(float) {
        switch (state) {
            case 0: return this->init();
            case 1: return;
        }
    }

    void Game::init() {
        orias::utils::Json config("./config.json");
        auto const &map = config["game"]["map"];
        state++;
        auto addTile = [this](float x, float y, float z){
            fengin::vec3f pos;
            pos.x = x;
            pos.y = y;
            pos.z = z;
            auto *t = &entityManager->smartCreate<orias::game::Tile>(pos, fengin::vec3f(1, 1, 1));
//            events->send<fengin::components::Transform>(t->get<fengin::components::Transform>());
            this->tiles.push_back(t);
            return t;
        };
        auto *billboard = addTile(0, 0, 0.1f);
        billboard->attach<fengin::components::Billboard>();
        auto &btr = billboard->get<fengin::components::Transform>();
        btr.size.z = 1.0f;
        btr.size.y = 0.1f;
        btr.position.z = 0.5f;
        for (auto const &tile: map) {
            auto *t = addTile(tile[0].asFloat(), tile[1].asFloat(), tile[2].asFloat());
            t->get<fengin::components::Transform>().rotation.x = 60;
            auto &onClick = t->get<fengin::components::Clickable>();
            onClick.waitForRelease = true;
            onClick.func = [this, t](){
                cam->setFocusOn(*t);
                const auto &camPos = cam->get<fengin::components::Transform>();
                win->setTitle("Cam:" + std::to_string(camPos.position.x) + " " +
                              std::to_string(camPos.position.y) + " " +
                              std::to_string(camPos.position.z));
            };
        }
        const auto move = [this](float x, float y) {
            this->cam->setPosition(this->cam->getPosition().x + x, this->cam->getPosition().y + y);
            events->send<std::string>(
                    "Position: " +
                    std::to_string(this->cam->getPosition().x)
                    + ", "
                    + std::to_string(this->cam->getPosition().y)
            );
        };
        const auto zoom = [this](float delta){
            auto &camComponent = this->cam->get<fengin::components::Camera>();
            camComponent.zoom += delta;
        };
        addReaction<futils::Keys>([this, move, zoom](futils::IMediatorPacket &pkg){
            const auto &key = futils::Mediator::rebuild<futils::Keys>(pkg);
            std::cout << "Received key" << std::endl;
            if (key == futils::Keys::ArrowUp)
                move(1, -1);
            if (key == futils::Keys::ArrowDown)
                move(-1, 1);
            if (key == futils::Keys::ArrowLeft)
                move(1, 1);
            if (key == futils::Keys::ArrowRight)
                move(-1, -1);
            if (key == futils::Keys::Q) {
                zoom(10);
            }
            if (key == futils::Keys::W) {
                zoom(-10);
            }
        });
        std::cout << "Initialized" << std::endl;
    }
}