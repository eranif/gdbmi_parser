#ifndef WXSTRING_H
#define WXSTRING_H

#include <string>
typedef std::string wxString;
typedef char wxChar;

// define the operator <<
inline wxString& operator<<(wxString& obj, const wxString& s)
{
    obj.append(s);
    return obj;
}

inline wxString& operator<<(wxString& obj, size_t i)
{
    obj.append(std::to_string(i));
    return obj;
}

#endif // WXSTRING_H
