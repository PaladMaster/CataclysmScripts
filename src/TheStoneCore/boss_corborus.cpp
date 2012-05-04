/*
* Copyright (C) 2011 ArkCORE <http://www.arkania.net/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ScriptPCH.h"
#include "the_stonecore.h"

enum Spells
{
    SPELL_CRYSTAL_BARRAGE                        = 86881,
    SPELL_SUMMON_CRYSTAL_SHARD                   = 92012,
    SPELL_DAMPENING_WAVE                         = 92650,
    SPELL_TRASHING_CHARGE_TELE                   = 81839,
    SPELL_TRASHING_CHARGE_VISUAL                 = 81801,
    SPELL_BURROW                                 = 26381,
};

enum Events
{
    EVENT_CRYSTAL_BARRAGE = 1,
    EVENT_SUMMON_CRYSTAL_SHARD,
    EVENT_DAMPENING_WAVE,
    EVENT_TRASHING_CHARGE_TELE,
    EVENT_TRASHING_CHARGE_VISUAL,
    EVENT_BURROW
};

class boss_corborus : public CreatureScript
{
public:
	boss_corborus() : CreatureScript("boss_corborus") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_corborusAI (creature);
	}

	struct boss_corborusAI : public ScriptedAI
	{
		boss_corborusAI(Creature* creature) : ScriptedAI(creature)
		{
			instance = creature->GetInstanceScript();
		}

		InstanceScript* instance;
		EventMap events;
		EventMap burrowEvents;
		bool burrowed;

		void Reset()
                {
                   teleCount = 0;
                   me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                   me->RemoveAura(65981);
                   phase = 0;
                   events.Reset();
                 }   

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_CRYSTAL_BARRAGE,urand(7000,10000));
			events.ScheduleEvent(EVENT_DAMPENING_WAVE,urand(5000,7000));
			events.ScheduleEvent(EVENT_BURROW, 13000);

			burrowed = false;
		}

		void UpdateAI(const uint32 uiDiff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			// We use 2 different EventMaps for 2 Phases
			if(burrowed)
			{
				burrowEvents.Update(uiDiff);
			}else
			{
				events.Update(uiDiff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
					case EVENT_CRYSTAL_BARRAGE:

						if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, SPELL_CRYSTAL_BARRAGE);

						events.ScheduleEvent(EVENT_CRYSTAL_BARRAGE,urand(15000,20000));
						break;
					case EVENT_DAMPENING_WAVE:
						DoCastAOE(SPELL_DAMPENING_WAVE);

						events.ScheduleEvent(EVENT_DAMPENING_WAVE,urand(10000,12000));
						break;
					case EVENT_BURROW:			
						DoCast(me,SPELL_BURROW);

						burrowEvents.Reset();
						events.ScheduleEvent(EVENT_BURROW, 30000);
						break;
					}
				}
			}

			DoMeleeAttackIfReady();
		}
	};
};

void AddSC_boss_corborus()
{
	new boss_corborus();
}