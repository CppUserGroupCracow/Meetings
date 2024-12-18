#include <iostream>
#include <charconv>
#include <string>
#include <string_view>

int main()
{
	for (;;)
	{
		std::string str;
		std::cin >> str;
		if (str == "x" || str == "end" || str == "exit")
			break;

		int value;
		const auto res = std::from_chars(str.data(), str.data() + str.size(), value);
		if (res.ec == std::errc::invalid_argument)
		{
			std::cout << "invalid argument!, res.p distance: " << res.ptr - str.data() << '\n';
		}
		else if (res.ec == std::errc::result_out_of_range)
		{
			std::cout << "out of range! res.p distance: " << res.ptr - str.data() << '\n';
		}
		else
		{
			std::cout << "value: " << value << ", distance: " << res.ptr - str.data() << '\n';

			std::string strBack = str;

			if (auto[ptr, ec] = std::to_chars(strBack.data(), strBack.data() + strBack.size(), value); ec == std::errc())
			{
				std::cout << "converted back: " << std::string_view(strBack.data(), ptr - strBack.data()) << ", " << strBack << '\n'; // not NUL-terminated!
			}
		}
	}
}
