// Parsing Files.cpp : Defines the entry point for the console application.
//

#include <string_view>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std::literals;

// code based on examples from https://tristanbrindle.com/posts/a-quicker-study-on-tokenising/

size_t numAllocations = 0;
size_t sizeAllocations = 0;

void* operator new(std::size_t sz) {
	numAllocations++;
	sizeAllocations += sz;
	return std::malloc(sz);
}

std::vector<std::string>
split(const std::string& str, const std::string& delims = " ")
{
	std::vector<std::string> output;
	//output.reserve(str.length() / 4);
	auto first = std::cbegin(str);

	while (first != std::cend(str))
	{
		const auto second = std::find_first_of(first, std::cend(str),
			std::cbegin(delims), std::cend(delims));
		if (first != second)
		{
			output.emplace_back(first, second);
		}

		if (second == std::cend(str))
			break;

		first = std::next(second);
	}

	return output;
}

std::vector<std::string> splitPtr(const std::string& str, const std::string& delims = " ")
{
	std::vector<std::string> output;
	output.reserve(str.size() / 2);

	for (auto first = str.data(), second = str.data(), last = first + str.size(); second != last && first != last; first = second + 1) {
		second = std::find_first_of(first, last, std::cbegin(delims), std::cend(delims));

		if (first != second)
			output.emplace_back(first, second);
	}

	return output;
}

std::vector<std::string_view>
splitSV(std::string_view strv, std::string_view delims = " ")
{
	std::vector<std::string_view> output;
	//output.reserve(strv.length() / 4);
	size_t first = 0;

	while (first < strv.size())
	{
		const auto second = strv.find_first_of(delims, first);
		//std::cout << first << ", " << second << '\n';
		if (first != second)
		{
			output.emplace_back(strv.substr(first, second-first));
		}

		if (second == std::string_view::npos)
			break;

		first = second + 1;
	}

	return output;
}

std::vector<std::string_view>
splitSVStd(std::string_view strv, std::string_view delims = " ")
{
	std::vector<std::string_view> output;
	//output.reserve(strv.length() / 4);
	auto first = strv.begin();

	while (first != strv.end())
	{
		const auto second = std::find_first_of(first, std::cend(strv),
			std::cbegin(delims), std::cend(delims));
		//std::cout << first << ", " << second << '\n';
		if (first != second)
		{
			output.emplace_back(strv.substr(std::distance(strv.begin(), first), std::distance(first, second)));
		}

		if (second == strv.end())
			break;

		first = std::next(second);
	}

	return output;
}

std::vector<std::string_view> splitSVPtr(std::string_view str, std::string_view delims = " ")
{
	std::vector<std::string_view> output;
	output.reserve(str.size() / 2);

	for (auto first = str.data(), second = str.data(), last = first + str.size(); second != last && first != last; first = second + 1) {
		second = std::find_first_of(first, last, std::cbegin(delims), std::cend(delims));

		if (first != second)
			output.emplace_back(first, second - first);
	}

	return output;
}

const std::string_view LoremIpsumStrv{ "Lorem ipsum dolor sit amet, consectetur adipiscing elit, "
"sed do eiusmod tempor incididuntsuperlongwordsuper ut labore et dolore magna aliqua. Ut enim ad minim veniam, "
"quis nostrud exercitation ullamco laboris nisi ut aliquipsuperlongword ex ea commodo consequat. Duis aute "
"irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
"Excepteur sint occaecat cupidatatsuperlongword non proident, sunt in culpa qui officia deserunt mollit anim id est laborum." };

template <typename TFunc> void RunAndMeasure(const char* title, TFunc func)
{
	numAllocations = 0;
	sizeAllocations = 0;

	const auto start = std::chrono::steady_clock::now();
	auto ret = func();
	const auto end = std::chrono::steady_clock::now();
	std::cout << title << ": " <<
		std::chrono::duration <double, std::milli>(end - start).count()
		<< " ms, res " << ret << " Allocation count: " << numAllocations << ", size " << sizeAllocations << '\n';
}

int main(int argc, const char** argv)
{
	std::cout << sizeof(std::string_view) << '\n';
	std::cout << sizeof(std::string) << '\n';

	std::string testString{ LoremIpsumStrv };

	if (argc > 1 && "nofile"s != argv[1])
	{
		std::ifstream inFile(argv[1]);

		std::stringstream strStream;
		strStream << inFile.rdbuf();
		testString = strStream.str();
	}

	std::cout << "string length: " << testString.length() << '\n';

	const int ITERS = argc > 2 ? atoi(argv[2]) : 10000;
	std::cout << "test iterations: " << ITERS << '\n';

	RunAndMeasure("string split", [ITERS, &testString]()
	{
		std::size_t sizes = 0;
		for (int i = 0; i < ITERS; ++i)
		{
			auto v = split(testString);
			sizes += v.size();
		}
		return sizes;
	});

	RunAndMeasure("string split ptr", [ITERS, &testString]()
	{
		std::size_t sizes = 0;
		for (int i = 0; i < ITERS; ++i)
		{
			auto v = splitPtr(testString);
			sizes += v.size();
		}
		return sizes;
	});

	//for (const auto &s : splitStrVec)
	//        std::cout << s << ".\n";

	const auto sv = "Hello Super Extra World"sv;
	auto splitSVVec = splitSV(sv);

	RunAndMeasure("string_view split", [ITERS, &testString]()
	{
		std::size_t sizes = 0;
		for (int i = 0; i < ITERS; ++i)
		{
			auto v = splitSV(testString);
			sizes += v.size();
		}
		return sizes;
	});

	RunAndMeasure("string_view split Std", [ITERS, &testString]()
	{
		std::size_t sizes = 0;
		for (int i = 0; i < ITERS; ++i)
		{
			auto v = splitSVStd(testString);
			sizes += v.size();
		}
		return sizes;
	});

	RunAndMeasure("string_view split Ptr", [ITERS, &testString]()
	{
		std::size_t sizes = 0;
		for (int i = 0; i < ITERS; ++i)
		{
			auto v = splitSVStd(testString);
			sizes += v.size();
		}
		return sizes;
	});
}
