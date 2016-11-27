#ifndef LIMIT_H
#define LIMIT_H

#include <vector>
#include "Occurrence.h"

/** \brief Representation of a limite. */
//4 taille alphabet
//5 taille du mot
//1 1 1 1 liste des valeurs minimales - Une lettre doit se trouver au moins une fois sur le chemin le plus court
//2 2 2 2 liste des valeurs maximales - Une lettre doit se trouver au maximum 2 fois sur le chemin le plus court
class Limit
{
public:
	/** \brief Constructor.
	* @param alphabetSize The size of the alphabet
	* @param wordSize The size of the word
	*/
	Limit(int alphabetSize, int wordSize);

	/** \brief The size of the alphabet getter.
	* \return The size of the alphabet
	*/
	int getAlphabetSize() const;

	/** \brief The size of the word getter.
	* \return The size of the word weight.
	*/
	int getWordSize() const;

	/** \brief The occurence of each letter getter.
	* \return The occurence of each letter.
	*/
	std::vector<Occurrence> getOccurrences() const;

	/** \brief The occurence of one letter getter.
	* \return The occurence of one letter
	*/
	Occurrence getOccurenceOnWord(int index) const;

	/** \brief Add an occurrence of a letter*/
	void AddOccurrence(Occurrence occurrence);

	/** \brief Parse a file into a Limit
	* \param filename The name of the file to parse
	* \return Limit from a file.
	*/
	static Limit Parse(std::string filename);

private:
	/** \brief The size of the alphabet. */
	int m_alphabetSize;

	/** \brief The size of the word. */
	int m_wordSize;

	/** \brief The occurence of each letter. */
	std::vector<Occurrence> m_occurrences;
};
#endif



