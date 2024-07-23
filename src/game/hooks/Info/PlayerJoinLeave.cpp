#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/rdr/Natives.hpp"
#include "network/CNetGamePlayer.hpp"

#include <regex>

namespace YimMenu::Hooks
{
	void Info::PlayerHasJoined(CNetGamePlayer* player)
	{
		BaseHook::Get<Info::PlayerHasJoined, DetourHook<decltype(&Info::PlayerHasJoined)>>()->Original()(player);

		LOG(INFO) << player->GetName() << " is joining your session.";

		static const std::regex namePattern{R"(^([\w\.-]{6,16})$)"};
		if (!std::regex_match(player->GetName(), namePattern))
		{
			LOG(WARNING) << player->GetName() << " has an invalid name.";
		}
	}

	void Info::PlayerHasLeft(CNetGamePlayer* player)
	{
		BaseHook::Get<Info::PlayerHasLeft, DetourHook<decltype(&Info::PlayerHasLeft)>>()->Original()(player);

		LOG(INFO) << player->GetName() << " has left your session.";
	}
}