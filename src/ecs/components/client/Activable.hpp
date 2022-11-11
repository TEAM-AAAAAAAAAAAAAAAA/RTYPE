/*
** EPITECH PROJECT, by hourcadettej on 11/11/22.
** rtype
** File description:
** rtype
*/

#pragma once
#include "Constant.hpp"

namespace ecs::component
{
    struct Activable {

        Activable(bool isActivate = true, bool isButton = false, utils::constant::ButtonType buttonType = utils::constant::UNDEFINED) : _isActivate(isActivate), _isButton(isButton), _buttonType(buttonType), _isHover(false), _lastSwitch(0){}

        inline void setIsActivate(bool isActivate) { _isActivate = isActivate;};
        inline bool getIsActivate() const {return _isActivate;};
        inline void setIsButton(bool isButton) {_isButton = isButton;};
        inline bool getIsButton() const {return _isButton;};
        inline void setIsHover(bool isHover) {_isHover = isHover;};
        inline bool getIsHover() const {return _isHover;};
        inline void setButtonType(utils::constant::ButtonType buttonType) {_buttonType = buttonType;};
        inline utils::constant::ButtonType getButtonType() {return _buttonType;};
        inline void switchSetIsActivate() {_isActivate = !_isActivate;};
        inline int64_t getLastSwitch() const {return _lastSwitch;};
        inline void setLastSwitch(int64_t time) {_lastSwitch = time;};

      private:
        bool _isActivate;
        bool _isButton;
        bool _isHover;
        utils::constant::ButtonType _buttonType;
        int64_t _lastSwitch;
    };
} // namespace ecs::component
