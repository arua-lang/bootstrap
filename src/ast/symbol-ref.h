#ifndef ARUAB_AST_SYMBOL_REF_H__
#define ARUAB_AST_SYMBOL_REF_H__
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "symbol.h"
#include "symbol-context.h"
#include "type.h"

namespace arua {

class SymbolRef {
public:
	SymbolRef(std::shared_ptr<SymbolContext> symCtx);

	void addIdentifier(std::string identifier) throw();

	const std::shared_ptr<SymbolContext> getSymbolContext() const throw();
	const std::vector<std::string> & getIdentifiers() const throw();

	std::shared_ptr<Symbol> resolve() const throw();

private:
	std::shared_ptr<SymbolContext> symCtx;
	std::vector<std::string> identifiers;
};

}

#endif
