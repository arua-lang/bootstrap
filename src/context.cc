#include <iostream>

#include "context.h"

using namespace arua;
using namespace std;

Context::Context(Ptr<Context> parent)
		: Value(ValueType::CONTEXT)
		, parent(parent) {
}

Ptr<Value> Context::resolve(string name, Ptr<Value> requester) throw() {
	// determine if the request is 'privileged' - if it's privileged, it means
	// that it is able to access privatized members in this context and above contexts.
	bool privileged = false;
	Ptr<Context> cur;
	if (requester) {
		cur = requester->getValueType() == ValueType::CONTEXT
			? requester.as<Context>()
			: requester->getContext();

		if (!cur) {
			cerr << "aruab: warning: resolve was given a value with no context. Is the parser feeling okay?" << endl;
		}
	}

	for (; cur; cur = cur->parent) {
		if (cur.get() == this) {
			privileged = true;
			break;
		}
	}

	if (!privileged && !this->publicNames.count(name)) {
		// it doesn't even matter if the thing really exists as a private member
		// or not; if it's not privileged and not publicized, then return nullptr.
		//
		// in the future, this will be able to return some sort of reason as to
		// why it was denied, in order to get better error messages.
		return nullptr;
	}

	{
		auto itr = this->types.find(name);
		if (itr != this->types.end()) {
			return itr->second.as<Value>();
		}
	}

	return parent ? parent->resolve(name) : nullptr;
}

void Context::addType(Ptr<Type> type, bool pub) throw() {
	if (type->getName().empty()) {
		cerr << "warning: Context::addType() was passed a type with no name" << endl;
		return;
	}

	this->types[type->getName()] = type;
	if (pub) {
		this->publicNames.insert(type->getName());
	}
}
