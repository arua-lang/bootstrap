#ifndef ARUAB_AST_TYPE_H__
#define ARUAB_AST_TYPE_H__
#pragma once

#include "token.h"

namespace arua {

enum class PrimitiveType {
	SCALAR,
	ARRAY,
	FUNCTION,
	DEF,
};

class Type : public Token {
public:
	Type(unsigned int line, unsigned int col, PrimitiveType primType);

	PrimitiveType getPrimitiveType() const throw();

	virtual bool equals(const Type &type) const throw() = 0;

	// ThisType = OtherType -- possible?
	virtual bool canAssignTo(const Type &other) const throw() = 0;

	bool operator ==(const Type &other) const;

private:
	PrimitiveType primType;
};

}

#endif