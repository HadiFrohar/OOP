#pragma once
#include "BinaryOperation.h"

class Calculator;

class Add: public BinaryOperation
{
public:
	Add(std::istream& is, const Calculator& calculator);
	virtual ~Add() = default;
	double area() const override;
	double perimeter() const override;
	void draw() const override;
	void printDetails() const override;
};

