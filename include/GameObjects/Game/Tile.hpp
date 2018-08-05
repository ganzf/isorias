//
// Created by arroganz on 7/30/18.
//


#pragma once
#include <utils/ecs.hpp>
#include <Entities/GameObject.hpp>
#include <Components/Input.hpp>

namespace orias::game {
    class Tile: public fengin::entities::GameObject {
    public:
        Tile(fengin::vec3f pos, fengin::vec3f size) {
            afterBuild = [this, pos, size](){
                auto &tr = get<fengin::components::Transform>();
                tr.position = pos;
                tr.size = size;
            };
        }
    };
}

