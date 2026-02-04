#pragma once

namespace zutil {

enum class BuildMode {
    Debug,
    Release,
};

#ifdef NDEBUG
inline constexpr BuildMode CURRENT_BUILD = BuildMode::Release;
#else
inline constexpr BuildMode CURRENT_BUILD = BuildMode::Debug;
#endif

} // namespace zutil
