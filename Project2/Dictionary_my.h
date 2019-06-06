#pragma once
#include "Interface.h"
#include "NotFoundException_my.h"
#include <map>

template<class TKey, class TValue>
class Dictionary_my : public Dictionary<TKey, TValue>
{
private:
	std::map<TKey, TValue> dictionary_map;
public:
	Dictionary_my() {}
	~Dictionary_my() {}

	const TValue& Get(const TKey& key) const {
		auto it = dictionary_map.find(key);
		if (it == dictionary_map.end())
		{
			throw NotFoundException_my<TKey>(key);
			//throw NotFoundException_my<TKey>(key, "test");
		}
		return it->second;
	}
	void Set(const TKey& key, const TValue& value) {
		dictionary_map.insert(std::pair<TKey, TValue>(key, value));
	}
	bool IsSet(const TKey& key) const {
		auto it = dictionary_map.find(key);
		if (it == dictionary_map.end())
		{
			return false;
		}
		return true;
	}
};

