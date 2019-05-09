#pragma once
#include "CalculatorItem.h"
#include <memory>

class Calculator;

class BinaryOperation : public CalculatorItem
{
public:
	BinaryOperation(std::istream& is, const Calculator& calculator);
	virtual ~BinaryOperation() = default;
protected:
	std::shared_ptr<CalculatorItem> m_item1;
	std::shared_ptr<CalculatorItem> m_item2;
};

