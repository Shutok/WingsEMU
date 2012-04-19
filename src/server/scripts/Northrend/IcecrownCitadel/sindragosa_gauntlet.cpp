/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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
 
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "icecrown_citadel.h"

#define MAX_WEBWEAVER 4
#define MAX_CHAMPION 4

enum IntroText
{
    SAY_INTRO               = 0,
};

enum GauntletMobs
{
    NPC_NERUBAR_WEBWEAVER       = 37502,
    NPC_NERUBAR_CHAMPION        = 37501,
};

enum GauntletSpells
{
    //climbing off the wall net visual
    SPELL_HANG_DOWN         = 69986,
    //Nerubar Champion
    SPELL_RUSH_ATTACK       = 71801,
    SPELL_SOUL_FEAST        = 71203, //used for both mobs
    //Neruber Webweaver
    SPELL_WEB               = 71327,
    SPELL_SCARABS           = 71326,
};

enum GauntletActions
{
    ACTION_START_GAUNTLET   = 1,
};

enum MovementPoints
{
    POINT_CENTER  = 1,
};

const Position SpawnWeb[4] =
{
    {4132.149f, 2510.760f, 241.034f, 5.674f},
    {4155.576f, 2345.310f, 241.034f, 0.780f},
    {4229.090f, 2458.494f, 241.034f, 2.615f},
    {4208.231f, 2534.020f, 241.034f, 3.910f},
};

const Position SpawnChamp[4] =
{
    {4145.036f, 2533.892f, 241.034f, 5.462f},
    {4132.119f, 2457.622f, 241.034f, 0.597f},
    {4207.355f, 2435.044f, 241.034f, 2.382f},
    {4229.515f, 2510.715f, 241.034f, 3.554f},
};

const Position ground1[4] =
{
    {4132.149f, 2510.760f, 211.034f, 5.674f},
    {4155.576f, 2345.310f, 211.034f, 0.780f},
    {4229.090f, 2458.494f, 211.034f, 2.615f},
    {4208.231f, 2534.020f, 211.034f, 3.910f},
};

const Position ground2[4] =
{
    {4145.036f, 2533.892f, 211.034f, 5.462f},
    {4132.119f, 2457.622f, 211.034f, 0.597f},
    {4207.355f, 2435.044f, 211.034f, 2.382f},
    {4229.515f, 2510.715f, 211.034f, 3.554f},
};

Position const Center = {4181.261f, 2484.272f, 211.032f, 6.227f};

class at_icc_start_sindragosa_gauntlet : public AreaTriggerScript
{
    public:
        at_icc_start_sindragosa_gauntlet() : AreaTriggerScript("at_icc_start_sindragosa_gauntlet") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
        {
            if (InstanceScript* instance = player->GetInstanceScript())
                if (Creature* Ward = ObjectAccessor::GetCreature(*player, instance->GetData64(DATA_SINDRAGOSA_WARD)))
                    Ward->AI()->DoAction(ACTION_START_GAUNTLET);
            return true;
        }
};

class npc_sindragosa_ward : public CreatureScript
{
    public:
        npc_sindragosa_ward() : CreatureScript("npc_sindragosa_ward") { }

        struct npc_sindragosa_wardAI : public ScriptedAI
        {
            npc_sindragosa_wardAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript())
            {
            }
			
            void Reset()
            {
                isEventDone=false;
            }
			
            void DoAction(int32 const action)
            {
                if (action == ACTION_START_GAUNTLET)
                {
                    if (isEventDone || !me->isAlive())
                        return;
						
                    isEventDone = true;

                    //Talk(SAY_INTRO);
                    me->PlayDirectSound(17167);
                    for (uint8 i = 0; i < MAX_WEBWEAVER; ++i)
                    {
                        if (Creature* Ward = me->SummonCreature(NPC_NERUBAR_WEBWEAVER, SpawnWeb[i]))
                        {
                            Ward->GetMotionMaster()->MovePoint(POINT_CENTER, Center);
                        }
                    }
                    for (uint8 i = 0; i < MAX_CHAMPION; ++i)
                    {
                        if (Creature* Ward = me->SummonCreature(NPC_NERUBAR_CHAMPION, SpawnChamp[i]))
                        {
                            Ward->GetMotionMaster()->MovePoint(POINT_CENTER, Center);
                        }
                    }
                }
            }

        private:
            bool isEventDone;
            InstanceScript* const instance;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_sindragosa_wardAI(creature);
        }
};
			
void AddSC_sindra_gauntlet()
{
    new at_icc_start_sindragosa_gauntlet();
    new npc_sindragosa_ward();
}