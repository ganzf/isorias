//
// Created by arroganz on 7/29/18.
//

#include "Splashscreen.hpp"
#include "Game.hpp"

namespace orias::scenes {
    Splashscreen::Splashscreen(orias::utils::Json const &config): config(config) {
        name = "Splashscreen";
        afterBuild = [this](){
            init();
        };
    }

    void Splashscreen::init() {
        phase++;
        const auto &version = config["version"];
        const auto &windowConfig = config["rendering"]["window"];
        addReaction<fengin::events::Shutdown>([this](fengin::Event &){
            entityManager->removeSystem(name);
        });
        window = &entityManager->create<Window>(windowConfig["width"].asFloat(),
                                                windowConfig["height"].asFloat(),
                                                windowConfig["title"].asString() + " (version " + version.asString() + ")");

        world = &entityManager->create<World>("SplashscreenWorld",
                                              fengin::components::World::Type::Isometric);

        camera = &entityManager->create<Camera>(window, "MainCamera");
        auto &camPos = camera->get<fengin::components::Transform>();
        camPos.position.z = 0;
        input = &entityManager->create<Input>();
        auto &_events = this->events;
        input->on(futils::Keys::Escape, [_events](){
            _events->send<fengin::events::Shutdown>();
        });
        input->on(futils::Keys::Space, [this, _events](){
            const auto _name = name;
            afterDeath = [this, _name](fengin::EntityManager *em){
                std::cout << "System " + _name + " died." << std::endl;
                em->addSystem<orias::scenes::Game>(this->camera, this->window);
            };
            entityManager->removeSystem(name);
        });

        window->setVisible(true);
        input->setActivated(true);
        camera->setActivated(true);

//        button = &entityManager->smartCreate<Button>("Play", [this](){
//            const auto _name = name;
//            afterDeath = [this, _name](futils::EntityManager *em){
//                std::cout << "System " + _name + " died." << std::endl;
//                em->addSystem<orias::scenes::Game>(this->camera);
//            };
//            entityManager->removeSystem(name);
//        });
    }

    void Splashscreen::run(float) {
        switch (phase) {
            case 0: return;
        }
    }
}