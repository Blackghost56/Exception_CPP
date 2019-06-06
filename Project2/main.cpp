#include "Dictionary_my.h"
#include <iostream>
#include <string>

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
	Dictionary_my<std::string, std::string> dict;

	// Dictionary_my<TKey, TValue>::Set test
	dict.Set("Tsvetkov", "+79811213016");

	// Dictionary_my<TKey, TValue>::isSet Test
	std::string name = "Zenkin";
	isSet<std::string, std::string>(dict, name);	// is not set
	dict.Set(name, "+79811213032");
	isSet<std::string, std::string>(dict, name);	// is set
	
	// Dictionary_my<TKey, TValue>::Get Test
	search<std::string, std::string>(dict, "Tsvetkov");  
	search<std::string, std::string>(dict, "Ptushkin");  // Not found exception
	search<std::string, std::string>(dict, "Zenkin");

	system("pause");
	return 0;
}