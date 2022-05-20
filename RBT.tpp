#include "RBT.h"

template<typename T>
void Node::remove_data(const string& key_name)
{
	shared_ptr<Concept> to_remove{nullptr};
	if (data.empty())
		return;
	to_remove = find_data<T>(key_name);
	if (to_remove){
		if (dynamic_pointer_cast<T>(to_remove)){
			data.remove(to_remove);
		}
	}
}

//This should use iterators instead of returning a pointer, but
//we have not gone over them in class...
//Could also use exception handling, but would rather check a pointer in
//client code than have to code and catch yet another exception
template<typename T>
shared_ptr<Concept> Node::find_data(const Concept& key, L_iterator list, L_iterator end)
{
	if (list == end)
		return nullptr;
	else if (**list == key){
		if (dynamic_pointer_cast<T>(*list)) //type check
			return *list;
		else
			return find_data<T>(key, ++list, end);
	}
	else
		return find_data<T>(key, ++list, end);
}

template<typename T>
shared_ptr<Concept> Node::find_data(const string& key_name)
{
	shared_ptr<Concept> ret {nullptr};
	if (!data.empty()){
		auto key = ModernCpp(key_name); //don't instantiate unless searching
		ret = find_data<T>(key, data.begin(), data.end());
	}
	return ret;
}
