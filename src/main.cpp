#include "absl/container/flat_hash_map.h"
#include "absl/strings/string_view.h"
#include "gdbmi.hpp"
#include <memory>
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    std::string input_str =
        R"str(00000010^done,BreakpointTable={nr_rows="1",nr_cols="6",hdr=[{width="7",alignment="-1",col_name="number",colhdr="Num"},{width="14",alignment="-1",col_name="type",colhdr="Type"},{width="4",alignment="-1",col_name="disp",colhdr="Disp"},{width="3",alignment="-1",col_name="enabled",colhdr="Enb"},{width="18",alignment="-1",col_name="addr",colhdr="Address"},{width="40",alignment="2",col_name="what",colhdr="What"}],body=[bkpt={number="1",type="breakpoint",disp="keep",enabled="y",addr="0x00007ff791f31599",func="main(int,char**)",file="C:\\src\\gdbmi_parser\\src\\main.cpp",fullname="C:\\src\\gdbmi_parser\\src\\main.cpp",line="11",thread-groups=["i1"],times="1",original-location="C:/src/gdbmi_parser/src/main.cpp:11"}]})str";

    std::string input_str_2 =
        R"str(00001547^done,variables=[{name="vt",value="{first = <error reading variable: Cannot access memory at address 0x1>"},{name="__for_range",value="<error reading variable>"},{name="__for_begin",value="{ctrl_ = 0x2345e170000 \"\", {slot_ = 0x50000061}}"},{name="__for_end",value="{ctrl_ = 0x2345e1712c0 \"\\a\", {slot_ = 0x7ffb4c33cc48 <ntdll!memset+26376>}}"},{name="argc",arg="1",value="1"},{name="argv",arg="1",value="0x2345e171900"},{name="input_str",value="\"00000010^done,BreakpointTable={nr_rows=\\\"1\\\",nr_cols=\\\"6\\\",hdr=[{width=\\\"7\\\",alignment=\\\"-1\\\",col_name=\\\"number\\\",colhdr=\\\"Num\\\"},{width=\\\"14\\\",alignment=\\\"-1\\\",col_name=\\\"type\\\",colhdr=\\\"Type\\\"},{width=\\\"4\\\",alignment=\\\"-1\"..."},{name="parser",value="{txid = {static npos = 18446744073709551615, static kMaxSize = 9223372036854775807, ptr_ = 0x2345e192b00 \"00000010^done,BreakpointTable={nr_rows=\\\"1\\\",nr_cols=\\\"6\\\",hdr=[{width=\\\"7\\\",alignment=\\\"-1\\\",col_name=\\\"number\\\",colhdr=\\\"Num\\\"},{width=\\\"14\\\",alignment=\\\"-1\\\",col_name=\\\"type\\\",colhdr=\\\"Type\\\"},{width=\\\"4\\\",alignment=\\\"-1\"..., length_ = 8}, result_class = {static npos = 18446744073709551615, static kMaxSize = 9223372036854775807, ptr_ = 0x2345e192b09 \"done,BreakpointTable={nr_rows=\\\"1\\\",nr_cols=\\\"6\\\",hdr=[{width=\\\"7\\\",alignment=\\\"-1\\\",col_name=\\\"number\\\",colhdr=\\\"Num\\\"},{width=\\\"14\\\",alignment=\\\"-1\\\",col_name=\\\"type\\\",colhdr=\\\"Type\\\"},{width=\\\"4\\\",alignment=\\\"-1\\\",col_nam\"..., length_ = 4}}"},{name="props",value="{<absl::container_internal::raw_hash_map<absl::container_internal::FlatHashMapPolicy<absl::string_view, absl::string_view>, absl::container_internal::StringHash, absl::container_internal::StringHashEq::Eq, std::allocator<std::pair<absl::string_view const, absl::string_view> > >> = {<absl::container_internal::raw_hash_set<absl::container_internal::FlatHashMapPolicy<absl::string_view, absl::string_view>, absl::container_internal::StringHash, absl::container_internal::StringHashEq::Eq, std::allocator<std::pair<absl::string_view const, absl::string_view> > >> = {ctrl_ = 0x2345e193540 \"+\\200\\200\\200a\\a\\200u\\200 \\200\\200\\200\\200\\200\\200\\200W]_!qD\\016pH\\200\\200px%\377+\\200\\200\\200a\\a\\200u\\200 \\200\\200\\200\\200\\200\272:-\\031^4\\002\", slots_ = 0x2345e193570, size_ = 17, capacity_ = 31, settings_ = {<absl::container_internal::internal_compressed_tuple::CompressedTupleImpl<absl::container_internal::CompressedTuple<unsigned long long, absl::container_internal::HashtablezInfoHandle, absl::container_internal::StringHash, absl::container_internal::StringHashEq::Eq, std::allocator<std::pair<absl::string_view const, absl::string_view> > >, absl::integer_sequence<unsigned long long, 0, 1, 2, 3, 4>, true>> = {<absl::container_internal::internal_compressed_tuple::uses_inheritance> = {<No data fields>}, <absl::container_internal::internal_compressed_tuple::Storage<unsigned long long, 0, false>> = {value = 11}, <absl::container_internal::internal_compressed_tuple::Storage<absl::container_internal::HashtablezInfoHandle, 1, true>> = {<absl::container_internal::HashtablezInfoHandle> = {<No data fields>}, <No data fields>}, <absl::container_internal::internal_compressed_tuple::Storage<absl::container_internal::StringHash, 2, true>> = {<absl::container_internal::StringHash> = {<No data fields>}, <No data fields>}, <absl::container_internal::internal_compressed_tuple::Storage<absl::container_internal::StringHashEq::Eq, 3, true>> = {<absl::container_internal::StringHashEq::Eq> = {<No data fields>}, <No data fields>}, <absl::container_internal::internal_compressed_tuple::Storage<std::allocator<std::pair<absl::string_view const, absl::string_view> >, 4, true>> = {<std::allocator<std::pair<absl::string_view const, absl::string_view> >> = {<__gnu_cxx::new_allocator<std::pair<absl::string_view const, absl::string_view> >> = {<No data fields>}, <No data fields>}, <No data fields>}, <No data fields>}, <No data fields>}}, <No data fields>}, <No data fields>}"}])str";

    gdbmi::Parser parser;
    {
        gdbmi::Node::ptr_t tree = std::make_shared<gdbmi::Node>();
        parser.parse(input_str, tree);
        parser.print(tree);
    }

//    std::cout << std::endl << std::endl << "printing second one" << std::endl << std::endl;
//    {
//        gdbmi::Node::ptr_t tree = std::make_shared<gdbmi::Node>();
//        parser.parse(input_str_2, tree);
//        parser.print(tree);
//    }
    return 0;
}
