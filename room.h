#ifndef ROOM_H
#define ROOM_H

#include "entity.h"

class Room : public Entity
{
public:
	Room(const std::string& name, const std::string& description);
	~Room();

	void Look() const;
	void LookAt(const std::string& thing) const;
};

#endif // !ROOM_H