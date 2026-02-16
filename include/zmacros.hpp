#pragma once

#define Z_VAR_SPLAT(variable) \
    "{} = ({})", ::zutil::ProString{::zutil::ANSI::Magenta, #variable}, (variable)

#define Z_CND_SPLAT(condition) \
    (condition), {"{}", #condition}
