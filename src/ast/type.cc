#include "type.h"

using namespace arua;

Type::Type(unsigned int line, unsigned int col, PrimitiveType primType)
		: Token(line, col)
		, primType(primType) {
}

PrimitiveType Type::getPrimitiveType() const throw() {
	return this->primType;
}

bool Type::operator ==(const Type &other) const {
	return this->equals(other);
}
