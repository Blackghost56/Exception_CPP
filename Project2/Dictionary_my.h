#pragma once
#include "Interface.h"
#include "NotFoundException_my.h"
#include <map>
#include <mutex>

template<class TKey, class TValue>
class Dictionary_my : public Dictionary<TKey, TValue>
{
private:
	std::map<TKey, TValue> dictionary_map;
	mutable std::mutex mutex_0;
public:
	Dictionary_my() {}
	~Dictionary_my() {}

	const TValue& Get(const TKey& key) const {
		std::lock_guard<std::mutex> lock(mutex_0);
		auto it = dictionary_map.find(key);
		if (it == dictionary_map.end())
		{
			throw NotFoundException_my<TKey>(key);
			//throw NotFoundException_my<TKey>(key, "test");
		}
		return it->second;
	}
	void Set(const TKey& key, const TValue& value) {
		std::lock_guard<std::mutex> lock(mutex_0);
		auto it = dictionary_map.find(key);
		if (it == dictionary_map.end())
		{
			dictionary_map.insert(std::pair<TKey, TValue>(key, value));
			return;
		}
		it->second = value;
	}
	bool IsSet(const TKey& key) const {
		std::lock_guard<std::mutex> lock(mutex_0);
		auto it = dictionary_map.find(key);
		if (it == dictionary_map.end())
		{
			return false;
		}
		return true;
	}
};

