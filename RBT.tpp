#include "RBT.h"

template<typename T>
void Node::remove_data(const string& key_name)
{
	shared_ptr<Concept> to_remove{nullptr};
	if (data.empty())
		return;
	to_remove = find_data(key_name);
	if (to_remove){
		if (dynamic_pointer_cast<T>(to_remove)){
			data.remove(to_remove);
		}
	}
}
