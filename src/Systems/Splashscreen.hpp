//
// Created by arroganz on 7/29/18.
//


#pragma once

# include "fengin-core/include/events.hpp"
# include "fengin-core/include/FenginCore.hpp"
# include "utils/rendering.hpp"
# include "utils/inputKeys.hpp"

# include "Entities/Window.hpp"
# include "Entities/World.hpp"
# include "Entities/Camera.hpp"
# include "Entities/Input.hpp"

# include "GameObjects/UI/MenuButton.hpp"
# include "GameObjects/UI/Window.hpp"
# include "json/Json.hpp"

namespace orias::scenes {
    using Window = orias::ui::Window;
    using World = fengin::entities::World;
    using Camera = fengin::entities::Camera;
    using Input = fengin::entities::Input;
    using Button = orias::ui::MenuButton;

    class Splashscreen : public fengin::System {
        int phase{0};
        orias::utils::Json const &config;
        Window *window{nullptr};
        World *world{nullptr};
        Camera *camera{nullptr};
        Input *input{nullptr};
        Button *button{nullptr};

        void init();
    public:
        Splashscreen(orias::utils::Json const &config);
        virtual void run(float) final;
    };
}

