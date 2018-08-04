//
// Created by arroganz on 7/30/18.
//


#pragma once
#include <utils/ecs.hpp>
#include <Entities/GameObject.hpp>
#include <Components/Image.hpp>
#include <Components/Input.hpp>
#include <Components/rigidBody.hpp>

namespace orias::game {
    class Player: public fengin::entities::GameObject {
        fengin::components::rigidBody *rigidBody;
    public:
        Player() {
            afterBuild = [this](){
                this->setPosition(0, 0);
                this->setSize(3, 3);
                auto &img = this->attach<fengin::components::Image>();
                img.file = "ship.png";
                auto &input = this->attach<fengin::components::Input>();
                input.activated = true;
                input.name = "PlayerActions";
                rigidBody = &attach<fengin::components::rigidBody>();
                rigidBody->weight = 100;
                input.map[futils::Keys::ArrowRight] = [this](){
                    rigidBody->force.x += 1;
                };
                input.map[futils::Keys::ArrowLeft] = [this](){
                    rigidBody->force.x -= 1;
                };
            };
        }

        ~Player() {
            detach<fengin::components::Image>();
            detach<fengin::components::Input>();
        }
    };
}

