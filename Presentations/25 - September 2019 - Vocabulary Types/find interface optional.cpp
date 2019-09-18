#include <iostream>
#include <vector>
#include <optional>

template <typename TContainer>
std::optional<typename TContainer::value_type> FindVal(const TContainer& container, const typename TContainer::value_type& key)
{
	auto it = std::find(std::begin(container), std::end(container), key);
	if (it != std::end(container))
		return *it;

	return std::nullopt; // or std::nullopt
}

int main()
{
	std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7 };
	auto i = FindVal(v, 1);
	if (i)
		std::cout << *i;
}