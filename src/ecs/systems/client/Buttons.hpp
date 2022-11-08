/*
** EPITECH PROJECT, 2022
** R-TYPEMIRROR
** File description:
** Buttons
*/

#ifndef BUTTONS_HPP_
#define BUTTONS_HPP_

#include <functional>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "World.hpp"
#include "components/client/Activable.hpp"

namespace ecs::systems
{
    std::function<void(World &)> buttons = [](World &world) {
        auto &activable = world.registry.getComponents<component::Activable>();
        auto &positions = world.registry.getComponents<component::Position>();
        auto &controllabe = world.registry.getComponents<component::Controllable>();

        for (size_t i = 0; i < activable.size() && i < positions.size(); ++i) {
            auto &act = activable[i];
            auto &pos = positions[i];
            auto &cont = controllabe[i];
            if (act && pos) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && act->getHover()) {
                    std::cout << "Space" << std::endl;
                    act.value().setSelected(true);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    std::cout << "Up" << std::endl;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && act->getHover()) {
                    std::cout << "Down" << std::endl;
                    for (int i = 0; i < activable.size(); ++i) {
                        auto &actmp = activable[i];
                        if (actmp && actmp->getHover()) {
                            actmp.value().setHover(false);
                            std::cout << i << std::endl;
                            if (i + 1 < activable.size()) {
                                auto &actmp2 = activable[i + 1];
                                actmp2.value().setHover(true);
                            } else {
                                auto &actmp2 = activable[0];
                                actmp2.value().setHover(true);
                            }
                            break;
                        }
                        // if (actmp->getHover()) {
                        //     std::cout << i << std::endl;
                        //     if (i == 0) {
                        //         std::cout << "i == 0\n\n\n" << std::endl;
                        //         actmp.value().setHover(false);
                        //         activable[1].value().setHover(true);
                        //         break;
                        //     } else if (i == 1) {
                        //         std::cout << "i == 1\n\n\n" << std::endl;
                        //         actmp.value().setHover(false);
                        //         activable[2].value().setHover(true);
                        //         break;
                        //     } else if (i == 2) {
                        //         std::cout << "i == 2\n\n\n" << std::endl;
                        //         actmp.value().setHover(false);
                        //         activable[0].value().setHover(true);
                        //         break;
                        //     }
                        // }
                    }
                }
                if (act.value().getHover()) {
                    std::cout << "Button " << i << " is hover" << std::endl;
                    // std::cout << "At position " << pos.value().x << " " << pos.value().y << std::endl;
                } else
                    std::cout << "Button " << i << " is not hover" << std::endl;
                std::cout << "At position " << pos.value().x << " " << pos.value().y << std::endl;
                if (act.value().getSelected()) {
                    // doAction(act.value().getType());
                    std::cout << "Button " << i << " is selected" << std::endl;
                }
                std::cout << "Button type " << i << act.value().getType() << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
    };
} // namespace ecs::systems

#endif /* !BUTTONS_HPP_ */
