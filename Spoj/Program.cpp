// Spoj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

class palindrome_finder
{
private:
	std::vector<short> phrase;
	bool onlyNines;
	size_t leftIndex;
	size_t rightIndex;

	void find_next_palindrome()
	{
		int iterations = ceil(phrase.size() / 2.0);
		for (int i = 0; i < iterations; i++)
		{
			compare_most_far_digits();
			update_left_and_right_indexes();
		}
		if (phrase.size() % 2 == 0)
		{
			phrase[leftIndex] = phrase[rightIndex];
		}
	}

	void ensure_not_already_palindrome()
	{
		for(int i = leftIndex, j = rightIndex; i< j; i++, j--)
		{
			if(phrase[i] != phrase[j])
				return;
		}
		if(phrase[rightIndex] == 9)
		{
			phrase[rightIndex] = 0;
			phrase[rightIndex-1]++;
		}
		else
		{
			phrase[rightIndex]++;
		}
	}

	void compare_most_far_digits()
	{
		if (phrase[leftIndex] > phrase[rightIndex])
		{
			phrase[rightIndex] = phrase[leftIndex];
		}
		else if (phrase[leftIndex] < phrase[rightIndex])
		{
			increment_left_neighbour(rightIndex);
			phrase[rightIndex] = phrase[leftIndex];
		}
	}

	void update_left_and_right_indexes()
	{
		rightIndex--;
		leftIndex++;
	}

	void increment_left_neighbour(size_t index)
	{
		if (index - 1 >= 0)
		{
			phrase[index - 1]++;
			if (phrase[index - 1] >= 10)
			{
				phrase[index - 1] %= 10;
				increment_left_neighbour(index - 1);
			}
		}
	}

	void increment_right_neighbour(size_t index)
	{
		if (index + 1 < phrase.size())
			phrase[index + 1]++;
	}

	void display_one_zeroes_one()
	{
		std::cout << 1;
		for (int i = 1; i < phrase.size(); i++)
		{
			std::cout << 0;
		}
		std::cout << 1;
	}

public:
	palindrome_finder(std::string source)
	{
		onlyNines = true;
		leftIndex = 0;
		for (char value : source)
		{
			short v = value - '0';
			phrase.push_back(v);
			onlyNines = onlyNines && (v == 9);
		}
		rightIndex = phrase.size() - 1;
	}

	void display_next_palindrome()
	{
		if (onlyNines)
			display_one_zeroes_one();
		else
		{
			ensure_not_already_palindrome();
			find_next_palindrome();
			for (auto i : phrase)
				std::cout << i;
		}
	}
};

int main()
{
	std::string text;
	std::string loop;
	std::getline(std::cin, loop);
	int limit = std::stoi(loop);
	for(int i =0; i<limit; i++)
	{
		std::getline(std::cin, text);
		palindrome_finder pf(text);
		pf.display_next_palindrome();
		std::cout << std::endl;
	}
	return 0;
}



/*kroki
 1. lewy < prawy
		- prawy = lewy
		- prawy[index-1] ++;
		- prawy


 **/