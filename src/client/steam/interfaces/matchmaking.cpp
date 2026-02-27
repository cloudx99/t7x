#include <std_include.hpp>
#include "../steam.hpp"

#include "../../game/game.hpp"

#include "component/network.hpp"
#include "component/server_list.hpp"

namespace steam
{
	namespace
	{
		constexpr unsigned long long k_chat_room_enter_response_success = 1;
		uint64_t global_lan_session_id = 0;

		void enforce_lan_dvars()
		{
			game::Dvar_SetFromStringByName("lobby_forceLAN", "1", true);
			game::Dvar_SetFromStringByName("live_forceLAN", "1", true);
			game::Dvar_SetFromStringByName("sv_maxclients", "18", true);
		}

		steam_id make_lobby_id_from_session(const uint64_t session_id)
		{
			steam_id lobby{};
			lobby.bits = session_id;

			if (lobby.bits == 0)
			{
				lobby = SteamUser()->GetSteamID();
			}

			lobby.raw.universe = 1;
			lobby.raw.account_type = 8;
			lobby.raw.account_instance = 0x40000;
			return lobby;
		}
	}

	matchmaking::matchmaking()
	{
		enforce_lan_dvars();
		global_lan_session_id = SteamUser()->GetSteamID().bits;
	}

	int matchmaking::GetFavoriteGameCount()
	{
		return 0;
	}

	bool matchmaking::GetFavoriteGame(int iGame, unsigned int* pnAppID, unsigned int* pnIP, unsigned short* pnConnPort,
	                                  unsigned short* pnQueryPort, unsigned int* punFlags,
	                                  unsigned int* pRTime32LastPlayedOnServer)
	{
		return false;
	}

	int matchmaking::AddFavoriteGame(unsigned int nAppID, unsigned int nIP, unsigned short nConnPort,
	                                 unsigned short nQueryPort, unsigned int unFlags,
	                                 unsigned int rTime32LastPlayedOnServer)
	{
		auto addr = network::address_from_ip(htonl(nIP), nConnPort);
		server_list::add_favorite_server(addr);
		return 0;
	}

	bool matchmaking::RemoveFavoriteGame(unsigned int nAppID, unsigned int nIP, unsigned short nConnPort,
	                                     unsigned short nQueryPort, unsigned int unFlags)
	{
		auto addr = network::address_from_ip(htonl(nIP), nConnPort);
		server_list::remove_favorite_server(addr);
		return false;
	}

	unsigned long long matchmaking::RequestLobbyList()
	{
		enforce_lan_dvars();
		global_lan_session_id = SteamUser()->GetSteamID().bits;
		return k_chat_room_enter_response_success;
	}

	void matchmaking::AddRequestLobbyListStringFilter(const char* pchKeyToMatch, const char* pchValueToMatch,
	                                                  int eComparisonType)
	{
	}

	void matchmaking::AddRequestLobbyListNumericalFilter(const char* pchKeyToMatch, int nValueToMatch,
	                                                     int eComparisonType)
	{
	}

	void matchmaking::AddRequestLobbyListNearValueFilter(const char* pchKeyToMatch, int nValueToBeCloseTo)
	{
	}

	void matchmaking::AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable)
	{
	}

	void matchmaking::AddRequestLobbyListDistanceFilter(int eLobbyDistanceFilter)
	{
	}

	void matchmaking::AddRequestLobbyListResultCountFilter(int cMaxResults)
	{
	}

	void matchmaking::AddRequestLobbyListCompatibleMembersFilter(steam_id steamID)
	{
	}

	steam_id matchmaking::GetLobbyByIndex(int iLobby)
	{
		return make_lobby_id_from_session(global_lan_session_id);
	}

	unsigned long long matchmaking::CreateLobby(int eLobbyType, int cMaxMembers)
	{
		enforce_lan_dvars();
		global_lan_session_id = SteamUser()->GetSteamID().bits;
		return k_chat_room_enter_response_success;
	}

	unsigned long long matchmaking::JoinLobby(steam_id steamIDLobby)
	{
		enforce_lan_dvars();
		global_lan_session_id = steamIDLobby.bits ? steamIDLobby.bits : SteamUser()->GetSteamID().bits;
		return k_chat_room_enter_response_success;
	}

	void matchmaking::LeaveLobby(steam_id steamIDLobby)
	{
	}

	bool matchmaking::InviteUserToLobby(steam_id steamIDLobby, steam_id steamIDInvitee)
	{
		return true;
	}

	int matchmaking::GetNumLobbyMembers(steam_id steamIDLobby)
	{
		return 1;
	}

	steam_id matchmaking::GetLobbyMemberByIndex(steam_id steamIDLobby, int iMember)
	{
		return make_lobby_id_from_session(global_lan_session_id);
	}

	const char* matchmaking::GetLobbyData(steam_id steamIDLobby, const char* pchKey)
	{
		return "";
	}

	bool matchmaking::SetLobbyData(steam_id steamIDLobby, const char* pchKey, const char* pchValue)
	{
		return true;
	}

	int matchmaking::GetLobbyDataCount(steam_id steamIDLobby)
	{
		return 0;
	}

	bool matchmaking::GetLobbyDataByIndex(steam_id steamIDLobby, int iLobbyData, char* pchKey, int cchKeyBufferSize,
	                                      char* pchValue, int cchValueBufferSize)
	{
		return true;
	}

	bool matchmaking::DeleteLobbyData(steam_id steamIDLobby, const char* pchKey)
	{
		return true;
	}

	const char* matchmaking::GetLobbyMemberData(steam_id steamIDLobby, steam_id steamIDUser, const char* pchKey)
	{
		return "";
	}

	void matchmaking::SetLobbyMemberData(steam_id steamIDLobby, const char* pchKey, const char* pchValue)
	{
	}

	bool matchmaking::SendLobbyChatMsg(steam_id steamIDLobby, const void* pvMsgBody, int cubMsgBody)
	{
		return true;
	}

	int matchmaking::GetLobbyChatEntry(steam_id steamIDLobby, int iChatID, steam_id* pSteamIDUser, void* pvData,
	                                   int cubData, int* peChatEntryType)
	{
		return 0;
	}

	bool matchmaking::RequestLobbyData(steam_id steamIDLobby)
	{
		return true;
	}

	void matchmaking::SetLobbyGameServer(steam_id steamIDLobby, unsigned int unGameServerIP,
	                                     unsigned short unGameServerPort, steam_id steamIDGameServer)
	{
	}

	bool matchmaking::GetLobbyGameServer(steam_id steamIDLobby, unsigned int* punGameServerIP,
	                                     unsigned short* punGameServerPort, steam_id* psteamIDGameServer)
	{
		return true;
	}

	bool matchmaking::SetLobbyMemberLimit(steam_id steamIDLobby, int cMaxMembers)
	{
		return true;
	}

	int matchmaking::GetLobbyMemberLimit(steam_id steamIDLobby)
	{
		return 0;
	}

	bool matchmaking::SetLobbyType(steam_id steamIDLobby, int eLobbyType)
	{
		return true;
	}

	bool matchmaking::SetLobbyJoinable(steam_id steamIDLobby, bool bLobbyJoinable)
	{
		return true;
	}

	steam_id matchmaking::GetLobbyOwner(steam_id steamIDLobby)
	{
		return make_lobby_id_from_session(global_lan_session_id);
	}

	bool matchmaking::SetLobbyOwner(steam_id steamIDLobby, steam_id steamIDNewOwner)
	{
		return true;
	}

	bool matchmaking::SetLinkedLobby(steam_id steamIDLobby, steam_id steamIDLobby2)
	{
		return true;
	}
}
