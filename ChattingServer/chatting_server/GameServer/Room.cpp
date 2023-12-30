#include "pch.h"
#include "Room.h"
#include "User.h"
#include "GameSession.h"

shared_ptr<Room> GRoom = make_shared<Room>();
map<uint64, RoomRef>* GRoomMap = new map<uint64, RoomRef>();
bool Room::Enter(UserRef user)
{
	WRITE_LOCK;
	if (maxUser <= _users.size())
		return false;
	else
	{
		_users[user->userId] = user;
		return true;
	}
	
}

void Room::Leave(UserRef user)
{
	WRITE_LOCK;
	_users.erase(user->userId);
}

void Room::Broadcast(SendBufferRef sendBuffer)
{
	for (auto& p : _users)
	{
		p.second->ownerSession.lock()->Send(sendBuffer);
	}
}