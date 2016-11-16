#ifndef ROOM_H
#define ROOM_H

#include "entity.h"
#include "exit.h"

class Exit;

class Room : public Entity
{
public:
	Room(const std::string& name, const std::string& description);
	~Room();

	void Look(Entity* origin) const;
	bool LookAt(Entity* origin, const std::string& thing) const;
	Exit* GetExit(const std::string& thing) const;
	void PrintSubentitiesByType(const std::string& intro, Entity_Type type_check) const;
	void PrintCreaturesByStatus(const std::string& intro, bool alive, Entity* origin) const;

};

#endif // !ROOM_H