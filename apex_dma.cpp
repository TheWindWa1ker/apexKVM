#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <random>
#include <chrono>
#include <iostream>
#include <cfloat>
#include "Game.h"
#include <thread>
#include <array>
#include <map>
#include <cstdlib> // For the system() function
#include <fstream>
#include <filesystem>
//this is a test, with seconds
Memory apex_mem;


//Just setting things up, dont edit.
bool active = true;
uintptr_t aimentity = 0;
uintptr_t tmp_aimentity = 0;
uintptr_t lastaimentity = 0;
float max = 999.0f;
int team_player = 0;
const int toRead = 100;
bool aiming = false;

//Removed but not all the way, dont edit.
int glowtype;
int glowtype2;
float aimdist = 200.0f * 40.0f;
bool actions_t = false;
bool cactions_t = false;
bool updateInsideValue_t = false;
bool terminal_t = false;
bool esp_t = false;
bool aim_t = false;
bool vars_t = false;
bool item_t = false;
uint64_t g_Base;
bool next2 = false;
bool valid = false;
bool lock = false;
float ADSfov = 10;
float nonADSfov = 50;
extern float bulletspeed;
extern float bulletgrav;


//^^ Don't EDIT^^

//CONFIG AREA, you must set all the true/false to what you want.
//Enable Loading of setting file automaticly.
bool LoadSettings = true;
bool SuperKey = true;
//Gamepad or Keyboard config, Only one true at once or it wont work.
bool keyboard = true;
bool gamepad = false;
//Done with Gamepad or Keyboard config
//Terminal Stuff
bool lootfilledtoggle = true;
bool playerfilledtoggle = true;
bool SuperKeyToggle = true;
//end Terminal Stuff
bool TDMToggle = false;
bool item_glow = false; //item glow
bool player_glow = true; //player glow
bool aim_no_recoil = true; //no recoil
float max_fov = 30; // Fov you want to use while aiming
int aim = 2; // 0 no aim, 1 aim with no vis check, 2 aim with vis check
//aimbot for nades on or off
bool NoNadeAim = true;
bool firing_range = false; //firing range
int bone = 2; //bone 0 head, 1 neck, 2 chest, 3 dick shot
float smooth = 100.0f; //min 85 no beaming, 100 somewhat beam people, 125 should be safe
//Player Glow Color and Brightness.
//inside fill
unsigned char insidevalue = 14;  //0 = no fill, 14 = full fill
//Outline size
unsigned char outlinesize = 32; // 0-255
//Not Visable 
float glowrnot = 1; //Red 0-1, higher is brighter color.
float glowgnot = 0; //Green 0-1, higher is brighter color.
float glowbnot = 0; //Blue 0-1, higher is brighter color.
//Visable
float glowrviz = 0; //Red 0-1, higher is brighter color.
float glowgviz = 1; //Green 0-1, higher is brighter color.
float glowbviz = 1; //Blue 0-1, higher is brighter color.
//Knocked
float glowrknocked = 1; //Red 0-1, higher is brighter color.
float glowgknocked = 1; //Green 0-1, higher is brighter color.
float glowbknocked = 1; //Blue 0-1, higher is brighter color.
//Item Configs
//loot Fill
unsigned char lootfilled = 14;  //0 no fill, 14 100% fill
//rev skull
bool skull = true;
//Backpacks
bool lightbackpack = false;
bool medbackpack = true;
bool heavybackpack = true;
bool goldbackpack = true;
//Shield upgrades
bool shieldupgrade1 = false;  //white
bool shieldupgrade2 = true;  //blue
bool shieldupgrade3 = true;  //purple
bool shieldupgrade4 = true;  //gold
bool shieldupgrade5 = true;  //red
bool shieldupgradehead1 = false;
bool shieldupgradehead2 = true;
bool shieldupgradehead3 = true;
bool shieldupgradehead4 = true;
bool shielddown1 = false;
bool shielddown2 = true;
bool shielddown3 = true;
bool shielddown4 = true;
//heaing and Misc
bool accelerant = false;
bool phoenix = true;
bool healthlarge = true;
bool healthsmall = false;
bool shieldbattsmall = false;
bool shieldbattlarge = true;
//Ammo
bool sniperammo = false;
bool heavyammo = true;
bool lightammo = true;
bool energyammo = true;
bool shotgunammo = false;
//Optics
bool optic1xhcog = false;
bool optic2xhcog = true;
bool opticholo1x = false;
bool opticholo1x2x = true;
bool opticthreat = false;
bool optic3xhcog = true;
bool optic2x4x = true;
bool opticsniper6x = false;
bool opticsniper4x8x = true;
bool opticsniperthreat = false;
//Magazines
bool sniperammomag1 = false;
bool energyammomag1 = true;
bool lightammomag1 = true;
bool heavyammomag1 = true;
bool sniperammomag2 = false;
bool energyammomag2 = true;
bool lightammomag2 = true;
bool heavyammomag2 = true;
bool sniperammomag3 = false;
bool energyammomag3 = true;
bool lightammomag3 = true;
bool heavyammomag3 = true;
bool sniperammomag4 = false;
bool energyammomag4 = true;
bool lightammomag4 = true;
bool heavyammomag4 = true;
//Attachments 
bool lasersight1 = false;
bool lasersight2 = true;
bool lasersight3 = true;
bool lasersight4 = true;
bool stocksniper1 = false;
bool stocksniper2 = true;
bool stocksniper3 = true;
bool stocksniper4 = true;
bool stockregular1 = false;
bool stockregular2 = true;
bool stockregular3 = true;
bool suppressor1 = false;
bool suppressor2 = true;
bool suppressor3 = true;
bool turbo_charger = false;
bool skull_piecer = false;
bool hammer_point = true;
bool disruptor_rounds = true;
bool boosted_loader = false;
bool shotgunbolt1 = false;
bool shotgunbolt2 = false;
bool shotgunbolt3 = false;
bool shotgunbolt4 = false;
//Nades
bool grenade_frag = false;
bool grenade_arc_star = false;
bool grenade_thermite = false;
//Kraber
bool weapon_kraber = true;
//Shotguns
bool weapon_mastiff = false;
bool weapon_eva8  = false;
bool weapon_peacekeeper  = false;
bool weapon_mozambique  = false;
//Energy weapons
bool weapon_lstar = true;
bool weapon_nemesis = true;
bool weapon_havoc = false;
bool weapon_devotion = false;
bool weapon_triple_take = false;
bool weapon_prowler  = false;
bool weapon_volt  = true;
//Heavy Weapons
bool weapon_flatline = true;
bool weapon_hemlock  = true;
bool weapon_3030_repeater = false; 
bool weapon_rampage  = false;
bool weapon_car_smg  = true;
//Light weapons
bool weapon_p2020  = false;
bool weapon_re45  = true;
bool weapon_g7_scout  = false;
bool weapon_alternator  = false;
bool weapon_r99  = true;
bool weapon_spitfire  = true;
bool weapon_r301 = true;
//Snipers.. wingman is the odd one...and the bow..
bool weapon_wingman  = false;
bool weapon_longbow  = false;
bool weapon_charge_rifle  = false;
bool weapon_sentinel  = false;
bool weapon_bow  = false;
//trigger bot
bool is_trigger;
//Used to change things on a timer
/* unsigned char insidevalueItem = 1;
void updateInsideValue()
{
	updateInsideValue_t = true;
	while (updateInsideValue_t)
	{
		insidevalueItem++;
		insidevalueItem %= 256;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		printf("smooth: %f\n", smooth);
		printf("bone: %i\n", bone);
		printf("glowrnot: %f\n", glowrnot);
		printf("glowgnot: %f\n", glowgnot);
		printf("glowbnot: %f\n", glowbnot);
		
		
	}
	updateInsideValue_t = false;
} */
//DONE WITH THE EDITING
//Player Definitions, dont edit unless you know what you are doing.
typedef struct player
{
	float dist = 0;
	int entity_team = 0;
	bool knocked = false;
	bool visible = false;
	int health = 0;
	int shield = 0;
}player;
struct Matrix
{
	float matrix[16];
};
float lastvis_aim[toRead];
int tmp_spec = 0, spectators = 0;
int tmp_all_spec = 0, allied_spectators = 0;
int glowtype3;
int settingIndex;
int contextId;
std::array<float, 3> highlightParameter;
//works
void SetPlayerGlow(Entity& LPlayer, Entity& Target, int index)
{
	if (player_glow >= 1)
	{
			if (!Target.isGlowing() || (int)Target.buffer[OFFSET_GLOW_THROUGH_WALLS_GLOW_VISIBLE_TYPE] != 1) {
				float currentEntityTime = 5000.f;
				if (!isnan(currentEntityTime) && currentEntityTime > 0.f) {
					if (!(firing_range) && (Target.isKnocked() || !Target.isAlive()))
					{
						contextId = 5;
						settingIndex = 80;
						highlightParameter = { glowrknocked, glowgknocked, glowbknocked };
					}
					else if (Target.lastVisTime() > lastvis_aim[index] || (Target.lastVisTime() < 0.f && lastvis_aim[index] > 0.f))
					{
						contextId = 6;
						settingIndex = 81;
						highlightParameter = { glowrviz, glowgviz, glowbviz };
					}
					else 
					{
						contextId = 7;
						settingIndex = 82;
						highlightParameter = { glowrnot, glowgnot, glowbnot };
					}
					Target.enableGlow();
				}
			}
	}
	else
		{
			if (!Target.isGlowing() || (int)Target.buffer[OFFSET_GLOW_THROUGH_WALLS_GLOW_VISIBLE_TYPE] != 1) {
				float currentEntityTime = 5000.f;
				if (!isnan(currentEntityTime) && currentEntityTime > 0.f) {
					if (!(firing_range) && (Target.isKnocked() || !Target.isAlive()))
					{
						insidevalue = 0;  //0 = no fill, 14 = full fill
						//Outline size
						outlinesize = 0; // 0-255
						contextId = 5;
						settingIndex = 80;
						highlightParameter = { 0, 0, 0 };
					}
					else if (Target.lastVisTime() > lastvis_aim[index] || (Target.lastVisTime() < 0.f && lastvis_aim[index] > 0.f))
					{
						insidevalue = 0;  //0 = no fill, 14 = full fill
						//Outline size
						outlinesize = 0; // 0-255
						contextId = 6;
						settingIndex = 81;
						highlightParameter = { 0, 0, 0 };
					}
					else 
					{
						insidevalue = 0;  //0 = no fill, 14 = full fill
						//Outline size
						outlinesize = 0; // 0-255
						contextId = 7;
						settingIndex = 82;
						highlightParameter = { 0, 0, 0 };
					}
					Target.enableGlow();
				}
			}
		}
}

bool IsInCrossHair(Entity& target)
{
    static uintptr_t last_t;
		static float last_crosshair_target_time = -1.f;
		float now_crosshair_target_time = target.lastVisTime();
		bool is_trigger = false;
		
		/* driver.Writevirtual<uint32_t>(driver.GameBase + OFFSET_IN_ATTACK + 0x8, 4);
		Sleep(1);
		driver.Writevirtual<uint32_t>(driver.GameBase + OFFSET_IN_ATTACK + 0x8, 5);
		Sleep(1);
		driver.Writevirtual<uint32_t>(driver.GameBase + OFFSET_IN_ATTACK + 0x8, 4); */
		if (last_t == target.ptr)
		{
			if (last_crosshair_target_time != -1.f)
			{
				if (now_crosshair_target_time > last_crosshair_target_time)
				{
					is_trigger = true;
					last_crosshair_target_time = -1.f;
				}
				else
				{
					is_trigger = false;
					last_crosshair_target_time = now_crosshair_target_time;
				}
			}
			else
			{
				is_trigger = false;
				last_crosshair_target_time = now_crosshair_target_time;
			}
	 
		}
		else
		{
			last_t = target.ptr;
			last_crosshair_target_time = -1.f;
		}
	 
		return is_trigger;
}


void MapRadarTesting()
{
	uintptr_t pLocal;
		apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, pLocal);
	int dt;
		apex_mem.Read<int>(pLocal + OFFSET_TEAM, dt);

	for (uintptr_t i = 0; i <= 80000; i++)
	{
		apex_mem.Write<int>(pLocal + OFFSET_TEAM, 1);
	}

	for (uintptr_t i = 0; i <= 80000; i++)
	{
		apex_mem.Write<int>(pLocal + OFFSET_TEAM, dt);
	}
}

uint64_t PlayerLocal;
int PlayerLocalTeamID;
int EntTeam;
int LocTeam;

using Clock = std::chrono::steady_clock;
std::chrono::time_point<std::chrono::steady_clock> start1, now1;
std::chrono::milliseconds duration1;

void loop()
{
	start1 = Clock::now();
}

std::chrono::steady_clock::time_point tduckStartTime;
bool mapRadarTestingEnabled = true;




void ClientActions()
{
	cactions_t = true;
	while (cactions_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		while (g_Base!=0)
		{
			
			uint64_t LocalPlayer = 0;
			apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
			Entity LPlayer = getEntity(LocalPlayer);
			uint64_t entitylist = g_Base + OFFSET_ENTITYLIST;
			int attackState = 0;
			apex_mem.Read<int>(g_Base + OFFSET_IN_ATTACK, attackState); //108
			int tduckState = 0;
			apex_mem.Read<int>(g_Base + OFFSET_IN_TOGGLE_DUCK, tduckState); //61			
			int zoomState = 0;
			apex_mem.Read<int>(g_Base + OFFSET_IN_ZOOM, zoomState); //109
			int frameSleepTimer;
			int lastFrameNumber;
			bool superGlideStart;
			int superGlideTimer;
			int curFrameNumber;
			float m_traversalProgressTmp = 0.0f;
			apex_mem.Read<int>(g_Base + OFFSET_GLOBAL_VARS + 0x0008, curFrameNumber); // GlobalVars + 0x0008
			float m_traversalProgress;
			
			apex_mem.Read<float>(LocalPlayer + OFFSET_TRAVERSAL_PROGRESS, m_traversalProgress);
			//printf("Travel Time: %f\n", m_traversalProgress);
			//printf("Frame Sleep Timer: %i\n", frameSleepTimer);
			//printf("Last Frame: %i\n", lastFrameNumber);
			//printf("Super Glide Timer: %i\n", superGlideTimer);
			//printf("Last Frame: %i\n", lastFrameNumber);
			//printf("Cur Frame: %i\n", curFrameNumber);
			//printf("superGlideStart: %d\n", superGlideStart ? 1 : 0);
			int jump;
			int ducktoggle;
			int forceduck;
			//printf("Jump Value: %i\n", jump);
			//printf("Toggle Jump: %i\n", ducktoggle);
			//printf("Force Duck: %i\n", forceduck);
			apex_mem.Read<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, jump);
			apex_mem.Read<int>(g_Base + OFFSET_IN_TOGGLE_DUCK + 0x8, ducktoggle);
			apex_mem.Read<int>(g_Base + OFFSET_FORCE_DUCK + 0x8, forceduck);
			//apex_mem.Write<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, 4);
			
			if (curFrameNumber > lastFrameNumber)
			{
				frameSleepTimer = 5; // <- middle of the frame // needs 5 for 144fps and 10 for 75 fps
			}
			lastFrameNumber = curFrameNumber;
			 
			if (frameSleepTimer == 0)
			{
				if(SuperKey)
				{
					if (m_traversalProgress > 0.85 && m_traversalProgress < 0.92) // needs to end at 0.90 for 144 fps and 0.92 for 75 fps
					{
						superGlideStart = true;
					}
				 
					if (superGlideStart)
					{
						superGlideTimer++;
						//printf("Timer Started \n");
						if (superGlideTimer == 5)
						{
							apex_mem.Write<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, 5);
						}
						else if (superGlideTimer == 6)
						{
							apex_mem.Write<int>(g_Base + OFFSET_IN_TOGGLE_DUCK + 0x8, 6);
						}
						else if (superGlideTimer == 10) //needs to be 10 for 75 and 144fps?
						{
							apex_mem.Write<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, 4);
							apex_mem.Write<int>(g_Base + OFFSET_FORCE_DUCK + 0x8, 5);
							apex_mem.Write<int>(g_Base + OFFSET_FORCE_DUCK + 0x8, 4);
							m_traversalProgressTmp = m_traversalProgress;
						}
						else if (superGlideTimer > 10 && m_traversalProgress != m_traversalProgressTmp)
						{
							superGlideStart = false;
							superGlideTimer = 0;
						}
					}
				}
			}
			frameSleepTimer -= 1;
			//printf("Minimap: %ld\n", minimap);
			//apex_mem.Write(LocalPlayer + 0x270 , 1);
			if(keyboard)
			{
				if (attackState == 108 || zoomState == 109)
				{
					aiming = true;
				}
				else
				{
					aiming = false;
				}
				
				
				if (attackState == 108 || !zoomState == 109)
				{
					max_fov = nonADSfov;
				}
				if (!attackState == 108 || zoomState == 109)
				{
					max_fov = ADSfov;
				}
			}
			
			if(gamepad)
			{
				if (attackState == 264 || zoomState == 263)
				{
					aiming = true;
				}
				else
				{
					aiming = false;
				}
				
				
				if (attackState == 264 || !zoomState == 263)
				{
					max_fov = nonADSfov;
				}
				if (!attackState == 264 || zoomState == 263)
				{
					max_fov = ADSfov;
				}
			}
			
			
			now1 = Clock::now();
			duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(now1 - start1);
			
						
			
			
		
				
			// Toggle crouch = check for ring
			if (attackState != 108 && tduckState == 65)
			{
				if (mapRadarTestingEnabled)
				{
					MapRadarTesting();
				}

				if (tduckStartTime == std::chrono::steady_clock::time_point())
				{
					tduckStartTime = std::chrono::steady_clock::now();
				}

				auto currentTime = std::chrono::steady_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - tduckStartTime).count();

				if (duration >= 500)
				{
					mapRadarTestingEnabled = false;
				}
			}
			else
			{
				tduckStartTime = std::chrono::steady_clock::time_point();
				mapRadarTestingEnabled = true;
			}
							
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			
		}
	}
	cactions_t = false;
}

