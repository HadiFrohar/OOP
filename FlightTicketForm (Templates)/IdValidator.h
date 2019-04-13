#pragma once
#include "ValidatorTemplate.h"
class IdValidator : public ValidatorTemplate<uint32_t>
{
public:

	//constructor, it sends the appropriate message to base class
	IdValidator();

	//validates if the id is correct or not
	bool validate(const uint32_t& item) override;
};

