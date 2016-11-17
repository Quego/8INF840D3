#ifndef VALUES_H
#define VALUES_H

/** \brief Representation of the minimum and maximum occurrence of a letter */
class Occurrence
{
public:

	/** Constructor */
	Occurrence();

	/** Constructor
	* @param min The minimum occurrence of a letter.
	* @param max The max occurrence of a letter.
	*/
	Occurrence(int min, int max);

	/** \brief min getter.
	* \return The minimum occurrence of a letter.
	*/
	int getMin() const;

	/** \brief max getter.
	* \return The max occurrence of a letter.
	*/
	int getMax() const;

private:
	//1 1 1 1 liste des valeurs minimales - Une lettre doit se trouver au moins une fois sur le chemin le plus court
	//2 2 2 2 liste des valeurs maximales - Une lettre doit se trouver au maximum 2 fois sur le chemin le plus court

	/** \brief The minimum occurrence of a letter */
	int m_min;

	/** \brief The maximum occurrence of a letter */
	int m_max;
};

#endif