void ProcessPlayer(Entity& LPlayer, Entity& target, uint64_t entitylist, int index)
{
	int entity_team = target.getTeamId();

	if (!target.isAlive())
	{
		float localyaw = LPlayer.GetYaw();
		float targetyaw = target.GetYaw();

		if(localyaw==targetyaw)
		{
			if(LPlayer.getTeamId() == entity_team)
				tmp_all_spec++;
			else
				tmp_spec++;
		}
		return;
	}
	
	if (TDMToggle)
	{// Check if the target entity is on the same team as the local player
		//int entity_team = Target.getTeamId();
		//printf("Target Team: %i\n", entity_team);


		uint64_t PlayerLocal;
		apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, PlayerLocal);
		int PlayerLocalTeamID;
		apex_mem.Read<int>(PlayerLocal + OFFSET_TEAM, PlayerLocalTeamID);



		if (entity_team % 2) EntTeam = 1;
		else EntTeam = 2;
		if (PlayerLocalTeamID % 2) LocTeam = 1;
		else LocTeam = 2;

		//printf("Target Team: %i\nLocal Team: %i\n", EntTeam, LocTeam);
		if (EntTeam == LocTeam)
			return;

	}
	

	Vector EntityPosition = target.getPosition();
	Vector LocalPlayerPosition = LPlayer.getPosition();
	float dist = LocalPlayerPosition.DistTo(EntityPosition);
	//if (dist > aimdist) return;
	
	
	//Firing range stuff
	if(!firing_range)
		if (entity_team < 0 || entity_team>50 || entity_team == team_player) return;
	
	
	//Vis check aiming? dunno
	if(aim==2)
	{
		if((target.lastVisTime() > lastvis_aim[index]))
		{
			float fov = CalculateFov(LPlayer, target);
			if (fov < max)
			{
				max = fov;
				tmp_aimentity = target.ptr;
			}
		}
		else
		{
			if(aimentity==target.ptr)
			{
				aimentity=tmp_aimentity=lastaimentity=0;
			}
		}
	}
	else
	{
		float fov = CalculateFov(LPlayer, target);
		if (fov < max)
		{
			max = fov;
			tmp_aimentity = target.ptr;
		}
	}
	SetPlayerGlow(LPlayer, target, index);
	lastvis_aim[index] = target.lastVisTime();
}
std::map<uint64_t, int> centityToNumber; // Map centity to a unique number
int uniqueNumber = 1; // Initialize a unique number
//Main stuff, dont edit.
void DoActions()
{
	actions_t = true;
	while (actions_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		uint32_t counter = 0;

		while (g_Base!=0)
		{
			
			std::this_thread::sleep_for(std::chrono::milliseconds(30));	

			uint64_t LocalPlayer = 0;
			apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
			if (LocalPlayer == 0) continue;

			Entity LPlayer = getEntity(LocalPlayer);

			team_player = LPlayer.getTeamId();
			if (team_player < 0 || team_player>50)
			{
				continue;
			}
			uint64_t entitylist = g_Base + OFFSET_ENTITYLIST;

			uint64_t baseent = 0;
			apex_mem.Read<uint64_t>(entitylist, baseent);
			if (baseent == 0)
			{
				continue;
			}

			max = 999.0f;
			tmp_aimentity = 0;
			tmp_spec = 0;
			tmp_all_spec = 0;
			if(firing_range)
			{
				int c=0;
				for (int i = 0; i < 16000; i++)
				{
					uint64_t centity = 0;
					apex_mem.Read<uint64_t>(entitylist + ((uint64_t)i << 5), centity);
					if (centity == 0) continue;
					if (LocalPlayer == centity) continue;

					Entity Target = getEntity(centity);
					if (!Target.isDummy())
					{
						continue;
					}
					
				

					ProcessPlayer(LPlayer, Target, entitylist, c);
					c++;
				}
			}
			else
			{
				

				for (int i = 0; i < toRead; i++)
				{
					uint64_t centity = 0;
					apex_mem.Read<uint64_t>(entitylist + ((uint64_t)i << 5), centity);
					if (centity == 0) continue;
					if (LocalPlayer == centity) continue;

					Entity Target = getEntity(centity);
					if (!Target.isPlayer())
					{
						continue;
					}
					
					ProcessPlayer(LPlayer, Target, entitylist, i);

					int entity_team = Target.getTeamId();
					if (entity_team == team_player)
					{
						continue;
					}
				}
			}

			if(!spectators && !allied_spectators)
			{
				spectators = tmp_spec;
				allied_spectators = tmp_all_spec;
			}
			else
			{
				//refresh spectators count every ~2 seconds
				counter++;
				if(counter==70)
				{
					spectators = tmp_spec;
					allied_spectators = tmp_all_spec;
					counter = 0;
				}
			}

			if(!lock)
				aimentity = tmp_aimentity;
			else
				aimentity = lastaimentity;

			
		}
	}
	actions_t = false;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////

player players[toRead];

//ESP loop.. this helps right?

//Aimbot Loop stuff
static void AimbotLoop()
{
	aim_t = true;
	while (aim_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		while (g_Base!=0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (aim>0)
			{
				if (aimentity == 0 || !aiming)
				{
					lock=false;
					lastaimentity=0;
					continue;
				}
				lock=true;
				lastaimentity = aimentity;
				uint64_t LocalPlayer = 0;
				apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
				Entity LPlayer = getEntity(LocalPlayer);
				if (LocalPlayer == 0) continue;
				QAngle Angles = CalculateBestBoneAim(LPlayer, aimentity, max_fov);
				if (Angles.x == 0 && Angles.y == 0)
				{
					lock=false;
					lastaimentity=0;
					continue;
				}
				LPlayer.SetViewAngles(Angles);
			}
		}
	}
	aim_t = false;
}
// Item Glow Stuff


static void item_glow_t()
{
	item_t = true;
	while(item_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		int k = 0;
		while(g_Base!=0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			uint64_t entitylist = g_Base + OFFSET_ENTITYLIST;
			if (item_glow)
			{
				//item ENTs to loop, 10k-15k is normal. 10k might be better but will not show all the death boxes i think.
				for (int i = 0; i < 15000; i++)
				{
					uint64_t centity = 0;
					apex_mem.Read<uint64_t>(entitylist + ((uint64_t)i << 5), centity);
					if (centity == 0) continue;
					Item item = getItem(centity);
					//testing
					uint64_t LocalPlayer = 0;
					apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
						
					
					//Item filter glow name setup and search.
					char glowName[200] = { 0 };
					uint64_t name_ptr;
					apex_mem.Read<uint64_t>(centity + OFFSET_MODELNAME, name_ptr);
					apex_mem.ReadArray<char>(name_ptr, glowName, 200);
					
					//item ids?
					uint64_t ItemID;
					apex_mem.Read<uint64_t>(centity + OFFSET_ITEM_ID, ItemID);
					/* uint64_t ItemID2;
					ItemID2 = ItemID % 301;
					printf("%ld\n", ItemID2); */
					
					//Level name printf
					//char LevelNAME[200] = { 0 };
					//uint64_t levelname_ptr;
					//apex_mem.Read<uint64_t>(g_Base + OFFSET_LEVELNAME, levelname_ptr);
					//apex_mem.ReadArray<char>(levelname_ptr, LevelNAME, 200);
					
					//printf("%s\n", LevelNAME);
					
					
					//Prints stuff you want to console
					//if (strstr(glowName, "mdl/")) 
					//{
					//printf("%ld\n", ItemID);
					//}
					//Search model name and if true sets glow, must be a better way to do this.. if only i got the item id to work..
					if (lightbackpack && ItemID == 206) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
												apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					
					}
					else
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 99;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	
					}
					if (medbackpack && ItemID == 207) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	
					
					}
					if (heavybackpack && ItemID == 208) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	
					
					}
					if (goldbackpack && ItemID == 209) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	
					
					}
					//item id would help so much here, cant make them all the same color so went with loba glow for body shield and helmet
					if (shieldupgrade1 && (ItemID == 214748364992 || ItemID == 14073963583897797))
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter); 
						
						uint64_t ItemID;
						apex_mem.Read<uint64_t>(centity + OFFSET_ITEM_ID, ItemID);
						//uint64_t ItemID2;
						//ItemID2 = ItemID % 301;
						//printf("%ld\n", ItemID);
						//apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);;
					}
					if (shieldupgrade2 && (ItemID == 322122547393 || ItemID == 21110945375846598))
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shieldupgrade3 && (ItemID == 429496729794 || ItemID == 52776987629977799)) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shieldupgrade4 && (ItemID == 429496729795))  
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shieldupgrade5 && ItemID == 536870912200)  
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shieldupgradehead1 && ItemID == 187) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shieldupgradehead2 && ItemID == 188) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shieldupgradehead3 && ItemID == 189) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shieldupgradehead4 && ItemID == 190) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (accelerant && ItemID == 181) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (phoenix && ItemID == 182) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (skull && strstr(glowName, "mdl/Weapons/skull_grenade/skull_grenade_base_v.rmdl")) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (item.isBox())
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 88;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						
					}
					
					if (item.isTrap())
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	
						
					}
					
					//Gas Trap
					if (strstr(glowName, "mdl/props/caustic_gas_tank/caustic_gas_tank.rmdl")) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (healthlarge && ItemID == 183) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
												apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (healthsmall && ItemID == 184) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
												apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shieldbattsmall && ItemID == 186) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shieldbattlarge && ItemID == 185) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
												apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (sniperammo && ItemID == 143) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
												apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (heavyammo && ItemID == 142) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 65;
												apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (optic1xhcog && ItemID == 214) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (lightammo && ItemID == 139) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.5490, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 66;
												apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (energyammo && ItemID == 140) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2, 1, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 73;
												apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shotgunammo && ItemID == 141) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (lasersight1 && ItemID == 228) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (lasersight2 && ItemID == 229) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (lasersight3 && ItemID == 230) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (sniperammomag1 && ItemID == 243) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (sniperammomag2 && ItemID == 244) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (sniperammomag3 && ItemID == 245) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (sniperammomag4 && ItemID == 246) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (energyammomag1 && ItemID == 239) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (energyammomag2 && ItemID == 240) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (energyammomag3 && ItemID == 241) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (energyammomag4 && ItemID == 242) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (stocksniper1 && ItemID == 254) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
								lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
								125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
								64,
								64
							};
							std::array<float, 3> highlightParameter = { 1, 1, 1 };
							apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
							static const int contextId = 0;
							int settingIndex = 72;
							apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
							long highlightSettingsPtr;
							apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
							apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
							apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (stocksniper2 && ItemID == 255) 
					{
					std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (stocksniper3 && ItemID == 256) 
					{
					std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (stockregular1 && ItemID == 251) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (stockregular2 && ItemID == 252) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (stockregular3 && ItemID == 253) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shielddown1 && ItemID == 202) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shielddown2 && ItemID == 203) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shielddown3 && ItemID == 204) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shielddown4 && ItemID == 205) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (lightammomag1 && ItemID == 231) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (lightammomag2 && ItemID == 232) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (lightammomag3 && ItemID == 233) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (lightammomag4 && ItemID == 234) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (heavyammomag1 && ItemID == 235) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (heavyammomag2 && ItemID == 236) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (heavyammomag3 && ItemID == 237) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (heavyammomag4 && ItemID == 238) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (optic2xhcog && ItemID == 215) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (opticholo1x && ItemID == 216) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (opticholo1x2x && ItemID == 217) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (opticthreat && ItemID == 218) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (optic3xhcog && ItemID == 219) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (optic2x4x && ItemID == 220) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (opticsniper6x && ItemID == 221) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (opticsniper4x8x && ItemID == 222) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (opticsniperthreat && ItemID == 223) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (suppressor1 && ItemID == 224) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (suppressor2 && ItemID == 225) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (suppressor3 && ItemID == 226) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (turbo_charger && ItemID == 257) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (skull_piecer && ItemID == 259) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (hammer_point && ItemID == 261) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (disruptor_rounds && ItemID == 260) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (boosted_loader && ItemID == 271) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shotgunbolt1 && ItemID == 247) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shotgunbolt2 && ItemID == 248) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shotgunbolt3 && ItemID == 249) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2941, 0, 0.5098 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (shotgunbolt4 && ItemID == 250) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.8431, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					//Nades
					if (grenade_frag && ItemID == 212) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	
					}
					
					if (grenade_thermite && ItemID == 211) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 67;
												apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	
					}
					if (grenade_arc_star && ItemID == 213) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 70;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	
					}
					//Weapons
					if (weapon_kraber && ItemID == 1) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_mastiff && ItemID == 2) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							14,   // InsideFunction
							125, // OutlineFunction: HIGHLIGHT_OUTLINE_OBJECTIVE
							64,  // OutlineRadius: size * 255 / 8
							64   // (EntityVisible << 6) | State & 0x3F | (AfterPostProcess << 7)
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						int settingIndex = 67;
						static const int contextId = 2;
						apex_mem.Write<int>(centity + OFFSET_GLOW_ENABLE, contextId);
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						//apex_mem.Write<int>(ptr + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<int>(centity + OFFSET_GLOW_THROUGH_WALLS , 2);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 0x28 * settingIndex + 4, highlightFunctionBits);
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 0x28 * settingIndex + 8, highlightParameter);
					}
					if (weapon_lstar && ItemID == 8) 
					{
					std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2, 1, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					//new gun, nemesis
					if (weapon_nemesis && ItemID == 134) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2, 1, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					
					if (weapon_havoc && ItemID == 13) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2, 1, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_devotion && ItemID == 18) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2, 1, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_triple_take && ItemID == 23) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2, 1, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_flatline  && ItemID == 28) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_hemlock && ItemID == 33) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_g7_scout && ItemID == 39) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.5490, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_alternator && ItemID == 44) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.5490, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_r99 && ItemID == 49) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.5490, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_prowler && ItemID == 55) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_volt && ItemID == 60) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0.2, 1, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_longbow && ItemID == 65) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_charge_rifle && ItemID == 70) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						uint64_t ItemID;
						apex_mem.Read<uint64_t>(centity + OFFSET_ITEM_ID, ItemID);
						//printf("%ld\n", ItemID);
					}
					if (weapon_spitfire && ItemID == 75) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.5490, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_r301 && ItemID == 80) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.5490, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_eva8 && ItemID == 85) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_peacekeeper && ItemID == 90) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_mozambique && ItemID == 95) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_wingman && ItemID == 105) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_p2020 && ItemID == 110) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.5490, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_re45 && ItemID == 115) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0.5490, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_sentinel && ItemID == 121) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_bow && ItemID == 126) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_3030_repeater && ItemID == 128) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_rampage && ItemID == 145) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					if (weapon_car_smg && ItemID == 150) 
					{
						std::array<unsigned char, 4> highlightFunctionBits = {
							lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
							125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
							64,
							64
						};
						std::array<float, 3> highlightParameter = { 0, 1, 1 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 2);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
					}
					
					

					// CREDITS to Rikkie https://www.unknowncheats.me/forum/members/169606.html
					// for all the weapon ids and item ids code, you are a life saver!
					ulong ehWeaponHandle;
					apex_mem.Read<uint64_t>(LocalPlayer + OFFSET_WEAPON, ehWeaponHandle); // 0x1a1c
					ehWeaponHandle &= 0xFFFF; // eHandle
					ulong pWeapon;
					apex_mem.Read<uint64_t>(entitylist + (ehWeaponHandle * 0x20), pWeapon);
					
					
					enum HeldWeaponID
					{
						r301 = 0,
						sentinel = 1,
						bow = 2,
						rampage = 19,
						alternator = 75,
						re45,
						chargerifle,
						devotion,
						longbow,
						havoc,
						eva8,
						flatline,
						scout,
						hemlock,
						kraber,
						lstar,
						mastiff,
						mozambique,
						prowler,
						peacekeeper,
						r99,
						p2020,
						spitfire,
						tripletake,
						wingman,
						volt,
						repeater,
						car,
						nemesis,
						melee_survival = 100,
						shield,
						heirloom_wraith = 130, 
						heirloom_valkyrie = 136, 
						throwing_knife = 139
					};
					
					//Nade test
					int HeldID;
					apex_mem.Read<int>(LocalPlayer + OFFSET_OFF_WEAPON, HeldID); // 0x1a1c
					
					if(NoNadeAim)
					{
						if (HeldID == -251)
						{
							aim = 0;
						}
						else
						{
							aim = 2;
						}
					}
					uint32_t weaponID;
					apex_mem.Read<uint32_t>(pWeapon + OFFSET_WEAPON_NAME, weaponID); //0x1844
					//printf("%d\n", HeldID);
					//snipers for headsbots
					/* if (weaponID == 101 || weaponID == 87 || weaponID == 2 || weaponID == 84 || weaponID == 1 || weaponID == 78 || weaponID == 80 || weaponID == 102 || weaponID == 104 || weaponID == 105)
					{
					
						bone = 0;
					}
					else if (weaponID != 101 || weaponID != 87 || weaponID != 2 || weaponID != 84 || weaponID != 1 || weaponID != 78 || weaponID != 80 || weaponID != 102 || weaponID != 104 || !weaponID == 105)
					{
						bone = 2;
					} */
					//bow
					if (weaponID == 2)
					{
						//Ctx.BulletSpeed = BulletSpeed - (BulletSpeed*0.08);
						//Ctx.BulletGravity = BulletGrav + (BulletGrav*0.05);
						bulletspeed = 10.08;
						bulletgrav = 10.05;
					}
					else if (weaponID != 2)
					{
						bulletspeed = 0.08;
						bulletgrav = 0.05;
					}
					
				}
				k=1;
				//Change the 60 ms to lower to make the death boxes filker less.
				//std::this_thread::sleep_for(std::chrono::milliseconds(60));
			}
			else
			{		
				if(k==1)
				{
					//same and the ents above to turn the glow off
					for (int i = 0; i < 15000; i++)
					{
						uint64_t centity = 0;
						apex_mem.Read<uint64_t>(entitylist + ((uint64_t)i << 5), centity);
						if (centity == 0) continue;
						Item item = getItem(centity);
						//testing
						uint64_t LocalPlayer = 0;
						apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
							
						
						//Item filter glow name setup and search.
						char glowName[200] = { 0 };
						uint64_t name_ptr;
						apex_mem.Read<uint64_t>(centity + OFFSET_MODELNAME, name_ptr);
						apex_mem.ReadArray<char>(name_ptr, glowName, 200);
						
						//item ids?
						uint64_t ItemID;
						apex_mem.Read<uint64_t>(centity + OFFSET_ITEM_ID, ItemID);
 
						if (lightbackpack && ItemID == 206) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						14,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						125,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 1, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);

						}
						else
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 99;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	
						}
						if (medbackpack && ItemID == 207) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	

						}
						if (heavybackpack && ItemID == 208) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	

						}
						if (goldbackpack && ItemID == 209) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	

						}
						//item id would help so much here, cant make them all the same color so went with loba glow for body shield and helmet
						if (shieldupgrade1 && (ItemID == 214748364992 || ItemID == 14073963583897797))
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter); 

						uint64_t ItemID;
						apex_mem.Read<uint64_t>(centity + OFFSET_ITEM_ID, ItemID);
						//uint64_t ItemID2;
						//ItemID2 = ItemID % 301;
						//printf("%ld\n", ItemID);
						//apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);;
						}
						if (shieldupgrade2 && (ItemID == 322122547393 || ItemID == 21110945375846598))
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shieldupgrade3 && (ItemID == 429496729794 || ItemID == 52776987629977799)) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shieldupgrade4 && (ItemID == 429496729795))  
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shieldupgrade5 && ItemID == 536870912200)  
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shieldupgradehead1 && ItemID == 187) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shieldupgradehead2 && ItemID == 188) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shieldupgradehead3 && ItemID == 189) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shieldupgradehead4 && ItemID == 190) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (accelerant && ItemID == 181) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (phoenix && ItemID == 182) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (skull && strstr(glowName, "mdl/Weapons/skull_grenade/skull_grenade_base_v.rmdl")) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (item.isBox())
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 88;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);

						}

						if (item.isTrap())
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	

						}

						//Gas Trap
						if (strstr(glowName, "mdl/props/caustic_gas_tank/caustic_gas_tank.rmdl")) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (healthlarge && ItemID == 183) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (healthsmall && ItemID == 184) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shieldbattsmall && ItemID == 186) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shieldbattlarge && ItemID == 185) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (sniperammo && ItemID == 143) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (heavyammo && ItemID == 142) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (optic1xhcog && ItemID == 214) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (lightammo && ItemID == 139) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (energyammo && ItemID == 140) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shotgunammo && ItemID == 141) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (lasersight1 && ItemID == 228) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (lasersight2 && ItemID == 229) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (lasersight3 && ItemID == 230) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (sniperammomag1 && ItemID == 243) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (sniperammomag2 && ItemID == 244) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (sniperammomag3 && ItemID == 245) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (sniperammomag4 && ItemID == 246) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (energyammomag1 && ItemID == 239) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (energyammomag2 && ItemID == 240) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (energyammomag3 && ItemID == 241) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (energyammomag4 && ItemID == 242) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (stocksniper1 && ItemID == 254) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (stocksniper2 && ItemID == 255) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (stocksniper3 && ItemID == 256) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (stockregular1 && ItemID == 251) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (stockregular2 && ItemID == 252) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (stockregular3 && ItemID == 253) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shielddown1 && ItemID == 202) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shielddown2 && ItemID == 203) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shielddown3 && ItemID == 204) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shielddown4 && ItemID == 205) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (lightammomag1 && ItemID == 231) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (lightammomag2 && ItemID == 232) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (lightammomag3 && ItemID == 233) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (lightammomag4 && ItemID == 234) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (heavyammomag1 && ItemID == 235) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (heavyammomag2 && ItemID == 236) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (heavyammomag3 && ItemID == 237) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (heavyammomag4 && ItemID == 238) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (optic2xhcog && ItemID == 215) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (opticholo1x && ItemID == 216) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (opticholo1x2x && ItemID == 217) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (opticthreat && ItemID == 218) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (optic3xhcog && ItemID == 219) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (optic2x4x && ItemID == 220) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (opticsniper6x && ItemID == 221) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (opticsniper4x8x && ItemID == 222) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (opticsniperthreat && ItemID == 223) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (suppressor1 && ItemID == 224) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (suppressor2 && ItemID == 225) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (suppressor3 && ItemID == 226) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (turbo_charger && ItemID == 257) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (skull_piecer && ItemID == 259) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (hammer_point && ItemID == 261) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (disruptor_rounds && ItemID == 260) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (boosted_loader && ItemID == 271) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shotgunbolt1 && ItemID == 247) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 72;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shotgunbolt2 && ItemID == 248) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shotgunbolt3 && ItemID == 249) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 74;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (shotgunbolt4 && ItemID == 250) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 75;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						//Nades
						if (grenade_frag && ItemID == 212) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	
						}

						if (grenade_thermite && ItemID == 211) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	
						}
						if (grenade_arc_star && ItemID == 213) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 70;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);	
						}
						//Weapons
						if (weapon_kraber && ItemID == 1) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_mastiff && ItemID == 2) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction
						0, // OutlineFunction: HIGHLIGHT_OUTLINE_OBJECTIVE
						64,  // OutlineRadius: size * 255 / 8
						64   // (EntityVisible << 6) | State & 0x3F | (AfterPostProcess << 7)
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						int settingIndex = 67;
						static const int contextId = 2;
						apex_mem.Write<int>(centity + OFFSET_GLOW_ENABLE, contextId);
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						//apex_mem.Write<int>(ptr + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<int>(centity + OFFSET_GLOW_THROUGH_WALLS , 2);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 0x28 * settingIndex + 4, highlightFunctionBits);
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 0x28 * settingIndex + 8, highlightParameter);
						}
						if (weapon_lstar && ItemID == 8) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						//new gun, nemesis
						if (weapon_nemesis && ItemID == 134) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}

						if (weapon_havoc && ItemID == 13) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_devotion && ItemID == 18) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_triple_take && ItemID == 23) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_flatline  && ItemID == 28) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_hemlock && ItemID == 33) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_g7_scout && ItemID == 39) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_alternator && ItemID == 44) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_r99 && ItemID == 49) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_prowler && ItemID == 55) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_volt && ItemID == 60) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 73;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_longbow && ItemID == 65) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_charge_rifle && ItemID == 70) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						uint64_t ItemID;
						apex_mem.Read<uint64_t>(centity + OFFSET_ITEM_ID, ItemID);
						//printf("%ld\n", ItemID);
						}
						if (weapon_spitfire && ItemID == 75) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_r301 && ItemID == 80) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_eva8 && ItemID == 85) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_peacekeeper && ItemID == 90) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_mozambique && ItemID == 95) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_wingman && ItemID == 105) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_p2020 && ItemID == 110) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_re45 && ItemID == 115) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 66;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_sentinel && ItemID == 121) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 69;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_bow && ItemID == 126) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 67;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_3030_repeater && ItemID == 128) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_rampage && ItemID == 145) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
						if (weapon_car_smg && ItemID == 150) 
						{
						std::array<unsigned char, 4> highlightFunctionBits = {
						0,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
						0,   // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED 
						64,
						64
						};
						std::array<float, 3> highlightParameter = { 0, 0, 0 };
						apex_mem.Write<uint32_t>(centity + OFFSET_GLOW_THROUGH_WALLS, 0);
						static const int contextId = 0;
						int settingIndex = 65;
						apex_mem.Write<unsigned char>(centity + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);
						long highlightSettingsPtr;
						apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
						apex_mem.Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + 40 * settingIndex + 4, highlightFunctionBits); 
						apex_mem.Write<typeof(highlightParameter)>(highlightSettingsPtr + 40 * settingIndex + 8, highlightParameter);
						}
					
					}
					k=0;
				}
			}	
		}
	}
	item_t = false;
}

