#include "GDBMI.hpp"
#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include <absl/strings/match.h>
#include <cctype>
#include <memory>
#include <stdexcept>
#include <unordered_set>

namespace
{
absl::flat_hash_map<absl::string_view, gdbmi::eToken> words = {
    { "done", gdbmi::T_DONE },   { "running", gdbmi::T_RUNNING }, { "connected", gdbmi::T_CONNECTED },
    { "error", gdbmi::T_ERROR }, { "exit", gdbmi::T_EXIT },       { "stopped", gdbmi::T_STOPPED },
};
}
#define CHECK_EOF()                      \
    {                                    \
        if(m_buffer.length() == m_pos) { \
            *type = T_EOF;               \
            return {};                   \
        }                                \
    }

#define RETURN_TYPE(ret_type)                                     \
    {                                                             \
        *type = ret_type;                                         \
        ++m_pos;                                                  \
        return absl::string_view(m_buffer.data() + m_pos - 1, 1); \
    }

gdbmi::Tokenizer::Tokenizer(absl::string_view buffer)
    : m_buffer(buffer)
{
}

absl::string_view gdbmi::Tokenizer::next_token(eToken* type)
{
    *type = T_EOF;
    absl::string_view curbuf;

    // skip leading whitespaces
    for(; m_pos < m_buffer.length(); ++m_pos) {
        if(m_buffer[m_pos] == ' ' || m_buffer[m_pos] == '\t') {
            continue;
        }
        break;
    }

    CHECK_EOF();
    switch(m_buffer[m_pos]) {
    case '{':
        RETURN_TYPE(T_TUPLE_OPEN);
    case '}':
        RETURN_TYPE(T_TUPLE_CLOSE);
    case '[':
        RETURN_TYPE(T_LIST_OPEN);
    case ']':
        RETURN_TYPE(T_LIST_CLOSE);
    case '=':
        RETURN_TYPE(T_EQUAL);
    case '^':
        RETURN_TYPE(T_POW);
    case '*':
        RETURN_TYPE(T_STAR);
    case '+':
        RETURN_TYPE(T_PLUS);
    case '@':
        RETURN_TYPE(T_TARGET_OUTPUT);
    case '&':
        RETURN_TYPE(T_LOG_OUTPUT);
    case '~':
        RETURN_TYPE(T_STREAM_OUTPUT);
    case ',':
        RETURN_TYPE(T_COMMA);
    default:
        break;
    }

    if(m_buffer[m_pos] == '"') {
        // c-string
        ++m_pos;
        return read_string(type);
    } else {

        auto w = read_word(type);
        if(words.contains(w)) {
            *type = words[w];
            return w;
        } else {
            *type = T_WORD;
            return w;
        }
    }
}

absl::string_view gdbmi::Tokenizer::read_string(eToken* type)
{
    constexpr int STATE_NORMAL = 0;
    constexpr int STATE_IN_ESCAPE = 1;

    int state = STATE_NORMAL;
    size_t start_pos = m_pos;
    for(; m_pos < m_buffer.length(); ++m_pos) {
        char ch = m_buffer[m_pos];
        switch(state) {
        case STATE_NORMAL:
            switch(ch) {
            case '"': {
                *type = T_CSTRING;
                auto cstr = absl::string_view(m_buffer.data() + start_pos, m_pos - start_pos);
                // now move the position
                m_pos++;
                return cstr;
            }
            case '\\':
                state = STATE_IN_ESCAPE;
                break;
            default:
                break; // let the m_pos progress
            }
            break;
        case STATE_IN_ESCAPE:
        default:
            // we have nothing to do in this state, but only skip the escaped char
            // and return to the normal state
            state = STATE_NORMAL;
            break;
        }
    }

    // if we reached here, it means that the buffer is in complete
    *type = T_EOF;
    return {};
}

absl::string_view gdbmi::Tokenizer::read_word(eToken* type)
{
    size_t start_pos = m_pos;
    while(std::isalnum(m_buffer[m_pos]) || m_buffer[m_pos] == '-' || m_buffer[m_pos] == '_') {
        ++m_pos;
    }
    *type = T_WORD;
    return absl::string_view(m_buffer.data() + start_pos, m_pos - start_pos);
}
