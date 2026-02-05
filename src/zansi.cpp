#include "zansi.hpp"

namespace zutil {

std::ostream& operator<<(std::ostream& os, const ANSI& ansi) noexcept
{
    return os << "\033[" << static_cast<int>(ansi) << "m";
}

} // namespace zutil
