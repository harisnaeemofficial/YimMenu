#pragma once
#include "common.hpp"
#include "gta/player.hpp"

namespace big
{
	class settings
	{
	public:
		explicit settings() = default;
		~settings() = default;

		nlohmann::json options;
		nlohmann::json default_options =
		R"({
			"god_mode": false,
			"never_wanted": false,
			"no_bike_fall": false,
			"no_idle_kick": false,
			"off_radar": false,
			"ragdoll": false,
			"rank": 6969,
			"spoof_rank": false,
			"sticky_tyres": false,
			"super_sprint": false
		})"_json;

		bool save()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += "\\BigBaseV2\\settings.json";

			std::ofstream file(settings_file, std::ios::out | std::ios::trunc);
			file << options.dump(4);
			file.close();
			return true;
		}

		bool load()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += "\\BigBaseV2\\settings.json";

			std::ifstream file(settings_file);

			if (!file.is_open())
			{
				write_default_config();
				file.open(settings_file);
			}

			file >> options;

			bool should_save = false;
			for (auto& e : default_options.items())
			{
				if (options.count(e.key()) == 0)
				{
					should_save = true;
					options[e.key()] = e.value();
				}
					
			}

			if (should_save)
			{
				LOG(INFO) << "Updating settings.";
				save();
			}

			return true;
		}

	private:
		bool write_default_config()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += "\\BigBaseV2\\settings.json";

			std::ofstream file(settings_file, std::ios::out);
			file << default_options.dump(4);
			file.close();

			options.clear();
			options = default_options;

			return true;
		}
	};

	inline settings g_settings;
}
