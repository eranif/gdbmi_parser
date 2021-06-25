#include "gdbmi.hpp"
#include <string>

int main(int argc, char** argv)
{
    std::string input_str =
        R"str(00000010^done,BreakpointTable={nr_rows="1",nr_cols="6",hdr=[{width="7",alignment="-1",col_name="number",colhdr="Num"},{width="14",alignment="-1",col_name="type",colhdr="Type"},{width="4",alignment="-1",col_name="disp",colhdr="Disp"},{width="3",alignment="-1",col_name="enabled",colhdr="Enb"},{width="18",alignment="-1",col_name="addr",colhdr="Address"},{width="40",alignment="2",col_name="what",colhdr="What"}],body=[bkpt={number="1",type="breakpoint",disp="keep",enabled="y",addr="0x00007ff791f31599",func="main(int,char**)",file="C:\\src\\gdbmi_parser\\src\\main.cpp",fullname="C:\\src\\gdbmi_parser\\src\\main.cpp",line="11",thread-groups=["i1"],times="1",original-location="C:/src/gdbmi_parser/src/main.cpp:11"}]})str";
    gdbmi::Tokenizer tokenizer(input_str);
    gdbmi::eToken token;

    while(true) {
        auto str = tokenizer.next_token(&token);
        if(token == gdbmi::T_EOF) {
            break;
        }
        std::cout << token << ": " << str << std::endl;
    }
    return 0;
}
