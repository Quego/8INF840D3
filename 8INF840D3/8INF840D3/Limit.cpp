#include "stdafx.h"
#include "Limit.h"
#include <iostream>
#include <fstream>
#include <sstream>

Limit::Limit(int alphabetSize, int wordSize) : 
	m_alphabetSize(alphabetSize),
	m_wordSize(wordSize)
{
	std::vector<Occurrence> m_occurrences(alphabetSize);
}

int Limit::getAlphabetSize() const
{
	return m_alphabetSize;
}

int Limit::getWordSize() const
{
	return m_wordSize;
}

std::vector<Occurrence> Limit::getOccurences() const
{
	return m_occurrences;
}

Occurrence Limit::getOccurenceOnWord(int index) const
{
	return m_occurrences[index];;
}

void Limit::AddOccurrence(Occurrence occurrence)
{
	m_occurrences.push_back(occurrence);
}

Limit Limit::Parse(std::string filename)
{
	std::ifstream file(filename, std::ios::in);

	if (file.is_open())
	{
		int alphabetSize;
		int wordSize;
		std::vector<int> mins;
		std::vector<int> max;

		std::string content;


		//TODO
		//getline(file, content);
		//alphabetSize = std::stoi(content);


	}
	return Limit(-1, -1);
}
