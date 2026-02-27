#include <std_include.hpp>

#include "../steam.hpp"

namespace steam
{
	namespace
	{
		std::string auth_ticket;

		uint32_t hash_machine_name()
		{
			char computer_name[MAX_COMPUTERNAME_LENGTH + 1]{};
			DWORD computer_name_size = static_cast<DWORD>(std::size(computer_name));

			if (!GetComputerNameA(computer_name, &computer_name_size) || computer_name_size == 0)
			{
				return 0x5F3759DFu;
			}

			uint32_t hash = 2166136261u;
			for (DWORD index = 0; index < computer_name_size; ++index)
			{
				hash ^= static_cast<uint8_t>(computer_name[index]);
				hash *= 16777619u;
			}

			return (hash == 0) ? 0xA5A5A5A5u : hash;
		}

		steam_id generate_steam_id()
		{
			steam_id id{};
			id.raw.account_id = hash_machine_name();
			id.raw.account_instance = 1;
			id.raw.account_type = 1;
			id.raw.universe = 1;

			if (id.bits == 0)
			{
				id.raw.account_id = 0x13572468u;
				id.raw.account_instance = 1;
				id.raw.account_type = 1;
				id.raw.universe = 1;
			}

			return id;
		}
	}

	int user::GetHSteamUser()
	{
		return 1;
	}

	bool user::LoggedOn()
	{
		return true;
	}

	steam_id user::GetSteamID()
	{
		static auto id = generate_steam_id();
		return id;
	}

	int user::InitiateGameConnection(void* pAuthBlob, int cbMaxAuthBlob, steam_id steamIDGameServer,
	                                 unsigned int unIPServer, unsigned short usPortServer, bool bSecure)
	{
		return 0;
	}

	void user::TerminateGameConnection(unsigned int unIPServer, unsigned short usPortServer)
	{
	}

	void user::TrackAppUsageEvent(steam_id gameID, int eAppUsageEvent, const char* pchExtraInfo)
	{
	}

	bool user::GetUserDataFolder(char* pchBuffer, int cubBuffer)
	{
		return false;
	}

	void user::StartVoiceRecording()
	{
	}

	void user::StopVoiceRecording()
	{
	}

	int user::GetAvailableVoice(unsigned int* pcbCompressed, unsigned int* pcbUncompressed,
	                            unsigned int nUncompressedVoiceDesiredSampleRate)
	{
		return 0;
	}

	int user::GetVoice(bool bWantCompressed, void* pDestBuffer, unsigned int cbDestBufferSize,
	                   unsigned int* nBytesWritten, bool bWantUncompressed, void* pUncompressedDestBuffer,
	                   unsigned int cbUncompressedDestBufferSize, unsigned int* nUncompressBytesWritten,
	                   unsigned int nUncompressedVoiceDesiredSampleRate)
	{
		return 2;
	}

	int user::DecompressVoice(void* pCompressed, unsigned int cbCompressed, void* pDestBuffer,
	                          unsigned int cbDestBufferSize, unsigned int* nBytesWritten)
	{
		return 0;
	}

	unsigned int user::GetVoiceOptimalSampleRate()
	{
		return 0;
	}

	unsigned int user::GetAuthSessionTicket(void* pTicket, int cbMaxTicket, unsigned int* pcbTicket)
	{
		static uint32_t ticket = 0;

		if (pcbTicket)
		{
			*pcbTicket = 1;
		}

		if (pTicket && cbMaxTicket > 0)
		{
			static constexpr uint8_t local_ticket_byte = 0x01;
			std::memcpy(pTicket, &local_ticket_byte, 1);
		}

		return ++ticket;
	}

	int user::BeginAuthSession(const void* pAuthTicket, int cbAuthTicket, steam_id steamID)
	{
		return 0;
	}

	void user::EndAuthSession(steam_id steamID)
	{
	}

	void user::CancelAuthTicket(unsigned int hAuthTicket)
	{
	}

	unsigned int user::UserHasLicenseForApp(steam_id steamID, unsigned int appID)
	{
		return 1;
	}

	bool user::BIsBehindNAT()
	{
		return false;
	}

	void user::AdvertiseGame(steam_id steamIDGameServer, unsigned int unIPServer, unsigned short usPortServer)
	{
	}

	unsigned long long user::RequestEncryptedAppTicket(void* pUserData, int cbUserData)
	{
		const auto id = this->GetSteamID();

		auth_ticket = "T7x";
		auth_ticket.resize(32);
		auth_ticket.append(static_cast<char*>(pUserData), 24); // key
		auth_ticket.append(reinterpret_cast<const char*>(&id.bits), sizeof(id.bits)); // user id
		auth_ticket.append(&static_cast<char*>(pUserData)[24], 64); // user name

		return 1;
	}

	bool user::GetEncryptedAppTicket(void* pTicket, int cbMaxTicket, unsigned int* pcbTicket)
	{
		if (cbMaxTicket < 0 || auth_ticket.empty()) return false;

		const auto size = auth_ticket.size();
		if (size_t(cbMaxTicket) < size)
		{
			*pcbTicket = static_cast<unsigned>(size);
			return false;
		}

		std::memcpy(pTicket, auth_ticket.data(), size);
		*pcbTicket = static_cast<unsigned>(size);

		return true;
	}

	int user::GetGameBadgeLevel(int nSeries, bool bFoil)
	{
		return 1;
	}

	int user::GetPlayerSteamLevel()
	{
		return 0;
	}

	uint64_t user::RequestStoreAuthURL(const char* pchRedirectURL)
	{
		return 0;
	}

	bool user::BIsPhoneVerified()
	{
		return true;
	}

	bool user::BIsTwoFactorEnabled()
	{
		return true;
	}

	bool user::BIsPhoneIdentifying()
	{
		return false;
	}

	bool user::BIsPhoneRequiringVerification()
	{
		return false;
	}
}
