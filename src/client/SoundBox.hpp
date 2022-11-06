/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** SoundBox
*/

#pragma once

#include "AssetLoader.hpp"
#include <SFML/Audio.hpp>
#include <filesystem>

namespace sound {

	class SoundBox {
		public:
			/**
			 * Destroy the SoundBox object
			 */
			~SoundBox() = default;


			/**
			 * Instance of the SoundBox, lazy loaded
			 */
			static SoundBox _Instance;
	};


}