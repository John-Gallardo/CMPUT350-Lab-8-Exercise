#ifndef BASIC_TRANSFORM_H
#define BASIC_TRANSFORM_H

#include <cassert>

#include "vector_util.h"
#include <SFML/System/Vector2.hpp>

struct BasicTransform {
    // Determine if possible in general, else provide counterexample:
    // compose(f, g) is equivalent to first applying g, then applying f.
    static BasicTransform compose(const BasicTransform& f, const BasicTransform& g) {
        // Answer: I don't see why it wouldn't be possible? a BasicTransform can be represented as a single 3x3 change of basis matrix in 2D.
        // Wouldn't the composition just be equivalent to the matrix multiplication of the two matrices F & G
        // NOTE: derive this formula by turning f into a 3x3 matrix, g into a 3x3 matrix and multiply them together
        return BasicTransform(
            sf::Vector2f{f.scale.x * g.scale.x, f.scale.y * g.scale.y},
            sf::Vector2f{f.scale.x * g.translation.x + f.translation.x, f.scale.y * g.translation.y + f.translation.y}
        );
    };

    // TODO: Determine if possible in general, else provide counterexample:
    static BasicTransform inverse(const BasicTransform& f) {
        // Answer: it should be possible. There is a linear algebra theorem that says if det(F) (where F corresponds to the 3x3 matrix for the basic transform f)
        // != 0, you can take the inverse. det(F) = f.scale.x * f.scale.y * 1 since it's an upper triangular matrix.
        // since it specifies non-zero scale components, det(F) != 0 always, meaning we can always take the transpose.
        
        // formula: https://www.cuemath.com/algebra/inverse-of-3x3-matrix/
        // NOTE: derive formula by turning f into a 3x3 matrix & then plugging it into the formula
        return BasicTransform(
            sf::Vector2f{1 / f.scale.x, 1 / f.scale.y},
            sf::Vector2f{-f.translation.x / f.scale.x, -f.translation.y / f.scale.y}
        );
    };

    constexpr BasicTransform(const sf::Vector2f& scale = {1.f, 1.f},
                             const sf::Vector2f& translation = {0.f, 0.f})
        : scale{scale}, translation{translation} {}

    constexpr sf::Vector2f applyPoint(const sf::Vector2f& p) const {
        // first scale, then translate -- if you do the reverse, the translation gets messed up.
        return {p.x * scale.x + translation.x, p.y * scale.y + translation.y};
    }

    constexpr sf::Vector2f applyVector(const sf::Vector2f& p) const {
        // vectors are not translated by transformations
        return {p.x * scale.x, p.y * scale.y};
    }

    constexpr bool operator==(const BasicTransform& other) const {
        return scale == other.scale && translation == other.translation;
    }

    sf::Vector2f scale;
    sf::Vector2f translation;
};

#endif
