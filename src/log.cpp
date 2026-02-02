#include "log.hpp"
#include "ansi.hpp"

namespace zutil {

std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept
{
    static const ColorString TAGS[4] {
        { ANSI::Blue   , "[DBUG]" },
        { ANSI::Green  , "[INFO]" },
        { ANSI::Yellow , "[WARN]" },
        { ANSI::Red    , "[ERRO]" },
    };

    return os << "\n" << TAGS[static_cast<size_t>(log_lvl)] << " : ";
}

} // namespace zutil
