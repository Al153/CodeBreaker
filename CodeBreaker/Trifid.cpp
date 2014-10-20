#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "Trifid.h"
#include "Globals.h"

//Constants
const double TEMP = 20.0;
const float STEP = 0.1;

//Crack simple substitution ciphers
void trifid(std::string text)
{

	char input;
	std::cout << "What period do you want to use? " << std::endl;
	std::cin >> input;

	int period = (int)input;

	//Decrypt text with key
	auto decrypt = [](std::string key, std::string text)
	{
		std::vector<int> vals;

		for (char c : text)
		{
			int index = key.find_first_of(c);
			vals.push_back(index / 9);
			vals.push_back((index / 3)%3);
			vals.push_back(index % 3);
		}

		for (int i = 0; i < text.length(); i++)
		{
			text[i] = key[vals[i] * 9 + vals[i + text.length()] * 3 + vals[i + 2*text.length()]];
		}

		return text;
	};

	//Overall max key
	std::string parent_key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ#";
	double parent_eval = -INT_MAX;

	std::random_shuffle(parent_key.begin(), parent_key.end());

	//Implement simulated annealing
	for (double T = TEMP; T >= 0; T -= STEP)
	{
		unsigned cnt = 0;
		while (cnt < 728)
		{
			std::string child_key = parent_key;

			//Swap letters
			std::swap(child_key[cnt / 27], child_key[cnt % 27]);

			double eval = evaluate(decrypt(child_key, text));

			//If key is better then always switch
			if (eval - parent_eval >= 0)
			{
				parent_eval = eval;
				parent_key = child_key;
			}
			else if (T>0)
			{
				//Otherwise switch if temperature is high enough
				if (exp((eval - parent_eval) / T) > 1.0*rand() / (double)RAND_MAX)
				{
					parent_eval = eval;
					parent_key = child_key;
				}
			}
			cnt++;
		}
		system("cls");
		std::cout << "\n\nCurrent score: " << parent_eval << std::endl;
		std::cout << "Current Temp.: " << T << std::endl;
		std::cout << "Best key:  " << parent_key << std::endl;
		std::cout << "Plaintext:\n\n    " << decrypt(parent_key, text) << std::endl;
	}
}