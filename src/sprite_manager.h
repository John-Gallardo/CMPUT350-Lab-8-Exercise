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
            createdSprites.emplace_back(std::forward<Args>(args)...);

            // 2. return ID: should be vector's size - 1
            return createdSprites.size() - 1;
        }

        // 3. get sprite
        Sprite &getSprite(SpriteID id) {
            return createdSprites[id];
        }
    private:
        // maps a string to a texture. used for 1. 
        std::unordered_map<std::string, sf::Texture> registeredTextures{};
        std::vector<Sprite> createdSprites{};
};

#endif  // SPRITE_MANAGER_H
