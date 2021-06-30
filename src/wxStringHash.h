#ifndef WXSTRING_HASH
#define WXSTRING_HASH

#include <unordered_map>
#include <unordered_set>

#if defined(wxVERSION_NUMBER) && (wxVERSION_NUMBER < 3100)
#include <functional>
#include <wx/string.h>
#include <wx/version.h>

namespace std
{
template <> struct hash<wxString> {
    std::size_t operator()(const wxString& s) const { return hash<std::wstring>{}(s.ToStdWstring()); }
};
} // namespace std
#endif

#endif // WXSTRING_HASH