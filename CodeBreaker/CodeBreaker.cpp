// CodeBreaker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>
#include "Globals.h"
#include "SimpleSubstitution.h"
#include "Vigenere.h"
#include "FourSquare.h"
#include "Bifid.h"
#include "Trifid.h"




int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Which file do you want to open?" << std::endl;

	bool done = false;
	std::string text;

	while(!done)
	{
		try
		{
			std::string filename;
			std::cin >> filename;

			std::ifstream ifile;
			ifile.open(filename);
	
			std::string line;

			while(std::getline(ifile,line))
			{
				text+=line+'\n';
			}

			ifile.close();

			done = true;
		}
		catch(int e)
		{
			std::cout << "That is not a valid filename!" << std::endl;
		}
	}

	std::regex e("[^A-Z#]");
	std::transform(text.begin(), text.end(),text.begin(), ::toupper);
	text = std::regex_replace(text, e,"");

	system("cls");
	std::cout << "What method of decryption would you like to use?\nb - Bifid\nf - Foursquare\ns - Simple Substitution\nt - Trifid\nv - Vigenere" << std::endl;

	done = false;
	char type;

	while(!done)
	{
		try
		{
			std::cin >> type;
			done = true;

			//Insert other cipher keys here
			switch(type)
			{
			case 'b':
				setNGrams();
				bifid(text);
				break;
			case 'f':
				setNGrams();
				fourSquare(text);
				break;
			case 's':
				setNGrams();
				simpleSubstitution(text);
				break;
			case 't':
				setNGrams();
				trifid(text);
				break;
			case 'v':
				setNGrams();
				vigenere(text);
				break;
			default:
				done = false;
				std::cout << "That is not a valid answer!" << std::endl;
				break;
			}

		}
		catch(int e)
		{
			std::cout << "That is not a valid answer!" << std::endl;
		}
	}

	std::cout << "The program has finished. ";
	system("pause");

	return 0;
}

