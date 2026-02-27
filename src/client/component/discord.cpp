#include <std_include.hpp>
#include "loader/component_loader.hpp"

namespace discord
{
	bool init()
	{
		return true;
	}

	class component final : public client_component
	{
	public:
		void post_load() override
		{
			this->initialized_ = init();
		}

		void pre_destroy() override
		{
			this->initialized_ = false;
		}

	private:
		bool initialized_ = false;
	};
}

#ifndef DEV_BUILD
REGISTER_COMPONENT(discord::component)
#endif
