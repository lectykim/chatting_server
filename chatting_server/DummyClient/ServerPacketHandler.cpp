#include "pch.h"
#include "ServerPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];
string GSession;
int32 GRoomNum;
// ���� ������ �۾���

static void stringToUTF16(const string& value, WCHAR* target)
{

	const char* str = value.c_str();
	int32 nLen = ::MultiByteToWideChar(CP_ACP, 0, str, strlen(str), NULL, NULL);

	::MultiByteToWideChar(CP_ACP, 0, str, strlen(str), target, nLen);
	target[nLen] = L'\0';
}

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

bool Handle_S_SIGNUP(PacketSessionRef& session, Protocol::S_SIGNUP& pkt)
{
	std::wcout.imbue(std::locale("kor"));
	if (pkt.success())
	{
		wcout << L"ȸ�����Կ� �����ϼ̽��ϴ�." << endl;
	}
	else
	{
		if (pkt.reason() == 1)
		{
			wcout << L"�ߺ� ȸ�������Դϴ�." << endl;
		}
		else
		{
			wcout << L"�� �� ���� ������ ȸ�����Կ� �����ϼ̽��ϴ�." << endl;
		}
		
		
		
	}
	return false;
}

bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt)
{
	std::wcout.imbue(std::locale("kor"));
	if (pkt.success() == false)
	{
		if (pkt.reason() == 1)
		{
			wcout << L"���̵� �Ǵ� ��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
		}
		else if (pkt.reason() == 2)
		{
			wcout << L"�ߺ� �α����Դϴ�." << endl;
		}
		else
		{
			wcout << L"�� �� ���� ������ �α��ο� �����Ͽ����ϴ�." << endl;
		}
	}
	else
	{
		wcout << L"�α��ο� �����Ͽ����ϴ�. ���� ������," << endl;
		cout << pkt.user().name() << endl;
		cout << pkt.user().id() << endl;
		cout << pkt.user().usertype() << endl;
		cout << pkt.session() << endl;
		wcout << L"�Դϴ�." << endl;
		GSession = pkt.session();
		Protocol::C_ENTER_GAME enterGamePkt;
		enterGamePkt.set_playerindex(pkt.user().id());
		enterGamePkt.set_loginsession(GSession);
		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(enterGamePkt);
		session->Send(sendBuffer);
		
	}


	//if (pkt.success() == false)
	//	return true;

	//if (pkt.players().size() == 0)
	//{
	//	// ĳ���� ����â
	//}

	//// ���� UI ��ư ������ ���� ����
	//Protocol::C_ENTER_GAME enterGamePkt;
	//enterGamePkt.set_playerindex(0); // ù��° ĳ���ͷ� ����
	//auto sendBuffer = ServerPacketHandler::MakeSendBuffer(enterGamePkt);
	//session->Send(sendBuffer);

	return true;
}

bool Handle_S_ENTER_GAME(PacketSessionRef& session, Protocol::S_ENTER_GAME& pkt)
{
	
	if (pkt.success())
	{
		wcout << L"�α��� ����" << endl;
		
	}
	else
	{
		wcout << L"�α��� ����" << endl;
	}
	return true;
}

bool Handle_S_CHAT(PacketSessionRef& session, Protocol::S_CHAT& pkt)
{
	cout << pkt.playerid() << " : " << pkt.msg() << endl;
	return true;
}

bool Handle_S_CREATE_ROOM(PacketSessionRef& session, Protocol::S_CREATE_ROOM& pkt)

{
	std::wcout.imbue(std::locale("kor"));
	if (pkt.success())
	{
		GRoomNum = pkt.roomnumber();
		wcout << L"���� " << endl;
	}
	else
	{
		wcout << L"�α��� ���� �ʾҰų�, ���� ���� ���� �ʾҽ��ϴ�." << endl;
	}
	return false;
}

bool Handle_S_ENTER_ROOM(PacketSessionRef& session, Protocol::S_ENTER_ROOM& pkt)
{
	std::wcout.imbue(std::locale("kor"));
	if (pkt.success())
	{
		GRoomNum = pkt.roomnumber();
		wcout << L"���� " << endl;
	}
	else
	{
		wcout << L"����" << endl;
	}
	return false;
}

bool Handle_S_BAN_OTHER_USER(PacketSessionRef& session, Protocol::S_BAN_OTHER_USER& pkt)
{
	std::wcout.imbue(std::locale("kor"));
	if (pkt.success())
	{
		wcout << L"���� " << endl;
	}
	else
	{
		wcout << L"����" << endl;
	}
	return false;
	
}

bool Handle_S_IS_BANNED(PacketSessionRef& session, Protocol::S_IS_BANNED& pkt)
{
	std::wcout.imbue(std::locale("kor"));
	wcout << L"�����" << pkt.roomnumber() << L"�� �濡�� ����Ǿ����ϴ�." << endl;
	GRoomNum = 0;
	return false;
}
