#include "GDBMI.hpp"
#include "absl/strings/string_view.h"
#include <absl/strings/match.h>
#include <exception>

namespace
{
constexpr size_t NOT_FOUND = absl::string_view::npos;
}

GDBMI::GDBMI()
{
}

GDBMI::~GDBMI()
{
}

void GDBMI::parse(absl::string_view line)
{
    m_curpos = 0;
    m_buffer = line;

    // search for the result-record
    // [ token ] "^" result-class ( "," result )* nl
    auto where = m_buffer.find('^', m_curpos);
    if(where == NOT_FOUND) {
        // invalid line
        throw GDBMIException("could not find ^ in line");
    }
}