//SSH terminal
// Function to save settings to a file
void ItemFilterMenu()
{
    std::cout << "1 - Light weapons" << std::endl;
    std::cout << "2 - Heavy Weapons" << std::endl;
    std::cout << "3 - Energy Weapons" << std::endl;
    std::cout << "4 - Sniper Weapons" << std::endl;
	std::cout << "5 - Armors" << std::endl;
	std::cout << "6 - Healing" << std::endl;
	std::cout << "7 - Nades" << std::endl;
	std::cout << "8 - Backpacks" << std::endl;
	std::cout << "9 - Scopes" << std::endl;
	std::cout << "10 - Back to Main Menu" << std::endl;
}
void saveSettings()
{
    std::ofstream settingsFile("settings.txt");

    if (settingsFile.is_open())
    {
        // Write the settings to the file.
		settingsFile << std::boolalpha << firing_range << "\n";
        settingsFile << std::boolalpha << TDMToggle << "\n";
        settingsFile << std::boolalpha << keyboard << "\n";
        settingsFile << std::boolalpha << gamepad << "\n";
        settingsFile << std::boolalpha << item_glow << "\n";
        settingsFile << std::boolalpha << player_glow << "\n";
        settingsFile << smooth << "\n";
        settingsFile << bone << "\n";
        settingsFile << glowrnot << "\n";
        settingsFile << glowgnot << "\n";
        settingsFile << glowbnot << "\n";
        settingsFile << glowrviz << "\n";
        settingsFile << glowgviz << "\n";
        settingsFile << glowbviz << "\n";
        settingsFile << glowrknocked << "\n";
        settingsFile << glowgknocked << "\n";
        settingsFile << glowbknocked << "\n";
		settingsFile << ADSfov << "\n";
		settingsFile << nonADSfov << "\n";
		settingsFile << lightbackpack << "\n";
		settingsFile << medbackpack << "\n";
		settingsFile << heavybackpack << "\n";
		settingsFile << goldbackpack << "\n";
		//Shield upgrades
		settingsFile << shieldupgrade1 << "\n";  //white
		settingsFile << shieldupgrade2 << "\n";  //blue
		settingsFile << shieldupgrade3 << "\n";  //purple
		settingsFile << shieldupgrade4 << "\n";  //gold
		settingsFile << shieldupgrade5 << "\n";  //red
		settingsFile << shieldupgradehead1 << "\n";
		settingsFile << shieldupgradehead2 << "\n";
		settingsFile << shieldupgradehead3 << "\n";
		settingsFile << shieldupgradehead4 << "\n";
		settingsFile << shielddown1 << "\n";
		settingsFile << shielddown2 << "\n";
		settingsFile << shielddown3 << "\n";
		settingsFile << shielddown4 << "\n";
		//heaing and Misc
		settingsFile << accelerant << "\n";
		settingsFile << phoenix << "\n";
		settingsFile << healthlarge << "\n";
		settingsFile << healthsmall << "\n";
		settingsFile << shieldbattsmall << "\n";
		settingsFile << shieldbattlarge << "\n";
		//Ammo
		settingsFile << sniperammo << "\n";
		settingsFile << heavyammo << "\n";
		settingsFile << lightammo << "\n";
		settingsFile << energyammo << "\n";
		settingsFile << shotgunammo << "\n";
		//Optics
		settingsFile << optic1xhcog << "\n";
		settingsFile << optic2xhcog << "\n";
		settingsFile << opticholo1x << "\n";
		settingsFile << opticholo1x2x << "\n";
		settingsFile << opticthreat << "\n";
		settingsFile << optic3xhcog << "\n";
		settingsFile << optic2x4x << "\n";
		settingsFile << opticsniper6x << "\n";
		settingsFile << opticsniper4x8x << "\n";
		settingsFile << opticsniperthreat << "\n";
		//Magazines
		settingsFile << sniperammomag1 << "\n";
		settingsFile << energyammomag1 << "\n";
		settingsFile << lightammomag1 << "\n";
		settingsFile << heavyammomag1 << "\n";
		settingsFile << sniperammomag2 << "\n";
		settingsFile << energyammomag2 << "\n";
		settingsFile << lightammomag2 << "\n";
		settingsFile << heavyammomag2 << "\n";
		settingsFile << sniperammomag3 << "\n";
		settingsFile << energyammomag3 << "\n";
		settingsFile << lightammomag3 << "\n";
		settingsFile << heavyammomag3 << "\n";
		settingsFile << sniperammomag4 << "\n";
		settingsFile << energyammomag4 << "\n";
		settingsFile << lightammomag4 << "\n";
		settingsFile << heavyammomag4 << "\n";
		//Attachments 
		settingsFile << lasersight1 << "\n";
		settingsFile << lasersight2 << "\n";
		settingsFile << lasersight3 << "\n";
		settingsFile << lasersight4 << "\n";
		settingsFile << stocksniper1 << "\n";
		settingsFile << stocksniper2 << "\n";
		settingsFile << stocksniper3 << "\n";
		settingsFile << stocksniper4 << "\n";
		settingsFile << stockregular1 << "\n";
		settingsFile << stockregular2 << "\n";
		settingsFile << stockregular3 << "\n";
		settingsFile << suppressor1 << "\n";
		settingsFile << suppressor2 << "\n";
		settingsFile << suppressor3 << "\n";
		settingsFile << turbo_charger << "\n";
		settingsFile << skull_piecer << "\n";
		settingsFile << hammer_point << "\n";
		settingsFile << disruptor_rounds << "\n";
		settingsFile << boosted_loader << "\n";
		settingsFile << shotgunbolt1 << "\n";
		settingsFile << shotgunbolt2 << "\n";
		settingsFile << shotgunbolt3 << "\n";
		settingsFile << shotgunbolt4 << "\n";
		//Nades
		settingsFile << grenade_frag << "\n";
		settingsFile << grenade_arc_star << "\n";
		settingsFile << grenade_thermite << "\n";
		//Kraber
		settingsFile << weapon_kraber << "\n";
		//Shotguns
		settingsFile << weapon_mastiff << "\n";
		settingsFile << weapon_eva8  << "\n";
		settingsFile << weapon_peacekeeper  << "\n";
		settingsFile << weapon_mozambique  << "\n";
		//Energy weapons
		settingsFile << weapon_lstar << "\n";
		settingsFile << weapon_nemesis << "\n";
		settingsFile << weapon_havoc << "\n";
		settingsFile << weapon_devotion << "\n";
		settingsFile << weapon_triple_take << "\n";
		settingsFile << weapon_prowler  << "\n";
		settingsFile << weapon_volt  << "\n";
		//Heavy Weapons
		settingsFile << weapon_flatline << "\n";
		settingsFile << weapon_hemlock  << "\n";
		settingsFile << weapon_3030_repeater << "\n"; 
		settingsFile << weapon_rampage  << "\n";
		settingsFile << weapon_car_smg  << "\n";
		//Light weapons
		settingsFile << weapon_p2020  << "\n";
		settingsFile << weapon_re45  << "\n";
		settingsFile << weapon_g7_scout  << "\n";
		settingsFile << weapon_alternator  << "\n";
		settingsFile << weapon_r99  << "\n";
		settingsFile << weapon_spitfire  << "\n";
		settingsFile << weapon_r301 << "\n";
		//Snipers.. wingman is the odd one...and the bow..
		settingsFile << weapon_wingman  << "\n";
		settingsFile << weapon_longbow  << "\n";
		settingsFile << weapon_charge_rifle  << "\n";
		settingsFile << weapon_sentinel  << "\n";
		settingsFile << SuperKeyToggle  << "\n";
		settingsFile << SuperKey << "\n";
		
		
		
		
		
        settingsFile.close();
		std::cout << "Settings saved to 'settings.txt'.\n";
		std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    }
    else
    {
        std::cout << "Error opening settings file for writing." << std::endl;
    }
}
void loadSettings()
{
    std::ifstream settingsFile("settings.txt");

    if (settingsFile.is_open())
    {
		settingsFile >> std::boolalpha >> firing_range;
        settingsFile >> std::boolalpha >> TDMToggle;
        settingsFile >> std::boolalpha >> keyboard;
        settingsFile >> std::boolalpha >> gamepad;
        settingsFile >> std::boolalpha >> item_glow;
        settingsFile >> std::boolalpha >> player_glow;
        settingsFile >> smooth;
        settingsFile >> bone;
        settingsFile >> glowrnot;
        settingsFile >> glowgnot;
        settingsFile >> glowbnot;
        settingsFile >> glowrviz;
        settingsFile >> glowgviz;
        settingsFile >> glowbviz;
        settingsFile >> glowrknocked;
        settingsFile >> glowgknocked;
        settingsFile >> glowbknocked;
		settingsFile >> ADSfov;
		settingsFile >> nonADSfov;
		settingsFile >> lightbackpack;
		settingsFile >> medbackpack;
		settingsFile >> heavybackpack;
		settingsFile >> goldbackpack;
		settingsFile >> shieldupgrade1;  //white
		settingsFile >> shieldupgrade2;  //blue
		settingsFile >> shieldupgrade3;  //purple
		settingsFile >> shieldupgrade4;  //gold
		settingsFile >> shieldupgrade5;  //red
		settingsFile >> shieldupgradehead1;
		settingsFile >> shieldupgradehead2;
		settingsFile >> shieldupgradehead3;
		settingsFile >> shieldupgradehead4;
		settingsFile >> shielddown1;
		settingsFile >> shielddown2;
		settingsFile >> shielddown3;
		settingsFile >> shielddown4;
		settingsFile >> accelerant;
		settingsFile >> phoenix;
		settingsFile >> healthlarge;
		settingsFile >> healthsmall;
		settingsFile >> shieldbattsmall;
		settingsFile >> shieldbattlarge;
		settingsFile >> sniperammo;
		settingsFile >> heavyammo;
		settingsFile >> lightammo;
		settingsFile >> energyammo;
		settingsFile >> shotgunammo;
		settingsFile >> optic1xhcog;
		settingsFile >> optic2xhcog;
		settingsFile >> opticholo1x;
		settingsFile >> opticholo1x2x;
		settingsFile >> opticthreat;
		settingsFile >> optic3xhcog;
		settingsFile >> optic2x4x;
		settingsFile >> opticsniper6x;
		settingsFile >> opticsniper4x8x;
		settingsFile >> opticsniperthreat;
		settingsFile >> sniperammomag1;
		settingsFile >> energyammomag1;
		settingsFile >> lightammomag1;
		settingsFile >> heavyammomag1;
		settingsFile >> sniperammomag2;
		settingsFile >> energyammomag2;
		settingsFile >> lightammomag2;
		settingsFile >> heavyammomag2;
		settingsFile >> sniperammomag3;
		settingsFile >> energyammomag3;
		settingsFile >> lightammomag3;
		settingsFile >> heavyammomag3;
		settingsFile >> sniperammomag4;
		settingsFile >> energyammomag4;
		settingsFile >> lightammomag4;
		settingsFile >> heavyammomag4;
		settingsFile >> lasersight1;
		settingsFile >> lasersight2;
		settingsFile >> lasersight3;
		settingsFile >> lasersight4;
		settingsFile >> stocksniper1;
		settingsFile >> stocksniper2;
		settingsFile >> stocksniper3;
		settingsFile >> stocksniper4;
		settingsFile >> stockregular1;
		settingsFile >> stockregular2;
		settingsFile >> stockregular3;
		settingsFile >> suppressor1;
		settingsFile >> suppressor2;
		settingsFile >> suppressor3;
		settingsFile >> turbo_charger;
		settingsFile >> skull_piecer;
		settingsFile >> hammer_point;
		settingsFile >> disruptor_rounds;
		settingsFile >> boosted_loader;
		settingsFile >> shotgunbolt1;
		settingsFile >> shotgunbolt2;
		settingsFile >> shotgunbolt3;
		settingsFile >> shotgunbolt4;
		settingsFile >> grenade_frag;
		settingsFile >> grenade_arc_star;
		settingsFile >> grenade_thermite;
		settingsFile >> weapon_kraber;
		settingsFile >> weapon_mastiff;
		settingsFile >> weapon_eva8 ;
		settingsFile >> weapon_peacekeeper ;
		settingsFile >> weapon_mozambique ;
		settingsFile >> weapon_lstar;
		settingsFile >> weapon_nemesis;
		settingsFile >> weapon_havoc;
		settingsFile >> weapon_devotion;
		settingsFile >> weapon_triple_take;
		settingsFile >> weapon_prowler ;
		settingsFile >> weapon_volt ;
		settingsFile >> weapon_flatline;
		settingsFile >> weapon_hemlock ;
		settingsFile >> weapon_3030_repeater; 
		settingsFile >> weapon_rampage ;
		settingsFile >> weapon_car_smg ;
		settingsFile >> weapon_p2020 ;
		settingsFile >> weapon_re45 ;
		settingsFile >> weapon_g7_scout ;
		settingsFile >> weapon_alternator ;
		settingsFile >> weapon_r99 ;
		settingsFile >> weapon_spitfire;
		settingsFile >> weapon_r301;
		settingsFile >> weapon_wingman ;
		settingsFile >> weapon_longbow ;
		settingsFile >> weapon_charge_rifle ;
		settingsFile >> weapon_sentinel ;
		settingsFile >> SuperKeyToggle;
		settingsFile >> SuperKey;
		
		


        settingsFile.close();
        std::cout << "Settings loaded from 'settings.txt'.\n";
    }
    else
    {
        std::cout << "Error opening settings file for reading. Using default settings.\n";
    }
}
const char* boneDescriptions[] = {
    "Head",
    "Neck",
    "Chest",
    "Gut Shot"
};
void updateGlowColor(float &glowr, float &glowg, float &glowb, const std::string &setName)
{
    std::cout << "Enter RGB values for " << setName << " (0-1 for each channel):\n";
    std::cout << "Red: ";
    std::cin >> glowr;

    std::cout << "Green: ";
    std::cin >> glowg;

    std::cout << "Blue: ";
    std::cin >> glowb;

    // Validate and clamp values to the range [0, 1].
    glowr = std::max(0.0f, std::min(1.0f, glowr));
    glowg = std::max(0.0f, std::min(1.0f, glowg));
    glowb = std::max(0.0f, std::min(1.0f, glowb));

    std::cout << setName << " RGB values updated (R: " << glowr << ", G: " << glowg << ", B: " << glowb << ").\n";
}
void displayMainMenu()
{
    
    system("clear"); // Use "cls" for Windows
	std::string userInput;
	std::cout << "Main Menu:" << std::endl;
		
	if (firing_range)
	{
		std::cout << "1 - Firing Range Enabled" << std::endl;
	}
	else
	{
		std::cout << "1 - Firing Range Disabled" << std::endl;
	}
	if (TDMToggle)
	{
		std::cout << "2 - TDMToggle Enabled" << std::endl;
	}
	else
	{
		std::cout << "2 - TDMToggle Disabled" << std::endl;
	}
	if (keyboard)
	{
		std::cout << "3 - Keyboard Enabled" << std::endl;
	}
	else
	{
		std::cout << "3 - Keyboard Disabled" << std::endl;
	}
	if (gamepad)
	{
		std::cout << "4 - Gamepad Enabled" << std::endl;
	}
	else
	{
		std::cout << "4 - Gamepad Disabled" << std::endl;
	}
	if (item_glow)
	{
		std::cout << "5 - Item Glow Enabled" << std::endl;
	}
	else
	{
		std::cout << "5 - Item Glow Disabled" << std::endl;
	}
	if (player_glow)
	{
		std::cout << "6 - Player Glow Enabled" << std::endl;
	}
	else
	{
		std::cout << "6 - Player Glow Disabled" << std::endl;
	}
	
	std::cout << "7 - Change Smooth Value: (Current: ";
	if (smooth < 100.0f)
	{
		std::cout << "\033[1;31m"; // Set text color to red for values below 100
	}
	else if (smooth > 120.0f)
	{
		std::cout << "\033[1;32m"; // Set text color to green for values above 120
	}
	std::cout << smooth << "\033[0m"; // Reset text color to default and close color tag
	std::cout << ")" << std::endl;
	
	std::cout << "8 - Change Bone Aim Value: (Current: ";
	if (bone == 0)
	{
		std::cout << "Head";
	}
	else if (bone == 1)
	{
		std::cout << "Neck";
	}
	else if (bone == 2)
	{
		std::cout << "Chest";
	}
	else if (bone == 3)
	{
		std::cout << "Gut Shot";
	}
	else
	{
		std::cout << "Unknown";
	}
	std::cout << ")" << std::endl;
	
	if (lootfilledtoggle)
	{
		lootfilled = 14;
		std::cout << "9 - Loot Glow Filled" << std::endl;
	}
	else
	{
		lootfilled = 0;
		std::cout << "9 - Loot Glow Not Filled" << std::endl;
	}
	if (playerfilledtoggle)
	{
		insidevalue = 14;
		std::cout << "10 - Player Glow Filled" << std::endl;
	}
	else
	{
		insidevalue = 0;
		std::cout << "10 - Player Glow Not Filled" << std::endl;
	}
	std::cout << "11 - Player Outline Glow" << std::endl;
	std::cout << "12 - Update Glow Colors" << std::endl;
	std::cout << "13 - Change ADS FOV: (Current: ";
	std::cout << ADSfov;
	std::cout << ")" << std::endl;
	std::cout << "14 - Change Non-ADS FOV: (Current: ";
	std::cout << nonADSfov;
	std::cout << ")" << std::endl;
	
	if (SuperKeyToggle)
	{
		std::cout << "15 - Super Glide Disabled" << std::endl;
	}
	else
	{
		std::cout << "15 - Super Glide Enabled" << std::endl;
	}
	std::cout << "16 - Item Filter Settings\n" << std::endl;
	
	std::cout << "17 - Save Settings" << std::endl;
	std::cout << "18 - Load Settings\n" << std::endl;
    
}

