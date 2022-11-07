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
                // if (sf::Keyboard::isKeyPressed(cont.value().MoveUp)) {

                // }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && act->getHidle()) {
                    std::cout << "Space" << std::endl;
                    act.value().setSelected(true);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    std::cout << "Up" << std::endl;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    std::cout << "Down" << std::endl;
                    for (int i = 0; i < activable.size(); ++i) {
                        auto &actmp = activable[i];
                        if (actmp->getHidle()) {
                            std::cout << i << std::endl;
                            if (i == 0) {
                                std::cout << "i == 0\n\n\n" << std::endl;
                                actmp.value().setHidle(false);
                                activable[1].value().setHidle(true);
                                break;
                            } else if (i == 1) {
                                std::cout << "i == 1\n\n\n" << std::endl;
                                actmp.value().setHidle(false);
                                activable[2].value().setHidle(true);
                                break;
                            } else if (i == 2) {
                                std::cout << "i == 2\n\n\n" << std::endl;
                                actmp.value().setHidle(false);
                                activable[0].value().setHidle(true);
                                break;
                            }
                        }
                    }
                }
                if (act.value().getHidle()) {
                    std::cout << "Button " << i << " is hidle" << std::endl;
                    std::cout << "At position " << pos.value().x << " " << pos.value().y << std::endl;
                } else
                    std::cout << "Button " << i << " is not hidle" << std::endl;
                std::cout << "At position " << pos.value().x << " " << pos.value().y << std::endl;
                if (act.value().getSelected()) {
                    // doAction(act.value().getType());
                    std::cout << "Button " << i << " is selected" << std::endl;
                }
                std::cout << "Button type " << i << act.value().getType() << std::endl;
            }
        }
    };
} // namespace ecs::systems

#endif /* !BUTTONS_HPP_ */
