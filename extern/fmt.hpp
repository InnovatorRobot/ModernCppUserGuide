#ifndef FMT_HPP
#define FMT_HPP
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/ranges.h>
#include <fmt/os.h>
#include <fmt/color.h>

void testFMT()
{
    /// simple usage
    fmt::print("Hello World\n");

    /// a little bit complex
    std::string s1 = fmt::format("The answer is {}.", 42);
    std::string s2 = fmt::format("I rather to be {1} than {0}", "right", "happy");
    fmt::print("{}\n", s1);
    fmt::print("{}\n", s2);
    using namespace std::chrono_literals;
    /// Print a chrono time
    fmt::print("Default format: {} {}\n", 42s, 100ms);
    fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);

    /// Print a container
    std::vector<int> v = {1, 2, 3};
    fmt::print("{}\n", v);

    /// This can be 5 to 9 times faster than fprintf.
    auto out = fmt::output_file("guide.txt"); // #include <fmt/os.h>
    out.print("Don't {}", "Panic");

    /// colorize
    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold, "Hello {} \n", "World");
    fmt::print(
        fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) | fmt::emphasis::underline, "Hello, {}!\n", "мир");
    fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic, "Hello, {}!\n", "世界");
}
#endif // FMT_HPP
