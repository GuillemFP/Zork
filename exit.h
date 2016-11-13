#ifndef EXIT_H
#define EXIT_H

#include "entity.h"

class Item;

using namespace std;

class Exit : public Entity
{
public:
	Exit(const string& name1, const string& name2, string& descript_1, string& descript_2, const string& description,
		Entity* room1, Entity* room2, Item* key, bool closed, bool locked);
	~Exit();
	void Look() const;

	string destination_name;
	string destination_desc;
	string connection_description;
	Entity* destination_entity;
	bool closed;
	bool locked;
	Item* key;

};



#endif // !EXIT_H