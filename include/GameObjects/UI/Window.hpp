//
// Created by arroganz on 7/30/18.
//


#pragma once

#include <Entities/Window.hpp>

using FenginWindow = fengin::entities::Window;

namespace orias::ui {
    class Window : public FenginWindow {
    public:
        Window(float width, float height, std::string const &title):
                FenginWindow(width, height, title, futils::WStyle::Default, futils::Granite)
        {

        }
    };
}

