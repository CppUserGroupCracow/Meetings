#include <iostream>
#include <vector>
#include <optional>

void Process(int) { };

int main()
{
    std::vector<int> vec { 1, 2, 3, 4, 5, 6, 7, 101, 8, 9 };
    std::optional<int> largerThan100;
    
    for (auto& elem : vec)
    {
        Process(elem);
        
        if (elem > 100 && !largerThan100)
            largerThan100 = elem;
    }
    
    // later on selected elements...
    if (largerThan100)
        std::cout << *largerThan100;
}