#include "Dictionary_my.h"
#include <iostream>
#include <string>

#define TYPE_KEY_0		int
#define TYPE_VALUE_0	int
#define TYPE_KEY_1		std::string
#define TYPE_VALUE_1	std::string


template<class TKey, class TValue>
void search(const Dictionary_my<TKey, TValue> &dict, const TKey& key) {
	TValue value;
	try {
		value = dict.Get(key);
	}
	catch (NotFoundException_my<TKey> &exception)
	{
		std::cout << "Not found key: " << exception.GetKey() << std::endl;
		//std::cout << "What: " << exception.what() << std::endl;
		return;
	}
	std::cout << "Search '" << key << "': " << value << std::endl;
}

template<class TKey, class TValue>
void isSet(const Dictionary_my<TKey, TValue> &dict, const TKey& key) {
	if (dict.IsSet(key)) {
		std::cout << "Key '" << key << "' is set" << std::endl;
	}
	else {
		std::cout << "Key '" << key << "' is not set" << std::endl;
	}
}

int main(int argc, char** argv)
{
	Dictionary_my<TYPE_KEY_0, TYPE_VALUE_0> dict_0;
	// Test. Old value replacement
	dict_0.Set(1, 2);
	search<TYPE_KEY_0, TYPE_VALUE_0>(dict_0, 1);
	dict_0.Set(1, 3);
	search<TYPE_KEY_0, TYPE_VALUE_0>(dict_0, 1);

	Dictionary_my<TYPE_KEY_1, TYPE_VALUE_1> dict_1;
	// Dictionary_my<TKey, TValue>::Set test
	dict_1.Set("Tsvetkov", "+79811213016");

	// Dictionary_my<TKey, TValue>::isSet Test
	TYPE_KEY_1 name = "Zenkin";
	isSet<TYPE_KEY_1, TYPE_VALUE_1>(dict_1, name);	// is not set
	dict_1.Set(name, "+79811213032");
	isSet<TYPE_KEY_1, TYPE_VALUE_1>(dict_1, name);	// is set
	
	// Dictionary_my<TKey, TValue>::Get Test
	search<TYPE_KEY_1, TYPE_VALUE_1>(dict_1, "Tsvetkov");
	search<TYPE_KEY_1, TYPE_VALUE_1>(dict_1, "Ptushkin");  // Not found exception
	search<TYPE_KEY_1, TYPE_VALUE_1>(dict_1, "Zenkin");

	// Thread test
	int size_1 = 100000;  // should be large enough for the second thread to start
	int size_2 = 100;  
	auto func_set = [](Dictionary_my<TYPE_KEY_0, TYPE_VALUE_0> &dict, const TYPE_KEY_0 key, const int size)
    {
		for (auto i = 0; i < size; i++)
		{
			dict.Set(key, i);
		}
    };
	auto func_get = [](const Dictionary_my<TYPE_KEY_0, TYPE_VALUE_0> &dict, const TYPE_KEY_0 key, const int size)
	{
		for (auto i = 0; i < size; i++)
		{
			search<TYPE_KEY_0, TYPE_VALUE_0>(dict, key);
		}
	};
	std::thread thread_set(func_set, std::ref(dict_0), 3, size_1);
	std::thread thread_get(func_get, std::ref(dict_0), 3, size_2);
	thread_set.join();
	thread_get.join();

	system("pause");
	return 0;
}