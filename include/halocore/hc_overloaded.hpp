#ifndef HC_OVERLOADED_HPP
#define HC_OVERLOADED_HPP

namespace hc {

// use for pattern matching:
//
// std::variant<int, float, std::string> var{ "string" };
// std::visit(
//     overloaded{
//         [](int n)                { std::cout << "int!\n";    },
//         [](float n)              { std::cout << "float!\n";  },
//         [](std::string const &s) { std::cout << "string!\n"; }
//     },
//     var
// );
//
// prints "string!"
template<typename... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<typename... Ts> overloaded(Ts...) -> overloaded<Ts...>; // not technically necessary in C++20 but that isnt
                                                                 // widely supported yet in compilers so

}

#endif // HC_OVERLOADED_HPP
