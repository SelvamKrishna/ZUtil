#include "log.hpp"
#include "ansi.hpp"

namespace zutils {

std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept
{
    static const ColorString TAGS[4] {
        ColorString { ANSI::Blue   , "[DBUG]" },
        ColorString { ANSI::Green  , "[INFO]" },
        ColorString { ANSI::Yellow , "[WARN]" },
        ColorString { ANSI::Red    , "[ERRO]" },
    };

    return os << TAGS[static_cast<size_t>(log_lvl)];
}

} // namespace zutils
