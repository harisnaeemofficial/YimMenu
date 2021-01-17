#include "features.hpp"
#include "gta/replay.hpp"
#include "pointers.hpp"

namespace big
{
	void features::replay_interface()
	{
		Ped player = PLAYER::PLAYER_PED_ID();
		
		rage::CReplayInterface* replay_interf = *g_pointers->m_replay_interface;
		rage::CObjectInterface* object_interf = replay_interf->m_object_interface;

		auto& protections = g_settings.options["settings"]["protections"];

		const int max_obj = object_interf->m_max_objects;
		for (int i = 0; i < max_obj; i++)
		{
			rage::CObject* obj = object_interf->get_object(i);
			if (obj == nullptr) continue;

			Object ent = g_pointers->m_ptr_to_handle(obj);

			if (
				protections["attach"] &&
				(
					ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(player, ent) ||
					ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(player, true), ent)
				)
			)
				functions::delete_entity(ent);

			if (protections["cage"] && ENTITY::GET_ENTITY_MODEL(ent) == RAGE_JOAAT("prop_gold_cont_01"))
				functions::delete_entity(ent);
		}
	}
}