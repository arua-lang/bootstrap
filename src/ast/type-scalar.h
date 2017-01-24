#ifndef ARUAB_AST_TYPE_SCALAR_H__
#define ARUAB_AST_TYPE_SCALAR_H__
#pragma once

#include "type.h"

namespace arua {

enum class ScalarClass {
	INT,
	UINT,
	FLOAT,
};

class TypeScalar : public Type {
public:
	TypeScalar(unsigned int line, unsigned int col, ScalarClass scalarClass, unsigned int width);

	ScalarClass getScalarClass() const throw();
	unsigned int getWidth() const throw();


	virtual bool equals(const Type &type) const throw();
	virtual bool canAssignTo(const Type &other) const throw();

private:
	ScalarClass scalarClass;
	unsigned int width;
};

}

#endif
