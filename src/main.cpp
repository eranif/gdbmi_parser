#include "gdbmi.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

int main(int argc, char** argv)
{
    // 00000372^done,stack=[frame={level="0",addr="0x00007ff77a9853b0",func="gdbmi::ParsedResult::operator[]",file="C:/src/gdbmi_parser/src/gdbmi.hpp",fullname="C:\\src\\gdbmi_parser\\src\\gdbmi.hpp",line="132",arch="i386:x86-64"},frame={level="1",addr="0x00007ff77a9816ec",func="main",file="C:\\src\\gdbmi_parser\\src\\main.cpp",fullname="C:\\src\\gdbmi_parser\\src\\main.cpp",line="20",arch="i386:x86-64"}]

    std::string input_str =
        R"str(00000372^done,stack=[frame={level="0",addr="0x00007ff77a9853b0",func="gdbmi::ParsedResult::operator[]",file="C:/src/gdbmi_parser/src/gdbmi.hpp",fullname="C:\\src\\gdbmi_parser\\src\\gdbmi.hpp",line="132",arch="i386:x86-64"},frame={level="1",addr="0x00007ff77a9816ec",func="main",file="C:\\src\\gdbmi_parser\\src\\main.cpp",fullname="C:\\src\\gdbmi_parser\\src\\main.cpp",line="20",arch="i386:x86-64"}])str";

    gdbmi::Parser parser;
    {
        gdbmi::ParsedResult result;
        parser.parse(input_str, &result);
        parser.print(result.tree);

        std::cout << result["stack"][0]["level"].value << " " << std::endl;
        std::cout << result["stack"][1]["level"].value << " " << std::endl;
    }
    return 0;
}
