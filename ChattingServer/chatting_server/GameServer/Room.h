#pragma once
#include "JobQueue.h"

class Room : public JobQueue
{
public:
	// 싱글쓰레드 환경인마냥 코딩
	bool Enter(UserRef user);
	void Leave(UserRef user);
	void Broadcast(SendBufferRef sendBuffer);


public:
	map<uint64, UserRef> _users;
	uint64 masterUserId;
	uint64 roomId;
	string roomName;
	string pw;
	uint32 maxUser = 8;
	bool isStarted = 0;

private:
	USE_LOCK;
};

extern shared_ptr<Room> GRoom;
extern map<uint64, RoomRef>* GRoomMap;