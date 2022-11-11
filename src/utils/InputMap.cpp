/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputMap
*/

#include "InputMap.hpp"
#include <exception>
#include <map>
#include <stdexcept>
#include <vector>

namespace utils
{
    /**
     * @brief Bidirectional map between sf::Keyboard::Key and std::string
     */
    template <typename T>
    class InputMap {
        static_assert(!std::is_same<T, std::string>::value, "InputMap: T cannot be std::string");

      public:
        explicit InputMap(std::size_t keySize) : _stringsVector(keySize), _map() {}

        void insert(T t, const std::string &string)
        {
            _stringsVector[t] = string;
            _map[string] = t;
        }

        /**
         * @throw std::out_of_range if string is not in the map
         */
        [[nodiscard]] const std::string& at(T t) const
        {
            auto idx = static_cast<std::size_t>(t);
            if (idx >= _stringsVector.size())
                throw std::out_of_range("InputMap: index out of range");
            else
                return _stringsVector[idx];
        }

        /**
         * @throw std::out_of_range if string is not in the map
         */
        T at(const std::string& string) const
        {
            auto it = _map.find(string);
            if (it == _map.end())
                throw std::out_of_range("InputMap: string not found");
            else
                return it->second;
        }
      private:
        std::vector<std::string> _stringsVector;
        std::map<std::string, T> _map;
    };

    InputMap<sf::Keyboard::Key> initMap(sf::Keyboard::Key) {
        InputMap<sf::Keyboard::Key> map(sf::Keyboard::Key::KeyCount);

        #define RTYPE_INSERT_MAP(id) map.insert(sf::Keyboard::Key::id, #id)

        RTYPE_INSERT_MAP(Unknown);
        RTYPE_INSERT_MAP(A);
        RTYPE_INSERT_MAP(B);
        RTYPE_INSERT_MAP(C);
        RTYPE_INSERT_MAP(D);
        RTYPE_INSERT_MAP(E);
        RTYPE_INSERT_MAP(F);
        RTYPE_INSERT_MAP(G);
        RTYPE_INSERT_MAP(H);
        RTYPE_INSERT_MAP(I);
        RTYPE_INSERT_MAP(J);
        RTYPE_INSERT_MAP(K);
        RTYPE_INSERT_MAP(L);
        RTYPE_INSERT_MAP(M);
        RTYPE_INSERT_MAP(N);
        RTYPE_INSERT_MAP(O);
        RTYPE_INSERT_MAP(P);
        RTYPE_INSERT_MAP(Q);
        RTYPE_INSERT_MAP(R);
        RTYPE_INSERT_MAP(S);
        RTYPE_INSERT_MAP(T);
        RTYPE_INSERT_MAP(U);
        RTYPE_INSERT_MAP(V);
        RTYPE_INSERT_MAP(W);
        RTYPE_INSERT_MAP(X);
        RTYPE_INSERT_MAP(Y);
        RTYPE_INSERT_MAP(Z);
        RTYPE_INSERT_MAP(Num0);
        RTYPE_INSERT_MAP(Num1);
        RTYPE_INSERT_MAP(Num2);
        RTYPE_INSERT_MAP(Num3);
        RTYPE_INSERT_MAP(Num4);
        RTYPE_INSERT_MAP(Num5);
        RTYPE_INSERT_MAP(Num6);
        RTYPE_INSERT_MAP(Num7);
        RTYPE_INSERT_MAP(Num8);
        RTYPE_INSERT_MAP(Num9);
        RTYPE_INSERT_MAP(Escape);
        RTYPE_INSERT_MAP(LControl);
        RTYPE_INSERT_MAP(LShift);
        RTYPE_INSERT_MAP(LAlt);
        RTYPE_INSERT_MAP(LSystem);
        RTYPE_INSERT_MAP(RControl);
        RTYPE_INSERT_MAP(RShift);
        RTYPE_INSERT_MAP(RAlt);
        RTYPE_INSERT_MAP(RSystem);
        RTYPE_INSERT_MAP(Menu);
        RTYPE_INSERT_MAP(LBracket);
        RTYPE_INSERT_MAP(RBracket);
        RTYPE_INSERT_MAP(SemiColon);
        RTYPE_INSERT_MAP(Comma);
        RTYPE_INSERT_MAP(Period);
        RTYPE_INSERT_MAP(Quote);
        RTYPE_INSERT_MAP(Slash);
        RTYPE_INSERT_MAP(BackSlash);
        RTYPE_INSERT_MAP(Tilde);
        RTYPE_INSERT_MAP(Equal);
        RTYPE_INSERT_MAP(Dash);
        RTYPE_INSERT_MAP(Space);
        RTYPE_INSERT_MAP(Return);
        RTYPE_INSERT_MAP(BackSpace);
        RTYPE_INSERT_MAP(Tab);
        RTYPE_INSERT_MAP(PageUp);
        RTYPE_INSERT_MAP(PageDown);
        RTYPE_INSERT_MAP(End);
        RTYPE_INSERT_MAP(Home);
        RTYPE_INSERT_MAP(Insert);
        RTYPE_INSERT_MAP(Delete);
        RTYPE_INSERT_MAP(Add);
        RTYPE_INSERT_MAP(Subtract);
        RTYPE_INSERT_MAP(Multiply);
        RTYPE_INSERT_MAP(Divide);
        RTYPE_INSERT_MAP(Left);
        RTYPE_INSERT_MAP(Right);
        RTYPE_INSERT_MAP(Up);
        RTYPE_INSERT_MAP(Down);
        RTYPE_INSERT_MAP(Numpad0);
        RTYPE_INSERT_MAP(Numpad1);
        RTYPE_INSERT_MAP(Numpad2);
        RTYPE_INSERT_MAP(Numpad3);
        RTYPE_INSERT_MAP(Numpad4);
        RTYPE_INSERT_MAP(Numpad5);
        RTYPE_INSERT_MAP(Numpad6);
        RTYPE_INSERT_MAP(Numpad7);
        RTYPE_INSERT_MAP(Numpad8);
        RTYPE_INSERT_MAP(Numpad9);
        RTYPE_INSERT_MAP(F1);
        RTYPE_INSERT_MAP(F2);
        RTYPE_INSERT_MAP(F3);
        RTYPE_INSERT_MAP(F4);
        RTYPE_INSERT_MAP(F5);
        RTYPE_INSERT_MAP(F6);
        RTYPE_INSERT_MAP(F7);
        RTYPE_INSERT_MAP(F8);
        RTYPE_INSERT_MAP(F9);
        RTYPE_INSERT_MAP(F10);
        RTYPE_INSERT_MAP(F11);
        RTYPE_INSERT_MAP(F12);
        RTYPE_INSERT_MAP(F13);
        RTYPE_INSERT_MAP(F14);
        RTYPE_INSERT_MAP(F15);
        RTYPE_INSERT_MAP(Pause);

        #undef RTYPE_INSERT_MAP

        static_assert(sf::Keyboard::KeyCount == 101, "sf::Keyboard::KeyCount has changed, please update the initMap function");
        return map;
    }

    template <typename T>
    InputMap<T>& getInstance()
    {
        static InputMap<T> map = initMap(T::KeyCount);
        return map;
    }

    std::string toString(sf::Keyboard::Key key) {
        return getInstance<sf::Keyboard::Key>().at(key);
    }

    sf::Keyboard::Key toKey(const std::string& str) {
        return getInstance<sf::Keyboard::Key>().at(str);
    }
}; // namespace utils