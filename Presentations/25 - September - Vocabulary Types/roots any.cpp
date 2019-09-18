#include <iostream>
#include <vector>
#include <optional>
#include <any>
#include <cmath>

// aX^2 + bX + c
std::any FindRoots(double a, double b, double c)
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
    
    return std::any();
}

void ShowRoots(const std::any& roots)
{
    if (!roots.has_value())
        std::cout << "no roots!\n";    
    else if (const double* x = std::any_cast<double>(&roots))
       std::cout << "one root: " << *x << '\n';
    else if (const std::pair<double, double>* p = std::any_cast<std::pair<double, double>>(&roots))
       std::cout << "two roots: " << p->first << ", " << p->second << '\n';
}


int main()
{
    ShowRoots(FindRoots(1, -3, 4));
    ShowRoots(FindRoots(-4, 12, -9));
    ShowRoots(FindRoots(2, -11, 5));
}