#pragma once
#ifndef CONSTRAINT_H
#define CONSTRAINT_H

struct Constraint {

	Constraint() :min(0), max(0) {};
	Constraint(int i, int j) : min(i), max(j) {};
	int min;

	int max;
};

#endif // !CONSTRAINT_H
