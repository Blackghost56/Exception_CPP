#pragma once
#include "Interface.h"
#include <string>

template<class TKey>
class NotFoundException_my : public NotFoundException<TKey>
{
private:
	TKey key_NF;
	std::string m_error;

public:
	NotFoundException_my(const TKey &key, const std::string &error) : key_NF(key), m_error(error){}
	NotFoundException_my(const TKey &key) : key_NF(key) {}
	~NotFoundException_my() {}

	const TKey& GetKey() const noexcept {
		return key_NF;
	}
	const char* what() const noexcept { 
		return m_error.c_str(); 
	}
};

