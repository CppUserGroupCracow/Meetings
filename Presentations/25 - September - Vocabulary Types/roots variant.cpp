#include <iostream>
#include <vector>
#include <optional>
#include <variant>
#include <cmath>

// aX^2 + bX + c
using TRoots = std::variant<std::monostate, double, std::pair<double, double>>;

TRoots FindRoots(double a, double b, double c)
{
    const auto delta = b*b-4*a*c;

    if (delta > 0.0)
    {
        auto p = sqrt(delta);
        double x1 = (-b + p)/(2*a);
        double x2 = (-b - p)/(2*a);
        return std::pair(x1, x2);
    }
    else if (delta == 0.0)
    {
        return -b/(2*a);
    }
    
    return std::monostate();
}

void ShowRoots(const TRoots& roots)
{
    switch (roots.index())
    {
        case 0: std::cout << "no roots!\n"; break;
        case 1: std::cout << std::get<1>(roots) << '\n'; break;
        case 2: std::cout << std::get<2>(roots).first << ", " << std::get<2>(roots).second << '\n'; break;
    }
}

int main()
{
    ShowRoots(FindRoots(1, -3, 4));
    ShowRoots(FindRoots(-4, 12, -9));
    ShowRoots(FindRoots(2, -11, 5));
}