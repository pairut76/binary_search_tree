// WordChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"
#include <iterator>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>
//#include <cassert>
WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
	
    return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
	std::vector<std::string> vect;
	//swapping each adjacent pair of characters in word.
	if(word.length()>=2)
	{
		for(int i=0; i<(word.length()-1);i++)
		{
			std::string new_word=word;
			new_word[i]=word[i+1];
			new_word[i+1]=word[i];
			if(words.contains(new_word))
				vect.push_back(new_word);
		
		}

	}

	//in between each adjacent pair of characters in word
	for(int i=0; i<word.length()+1;i++)
	{

		if(i<word.length())
		{
			//deleting each value//
			std::string nword=word;
			//std::string::iterator it=nword.begin()+i;
			nword.erase(nword.begin()+i);
			if(words.contains(nword))
			{
				//std::cout<<"nword: "<<nword<<std::endl;
				//for(std::vector<std::string>::iterator it=vect.begin(); it!=vect.end(); ++it)
				if(std::find(vect.begin(),vect.end(),nword)==vect.end())
				{
					vect.push_back(nword);
				}
			}

			//std::vector<std::string> temp;
			
			if(i!=0&&i!=word.length()-1)
			{
				//std::cout<<"i: "<<i<<std::endl;
				std::string oword=word;
				oword.insert(oword.begin()+i, ' ');

				std::istringstream ss(oword);
				std::vector<std::string> tokens;
			
				for(std::string _word; std::getline(ss, _word, ' ');tokens.push_back(_word));
						std::string str=tokens[0];
						//str.erase(str.end());
						std::string str2=tokens[1];
						//str.erase(str.begin());

					//std::cout<<"str str2: "<<str<<"	"<<str2<<std::endl;
					//std::cout<<"len: "<<str.length()<<"	"<<str2.length()<<std::endl;
				if(words.contains(str)&&words.contains(str2))
				{
					//for(int i=0; i<2;++i)
					//{
						
						vect.push_back(str+" "+str2);
					//}
					
				}
			}
			
		}

		char letter = 'A';
		while((int)letter<91)
		{
			//inserting char//
			std::string new_word=word;
			new_word.insert(new_word.begin()+i, letter);
			if(words.contains(new_word))
				if(std::find(vect.begin(),vect.end(),new_word)==vect.end())
				{
					vect.push_back(new_word);
				}
			//std::cout<<"alphabet: "<<new_word<<std::endl;

			//delete+insert char
			std::string nword=word;
			nword.erase(nword.begin()+i);
			nword.insert(nword.begin()+i,letter);
			if(words.contains(nword))
				if(std::find(vect.begin(),vect.end(),nword)==vect.end())
				{
					//std::cout<<"word: "<<word<<std::endl;
					//std::cout<<nword<<std::endl;
					vect.push_back(nword);
				}
			letter++;
			
		}
		
	}



    return vect;//std::vector<std::string>{};
}

