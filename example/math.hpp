#pragma once

#include "../zen/math/angle.hpp"
#include "../zen/math/constants.hpp"
#include "../zen/math/vec2.hpp"
#include "../zen/math/utils.hpp"

#include "../zen/core/test.hpp"
#include "../zen/core/macros.hpp"

#include <cassert>

namespace example {

    inline void AngleBasic() noexcept
    {
        zen::core::TestSuite test {__PRETTY_FUNCTION__};

        auto a = zen::math::Angle::FromDegrees(90.0f);
        auto b = zen::math::Angle::FromRadians(zen::constants::F32_PI / 2.0f);

        test.AddCase(Z_CND_SPLAT(a.AsDegrees() == 90.0f));
        test.AddCase(Z_CND_SPLAT(b.AsDegrees() == 90.0f));
        test.AddCase(Z_CND_SPLAT(a == b));
    }

    inline void AngleArithmetic() noexcept
    {
        zen::core::TestSuite test {__PRETTY_FUNCTION__};

        auto a = zen::math::Angle::FromDegrees(30.0f);
        auto b = zen::math::Angle::FromDegrees(60.0f);

        auto c = a + b;
        test.AddCase(Z_CND_SPLAT(c.AsDegrees() == 90.0f));

        auto d = b - a;
        test.AddCase(Z_CND_SPLAT(d.AsDegrees() == 30.0f));

        auto angle450 = zen::math::Angle::FromDegrees(450);
        test.AddCase(Z_CND_SPLAT(zen::math::NearlyEqual(angle450.Normalized().AsDegrees(), 90.0f)));
    }

    inline void Vec2Basic() noexcept
    {
        zen::core::TestSuite test {__PRETTY_FUNCTION__};

        zen::math::Vec2f v1 {3.0f, 4.0f};

        test.AddCase(Z_CND_SPLAT(v1.x == 3.0f));
        test.AddCase(Z_CND_SPLAT(v1.y == 4.0f));
        test.AddCase(Z_CND_SPLAT(v1.Length() == 5.0f));
    }

    inline void Vec2Arithmetic() noexcept
    {
        zen::core::TestSuite test {__PRETTY_FUNCTION__};
        test.AddCase(Z_CND_SPLAT(zen::math::DotProduct<zen::f32>({1.0f, 2.0f}, {3.0f, 4.0f}) == 11.0f));
        test.AddCase(Z_CND_SPLAT(zen::math::CrossProduct<zen::f32>({1.0f, 0.0f}, {0.0f, 1.0f}) == 1.0f));

        zen::math::Vec2f a {1.0f, 2.0f};
        zen::math::Vec2f b {3.0f, 4.0f};

        auto c = a + b;
        auto d = b - a;

        test.AddCase(Z_CND_SPLAT(zen::math::NearlyEqual(c, {4.0f, 6.0f})));
        test.AddCase(Z_CND_SPLAT(zen::math::NearlyEqual(d, {2.0f, 2.0f})));
    }

    inline void Vec2Advanced() noexcept
    {
        zen::core::TestSuite test {__PRETTY_FUNCTION__};
        zen::math::Vec2f a {0.0f, 0.0f};
        zen::math::Vec2f b {3.0f, 4.0f};

        test.AddCase(Z_CND_SPLAT(zen::math::NearlyEqual(b.Normalized(), {0.6f, 0.8f})));
        test.AddCase(Z_CND_SPLAT(a.Distance(b) == 5.0f));
    }

} // namespace example
