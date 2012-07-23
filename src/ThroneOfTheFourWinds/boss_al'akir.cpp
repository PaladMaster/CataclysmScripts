/*
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
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
 
#include "throne_of_the_four_winds.h"

class boss_alakir: public CreatureScript
{
    public:
        boss_alakir() : CreatureScript("boss_alakir") { }

    struct boss_alakirAI: public BossAI
    {
        boss_alakirAI(Creature* creature) : BossAI
        SummonList summons;
        
        void Reset ()
        
        void EnterCombat(Unit* who) {}
        
        void JustDied(Unit* killer) {}
        
        void UpdateAI(const uint32 diff) {}
        
    };
    
    CreatureAI* GetAI(Creature* creature) const
    
    {
        return new boss_alakirAI(creature);
    }
};

void AddSC_boss_alakir()
{
    new boss_alakir();
}
        
