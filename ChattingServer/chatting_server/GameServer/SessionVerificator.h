#pragma once
#include "GameSession.h"
#include "Room.h"
#include "User.h"
template<typename T>
class SessionVerificator
{
public:
	static SessionVerificator& GetInstance() 
	{
		static SessionVerificator* instance = new SessionVerificator();
		return *instance;
	}

	
	bool IsLogined(shared_ptr<GameSession> session,T& pkt);
	
	bool IsMaster(shared_ptr<GameSession> session, T& pkt);
	
	bool IsLobby(shared_ptr<GameSession> session, T& pkt);

	bool isGameStarted(shared_ptr<GameSession> session, T& pkt);
private:
	SessionVerificator() {};
};


template<typename T>
inline bool SessionVerificator<T>::IsLogined(shared_ptr<GameSession> session, T& pkt)
{
	if (session->user == nullptr)
	{
		//�α��� ����
		pkt.set_code(2);
		return false;
	}
		
	else
	{
		//�α��� ����
		pkt.set_code(1);
		return true;
	}
		
	
}

template<typename T>
inline bool SessionVerificator<T>::IsMaster(shared_ptr<GameSession> session, T& pkt)
{
	if (session->user->userId == session->_room.lock()->masterUserId)
	{
		//���� ����
		pkt.set_code(4);
		return true;
	}
		
	else
	{
		//���� ���� �ƴ�
		pkt.set_code(3);
		return false;
	}
		
	
}

template<typename T>
inline bool SessionVerificator<T>::IsLobby(shared_ptr<GameSession> session, T& pkt)
{
	if (session->_room.lock() == GRoom)
	{
		//���� �κ� ����
		pkt.set_code(5);
		return true;
	}
	else
	{
		//���� �κ� �ƴ� �ٸ� �濡 ��������
		pkt.set_code(6);
		return false;
	}
		
}

template<typename T>
inline bool SessionVerificator<T>::isGameStarted(shared_ptr<GameSession> session, T& pkt)
{
	if (session->_room.lock()->isStarted)
	{
		pkt.set_code(12);
		return true;
	}
	else
	{
		pkt.set_code(13);
		return false;
	}
	return false;
}
