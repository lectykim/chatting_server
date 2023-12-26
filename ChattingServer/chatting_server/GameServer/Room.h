#pragma once
#include "JobQueue.h"

class Room : public JobQueue
{
public:
	// �̱۾����� ȯ���θ��� �ڵ�
	void Enter(UserRef user);
	void Leave(UserRef user);
	void Broadcast(SendBufferRef sendBuffer);


public:
	map<uint64, UserRef> _users;
	uint64 masterUserId;
	uint64 roomId;
	string roomName;
	string pw;
	uint32 maxUser = 10000;
	bool isStarted = 0;
};

extern shared_ptr<Room> GRoom;
extern map<uint64, RoomRef>* GRoomMap;