//
// Created by arroganz on 7/29/18.
//


#pragma once

# include <Components/Text.hpp>
# include <Entities/Button.hpp>

using FenginButton = fengin::entities::Button;

namespace orias::ui {
    class Button : public FenginButton {
    public:
        Button(std::string const &label, float width, float height, int fontSize): FenginButton(label) {
            afterBuild = [this, label, width, height, fontSize](){
                this->setSize(width, height);
                auto &text = get<fengin::components::Text>();
                text.str = label;
                text.style.size = fontSize;
                text.style.font = "arial.ttf";
                text.style.valign = futils::VAlign::Middle;
                text.style.align = futils::Align::Center;
            };
        }
    };
}

