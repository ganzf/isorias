//
// Created by arroganz on 7/30/18.
//


#pragma once
#include <utils/rendering.hpp>
#include <utils/ecs.hpp>
#include <Entities/GameObject.hpp>
#include <Components/Input.hpp>
#include <fengin-base/src/Components/Hoverable.hpp>
#include <fengin-base/src/Components/Clickable.hpp>

namespace orias::game {
    class Tile: public fengin::entities::GameObject {
    public:
        Tile(fengin::vec3f pos, fengin::vec3f size) {
            afterBuild = [this, pos, size](){
                auto &tr = get<fengin::components::Transform>();
                tr.position = pos;
                tr.size = size;

                auto &border = get<fengin::components::Border>();
                border.visible = false;
                border.color = futils::Goldenrod;

                auto &hoverable = attach<fengin::components::Hoverable>();
                hoverable.onEnter = [this, &border]() {
                    border.visible = true;
                };
                hoverable.onLeave = [this, &border]() {
                    border.visible = false;
                };

                auto &clickable = attach<fengin::components::Clickable>();
                clickable.waitForRelease = true;
                clickable.func = [this, &tr](){
                    this->events->send<fengin::components::Transform>(tr);
                };
            };
        }
    };
}

