#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>

using SpriteID = size_t;

class SpriteManager {
    public:
        // 1. register texture
        sf::Texture &registerTexture(const std::string &filepath) {
            // edge case: already in -> return same reference
            if (registeredTextures.contains(filepath)) {
                return registeredTextures[filepath];
            }

            // register new texture: create from path then put into hashmap
            sf::Texture texture{filepath};
            registeredTextures[filepath] = texture;
            return registeredTextures[filepath];
        }

        // 2. create sprite
        template <typename... Args>
        SpriteID createSprite(Args&&... args) {
            // 1. create new sprite
            Sprite newSprite{std::forward<Args>(args)...};

            // 2. register into hashmap for sprites
            createdSprites[currSpriteID] = newSprite;
            return currSpriteID++;  // postfix -> move onto next ID
        }

        // 3. get sprite
        Sprite &getSprite(SpriteID id) {

        }
    private:
        // maps a string to a texture. used for 1. 
        std::unordered_map<std::string, sf::Texture> registeredTextures{};
        SpriteID currSpriteID{0};  // we start IDs at 0 and increase per created sprite
        std::unordered_map<SpriteID, Sprite> createdSprites{};
};

#endif  // SPRITE_MANAGER_H