void displayItemFilterMenu()
{
    std::cout << "Item Filter Menu:" << std::endl;
    std::cout << "1 - Light weapons" << std::endl;
    std::cout << "2 - Heavy Weapons" << std::endl;
    std::cout << "3 - Energy Weapons" << std::endl;
    std::cout << "4 - Sniper Weapons" << std::endl;
	std::cout << "5 - Armors" << std::endl;
	std::cout << "6 - Healing" << std::endl;
	std::cout << "7 - Nades" << std::endl;
	std::cout << "8 - Backpacks" << std::endl;
	std::cout << "9 - Scopes" << std::endl;
	std::cout << "10 - Back to Main Menu" << std::endl;
}

void displayLightWeapons()
{
	// Color definitions using ANSI escape codes
    std::string whiteColor = "\033[1;37m"; // White text
    std::string blueColor = "\033[1;34m";  // Blue text
    std::string purpleColor = "\033[1;35m"; // Purple text
    std::string goldColor = "\033[1;33m";  // Gold text
	std::string yellowColor = "\033[1;33m"; // Yellow text
	std::string redColor = "\033[1;31m"; // Red text
	 std::string greenColor = "\033[1;32m"; // Green text
	 std::string tealColor = "\033[1;36m";   // Teal text
    std::string yellowGoldColor = "\033[1;33m"; // Yellow-gold text
    std::string resetColor = "\033[0m";    // Reset text color to default
	
	std::cout << redColor << "Red = Disable" << resetColor << " - " << greenColor << "Green = Enabled" << resetColor << resetColor << std::endl;
	std::cout << yellowColor << "Light Weapons:\n" << resetColor << std::endl;
	if(weapon_p2020)
	{
		std::cout << "1 - " << greenColor <<"P2022" << resetColor << std::endl;
	}
	else if(!weapon_p2020)
	{
		std::cout << "1 - " << redColor <<"P2022" << resetColor << std::endl;
	}
    
	if(weapon_re45)
	{
		std::cout << "2 - " << greenColor <<"RE-45" << resetColor << std::endl;
	}
	else if(!weapon_re45)
	{
		std::cout << "2 - " << redColor <<"RE-45" << resetColor << std::endl;
	}
    
	if(weapon_alternator)
	{
		std::cout << "3 - " << greenColor <<"Alternator" << resetColor << std::endl;
	}
	else if(!weapon_alternator)
	{
		std::cout << "3 - " << redColor <<"Alternator" << resetColor << std::endl;
	}
    
	if(weapon_r99)
	{
		std::cout << "4 - " << greenColor <<"R-99" << resetColor << std::endl;
	}
	else if(!weapon_r99)
	{
		std::cout << "4 - " << redColor <<"R-99" << resetColor << std::endl;
	}
    
	if(weapon_r301)
	{
		std::cout << "5 - " << greenColor <<"R-301" << resetColor << std::endl;
	}
	else if(!weapon_r301)
	{
		std::cout << "5 - " << redColor <<"R-301" << resetColor << std::endl;
	}

	if(weapon_spitfire)
	{
		std::cout << "6 - " << greenColor <<"M600" << resetColor << std::endl;
	}
	else if(!weapon_spitfire)
	{
		std::cout << "6 - " << redColor <<"M600" << resetColor << std::endl;
	}
    
	if(weapon_g7_scout)
	{
		std::cout << "7 - " << greenColor <<"G7 Scout" << resetColor << std::endl;
	}
	else if(!weapon_g7_scout)
	{
		std::cout << "7 - " << redColor <<"G7 Scout" << resetColor << std::endl;
	}
    
	if(lightammo)
	{
		std::cout << "8 - " << greenColor <<"Light Ammo\n" << resetColor << std::endl;
	}
	else if(!lightammo)
	{
		std::cout << "8 - " << redColor <<"Light Ammo\n" << resetColor << std::endl;
	}
    std::cout << "Light Weapon Mags:\n" << std::endl;

    // Display colored options
    
	if(lightammomag1)
	{
		std::cout << "9 - " << greenColor << "Light Weapon Mag" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!lightammomag1)
	{
		std::cout << "9 - " << redColor << "Light Weapon Mag" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(lightammomag2)
	{
		std::cout << "10 - " << greenColor << "Light Weapon Mag" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!lightammomag2)
	{
		std::cout << "10 - " << redColor << "Light Weapon Mag" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(lightammomag3)
	{
		std::cout << "11 - " << greenColor << "Light Weapon Mag" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!lightammomag3)
	{
		std::cout << "11 - " << redColor << "Light Weapon Mag" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
    
	if(lightammomag4)
	{
		std::cout << "12 - " << greenColor << "Light Weapon Mag" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!lightammomag4)
	{
		std::cout << "12 - " << redColor << "Light Weapon Mag" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	
	std::cout << "Weapon Stocks:\n" << std::endl;
	
	
	if(stockregular1)
	{
		std::cout << "13 - " << greenColor << "Weapon Stock" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!stockregular1)
	{
		std::cout << "13 - " << redColor << "Weapon Stock" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(stockregular2)
	{
		std::cout << "14 - " << greenColor << "Weapon Stock" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!stockregular2)
	{
		std::cout << "14 - " << redColor << "Weapon Stock" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(stockregular3)
	{
		std::cout << "15 - " << greenColor << "Weapon Stock" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	else if(!stockregular3)
	{
		std::cout << "15 - " << redColor << "Weapon Stock" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	
    std::cout << "Weapon Suppressors:\n" << std::endl;
	
	
	if(suppressor1)
	{
		std::cout << "16 - " << greenColor << "Weapon Suppressors" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!suppressor1)
	{
		std::cout << "16 - " << redColor << "Weapon Suppressors" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(suppressor2)
	{
		std::cout << "17 - " << greenColor << "Weapon Suppressors" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!suppressor2)
	{
		std::cout << "17 - " << redColor << "Weapon Suppressors" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(suppressor3)
	{
		std::cout << "18 - " << greenColor << "Weapon Suppressors" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	else if(!suppressor3)
	{
		std::cout << "18 - " << redColor << "Weapon Suppressors" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	
	std::cout << "Weapon Lasers:\n" << std::endl;
	
	if(lasersight1)
	{
		std::cout << "19 - " << greenColor << "Weapon Lasers" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!lasersight1)
	{
		std::cout << "19 - " << redColor << "Weapon Lasers" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(lasersight2)
	{
		std::cout << "20 - " << greenColor << "Weapon Lasers" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!lasersight2)
	{
		std::cout << "20 - " << redColor << "Weapon Lasers" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(lasersight3)
	{
		std::cout << "21 - " << greenColor << "Weapon Lasers" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!lasersight3)
	{
		std::cout << "21 - " << redColor << "Weapon Lasers" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
    
	if(lasersight4)
	{
		std::cout << "22 - " << greenColor << "Weapon Lasers" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!lasersight4)
	{
		std::cout << "22 - " << redColor << "Weapon Lasers" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	
	std::cout << "Weapon Hop-Ups:\n" << std::endl;
	
	if(turbo_charger)
	{
		std::cout << "23 - " << greenColor << "Turbo Charger" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!turbo_charger)
	{
		std::cout << "23 - " << redColor << "Turbo Charger" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
    
	if(skull_piecer)
	{
		std::cout << "24 - " << greenColor << "Skull Piecer" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!skull_piecer)
	{
		std::cout << "24 - " << redColor << "Skull Piecer" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
    
	if(hammer_point)
	{
		std::cout << "25 - " << greenColor << "Hammer Points" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!hammer_point)
	{
		std::cout << "25 - " << redColor << "Hammer Points" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
    
	if(disruptor_rounds)
	{
		std::cout << "26 - " << greenColor << "Disruptor Rounds" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!disruptor_rounds)
	{
		std::cout << "26 - " << redColor << "Disruptor Rounds" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	
	if(boosted_loader)
	{
		std::cout << "27 - " << greenColor << "Boosted Loader" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!boosted_loader)
	{
		std::cout << "27 - " << redColor << "Boosted Loader" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	
    std::cout << "28 - Back to Settings Menu\n" << std::endl;
}

void displayHeavyWeapons()
{
	// Color definitions using ANSI escape codes
    std::string whiteColor = "\033[1;37m"; // White text
    std::string blueColor = "\033[1;34m";  // Blue text
    std::string purpleColor = "\033[1;35m"; // Purple text
    std::string goldColor = "\033[1;33m";  // Gold text
	std::string yellowColor = "\033[1;33m"; // Yellow text
	std::string redColor = "\033[1;31m"; // Red text
	 std::string greenColor = "\033[1;32m"; // Green text
	 std::string tealColor = "\033[1;36m";   // Teal text
    std::string yellowGoldColor = "\033[1;33m"; // Yellow-gold text
    std::string resetColor = "\033[0m";    // Reset text color to default
	
	std::cout << redColor << "Red = Disable" << resetColor << " - " << greenColor << "Green = Enabled" << resetColor << resetColor << std::endl;
	std::cout << tealColor << "Heavy Weapons:\n" << resetColor << std::endl;
	if(weapon_flatline)
	{
		std::cout << "1 - " << greenColor <<"Flatline" << resetColor << std::endl;
	}
	else if(!weapon_flatline)
	{
		std::cout << "1 - " << redColor <<"Flatline" << resetColor << std::endl;
	}
    
	if(weapon_hemlock)
	{
		std::cout << "2 - " << greenColor <<"Hemlock" << resetColor << std::endl;
	}
	else if(!weapon_hemlock)
	{
		std::cout << "2 - " << redColor <<"Hemlock" << resetColor << std::endl;
	}
    
	if(weapon_3030_repeater)
	{
		std::cout << "3 - " << greenColor <<"30-30 Repeater" << resetColor << std::endl;
	}
	else if(!weapon_3030_repeater)
	{
		std::cout << "3 - " << redColor <<"30-30 Repeater" << resetColor << std::endl;
	}
    
	if(weapon_rampage)
	{
		std::cout << "4 - " << greenColor <<"Rampage" << resetColor << std::endl;
	}
	else if(!weapon_rampage)
	{
		std::cout << "4 - " << redColor <<"Rampage" << resetColor << std::endl;
	}
	
	if(weapon_prowler)
	{
		std::cout << "5 - " << greenColor <<"Prowler" << resetColor << std::endl;
	}
	else if(!weapon_prowler)
	{
		std::cout << "5 - " << redColor <<"Prowler" << resetColor << std::endl;
	}
    
	if(weapon_car_smg)
	{
		std::cout << "6 - " << greenColor <<"Car SMG" << resetColor << std::endl;
	}
	else if(!weapon_car_smg)
	{
		std::cout << "6 - " << redColor <<"Car SMG" << resetColor << std::endl;
	}
    
	if(heavyammo)
	{
		std::cout << "7 - " << greenColor <<"Heavy Ammo\n" << resetColor << std::endl;
	}
	else if(!heavyammo)
	{
		std::cout << "7 - " << redColor <<"Heavy Ammo\n" << resetColor << std::endl;
	}
    std::cout << "Heavy Weapon Mags:\n" << std::endl;

    // Display colored options
    
	if(heavyammomag1)
	{
		std::cout << "8 - " << greenColor << "Heavy Weapon Mag" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!heavyammomag1)
	{
		std::cout << "8 - " << redColor << "Heavy Weapon Mag" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(heavyammomag2)
	{
		std::cout << "9 - " << greenColor << "Heavy Weapon Mag" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!heavyammomag2)
	{
		std::cout << "9 - " << redColor << "Heavy Weapon Mag" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(heavyammomag3)
	{
		std::cout << "10 - " << greenColor << "Heavy Weapon Mag" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!heavyammomag3)
	{
		std::cout << "10 - " << redColor << "Heavy Weapon Mag" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
    
	if(heavyammomag4)
	{
		std::cout << "11 - " << greenColor << "Heavy Weapon Mag" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!heavyammomag4)
	{
		std::cout << "11 - " << redColor << "Heavy Weapon Mag" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	
	std::cout << "Weapon Stocks:\n" << std::endl;
	
	
	if(stockregular1)
	{
		std::cout << "12 - " << greenColor << "Weapon Stock" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!stockregular1)
	{
		std::cout << "12 - " << redColor << "Weapon Stock" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(stockregular2)
	{
		std::cout << "13 - " << greenColor << "Weapon Stock" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!stockregular2)
	{
		std::cout << "13 - " << redColor << "Weapon Stock" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(stockregular3)
	{
		std::cout << "14 - " << greenColor << "Weapon Stock" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	else if(!stockregular3)
	{
		std::cout << "14 - " << redColor << "Weapon Stock" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	
    std::cout << "Weapon Suppressors:\n" << std::endl;
	
	
	if(suppressor1)
	{
		std::cout << "15 - " << greenColor << "Weapon Suppressors" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!suppressor1)
	{
		std::cout << "15 - " << redColor << "Weapon Suppressors" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(suppressor2)
	{
		std::cout << "16 - " << greenColor << "Weapon Suppressors" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!suppressor2)
	{
		std::cout << "16 - " << redColor << "Weapon Suppressors" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(suppressor3)
	{
		std::cout << "17 - " << greenColor << "Weapon Suppressors" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	else if(!suppressor3)
	{
		std::cout << "17 - " << redColor << "Weapon Suppressors" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	
	std::cout << "Weapon Lasers:\n" << std::endl;
	
	if(lasersight1)
	{
		std::cout << "18 - " << greenColor << "Weapon Lasers" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!lasersight1)
	{
		std::cout << "18 - " << redColor << "Weapon Lasers" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(lasersight2)
	{
		std::cout << "19 - " << greenColor << "Weapon Lasers" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!lasersight2)
	{
		std::cout << "19 - " << redColor << "Weapon Lasers" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(lasersight3)
	{
		std::cout << "20 - " << greenColor << "Weapon Lasers" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!lasersight3)
	{
		std::cout << "20 - " << redColor << "Weapon Lasers" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
    
	if(lasersight4)
	{
		std::cout << "21 - " << greenColor << "Weapon Lasers" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!lasersight4)
	{
		std::cout << "21 - " << redColor << "Weapon Lasers" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	
	std::cout << "Weapon Hop-Ups:\n" << std::endl;
	
	if(turbo_charger)
	{
		std::cout << "22 - " << greenColor << "Turbo Charger" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!turbo_charger)
	{
		std::cout << "22 - " << redColor << "Turbo Charger" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
    
	if(skull_piecer)
	{
		std::cout << "23 - " << greenColor << "Skull Piecer" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!skull_piecer)
	{
		std::cout << "23 - " << redColor << "Skull Piecer" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
    
	if(hammer_point)
	{
		std::cout << "24 - " << greenColor << "Hammer Points" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!hammer_point)
	{
		std::cout << "24 - " << redColor << "Hammer Points" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
    
	if(disruptor_rounds)
	{
		std::cout << "25 - " << greenColor << "Disruptor Rounds" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!disruptor_rounds)
	{
		std::cout << "25 - " << redColor << "Disruptor Rounds" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	
	if(boosted_loader)
	{
		std::cout << "26 - " << greenColor << "Boosted Loader" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!boosted_loader)
	{
		std::cout << "26 - " << redColor << "Boosted Loader" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	
    std::cout << "27 - Back to Settings Menu\n" << std::endl;
}

void displayEnergyWeapons()
{
	// Color definitions using ANSI escape codes
    std::string whiteColor = "\033[1;37m"; // White text
    std::string blueColor = "\033[1;34m";  // Blue text
    std::string purpleColor = "\033[1;35m"; // Purple text
    std::string goldColor = "\033[1;33m";  // Gold text
	std::string yellowColor = "\033[1;33m"; // Yellow text
	std::string redColor = "\033[1;31m"; // Red text
	 std::string greenColor = "\033[1;32m"; // Green text
	 std::string tealColor = "\033[1;36m";   // Teal text
    std::string yellowGoldColor = "\033[1;33m"; // Yellow-gold text
    std::string resetColor = "\033[0m";    // Reset text color to default
	
	std::cout << redColor << "Red = Disable" << resetColor << " - " << greenColor << "Green = Enabled" << resetColor << resetColor << std::endl;
	std::cout << yellowGoldColor << "Energy Weapons:\n" << resetColor << std::endl;
	if(weapon_lstar)
	{
		std::cout << "1 - " << greenColor <<"LSTAR" << resetColor << std::endl;
	}
	else if(!weapon_lstar)
	{
		std::cout << "1 - " << redColor <<"LSTAR" << resetColor << std::endl;
	}
    
	if(weapon_nemesis)
	{
		std::cout << "2 - " << greenColor <<"Nemesis" << resetColor << std::endl;
	}
	else if(!weapon_nemesis)
	{
		std::cout << "2 - " << redColor << "Nemesis" << resetColor << std::endl;
	}
    
	if(weapon_havoc)
	{
		std::cout << "3 - " << greenColor << "Havoc" << resetColor << std::endl;
	}
	else if(!weapon_havoc)
	{
		std::cout << "3 - " << redColor << "Havoc" << resetColor << std::endl;
	}
    
	if(weapon_devotion)
	{
		std::cout << "4 - " << greenColor <<"Deovtion" << resetColor << std::endl;
	}
	else if(!weapon_devotion)
	{
		std::cout << "4 - " << redColor <<"Deovtion" << resetColor << std::endl;
	}
    
	if(weapon_triple_take)
	{
		std::cout << "5 - " << greenColor <<"Tripple Take" << resetColor << std::endl;
	}
	else if(!weapon_triple_take)
	{
		std::cout << "5 - " << redColor <<"Tripple Take" << resetColor << std::endl;
	}
	
	if(weapon_volt)
	{
		std::cout << "6 - " << greenColor <<"Volt" << resetColor << std::endl;
	}
	else if(!weapon_volt)
	{
		std::cout << "6 - " << redColor <<"Volt" << resetColor << std::endl;
	}
	
	
    
	if(energyammo)
	{
		std::cout << "7 - " << greenColor <<"Energy Ammo\n" << resetColor << std::endl;
	}
	else if(!energyammo)
	{
		std::cout << "7 - " << redColor <<"Energy Ammo\n" << resetColor << std::endl;
	}
    std::cout << "Energy Weapon Mags:\n" << std::endl;

    // Display colored options
    
	if(energyammomag1)
	{
		std::cout << "8 - " << greenColor << "Energy Weapon Mag" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!energyammomag1)
	{
		std::cout << "8 - " << redColor << "Energy Weapon Mag" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(energyammomag2)
	{
		std::cout << "9 - " << greenColor << "Energy Weapon Mag" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!energyammomag2)
	{
		std::cout << "9 - " << redColor << "Energy Weapon Mag" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(energyammomag3)
	{
		std::cout << "10 - " << greenColor << "Energy Weapon Mag" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!energyammomag3)
	{
		std::cout << "10 - " << redColor << "Energy Weapon Mag" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
    
	if(energyammomag4)
	{
		std::cout << "11 - " << greenColor << "Energy Weapon Mag" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!energyammomag4)
	{
		std::cout << "11 - " << redColor << "Energy Weapon Mag" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	
	std::cout << "Weapon Stocks:\n" << std::endl;
	
	
	if(stockregular1)
	{
		std::cout << "12 - " << greenColor << "Weapon Stock" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!stockregular1)
	{
		std::cout << "12 - " << redColor << "Weapon Stock" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(stockregular2)
	{
		std::cout << "13 - " << greenColor << "Weapon Stock" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!stockregular2)
	{
		std::cout << "13 - " << redColor << "Weapon Stock" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(stockregular3)
	{
		std::cout << "14 - " << greenColor << "Weapon Stock" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	else if(!stockregular3)
	{
		std::cout << "14 - " << redColor << "Weapon Stock" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	
    std::cout << "Weapon Suppressors:\n" << std::endl;
	
	
	if(suppressor1)
	{
		std::cout << "15 - " << greenColor << "Weapon Suppressors" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!suppressor1)
	{
		std::cout << "15 - " << redColor << "Weapon Suppressors" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(suppressor2)
	{
		std::cout << "16 - " << greenColor << "Weapon Suppressors" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!suppressor2)
	{
		std::cout << "16 - " << redColor << "Weapon Suppressors" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(suppressor3)
	{
		std::cout << "17 - " << greenColor << "Weapon Suppressors" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	else if(!suppressor3)
	{
		std::cout << "17 - " << redColor << "Weapon Suppressors" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	
	std::cout << "Weapon Lasers:\n" << std::endl;
	
	if(lasersight1)
	{
		std::cout << "18 - " << greenColor << "Weapon Lasers" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!lasersight1)
	{
		std::cout << "18 - " << redColor << "Weapon Lasers" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(lasersight2)
	{
		std::cout << "19 - " << greenColor << "Weapon Lasers" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!lasersight2)
	{
		std::cout << "19 - " << redColor << "Weapon Lasers" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(lasersight3)
	{
		std::cout << "20 - " << greenColor << "Weapon Lasers" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!lasersight3)
	{
		std::cout << "20 - " << redColor << "Weapon Lasers" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
    
	if(lasersight4)
	{
		std::cout << "21 - " << greenColor << "Weapon Lasers" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!lasersight4)
	{
		std::cout << "21 - " << redColor << "Weapon Lasers" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	
	std::cout << "Weapon Hop-Ups:\n" << std::endl;
	
	if(turbo_charger)
	{
		std::cout << "22 - " << greenColor << "Turbo Charger" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!turbo_charger)
	{
		std::cout << "22 - " << redColor << "Turbo Charger" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
    
	if(skull_piecer)
	{
		std::cout << "23 - " << greenColor << "Skull Piecer" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!skull_piecer)
	{
		std::cout << "23 - " << redColor << "Skull Piecer" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
    
	if(hammer_point)
	{
		std::cout << "24 - " << greenColor << "Hammer Points" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!hammer_point)
	{
		std::cout << "24 - " << redColor << "Hammer Points" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
    
	if(disruptor_rounds)
	{
		std::cout << "25 - " << greenColor << "Disruptor Rounds" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!disruptor_rounds)
	{
		std::cout << "25 - " << redColor << "Disruptor Rounds" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	
	if(boosted_loader)
	{
		std::cout << "26 - " << greenColor << "Boosted Loader" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!boosted_loader)
	{
		std::cout << "26 - " << redColor << "Boosted Loader" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	
    std::cout << "27 - Back to Settings Menu\n" << std::endl;
}

void displaySniperWeapons()
{
	// Color definitions using ANSI escape codes
    std::string whiteColor = "\033[1;37m"; // White text
    std::string blueColor = "\033[1;34m";  // Blue text
    std::string purpleColor = "\033[1;35m"; // Purple text
    std::string goldColor = "\033[1;33m";  // Gold text
	std::string yellowColor = "\033[1;33m"; // Yellow text
	std::string redColor = "\033[1;31m"; // Red text
	 std::string greenColor = "\033[1;32m"; // Green text
	 std::string tealColor = "\033[1;36m";   // Teal text
    std::string yellowGoldColor = "\033[1;33m"; // Yellow-gold text
    std::string resetColor = "\033[0m";    // Reset text color to default
	
	std::cout << redColor << "Red = Disable" << resetColor << " - " << greenColor << "Green = Enabled" << resetColor << resetColor << std::endl;
	std::cout << yellowGoldColor << "Sniper Weapons:\n" << resetColor << std::endl;
	if(weapon_wingman)
	{
		std::cout << "1 - " << greenColor <<"Wingman" << resetColor << std::endl;
	}
	else if(!weapon_wingman)
	{
		std::cout << "1 - " << redColor <<"Wingman" << resetColor << std::endl;
	}
    
	if(weapon_longbow)
	{
		std::cout << "2 - " << greenColor <<"Longbow" << resetColor << std::endl;
	}
	else if(!weapon_longbow)
	{
		std::cout << "2 - " << redColor << "Longbow" << resetColor << std::endl;
	}
    
	if(weapon_charge_rifle)
	{
		std::cout << "3 - " << greenColor << "Charge Rifle" << resetColor << std::endl;
	}
	else if(!weapon_charge_rifle)
	{
		std::cout << "3 - " << redColor << "Charge Rifle" << resetColor << std::endl;
	}
    
	if(weapon_sentinel)
	{
		std::cout << "4 - " << greenColor <<"Sentinel" << resetColor << std::endl;
	}
	else if(!weapon_sentinel)
	{
		std::cout << "4 - " << redColor <<"Sentinel" << resetColor << std::endl;
	}
    
	if(weapon_bow)
	{
		std::cout << "5 - " << greenColor <<"Bow" << resetColor << std::endl;
	}
	else if(!weapon_bow)
	{
		std::cout << "5 - " << redColor <<"Bow" << resetColor << std::endl;
	}
	
	if(sniperammo)
	{
		std::cout << "6 - " << greenColor <<"Sniper Ammo\n" << resetColor << std::endl;
	}
	else if(!sniperammo)
	{
		std::cout << "6 - " << redColor <<"Sniper Ammo\n" << resetColor << std::endl;
	}
	
	std::cout << "Sniper Weapon Mags:\n" << std::endl;
    
	if(sniperammomag1)
	{
		std::cout << "7 - " << greenColor << "Sniper Ammo Mag:" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!sniperammomag1)
	{
		std::cout << "7 - " << redColor << "Sniper Ammo Mag:" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    

    // Display colored options
    
	if(sniperammomag2)
	{
		std::cout << "8 - " << greenColor << "Sniper Ammo Mag:" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!sniperammomag2)
	{
		std::cout << "8 - " << redColor << "Sniper Ammo Mag:" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(sniperammomag3)
	{
		std::cout << "9 - " << greenColor << "Sniper Ammo Mag:" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!sniperammomag3)
	{
		std::cout << "9 - " << redColor << "Sniper Ammo Mag:" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
    
	if(sniperammomag4)
	{
		std::cout << "10 - " << greenColor << "Sniper Ammo Mag:" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!sniperammomag4)
	{
		std::cout << "10 - " << redColor << "Sniper Ammo Mag:" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
    
	std::cout << "Sniper Stocks:\n" << std::endl;
	
	if(stocksniper1)
	{
		std::cout << "11 - " << greenColor << "Sniper Stock" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!stocksniper1)
	{
		std::cout << "11 - " << redColor << "Sniper Stock" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	
	
	
	
	if(stocksniper2)
	{
		std::cout << "12 - " << greenColor << "Sniper Stock" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!stocksniper2)
	{
		std::cout << "12 - " << redColor << "Sniper Stock" << resetColor << ": " << blueColor << "White" << resetColor << std::endl;
	}
    
	if(stocksniper3)
	{
		std::cout << "13 - " << greenColor << "Sniper Stock" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	else if(!stocksniper3)
	{
		std::cout << "13 - " << redColor << "Sniper Stock" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
    
	std::cout << "Weapon Suppressors:\n" << std::endl;
	
	if(suppressor1)
	{
		std::cout << "14 - " << greenColor << "Weapon Suppressors" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!suppressor1)
	{
		std::cout << "14 - " << redColor << "Weapon Suppressors" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	
    
	
	
	if(suppressor2)
	{
		std::cout << "15 - " << greenColor << "Weapon Suppressors" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!suppressor2)
	{
		std::cout << "15 - " << redColor << "Weapon Suppressors" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(suppressor3)
	{
		std::cout << "16 - " << greenColor << "Weapon Suppressors" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	else if(!suppressor3)
	{
		std::cout << "16 - " << redColor << "Weapon Suppressors" << resetColor << ": " << purpleColor << "Purple\n" << resetColor << std::endl;
	}
	
    std::cout << "Weapon Hop-Ups:\n" << std::endl;
	
	if(turbo_charger)
	{
		std::cout << "17 - " << greenColor << "Turbo Chager" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!turbo_charger)
	{
		std::cout << "17 - " << redColor << "Turbo Chager" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	
	
	
	if(skull_piecer)
	{
		std::cout << "18 - " << greenColor << "Skull Piecer" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!skull_piecer)
	{
		std::cout << "18 - " << redColor << "Skull Piecer" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
    
	if(hammer_point)
	{
		std::cout << "19 - " << greenColor << "Hammer Points" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!hammer_point)
	{
		std::cout << "19 - " << redColor << "Hammer Points" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
    
	if(disruptor_rounds)
	{
		std::cout << "20 - " << greenColor << "Disruptor Rounds" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!disruptor_rounds)
	{
		std::cout << "20 - " << redColor << "Disruptor Rounds" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
    
	if(boosted_loader)
	{
		std::cout << "21 - " << greenColor << "Boosted Loader" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!boosted_loader)
	{
		std::cout << "21 - " << redColor << "Boosted Loader" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	
    std::cout << "22 - Back to Settings Menu\n" << std::endl;
}

void displayArmors()
{
	// Color definitions using ANSI escape codes
    std::string whiteColor = "\033[1;37m"; // White text
    std::string blueColor = "\033[1;34m";  // Blue text
    std::string purpleColor = "\033[1;35m"; // Purple text
    std::string goldColor = "\033[1;33m";  // Gold text
	std::string yellowColor = "\033[1;33m"; // Yellow text
	std::string redColor = "\033[1;31m"; // Red text
	 std::string greenColor = "\033[1;32m"; // Green text
	 std::string tealColor = "\033[1;36m";   // Teal text
    std::string yellowGoldColor = "\033[1;33m"; // Yellow-gold text
    std::string resetColor = "\033[0m";    // Reset text color to default
	
	std::cout << redColor << "Red = Disable" << resetColor << " - " << greenColor << "Green = Enabled" << resetColor << resetColor << std::endl;
	std::cout << whiteColor << "Armors:\n" << resetColor << std::endl;
	
	if(shieldupgrade1)
	{
		std::cout << "1 - " << greenColor << "White Armor" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!shieldupgrade1)
	{
		std::cout << "1 - " << redColor << "White Armor" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(shieldupgrade2)
	{
		std::cout << "2 - " << greenColor << "Blue Armor" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!shieldupgrade2)
	{
		std::cout << "2 - " << redColor << "Blue Armor" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(shieldupgrade3)
	{
		std::cout << "3 - " << greenColor << "Purple Armor" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!shieldupgrade3)
	{
		std::cout << "3 - " << redColor << "Purple Armor" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
    
	if(shieldupgrade4)
	{
		std::cout << "4 - " << greenColor << "Gold Armor" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!shieldupgrade4)
	{
		std::cout << "4 - " << redColor << "Gold Armor" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	
	if(shieldupgrade5)
	{
		std::cout << "5 - " << greenColor << "Red Armor" << resetColor << ": " << redColor << "Red\n" << resetColor << std::endl;
	}
	else if(!shieldupgrade5)
	{
		std::cout << "5 - " << redColor << "Red Armor" << resetColor << ": " << redColor << "Red\n" << resetColor << std::endl;
	}
	
	std::cout << "Helmets:\n" << std::endl;
	
	
	if(shieldupgradehead1)
	{
		std::cout << "6 - " << greenColor << "Helmet" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!shieldupgradehead1)
	{
		std::cout << "6 - " << redColor << "Helmet" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(shieldupgradehead2)
	{
		std::cout << "7 - " << greenColor << "Helmet" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!shieldupgradehead2)
	{
		std::cout << "7 - " << redColor << "Helmet" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(shieldupgradehead3)
	{
		std::cout << "8 - " << greenColor << "Helmet" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!shieldupgradehead3)
	{
		std::cout << "8 - " << redColor << "Helmet" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	
	if(shieldupgradehead4)
	{
		std::cout << "9 - " << greenColor << "Helmet" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!shieldupgradehead4)
	{
		std::cout << "9 - " << redColor << "Helmet" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	
    std::cout << "Knockdown Shields:\n" << std::endl;
	
	
	if(shielddown1)
	{
		std::cout << "10 - " << greenColor << "Knockdown Shield" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!shielddown1)
	{
		std::cout << "10 - " << redColor << "Knockdown Shield" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(shielddown2)
	{
		std::cout << "11 - " << greenColor << "Knockdown Shield" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!shielddown2)
	{
		std::cout << "11 - " << redColor << "Knockdown Shield" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(shielddown3)
	{
		std::cout << "12 - " << greenColor << "Knockdown Shield" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!shielddown3)
	{
		std::cout << "12 - " << redColor << "Knockdown Shield" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	
	if(shielddown4)
	{
		std::cout << "13 - " << greenColor << "Knockdown Shield" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	else if(!shielddown4)
	{
		std::cout << "13 - " << redColor << "Knockdown Shield" << resetColor << ": " << goldColor << "Gold\n" << resetColor << std::endl;
	}
	
	
    std::cout << "14 - Back to Settings Menu\n" << std::endl;
}

void displayHealing()
{
	// Color definitions using ANSI escape codes
    std::string whiteColor = "\033[1;37m"; // White text
    std::string blueColor = "\033[1;34m";  // Blue text
    std::string purpleColor = "\033[1;35m"; // Purple text
    std::string goldColor = "\033[1;33m";  // Gold text
	std::string yellowColor = "\033[1;33m"; // Yellow text
	std::string redColor = "\033[1;31m"; // Red text
	 std::string greenColor = "\033[1;32m"; // Green text
	 std::string tealColor = "\033[1;36m";   // Teal text
    std::string yellowGoldColor = "\033[1;33m"; // Yellow-gold text
    std::string resetColor = "\033[0m";    // Reset text color to default
	
	std::cout << redColor << "Red = Disable" << resetColor << " - " << greenColor << "Green = Enabled" << resetColor << resetColor << std::endl;
	std::cout << whiteColor << "Healing Items:\n" << resetColor << std::endl;
	
	if(accelerant)
	{
		std::cout << "1 - " << greenColor << "Accelerant" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!accelerant)
	{
		std::cout << "1 - " << redColor << "Accelerant" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(phoenix)
	{
		std::cout << "2 - " << greenColor << "Phoenix" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!phoenix)
	{
		std::cout << "2 - " << redColor << "Phoenix" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
    
	if(healthlarge)
	{
		std::cout << "3 - " << greenColor << "Large Health" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!healthsmall)
	{
		std::cout << "3 - " << redColor << "Large Health" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(shieldbattsmall)
	{
		std::cout << "4 - " << greenColor << "Small Shield Batt" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!shieldbattsmall)
	{
		std::cout << "4 - " << redColor << "Small Shield Batt" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	
	if(shieldbattlarge)
	{
		std::cout << "5 - " << greenColor << "Large Shield Batt" << resetColor << ": " << blueColor << "Blue\n" << resetColor << std::endl;
	}
	else if(!shieldbattlarge)
	{
		std::cout << "5 - " << redColor << "Large Shield Batt" << resetColor << ": " << blueColor << "Blue\n" << resetColor << std::endl;
	}
	

    std::cout << "6 - Back to Settings Menu\n" << std::endl;
}

void displayNades()
{
	// Color definitions using ANSI escape codes
    std::string whiteColor = "\033[1;37m"; // White text
    std::string blueColor = "\033[1;34m";  // Blue text
    std::string purpleColor = "\033[1;35m"; // Purple text
    std::string goldColor = "\033[1;33m";  // Gold text
	std::string yellowColor = "\033[1;33m"; // Yellow text
	std::string redColor = "\033[1;31m"; // Red text
	 std::string greenColor = "\033[1;32m"; // Green text
	 std::string tealColor = "\033[1;36m";   // Teal text
    std::string yellowGoldColor = "\033[1;33m"; // Yellow-gold text
    std::string resetColor = "\033[0m";    // Reset text color to default
	
	std::cout << redColor << "Red = Disable" << resetColor << " - " << greenColor << "Green = Enabled" << resetColor << resetColor << std::endl;
	std::cout << whiteColor << "Nade Items:\n" << resetColor << std::endl;
	
	if(grenade_frag)
	{
		std::cout << "1 - " << greenColor << "Frag Grenade" << resetColor << ": " << redColor << "Red" << resetColor << std::endl;
	}
	else if(!grenade_frag)
	{
		std::cout << "1 - " << redColor << "Frag Grenade" << resetColor << ": " << redColor << "Red" << resetColor << std::endl;
	}
    
	if(grenade_arc_star)
	{
		std::cout << "2 - " << greenColor << "Arc Star" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!grenade_arc_star)
	{
		std::cout << "2 - " << redColor << "Arc Star" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(grenade_thermite)
	{
		std::cout << "3 - " << greenColor << "Thermite" << resetColor << ": " << redColor << "Red" << resetColor << std::endl;
	}
	else if(!grenade_thermite)
	{
		std::cout << "3 - " << redColor << "Thermite" << resetColor << ": " << redColor << "Red" << resetColor << std::endl;
	}

    std::cout << "4 - Back to Settings Menu\n" << std::endl;
}

void displayBackpacks()
{
	// Color definitions using ANSI escape codes
    std::string whiteColor = "\033[1;37m"; // White text
    std::string blueColor = "\033[1;34m";  // Blue text
    std::string purpleColor = "\033[1;35m"; // Purple text
    std::string goldColor = "\033[1;33m";  // Gold text
	std::string yellowColor = "\033[1;33m"; // Yellow text
	std::string redColor = "\033[1;31m"; // Red text
	 std::string greenColor = "\033[1;32m"; // Green text
	 std::string tealColor = "\033[1;36m";   // Teal text
    std::string yellowGoldColor = "\033[1;33m"; // Yellow-gold text
    std::string resetColor = "\033[0m";    // Reset text color to default
	
	std::cout << redColor << "Red = Disable" << resetColor << " - " << greenColor << "Green = Enabled" << resetColor << resetColor << std::endl;
	std::cout << whiteColor << "Backpacks:\n" << resetColor << std::endl;
	
	if(lightbackpack)
	{
		std::cout << "1 - " << greenColor << "Light Backpack" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!lightbackpack)
	{
		std::cout << "1 - " << redColor << "Light Backpack" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(medbackpack)
	{
		std::cout << "2 - " << greenColor << "Medium Backpack" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!medbackpack)
	{
		std::cout << "2 - " << redColor << "Medium Backpack" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(heavybackpack)
	{
		std::cout << "3 - " << greenColor << "Heavy Backpack" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!heavybackpack)
	{
		std::cout << "3 - " << redColor << "Heavy Backpack" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	
	if(goldbackpack)
	{
		std::cout << "4 - " << greenColor << "Gold Backpack" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!goldbackpack)
	{
		std::cout << "4 - " << redColor << "Gold Backpack" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}

    std::cout << "5 - Back to Settings Menu\n" << std::endl;
}

void displayScopes()
{
	// Color definitions using ANSI escape codes
    std::string whiteColor = "\033[1;37m"; // White text
    std::string blueColor = "\033[1;34m";  // Blue text
    std::string purpleColor = "\033[1;35m"; // Purple text
    std::string goldColor = "\033[1;33m";  // Gold text
	std::string yellowColor = "\033[1;33m"; // Yellow text
	std::string redColor = "\033[1;31m"; // Red text
	 std::string greenColor = "\033[1;32m"; // Green text
	 std::string tealColor = "\033[1;36m";   // Teal text
    std::string yellowGoldColor = "\033[1;33m"; // Yellow-gold text
    std::string resetColor = "\033[0m";    // Reset text color to default
	
	std::cout << redColor << "Red = Disable" << resetColor << " - " << greenColor << "Green = Enabled" << resetColor << resetColor << std::endl;
	std::cout << whiteColor << "Scopes:\n" << resetColor << std::endl;
	
	if(optic1xhcog)
	{
		std::cout << "1 - " << greenColor << "1x HCOG" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!optic1xhcog)
	{
		std::cout << "1 - " << redColor << "1x HCOG" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
    
	if(optic2xhcog)
	{
		std::cout << "2 - " << greenColor << "2x HCOG" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!optic2xhcog)
	{
		std::cout << "2 - " << redColor << "2x HCOG" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
    
	if(opticholo1x)
	{
		std::cout << "3 - " << greenColor << "1x HOLO" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	else if(!opticholo1x)
	{
		std::cout << "3 - " << redColor << "1x HOLO" << resetColor << ": " << whiteColor << "White" << resetColor << std::endl;
	}
	
	if(opticholo1x2x)
	{
		std::cout << "4 - " << greenColor << "1x-2x HOLO" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!opticholo1x2x)
	{
		std::cout << "4 - " << redColor << "1x-2x HOLO" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	
	if(opticthreat)
	{
		std::cout << "5 - " << greenColor << "Optic Threat" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!opticthreat)
	{
		std::cout << "5 - " << redColor << "Optic Threat" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	
	if(optic3xhcog)
	{
		std::cout << "6 - " << greenColor << "3x HCOG" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!optic3xhcog)
	{
		std::cout << "6 - " << redColor << "3x HCOG" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	
	if(optic2x4x)
	{
		std::cout << "7 - " << greenColor << "2x-4x HCOG" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!optic2x4x)
	{
		std::cout << "7 - " << redColor << "2x-4x HCOG" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	
	if(opticsniper6x)
	{
		std::cout << "8 - " << greenColor << "6x Sniper Optic" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	else if(!opticsniper6x)
	{
		std::cout << "8 - " << redColor << "6x Sniper Optic" << resetColor << ": " << blueColor << "Blue" << resetColor << std::endl;
	}
	
	if(opticsniper4x8x)
	{
		std::cout << "9 - " << greenColor << "4x-8x Sniper Optic" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	else if(!opticsniper4x8x)
	{
		std::cout << "9 - " << redColor << "4x-8x Sniper Optic" << resetColor << ": " << purpleColor << "Purple" << resetColor << std::endl;
	}
	
	if(opticsniperthreat)
	{
		std::cout << "10 - " << greenColor << "Sniper Threat" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	else if(!opticsniperthreat)
	{
		std::cout << "10 - " << redColor << "Sniper Threat" << resetColor << ": " << goldColor << "Gold" << resetColor << std::endl;
	}
	
	

    std::cout << "11 - Back to Settings Menu\n" << std::endl;
}

int getMenuOption()
{
    int option;
    std::cout << "Enter a command ##: ";
    std::cin >> option;
    return option;
}

void terminal()
{
    bool exitProgram = false;
    int menuLevel = 0; // 0 for Main Menu, 1 for Settings Menu, 2 for Submenu

    while (!exitProgram) {
        system("clear"); // Use "cls" for Windows

        if (menuLevel == 0)
		{
            displayMainMenu();
        }
		else if (menuLevel == 1)
		{
            displayItemFilterMenu();
        }
		else if (menuLevel == 2)
		{
            displayLightWeapons();
        }
		else if (menuLevel == 3)
		{
            displayHeavyWeapons();
        }
		else if (menuLevel == 4)
		{
            displayEnergyWeapons();
        }
		else if (menuLevel == 5)
		{
            displaySniperWeapons();
        }
		else if (menuLevel == 6)
		{
            displayArmors();
        }
		else if (menuLevel == 7)
		{
            displayHealing();
        }
		else if (menuLevel == 8)
		{
            displayNades();
        }
		else if (menuLevel == 9)
		{
            displayBackpacks();
        }
		else if (menuLevel == 10)
		{
            displayScopes();
        }
		
		


        int option = getMenuOption();
		
		//Main Menu
        if (menuLevel == 0) //displayMainMenu();
		{
			std::string userInput;
			if (option == 1)
			{
                // Toggle the firing_range.
				firing_range = !firing_range;
				
				if (firing_range)
				{
					std::cout << "Firing Range ON.\n";
				}
				else
				{
					std::cout << "Firing Range OFF.\n";
				}
            }
			if (option == 2)
			{
                // Toggle TDM.
				TDMToggle = !TDMToggle;
				
				if (TDMToggle)
				{
					std::cout << "TDM ON.\n";
				}
				else
				{
					std::cout << "TDM OFF.\n";
				}
            }
			if (option == 3)
			{
                // Keyboard Enable.
				keyboard = true;
				gamepad = false;
				std::cout << "Keyboard ON.\n";
            }
			if (option == 4)
			{
                // Gamepad Enable.
				keyboard = false;
				gamepad = true;
				std::cout << "Gamepad ON.\n";
            }
			if (option == 5)
			{
                // Toggle TDM.
				item_glow = !item_glow;
				
				if (item_glow)
				{
					std::cout << "Item Glow ON.\n";
				}
				else
				{
					std::cout << "Item Glow OFF.\n";
				}
            }
			if (option == 6)
			{
                // Toggle TDM.
				player_glow = !player_glow;
				
				if (player_glow)
				{
					std::cout << "Player Glow ON.\n";
				}
				else
				{
					std::cout << "Player Glow OFF.\n";
				}
            }
			if (option == 7)
			{
                // Command to change the 'smooth' value.
				std::cout << "Enter a new value for 'smooth' (70 to 200): ";
				float newSmooth;
				std::cin >> newSmooth;

				// Check if the new value is within the desired range.
				if (newSmooth >= 70.0f && newSmooth <= 500.0f)
				{
					smooth = newSmooth;
					std::cout << "'smooth' value updated to: " << smooth << std::endl;
					printf("The value of 'smooth' is: %f\n", smooth);
				}
				else
				{
					std::cout << "Invalid value. 'smooth' value must be between 70 and 500." << std::endl;
				}
				
				// Clear the input buffer to prevent any issues with future input.
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
			if (option == 8)
			{
                // Command to change the 'smooth' value.
				std::cout << "Enter a new value for 'bone' (0 to 3): ";
				int newBone;
				std::cin >> newBone;

				// Check if the new value is within the desired range.
				if (newBone >= 0 && newBone <= 3)
				{
					bone = newBone;
					std::cout << "'bone' value updated to: " << bone << std::endl;
				}
				else
				{
					std::cout << "Invalid value. 'bone' value must be between 0 and 3." << std::endl;
				}
				
				// Clear the input buffer to prevent any issues with future input.
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
			if (option == 9)
			{
                //Loot Filled.
				lootfilledtoggle = !lootfilledtoggle;
				
				if (lootfilledtoggle)
				{
					lootfilled = 14;
					std::cout << "Loot Glow Filled.\n";
				}
				else
				{
					lootfilled = 0;
					std::cout << "Loot Glow Not Filled.\n";
				}
            }
			if (option == 10)
			{
                //player Filled.
				playerfilledtoggle = !playerfilledtoggle;
				
				if (playerfilledtoggle)
				{
					insidevalue = 14;
					std::cout << "Player Glow Filled.\n";
				}
				else
				{
					insidevalue = 0;
					std::cout << "Player Glow Not Filled.\n";
				}
            }
			if (option == 11)
			{
                // Command to change the 'smooth' value.
				std::cout << "Enter a new value for Player Outlines (0 to 255): ";
				int newoutlinesize;
				std::cin >> newoutlinesize;

				// Check if the new value is within the desired range.
				if (newoutlinesize >= 0 && newoutlinesize <= 255)
				{
					outlinesize = newoutlinesize;
					std::cout << "Player Outline updated to: " << outlinesize << std::endl;
				}
				else
				{
					std::cout << "Invalid value. 'outlinesize' value must be between 0 and 255." << std::endl;
				}
				
				// Clear the input buffer to prevent any issues with future input.
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
			if (option == 12)
			{
                // Select a glow set (1 for "Not Visible," 2 for "Visible," 3 for "Knocked").
				std::cout << "Select Glow: 1 - Not Visible, 2 - Visible, 3 - Knocked (can do fractions IE: 0.863: ";
				std::cin >> userInput;
				int selectedSet = std::stoi(userInput);
				
				switch (selectedSet)
				{
					case 1:
						updateGlowColor(glowrnot, glowgnot, glowbnot, "'Not Visible'");
						break;
					case 2:
						updateGlowColor(glowrviz, glowgviz, glowbviz, "'Visible'");
						break;
					case 3:
						updateGlowColor(glowrknocked, glowgknocked, glowbknocked, "'Knocked'");
						break;
					default:
						std::cout << "Invalid set selection. Please choose 1-3.\n";
						break;
				}
            }
			if (option == 13)
			{
                // Command to change the 'smooth' value.
				std::cout << "Enter a new value for 'ADS FOV' (1 to 50): ";
				float newADSfov;
				std::cin >> newADSfov;

				// Check if the new value is within the desired range.
				if (newADSfov >= 0.0f && newADSfov <= 50.0f)
				{
					ADSfov = newADSfov;
					std::cout << "'ADS FOV' value updated to: " << ADSfov << std::endl;
					printf("The value of 'ADS FOV' is: %f\n", ADSfov);
				}
				else
				{
					std::cout << "Invalid value. 'ADS FOV' value must be between 85 and 200." << std::endl;
				}
				
				// Clear the input buffer to prevent any issues with future input.
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
			if (option == 14)
			{
                // Command to change the 'smooth' value.
				std::cout << "Enter a new value for 'Non-ADS FOV' (1 to 50): ";
				float newnonADSfov;
				std::cin >> newnonADSfov;

				// Check if the new value is within the desired range.
				if (newnonADSfov >= 0.0f && newnonADSfov <= 50.0f)
				{
					nonADSfov = newnonADSfov;
					std::cout << "'Non-ADS FOV' value updated to: " << nonADSfov << std::endl;
					printf("The value of 'Non-ADS FOV' is: %f\n", nonADSfov);
				}
				else
				{
					std::cout << "Invalid value. 'Non-ADS FOV' value must be between 85 and 200." << std::endl;
				}
				
				// Clear the input buffer to prevent any issues with future input.
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
			if (option == 15)
			{
                //player Filled.
				SuperKey = !SuperKey;
				SuperKeyToggle = !SuperKeyToggle;
            }
			
            if (option == 16)
			{
                //  displayItemFilterMenu
                menuLevel = 1;
            }
			if (option == 17)
			{
				saveSettings();
            }
			if (option == 18)
			{
				loadSettings(); 
            }
			
			else
			{
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
		
		//Filter Item Menu
		else if (menuLevel == 1)
		{
            if (option == 1)
			{
                // Light Weapons
                menuLevel = 2;
            }
			else if (option == 2)
			{
                // Heavy weapons
                menuLevel = 3;
            }
			else if (option == 3)
			{
                // Return to the Main Menu.
                menuLevel = 4;
            }
			else if (option == 4)
			{
                // Return to the Main Menu.
                menuLevel = 5;
            }
			else if (option == 5)
			{
                // Return to the Main Menu.
                menuLevel = 6;
            }
			else if (option == 6)
			{
                // Return to the Main Menu.
                menuLevel = 7;
            }
			else if (option == 7)
			{
                // Return to the Main Menu.
                menuLevel = 8;
            }
			else if (option == 8)
			{
                // Return to the Main Menu.
                menuLevel = 9;
            }
			else if (option == 9)
			{
                // Return to the Main Menu.
                menuLevel = 10;
            }
			else if (option == 10)
			{
                // Return to the Main Menu.
                menuLevel = 0;
            }
			else
			{
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
		
		//Light weapons
		else if (menuLevel == 2) //light
		{
            if (option == 1)
			{
				weapon_p2020  = !weapon_p2020 ;
            }
			if (option == 2)
			{
				weapon_re45  = !weapon_re45 ;
            }
			if (option == 3)
			{
				weapon_alternator  = !weapon_alternator ;
            }
			if (option == 4)
			{
				weapon_r99  = !weapon_r99 ;
            }
			if (option == 5)
			{
				weapon_r301  = !weapon_r301 ;
            }
			if (option == 6)
			{
				weapon_spitfire  = !weapon_spitfire ;
            }
			if (option == 7)
			{
				weapon_g7_scout  = !weapon_g7_scout ;
            }
			if (option == 8)
			{
				lightammo  = !lightammo ;
            }
			if (option == 9)
			{
				lightammomag1  = !lightammomag1 ;
            }
			if (option == 10)
			{
				lightammomag2  = !lightammomag2 ;
            }
			if (option == 11)
			{
				lightammomag3  = !lightammomag3 ;
            }
			if (option == 12)
			{
				lightammomag4  = !lightammomag4 ;
            }
			if (option == 13)
			{
				stockregular1  = !stockregular1 ;
            }
			if (option == 14)
			{
				stockregular2  = !stockregular2 ;
            }
			if (option == 15)
			{
				stockregular3  = !stockregular3 ;
            }
			if (option == 16)
			{
				suppressor1  = !suppressor1 ;
            }
			if (option == 17)
			{
				suppressor2  = !suppressor2 ;
            }
			if (option == 18)
			{
				suppressor3  = !suppressor3 ;
            }
			if (option == 19)
			{
				lasersight1  = !lasersight1 ;
            }
			if (option == 20)
			{
				lasersight2  = !lasersight2 ;
            }
			if (option == 21)
			{
				lasersight3  = !lasersight3 ;
            }
			if (option == 22)
			{
				lasersight4  = !lasersight4 ;
            }
			if (option == 23)
			{
				turbo_charger  = !turbo_charger ;
            }
			if (option == 24)
			{
				skull_piecer  = !skull_piecer ;
            }
			if (option == 25)
			{
				hammer_point  = !hammer_point ;
            }
			if (option == 26)
			{
				disruptor_rounds  = !disruptor_rounds ;
            }
			if (option == 27)
			{
				boosted_loader  = !boosted_loader ;
            }
			if (option == 28)
			{
				menuLevel = 1;
            }
			
			
			
			else
			{
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
		
		//Heavy weapons
		else if (menuLevel == 3) //heavy 
		{
            if (option == 1)
			{
				weapon_flatline  = !weapon_flatline ;
            }
			if (option == 2)
			{
				weapon_hemlock  = !weapon_hemlock ;
            }
			if (option == 3)
			{
				weapon_3030_repeater  = !weapon_3030_repeater ;
            }
			if (option == 4)
			{
				weapon_rampage  = !weapon_rampage ;
            }
			if (option == 5)
			{
				weapon_prowler  = !weapon_prowler ;
            }
			if (option == 6)
			{
				weapon_car_smg  = !weapon_car_smg ;
            }
			if (option == 7)
			{
				heavyammo  = !heavyammo ;
            }
			if (option == 8)
			{
				heavyammomag1  = !heavyammomag1 ;
            }
			if (option == 9)
			{
				heavyammomag2  = !heavyammomag2 ;
            }
			if (option == 10)
			{
				heavyammomag3  = !heavyammomag3 ;
            }
			if (option == 11)
			{
				heavyammomag4  = !heavyammomag4 ;
            }
			if (option == 12)
			{
				stockregular1  = !stockregular1 ;
            }
			if (option == 13)
			{
				stockregular2  = !stockregular2 ;
            }
			if (option == 14)
			{
				stockregular3  = !stockregular3 ;
            }
			if (option == 15)
			{
				suppressor1  = !suppressor1 ;
            }
			if (option == 16)
			{
				suppressor2  = !suppressor2 ;
            }
			if (option == 17)
			{
				suppressor3  = !suppressor3 ;
            }
			if (option == 18)
			{
				lasersight1  = !lasersight1 ;
            }
			if (option == 19)
			{
				lasersight2  = !lasersight2 ;
            }
			if (option == 20)
			{
				lasersight3  = !lasersight3 ;
            }
			if (option == 21)
			{
				lasersight4  = !lasersight4 ;
            }
			if (option == 22)
			{
				turbo_charger  = !turbo_charger ;
            }
			if (option == 23)
			{
				skull_piecer  = !skull_piecer ;
            }
			if (option == 24)
			{
				hammer_point  = !hammer_point ;
            }
			if (option == 25)
			{
				disruptor_rounds  = !disruptor_rounds ;
            }
			if (option == 26)
			{
				boosted_loader  = !boosted_loader ;
            }
			if (option == 27)
			{
				menuLevel = 1;
            }
			else
			{
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
		
		//Energy weapons
		else if (menuLevel == 4) //energy
		{
            if (option == 1)
			{
				weapon_lstar  = !weapon_lstar ;
            }
			if (option == 2)
			{
				weapon_nemesis  = !weapon_nemesis ;
            }
			if (option == 3)
			{
				weapon_havoc  = !weapon_havoc ;
            }
			if (option == 4)
			{
				weapon_devotion  = !weapon_devotion ;
            }
			if (option == 5)
			{
				weapon_triple_take  = !weapon_triple_take ;
            }
			if (option == 6)
			{
				weapon_volt  = !weapon_volt ;
            }
			if (option == 7)
			{
				energyammo  = !energyammo ;
            }
			if (option == 8)
			{
				energyammomag1  = !energyammomag1 ;
            }
			if (option == 9)
			{
				energyammomag2  = !energyammomag2 ;
            }
			if (option == 10)
			{
				energyammomag3  = !energyammomag3 ;
            }
			if (option == 11)
			{
				energyammomag4  = !energyammomag4 ;
            }
			if (option == 12)
			{
				stockregular1  = !stockregular1 ;
            }
			if (option == 13)
			{
				stockregular2  = !stockregular2 ;
            }
			if (option == 14)
			{
				stockregular3  = !stockregular3 ;
            }
			if (option == 15)
			{
				suppressor1  = !suppressor1 ;
            }
			if (option == 16)
			{
				suppressor2  = !suppressor2 ;
            }
			if (option == 17)
			{
				suppressor3  = !suppressor3 ;
            }
			if (option == 18)
			{
				lasersight1  = !lasersight1 ;
            }
			if (option == 19)
			{
				lasersight2  = !lasersight2 ;
            }
			if (option == 20)
			{
				lasersight3  = !lasersight3 ;
            }
			if (option == 21)
			{
				lasersight4  = !lasersight4 ;
            }
			if (option == 22)
			{
				turbo_charger  = !turbo_charger ;
            }
			if (option == 23)
			{
				skull_piecer  = !skull_piecer ;
            }
			if (option == 24)
			{
				hammer_point  = !hammer_point ;
            }
			if (option == 25)
			{
				disruptor_rounds  = !disruptor_rounds ;
            }
			if (option == 26)
			{
				boosted_loader  = !boosted_loader ;
            }
			if (option == 27)
			{
				menuLevel = 1;
            }
			else
			{
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
		
		//Sniper weapons
		else if (menuLevel == 5) //Sniper
		{
            if (option == 1)
			{
				weapon_wingman  = !weapon_wingman ;
            }
			if (option == 2)
			{
				weapon_longbow  = !weapon_longbow ;
            }
			if (option == 3)
			{
				weapon_charge_rifle  = !weapon_charge_rifle ;
            }
			if (option == 4)
			{
				weapon_sentinel  = !weapon_sentinel ;
            }
			if (option == 5)
			{
				weapon_bow  = !weapon_bow ;
            }
			if (option == 6)
			{
				sniperammo  = !sniperammo ;
            }
			if (option == 7)
			{
				sniperammomag1  = !sniperammomag1 ;
            }
			if (option == 8)
			{
				sniperammomag2  = !sniperammomag2 ;
            }
			if (option == 9)
			{
				sniperammomag3  = !sniperammomag3 ;
            }
			if (option == 10)
			{
				sniperammomag4  = !sniperammomag4 ;
            }
			if (option == 11)
			{
				stocksniper1  = !stocksniper1 ;
            }
			if (option == 12)
			{
				stocksniper2  = !stocksniper2 ;
            }
			if (option == 13)
			{
				stocksniper3  = !stocksniper3 ;
            }
			if (option == 14)
			{
				suppressor1  = !suppressor1 ;
            }
			if (option == 15)
			{
				suppressor2  = !suppressor2 ;
            }
			if (option == 16)
			{
				suppressor3  = !suppressor3 ;
            }
			if (option == 17)
			{
				turbo_charger  = !turbo_charger ;
            }
			if (option == 18)
			{
				skull_piecer  = !skull_piecer ;
            }
			if (option == 19)
			{
				hammer_point  = !hammer_point ;
            }
			if (option == 20)
			{
				disruptor_rounds  = !disruptor_rounds ;
            }
			if (option == 21)
			{
				boosted_loader  = !boosted_loader ;
            }
			if (option == 22)
			{
				menuLevel = 1;
            }
			else
			{
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
		
		//Armors
		else if (menuLevel == 6)
		{
            if (option == 1)
			{
				shieldupgrade1  = !shieldupgrade1 ;
            }
			if (option == 2)
			{
				shieldupgrade2  = !shieldupgrade2 ;
            }
			if (option == 3)
			{
				shieldupgrade3  = !shieldupgrade3 ;
            }
			if (option == 4)
			{
				shieldupgrade4  = !shieldupgrade4 ;
            }
			if (option == 5)
			{
				shieldupgrade5  = !shieldupgrade5 ;
            }
			if (option == 6)
			{
				shieldupgradehead1  = !shieldupgradehead1 ;
            }
			if (option == 7)
			{
				shieldupgradehead2  = !shieldupgradehead2 ;
            }
			if (option == 8)
			{
				shieldupgradehead3  = !shieldupgradehead3 ;
            }
			if (option == 9)
			{
				shieldupgradehead4  = !shieldupgradehead4 ;
            }
			if (option == 10)
			{
				shielddown1  = !shielddown1 ;
            }
			if (option == 11)
			{
				shielddown2  = !shielddown2 ;
            }
			if (option == 12)
			{
				shielddown3  = !shielddown3 ;
            }
			if (option == 13)
			{
				shielddown4  = !shielddown4 ;
            }
			
			if (option == 14)
			{
				menuLevel = 1;
            }
			else
			{
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
		
		//Healing Items
		else if (menuLevel == 7)
		{
            if (option == 1)
			{
				accelerant  = !accelerant ;
            }
			if (option == 2)
			{
				phoenix  = !phoenix ;
            }
			if (option == 3)
			{
				healthlarge  = !healthlarge ;
            }
			if (option == 4)
			{
				healthsmall  = !healthsmall ;
            }
			if (option == 5)
			{
				shieldbattsmall  = !shieldbattsmall ;
            }		
			if (option == 6)
			{
				menuLevel = 1;
            }
			else
			{
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
		
		//Nades
		else if (menuLevel == 8)
		{
            if (option == 1)
			{
				grenade_frag  = !grenade_frag ;
            }
			if (option == 2)
			{
				grenade_arc_star  = !grenade_arc_star ;
            }
			if (option == 3)
			{
				grenade_thermite  = !grenade_thermite ;
            }
			if (option == 4)
			{
				menuLevel = 1;
            }
			else
			{
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
		
		//Backpacks
		else if (menuLevel == 9)
		{
            if (option == 1)
			{
				lightbackpack  = !lightbackpack ;
            }
			if (option == 2)
			{
				medbackpack  = !medbackpack ;
            }
			if (option == 3)
			{
				heavybackpack  = !heavybackpack ;
            }
			if (option == 4)
			{
				goldbackpack  = !goldbackpack ;
            }
			if (option == 5)
			{
				menuLevel = 1;
            }
			else
			{
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
		
		//Scopes
		else if (menuLevel == 10)
		{
            if (option == 1)
			{
				optic1xhcog  = !optic1xhcog ;
            }
			if (option == 2)
			{
				optic2xhcog  = !optic2xhcog ;
            }
			if (option == 3)
			{
				opticholo1x  = !opticholo1x ;
            }
			if (option == 4)
			{
				opticholo1x2x  = !opticholo1x2x ;
            }
			if (option == 5)
			{
				opticthreat  = !opticthreat ;
            }
			if (option == 6)
			{
				optic3xhcog  = !optic3xhcog ;
            }
			if (option == 7)
			{
				optic2x4x  = !optic2x4x ;
            }
			if (option == 8)
			{
				opticsniper6x  = !opticsniper6x ;
            }
			if (option == 9)
			{
				opticsniper4x8x  = !opticsniper4x8x ;
            }
			if (option == 10)
			{
				opticsniperthreat  = !opticsniperthreat ;
            }
			
			if (option == 11)
			{
				menuLevel = 1;
            }
			else
			{
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
    }
	terminal_t = false;
}


int main(int argc, char *argv[])
{
	
	if(geteuid() != 0)
	{
		//run as root..
		return 0;
	}

	const char* ap_proc = "r5apex.exe";

	std::thread aimbot_thr;
	std::thread actions_thr;
	std::thread cactions_thr;
	//Used to change things on a timer
	//std::thread updateInsideValue_thr;
	std::thread terminal_thr;
	std::thread itemglow_thr;
	while(active)
	{
		if(apex_mem.get_proc_status() != process_status::FOUND_READY)
		{
			if(aim_t)
			{
				aim_t = false;
				actions_t = false;
				cactions_t = false;
				updateInsideValue_t = false;
				terminal_t = false;
				item_t = false;
				g_Base = 0;

				aimbot_thr.~thread();
				actions_thr.~thread();
				cactions_thr.~thread();
				//Used to change things on a timer
				//updateInsideValue_thr.~thread();
				terminal_thr.~thread();
				itemglow_thr.~thread();
			}

			std::this_thread::sleep_for(std::chrono::seconds(1));
			printf("窃玉偷香,寻花问柳(*^▽^*)...\n");

			apex_mem.open_proc(ap_proc);

			if(apex_mem.get_proc_status() == process_status::FOUND_READY)
			{
				g_Base = apex_mem.get_proc_baseaddr();
				printf("\n此曲只应天上有，人间能得几回闻\n");
				printf("(._.`) %lx\n", g_Base);

				aimbot_thr = std::thread(AimbotLoop);
				actions_thr = std::thread(DoActions);
				cactions_thr = std::thread(ClientActions);
				//Used to change things on a timer
				//updateInsideValue_thr = std::thread(updateInsideValue);
				terminal_thr = std::thread(terminal);
				itemglow_thr = std::thread(item_glow_t);
				aimbot_thr.detach();
				actions_thr.detach();
				cactions_thr.detach();
				//Used to change things on a timer
				//updateInsideValue_thr.detach();
				terminal_thr.detach();
				itemglow_thr.detach();
			}
		}
		else
		{
			apex_mem.check_proc();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	
	return 0;
}
