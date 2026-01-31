#include "ansi.hpp"

namespace zutils {

std::ostream& operator<<(std::ostream& os, const ANSI& ansi) noexcept
{
    return os << "\033[" << static_cast<int>(ansi) << "m";
}

} // namespace zutils
