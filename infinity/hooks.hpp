#pragma once
#include "memory/il2cpp.hpp"
#include "settings.hpp"
#include "offsets.h"
#include <math.h>
#include "Keybind.h"
vector3 m_debugcam_toggle_pos;
vector3 m_debugcam_pos;
typedef void(__fastcall* hk_performance_ui222_)(void*);
hk_performance_ui222_ hk_performance_ui_original;

namespace org
{
	static auto IsConnected = reinterpret_cast<bool (*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("IsConnected"), 0, _(""), _("Network"))));
}
//namespace manipulator {
//	vector3 m_manipulate = vector3::Zero();
//	base_player* local2;
//	void find_manipulate_angle() {
//		vector3 re_p = local2->get_bone_transform((int)rust::classes::Bone_List::head)->get_bone_position() + loco.player->get_transform()->up() * (PlayerEyes::EyeOffset().y + loco.player->player_eyes()->viewoffset().y);
//
//		vector3 choice = vector3::Zero();
//
//		if (unity::is_visible(re_p, local2->get_bone_transform((int)rust::classes::Bone_List::head)->get_bone_position())) {
//			m_manipulate = vector3::Zero();
//			return;
//		}
//		auto realtimeSinceStartup = 0x20B7550;
//		float desyncTime = (realtimeSinceStartup - lastSentTickTime) - 0.03125 * 3;
//		float desync_max_value = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.5f) * local2->MaxVelocity()) - 0.05f;
//		auto right = loco.player->player_eyes()->MovementRight();
//		auto forward = loco.player->player_eyes()->MovementForward();
//		auto _forward = loco.player->player_eyes()->HeadForward();
//
//		std::array<vector3, 10> arr = {
//			vector3(right.x * (desync_max_value / 2), 0.f, right.z),
//			vector3(right.x * desync_max_value, 0.f, right.z),
//
//			vector3(-(right.x * (desync_max_value / 2)), 0.f, -(right.z)),
//			vector3(-(right.x * desync_max_value), 0.f, -(right.z)),
//
//			vector3(0.f, 1.5, 0.f),
//			vector3(1.f, 1.5f, 0.f),
//			vector3(-1.f,1.5f, 0.f),
//			vector3(1.f, 1.2f, 0.1f),
//			vector3(-1.f, 1.2f, 0.1f),
//			vector3(-(forward.x), 0.f, -(forward.z * (desync_max_value / 2))),
//		};
//
//		for (auto s : arr) {
//			vector3 point = re_p + s;
//
//			if (!unity::is_visible(point, re_p))
//				continue;
//
//			if (!unity::is_visible(local2->get_bone_transform((int)rust::classes::Bone_List::head)->get_bone_position(), point))
//				continue;
//
//			choice = s;
//			break;
//		}
//		if (choice.is_empty()) {
//			m_manipulate = vector3::Zero();
//			return;
//		}
//
//		m_manipulate = choice;
//	}
//}
namespace hooks {
	namespace orig {
		static auto baseplayer_client_input = reinterpret_cast<void (*)(base_player*, input_state*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("ClientInput"), -1, _(""), _(""))));
		static auto BaseProjectile_OnSignal = reinterpret_cast<void (*)(base_projectile*, int, rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("OnSignal"), 2, _(""), _(""))));
		static auto playerwalkmovement_client_input = reinterpret_cast<void (*)(playerwalkmovement*, uintptr_t, modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("ClientInput"), -1, _(""), _(""))));
		static auto VisUpdateUsingCulling = reinterpret_cast<void (*)(void*, float, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("VisUpdateUsingCulling"), 1, _(""), _(""))));
		static auto DoFixedUpdate = reinterpret_cast<void (*)(playerwalkmovement*, modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("DoFixedUpdate"), -1, _(""), _(""))));
		static auto blocksprint = reinterpret_cast<void (*)(base_player*, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("BlockSprint"), 1, _(""), _(""))));
		static auto OnNetworkMessage = reinterpret_cast<void (*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("OnNetworkMessage"), 1, _(""), _(""))));

		static auto Run = reinterpret_cast<rust::classes::pUncStr(*)(uintptr_t , rust::classes::pUncStr , DWORD64 )>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ConsoleSystem"), _("Run"), 3, _(""), _(""))));
		uintptr_t playerprojectileattack;
		uintptr_t serverrpc_projectileshoot;
		uintptr_t serverrpc_processattack;
	}

	static auto serverrpc_projecileshoot = rb::pattern::find_rel(//
		_("GameAssembly.dll"), _("4C 8B 0D ? ? ? ? 48 8B 75 28"));

	static auto serverrpc_uint = rb::pattern::find_rel(
		_("GameAssembly.dll"), _("74 3A 4C 8B 0D ? ? ? ? 48 8B CB"));

	static auto set_sprinting = reinterpret_cast<void (*)(modelstate*, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_sprinting"), -1, _(""), _(""))));

	static auto draw_get = reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("Get"), 0, _(""), _("UnityEngine"))));

	static auto set_flying = reinterpret_cast<void (*)(modelstate * model_state, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_flying"), 1, _(""), _(""))));
	static auto line = reinterpret_cast<void (*)(vector3, vector3, gui222::Color, float, bool, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("Line"), 0, _(""), _("UnityEngine"))));

	static auto GetSpeed = reinterpret_cast<float (*)(base_player * baseplayer, float running, float ducking)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetSpeed"), 2, _(""), _(""))));

	static auto get_ducked = reinterpret_cast<bool (*)(modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("get_ducked"), 0, _(""), _(""))));

	static auto IsSwimming = reinterpret_cast<bool (*)(base_player*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("IsSwimming"), 0, _(""), _(""))));

	static auto ServerRPC = reinterpret_cast<void (*)(uintptr_t, rust::classes::string funcName)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("ServerRPC"), 1, _("funcName"), _(""), 1)));

	static auto OnLand = reinterpret_cast<void (*)(base_player*, float fVelocity)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("OnLand"), 1, _("fVelocity"), _(""), 1)));

	static auto change_code_rpc = reinterpret_cast<void (*)(base_player*, rust::classes::string, uintptr_t, bool, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_string_bool_Address); //BaseEntity$$ServerRPC<string, bool> Address

	static auto ServerRPC_int = reinterpret_cast<void (*)(base_projectile*, rust::classes::string funcName, unsigned int arg1, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_uint_);

	static auto DoHit = reinterpret_cast<bool (*)(base_projectile*, HitTest*, vector3, vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("DoHit"), 4, _(""), _(""))));

	void init_hooks() {
		orig::Run = reinterpret_cast<rust::classes::pUncStr(*)(uintptr_t, rust::classes::pUncStr, DWORD64)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ConsoleSystem"), _("Run"), 3, _(""), _(""))));

		org::IsConnected = reinterpret_cast<bool (*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("IsConnected"), 0, _(""), _("Network"))));
		orig::OnNetworkMessage = reinterpret_cast<void (*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("OnNetworkMessage"), 1, _(""), _(""))));
		orig::BaseProjectile_OnSignal = reinterpret_cast<void (*)(base_projectile*, int, rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("OnSignal"), 2, _(""), _(""))));
		orig::baseplayer_client_input = reinterpret_cast<void (*)(base_player*, input_state*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("ClientInput"), -1, _(""), _(""))));
		orig::playerwalkmovement_client_input = reinterpret_cast<void (*)(playerwalkmovement*, uintptr_t, modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("ClientInput"), -1, _(""), _(""))));
		orig::VisUpdateUsingCulling = reinterpret_cast<void (*)(void*, float, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("VisUpdateUsingCulling"), -1, _(""), _(""))));
		orig::DoFixedUpdate = reinterpret_cast<void (*)(playerwalkmovement*, modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("DoFixedUpdate"), -1, _(""), _(""))));
		orig::blocksprint = reinterpret_cast<void (*)(base_player*, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("BlockSprint"), 1, _(""), _(""))));
		serverrpc_projecileshoot = rb::pattern::find_rel(
			_("GameAssembly.dll"), _("4C 8B 0D ? ? ? ? 48 8B 75 28"));

		serverrpc_uint = rb::pattern::find_rel(
			_("GameAssembly.dll"), _("74 3A 4C 8B 0D ? ? ? ? 48 8B CB"));

		ServerRPC_int = reinterpret_cast<void (*)(base_projectile*, rust::classes::string funcName, unsigned int arg1, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_uint_);

		change_code_rpc = reinterpret_cast<void (*)(base_player*, rust::classes::string, uintptr_t, bool, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_string_bool_Address);

		set_sprinting = reinterpret_cast<void (*)(modelstate*, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_sprinting"), -1, _(""), _(""))));

		draw_get = reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("Get"), 0, _(""), _("UnityEngine"))));

		set_flying = reinterpret_cast<void (*)(modelstate * model_state, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_flying"), 1, _(""), _(""))));

		GetSpeed = reinterpret_cast<float (*)(base_player * baseplayer, float running, float ducking)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetSpeed"), 2, _(""), _(""))));

		get_ducked = reinterpret_cast<bool (*)(modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("get_ducked"), 0, _(""), _(""))));

		IsSwimming = reinterpret_cast<bool (*)(base_player*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("IsSwimming"), 0, _(""), _(""))));

		ServerRPC = ServerRPC = reinterpret_cast<void (*)(uintptr_t, rust::classes::string funcName)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("ServerRPC"), 1, _("funcName"), _(""), 1)));

		OnLand = reinterpret_cast<void (*)(base_player*, float fVelocity)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("OnLand"), 1, _("fVelocity"), _(""), 1)));

		DoHit = reinterpret_cast<bool (*)(base_projectile*, HitTest*, vector3, vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("DoHit"), 4, _(""), _(""))));
	}

	double CalcBulletDrop(double height, double DepthPlayerTarget, float velocity, float gravity) {
		double pitch = (vector3::my_atan2(height, DepthPlayerTarget));
		double BulletVelocityXY = velocity * vector3::my_cos(pitch);
		double Time = DepthPlayerTarget / BulletVelocityXY;
		double TotalVerticalDrop = (0.5f * gravity * Time * Time);
		return TotalVerticalDrop * 10;
	}

	void Prediction(vector3 local, vector3& target, vector3 targetvel, float bulletspeed, float gravity) {
		float Dist = local.get_3d_dist(target);
		float BulletTime = Dist / bulletspeed;

		vector3 vel = vector3(targetvel.x, 0, targetvel.z) * 0.75f;

		vector3 PredictVel = vel * BulletTime;

		target += PredictVel;

		double height = target.y - local.y;
		vector3 dir = target - local;
		float DepthPlayerTarget = vector3::my_sqrt(powFFFFFFFFFFFFFFFFFFFFFF(dir.x) + powFFFFFFFFFFFFFFFFFFFFFF(dir.z));

		float drop = CalcBulletDrop(height, DepthPlayerTarget, bulletspeed, gravity);

		target.y += drop;
	}

#pragma optimize("", off)
#pragma code_seg(".text")
	inline int64_t get_rbx_value()
	{
		static __declspec(allocate(".text")) char fn_stub[] = {
			0x48,
			0x89,
			0xD8, // mov    rax,rbx
			0xc3 // ret
		};

		return ((int64_t(*)())(&fn_stub))();
	}
#pragma code_seg(pop)
#pragma optimize("", on)

	uintptr_t game_object;
	void hk_performance_ui_update(void* instance)
	{
		if (gui::wakeup)
		{
			game_object = il2cpp::methods::object_new(il2cpp::init_class("GameObject", "UnityEngine"));
			gui::methods::create_with_shader_fn(game_object, Find(_(L"Hidden/Internal-Colored")));
			SetInt(game_object, _(L"_SrcBlend"), 5);
			SetInt(game_object, _(L"_DstBlend"), 10);
			SetInt(game_object, _(L"_Cull"), 0);
			SetInt(game_object, _(L"_ZWrite"), 0);
			//	gui::methods::AddComponent(il2cpp::init_class("", "DevControls")); // UnityEngine.GameObject::AddComponent
			gui::methods::dont_destroy_on_load(game_object);
			gui::wakeup = false;
		}

		return hk_performance_ui_original(instance);
	}
	//////////////////////////
	///////// PSILENT ////////
	//////////////////////////
	void hk_serverrpc_playerprojectileattack(int64_t rcx, int64_t rdx, int64_t r9, int64_t _ppa, int64_t arg5) {
		auto        projectile = reinterpret_cast<base_projectile*>(get_rbx_value());
		auto  ppa = reinterpret_cast<rust::classes::PlayerProjectileAttack*>(_ppa);
		auto& attack = ppa->playerAttack->attack;

		const auto orig_fn =
			reinterpret_cast<void (*)(int64_t, int64_t, int64_t, int64_t, int64_t)>(
				hooks::orig::playerprojectileattack);

		auto camera_pos = unity::get_camera_pos();
		if (camera_pos.is_empty())
			return orig_fn(rcx, rdx, r9, _ppa, arg5);

		do {
			if (!esp::local_player)
				break;

			auto hit_test = projectile->get_hit_test();
			if (!hit_test)
				break;

			if (!hit_test->get_gameobject())
				break;

			auto layer = hit_test->get_gameobject()->get_layer();
			auto prefab_name = hit_test->get_gameobject()->get_prefab_name();

			aim_target target = esp::local_player->get_aimbot_target(camera_pos);

			if (!target.player || !target.network_id)
				break;

			auto& hit_entity = hit_test->get_hit_entity();
			if (layer == rust::classes::layer::Player_Server) {
				if (hit_entity->is_teammate(esp::local_player)) {
					hit_test->set_ignore_entity(hit_entity);
					return;
				}
			}

			if (!settings::weapon::hitbox_override && !settings::weapon::random_hitbox && !settings::weapon::magic_bullet)
				break;

			if (hit_entity != target.player && settings::weapon::magic_bullet) {
				const auto hitdist_from_ent = attack->hitPositionLocal.get_3d_dist(target.pos);

				if (hitdist_from_ent > 2.5f)
					break;
				else {
					hit_entity = target.player;
					attack->hitID = target.network_id;
				}
			}
			else if (hit_entity != target.player && !settings::weapon::magic_bullet)
				break;


			if (!target.is_heli && settings::weapon::hitbox_override) {
				attack->hitBone = 698017942;
				attack->hitPartID = 2173623152;
				attack->hitPositionLocal = { -.1f, -.1f, 0 };
				attack->hitNormalLocal = { 0, -1, 0 };
			}
			else if (!target.is_heli && settings::weapon::random_hitbox) {
				switch (my_rand() % 4) {
				case 0: // Head
					attack->hitBone = 698017942;
					attack->hitPartID = 2173623152;
					break;
				case 1: // Chest
					attack->hitBone = 1031402764;
					attack->hitPartID = 1750816991;
					break;
				case 2: // LHand
					attack->hitBone = 182688154;
					attack->hitPartID = 1750816991;
					break;
				case 3: // RHand
					attack->hitBone = 102231371;
					attack->hitPartID = 1750816991;
					break;
				}
				attack->hitPositionLocal = { -.1f, -.1f, 0 };
				attack->hitNormalLocal = { 0, -1, 0 };
			}
			else {
				auto weakspots = target.player->get_weakspots();
				if (!weakspots)
					break;

				auto size = *reinterpret_cast<uintptr_t*>(weakspots + 0x18);

				bool tail_alive = false;
				bool main_alive = false;
				for (int i = 0; i < size; i++) {
					auto weakspot = *(uintptr_t*)(weakspots + 0x20 + i * 0x8);
					if (!weakspot)
						continue;
					auto health = *reinterpret_cast<float*>(weakspot + 0x24);
					if (health > 0) {
						if (i == 0) {
							main_alive = true;
						}
						else {
							tail_alive = true;
						}
					}
				}

				if (tail_alive) {
					attack->hitBone = 2699525250;
					attack->hitPartID = 2306822461;
					attack->hitPositionLocal = { .9f, -.4f, .1f };
					attack->hitNormalLocal = { .9f, -.4f, .1f };
				}
				else if (main_alive) {
					attack->hitBone = 224139191;
					attack->hitPartID = 2306822461;
					attack->hitPositionLocal = { .9f, -.4f, .1f };
					attack->hitNormalLocal = { .9f, -.4f, .1f };
				}
			}
		} while (0);

		return orig_fn(rcx, rdx, r9, _ppa, arg5);
	}
	void hk_serverrpc_projectileshoot(int64_t rcx, int64_t rdx, int64_t r9, int64_t projectileShoot, int64_t arg5) {
		do {
			if (!esp::local_player)
				break;

			auto weapon = esp::local_player->get_active_weapon();

			if (!weapon)
				break;

			auto baseprojectile = esp::local_player->get_active_weapon()->get_base_projetile();
			if (!baseprojectile)
				break;

			auto wep_class_name = *(const char**)(*(uintptr_t*)(uintptr_t)baseprojectile + 0x10);
			if (*(int*)(wep_class_name + 4) == 'eleM' || *(int*)(wep_class_name) == 'ddaP')
				break;

			base_projectile* projectile_list = *reinterpret_cast<base_projectile**>(
				*reinterpret_cast<uintptr_t*>((uintptr_t)baseprojectile + 0x358) + 0x10); //createdProjectiles;

			esp::matrix = unity::get_view_matrix();
			auto camera_pos = unity::get_camera_pos();

			aim_target target = esp::local_player->get_aimbot_target(camera_pos);

			uintptr_t shoot_list = *(uintptr_t*)(*(uintptr_t*)(projectileShoot + 0x18) + 0x10);

			auto size = *(int*)(*(uintptr_t*)(projectileShoot + 0x18) + 0x18);

			vector3 aimbot_velocity;

			const auto stats = baseprojectile->get_stats(weapon->get_item_definition_id());

			vector3 aim_angle;
			vector3 rpc_position;



			for (int i = 0; i < size; i++) {
				auto projectile = *(uintptr_t*)(shoot_list + 0x20 + i * 0x8);

				rpc_position = *reinterpret_cast<vector3*>(projectile + 0x18);
				auto original_vel = *reinterpret_cast<vector3*>(projectile + 0x24);

				if (target.player && target.visible && !target.teammate) {

					vector3 m_vecTarget = target.pos - vector3(0.0f, 0.2f, 0.0f);
					Prediction(rpc_position, m_vecTarget, target.velocity, original_vel.Length(), stats.gravity_modifier);

					aim_angle = m_vecTarget - rpc_position;

					aimbot_velocity = (aim_angle).Normalized() * original_vel.Length();

					*reinterpret_cast<vector3*>(projectile + 0x24) = aimbot_velocity;
				}
			}

			for (int i = 0; i < projectile_list->get_size(); i++) {
				auto projectile = *(base_projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);

				if (!projectile)
					continue;
				if (target.visible) {
					if (settings::weapon::psilent) {
						if (target.player && !target.teammate) {
							if (!settings::weapon::psilentvis || target.visible) {
								projectile->set_current_velocity(aimbot_velocity);
							}
						}
					}
				}


				if (settings::weapon::mods) {

					auto ItemModProjectile = projectile->get_item_mod_projectile();

					ItemModProjectile->projectileSpread() = 0;
					ItemModProjectile->projectileVelocitySpread() = 0;
				}

				if (settings::weapon::thick_bullet)
					projectile->set_projectile_thickness(settings::weapon::thickness);
				else
					projectile->set_projectile_thickness(projectile->thickness);


			}
		} while (0);

		reinterpret_cast<void (*)(int64_t, int64_t, int64_t, int64_t, int64_t)>(hooks::orig::serverrpc_projectileshoot)(rcx, rdx, r9, projectileShoot, arg5);
	}

	bool is_lagging;

	bool flying = false, is_speeding = false;

	bool has_intialized_methods = false;

	float nextActionTime = 0, period = 1.4721;


#define ptr_assert(val) \
    if(val == 0)        \
    return

	uintptr_t client_entities;
	//private bool swimming; 
	//	private float <Ducking>k__BackingField;
	//private bool jumping;
	void hk_dofixedupdate(playerwalkmovement* base_movement, modelstate* modelstate) {
		float speed = (safe_read(base_movement + 0x146, bool) /*swim*/ || safe_read(base_movement + 0x44, float) /* crouch */ > 0.5f) ? 1.7f : (safe_read(base_movement + 0x148, bool) /*jump*/ ? 8.f : 5.5f);// playermovmen
		vector3 vel = safe_read(base_movement + 0x34, vector3);
		speed = max(speed, vel.Length());
		if (settings::misc::always_sprint) {
			float len = vel.Length();
			if (len > 0.f) {
				vel = vector3(vel.x / len * speed, vel.y, vel.z / len * speed);
				safe_write(base_movement + 0x34, vel, vector3);
			}
			modelstate->set_flag(rust::classes::ModelState_Flag::Sprinting);
		}

		orig::DoFixedUpdate(base_movement, modelstate);
	}

	void hk_blocksprint(base_player* player, float duration) {
		if (!settings::weapon::always_shoot && settings::misc::Movement)
			return hooks::orig::blocksprint(player, duration);

		return;
	}
	void get_skydome()
	{
		uintptr_t m_skydome = NULL;
		uintptr_t m_camera = NULL;
		uintptr_t last_object = NULL;
		{
			auto gom = mem::read<uintptr_t>(mem::unity_player_base + 0x17C1F18);
			auto current_tagged_base = mem::read<uintptr_t>(gom + 0x08);
			auto current_tagged_obj = mem::read<uintptr_t>(current_tagged_base + 0x10);

			while (current_tagged_obj &&
				current_tagged_obj != last_object &&
				(!m_skydome || !m_camera)) {
				INT16 tag = mem::read<uintptr_t>(current_tagged_obj + 0x54);

				if (!m_camera) {
					if (tag == 5) {
						uintptr_t objClass = mem::read<uintptr_t>(current_tagged_obj + 0x30);

						uintptr_t ent = mem::read<uintptr_t>(objClass + 0x18);

						m_camera = mem::read<uintptr_t>(current_tagged_obj + 0x18);
					}
				}


				if (!m_skydome)
				{
					if (tag == 20011) {
						uint64_t p = mem::read<uint64_t>(current_tagged_obj + 0x30);
						uint64_t p1 = mem::read<uint64_t>(p + 0x18);
						uint64_t p2 = mem::read<uint64_t>(p1 + 0x28);

						const auto TOD_Day = *reinterpret_cast<uintptr_t*>(p2 + 0x50);
						const auto TOD_Night = *reinterpret_cast<uintptr_t*>(p2 + 0x58);
						const auto TOD_Stars = *reinterpret_cast<uintptr_t*>(p2 + 0x70);
						if (settings::misc::brightnight) {
							*(float*)(TOD_Night + 0x50) = 4.f;
							*(float*)(TOD_Night + 0x54) = 1.f;
							*(float*)(TOD_Day + 0x50) = 1.f;
							*(float*)(TOD_Day + 0x54) = 1.f;
							*(float*)(TOD_Stars + 0x14) = settings::misc::staramount;
						}


						m_skydome = mem::read<uintptr_t>(current_tagged_obj + 0x18);
					}
				}
				last_object = current_tagged_obj;
				current_tagged_base = mem::read<uintptr_t>(current_tagged_base + 0x8);
				current_tagged_obj = mem::read<uintptr_t>(current_tagged_base + 0x10);
			}
		}
	}


	void hk_FakeVisUpdateUsingCulling(void* baseplayer, float dist, bool visibility = false)
	{
		if (settings::visuals::chams)
			return orig::VisUpdateUsingCulling(baseplayer, 300.f, true);

		return orig::VisUpdateUsingCulling(baseplayer, dist, visibility);
	}
	void hk_playerwalkmovement_ClientInput(playerwalkmovement* player_walk_movement, uintptr_t inputstate, modelstate* model_state) {
		orig::playerwalkmovement_client_input(player_walk_movement, inputstate, model_state);

		set_sprinting(model_state, true);

		flying = player_walk_movement->get_flying();

		if (!keybinds::silentwalkb || unity::GetKey(keybinds::silentwalkk)) {
			if (settings::misc::silentwalk) {
				set_onLadder(model_state, true);
			}
		}
		model_state->remove_flag(rust::classes::ModelState_Flag::Flying);
	}
	//rust::classes::pUncStr __fastcall Run(uintptr_t options, rust::classes::pUncStr strCommand, DWORD64 args) {
	//	bool IsFromServer = mem::read<bool>(options + 0x6);
	//	if (IsFromServer) {
	//		std::wstring cmd = std::wstring(strCommand->str);
	//		if (cmd.find(L"noclip") != std::wstring::npos || cmd.find(L"debugcamera") != std::wstring::npos || cmd.find(L"camspeed") != std::wstring::npos || cmd.find(L"admintime") != std::wstring::npos) {
	//			strCommand = nullptr;
	//		}
	//	}
	//	return hooks::orig::Run(options, strCommand, args);
	///* original_consolerun(options, strCommand, args);*/
	//}

	uintptr_t do_fixed_update_ptr, client_input_ptr,run;

	void hk_baseplayer_ClientInput(base_player* baseplayer, input_state* state) {
		//if (settings::misc::rayleigh_changer) {
		//	reinterpret_cast<void(__fastcall*)(float)>(settings::gBase + 0x392BB0)(settings::misc::rayleigh); // public static void set_atmosphere_rayleigh(float value) { }
		//}

		if (!do_fixed_update_ptr)
			do_fixed_update_ptr = mem::hook_virtual_function(_("PlayerWalkMovement"), _("DoFixedUpdate"), &hk_dofixedupdate);
		
		if(!client_input_ptr)
			client_input_ptr = mem::hook_virtual_function(_("PlayerWalkMovement"), _("ClientInput"), &hk_playerwalkmovement_ClientInput);\

		//if (!run)
		//	run = mem::hook_virtual_function(_("ConsoleSystem"), _("Run"), &hooks::Run);
		//if (settings::misc::rayleigh_changer) {
		//	reinterpret_cast<void(__fastcall*)(float)>(Vars::User::gBase + 0x392BB0)(settings::misc::rayleigh);
		//}

		if (!has_intialized_methods) {
			auto il2cpp_codegen_initialize_method = reinterpret_cast<void (*)(unsigned int)>(il2cpp::methods::intialize_method);
			//56229 for real rust or 56204 for cracked rust
			for (int i = 0; i <
#ifdef cracked_rust
				56204
#else
				56229
#endif
				; i++) {
				il2cpp_codegen_initialize_method(i);
			}
			has_intialized_methods = true;
		}

		static uintptr_t* serverrpc_projecshoot;
		if (!serverrpc_projecshoot) {
			auto method_serverrpc_projecshoot = *reinterpret_cast<uintptr_t*>(hooks::serverrpc_projecileshoot);

			if (method_serverrpc_projecshoot) {
				serverrpc_projecshoot = **(uintptr_t***)(method_serverrpc_projecshoot + 0x30);

				hooks::orig::serverrpc_projectileshoot = *serverrpc_projecshoot;
		
				*serverrpc_projecshoot = reinterpret_cast<uintptr_t>(&hooks::hk_serverrpc_projectileshoot);
			}
		}

		static uintptr_t* serverrpc_playerprojectileattack;
		if (!serverrpc_playerprojectileattack) {
			auto method_serverrpc_playerprojectileattack = *reinterpret_cast<uintptr_t*>(mem::game_assembly_base + offsets::Method$BaseEntity_ServerRPC_PlayerProjectileAttack___);//Method$BaseEntity_ServerRPC_PlayerProjectileAttack___

			if (method_serverrpc_playerprojectileattack) {
				serverrpc_playerprojectileattack = **(uintptr_t***)(method_serverrpc_playerprojectileattack + 0x30);

				hooks::orig::playerprojectileattack = *serverrpc_playerprojectileattack;

				*serverrpc_playerprojectileattack = reinterpret_cast<uintptr_t>(&hooks::hk_serverrpc_playerprojectileattack);
			}
		}
		if (baseplayer) {
			get_skydome();


			if (settings::misc::attack_on_mountables) {
				auto mountable = baseplayer->get_mountable();
				if (mountable)
					mountable->canwielditem() = true;
			}

			bool kyslol = false;

			if (settings::misc::TakeFallDamage && unity::GetKey(rust::classes::KeyCode::P)) {

					OnLand(baseplayer, -8.0001f - 100);
			}



			if (settings::misc::admin_mode)
				baseplayer->set_admin_flag(rust::classes::PlayerFlags::IsAdmin);

			if (settings::misc::spiderman && settings::misc::Movement) {
				baseplayer->SpiderMan();

			}

			if (settings::misc::playerfovtoggle) {
				baseplayer->fov();

			}
			if (settings::misc::CustomTime) {
				baseplayer->Admintime();
			}

			weapon* Weapon = baseplayer->GetActiveWeapon();
			DWORD64 active = Weapon->entity();
			char* classname = Weapon->ClassName();
			//if (active && settings::misc::weapon_spam) {
			//	if (unity::GetKey(rust::classes::KeyCode::F) && !baseplayer->IsMenu()) {
			//		reinterpret_cast<void(*)(uintptr_t, rust::classes::Signal, str)>(mem::game_assembly_base + 0x890E80)(active, rust::classes::Signal::Attack, str(_(L"")));
			//	}
			//}

			if (!keybinds::fakelagb || unity::GetKey(keybinds::fakelagk)) {
				if (!is_lagging && !flying && settings::misc::fake_lag && !is_speeding) {
					baseplayer->set_client_tick_interval(0.5f);
					is_lagging = true;
				}
			}
			else if (is_lagging && flying || is_lagging && is_speeding) {
				esp::local_player->set_client_tick_interval(0.03f);
				is_lagging = false;
			}
			else if (is_lagging && !settings::misc::fake_lag) {
				esp::local_player->set_client_tick_interval(0.03f);
				is_lagging = false;
			}


			if (auto movement = baseplayer->get_movement()) {
				if (settings::misc::spiderman) {
					movement->set_ground_angles_new(0);

				}

			}

			if (settings::misc::eyeoffset) {
				baseplayer->Giraffe();

			}

			if (auto movement = baseplayer->get_movement()) {
				if (settings::misc::infinite_jump && settings::misc::Movement) {
					movement->set_land_time(0);
					movement->set_jump_time(0);
					movement->set_ground_time(100000);
				}

				if (settings::misc::gravity && settings::misc::Movement)
					movement->set_gravity_multiplier(1.75f);
				else
					movement->set_gravity_multiplier(2.35f);

				if (settings::weapon::always_shoot && settings::misc::Movement) {
					if (auto modelstate = baseplayer->get_model_state()) {
						modelstate->set_flag(rust::classes::ModelState_Flag::OnGround);
						mem::write<float>((uint64_t)movement + 0x4C, 1); //private float <Grounded>k__BackingField; // 0x4C
					}
				}
			}
			if (settings::misc::brightnight) {
				if (auto modelstate = baseplayer->get_model_state()) {
					modelstate->set_flag(rust::classes::ModelState_Flag::Sleeping);
				}
			}
			auto item = baseplayer->get_active_weapon();

			if (settings::misc::auto_lock) {
				auto closest_ent = baseplayer->resolve_closest_entity(3);

				auto addr = mem::read<uintptr_t>(mem::game_assembly_base + offsets::Method_BaseEntity_ServerRPC_string_bool_address); //Method$BaseEntity.ServerRPC<string, bool>() address

				if (closest_ent.first.found && addr) {
					if (closest_ent.second) {
						auto code_str = string::format(_("%d"), (int)settings::misc::code_lock_code);
						change_code_rpc(closest_ent.first.player, rust::classes::string(_(L"RPC_ChangeCode")), il2cpp::methods::new_string(code_str), false, addr);
						ServerRPC((uintptr_t)closest_ent.first.player, rust::classes::string(_(L"TryLock")));
						ServerRPC((uintptr_t)closest_ent.first.player, rust::classes::string(_(L"RPC_Lock")));
					}
					else
						ServerRPC((uintptr_t)closest_ent.first.player, rust::classes::string(_(L"RPC_Lock")));
				}
			}

			if (!keybinds::speedkeyb || unity::GetKey(keybinds::speedhackk)) {
				if (settings::misc::speedhack) {
					set_timeScale(settings::misc::speedhackspeed);
					is_speeding = true;
				}
			}
			else {
				set_timeScale(1);
				is_speeding = false;
			}

			if (item) {
				auto baseprojectile = item->get_base_projetile();
				if (baseprojectile) {
					auto wep_class_name = *(const char**)(*(uintptr_t*)(uintptr_t)baseprojectile + 0x10);

					auto attack = [&](aim_target target, bool is_tree) {
						auto gathering = baseprojectile->Gathering();

						if (is_tree) {
							if (!(gathering->tree()->gatherDamage() > 1)) {
								return;
							}
						}
						else {
							if (!(gathering->ore()->gatherDamage() > 1)) {
								return;
							}
						}

						attack_melee(target, baseprojectile);
					};

					if (settings::misc::silent_farm) {
						auto entity = baseplayer->resolve_closest_entity(3, false);
						if (entity.first.found && entity.first.player) {
							if (*(int*)(wep_class_name + 4) == 'eleM' || *(int*)(wep_class_name + 4) == 'mmah') {
								attack(entity.first, entity.second);
							}
						}
					}

					if (!(*(int*)(wep_class_name + 4) == 'eleM' && *(int*)(wep_class_name) == 'esaB')) {
						if (unity::GetKey(rust::classes::KeyCode::Mouse0) && settings::misc::instant_med) {
							const auto item_id = item->get_item_definition_id();

							if (item_id == 1079279582 || item_id == -2072273936) {
								auto time = get_time();
								if (baseprojectile->get_time_since_deploy() > baseprojectile->get_deploy_delay() && baseprojectile->get_next_attack_time() <= get_time()) {
									if (time > nextActionTime) {
										nextActionTime = time + period;
										ServerRPC((uintptr_t)baseprojectile, rust::classes::string(_(L"UseSelf")));
									}
								}
							}
						}
						else if (unity::GetKey(rust::classes::KeyCode::Mouse1) && settings::misc::instant_med) {
							const auto item_id = item->get_item_definition_id();

							if (item_id == 1079279582 || item_id == -2072273936) {
								esp::matrix = unity::get_view_matrix();
								auto camera_pos = unity::get_camera_pos();

								auto target = baseplayer->get_aimbot_target(camera_pos);

								if (target.player && target.distance < 5) {
									auto net = target.player->get_networkable();
									if (net) {
										auto id = net->get_id();
										if (id) {

											auto method_addr = mem::read<uintptr_t>(mem::game_assembly_base + offsets::Method$BaseEntity_ServerRPC_uint);
											if (method_addr) {
												auto time = get_time();
												if (baseprojectile->get_time_since_deploy() > baseprojectile->get_deploy_delay() && baseprojectile->get_next_attack_time() <= get_time()) {
													if (time > nextActionTime) {
														nextActionTime = time + period;
														ServerRPC_int(baseprojectile, rust::classes::string(_(L"UseOther")), id, method_addr);
													}
												}
											}
										}
									}
								}
							}
						}

						//////weapon mods/////
						if (*(int*)(wep_class_name) == 'esaB' && *(int*)(wep_class_name + 4) == 'jorP' || *(int*)(wep_class_name) == 'nilF') {
							if (item->is_weapon()) {
								const auto item_id = item->get_item_definition_id();
								DWORD64 heldentity = item->entity();
								//reinterpret_cast<void(*)(uintptr_t, rust::classes::Signal, Str)>(SendSignalBroadcast)(item, rust::classes::Signal::Attack, _(L""));

								switch (item_id) {
								case -75944661:
									if (settings::weapon::eoka)
											mem::write<bool>(heldentity + 0x370, true);
									break;
								//case -0x5A9F:
								//	if (settings::weapon::fastbow)
								//		mem::write<bool>(heldentity + 0x360, 1);
								//	else
								//		mem::write<float>(heldentity + 0x364, 3.f);
								//	break;
								default:	
										if (settings::weapon::magic_fire) 
											mem::write<float>(heldentity + repeatDelay, 0.02f);
										else
											mem::write<float>(heldentity + repeatDelay, 0.13f);
										if (settings::weapon::rapid_fire)
											mem::write<float>(heldentity + repeatDelay, 0.09f);
										if (settings::weapon::automatic)
											baseprojectile->is_automatic() = true;
										if (settings::weapon::nospread)
											baseprojectile->set_no_spread();
										if (settings::weapon::norecoil)
											baseprojectile->set_recoil(0, 0, 0, 0);
										if (settings::weapon::legit_recoil)
											baseprojectile->set_recoil(1, 1, -1, 0);
										if (settings::weapon::nosway)
											baseprojectile->set_no_sway();

									if (settings::weapon::magic_bullet)
										baseprojectile->projectileVelocityScale() = 0.5f;
									break;
									
								}
							}
						}
					}
				}
			}

			if (settings::misc::instant_revive) {
				auto target = baseplayer->get_aimbot_target(unity::get_camera_pos());
				if (!target.is_heli && target.player && target.distance <= 5 && target.teammate && target.player->get_health() <= 4 && target.visible)
					ServerRPC((uintptr_t)target.player, rust::classes::string(_(L"RPC_Assist")));
			}

			unity::IgnoreLayerCollision(rust::classes::layer::PlayerMovement, rust::classes::layer::Water, !settings::misc::no_playercollision);
			unity::IgnoreLayerCollision(rust::classes::layer::PlayerMovement, rust::classes::layer::Tree, settings::misc::no_playercollision);
			unity::IgnoreLayerCollision(rust::classes::layer::PlayerMovement, rust::classes::layer::AI, settings::misc::no_playercollision);

			draw_get();

			auto tick_time = baseplayer->get_last_sent_ticket_time();
			if (tick_time > gui::tick_time_when_called + 10) {
				unity::camera = unity::get_main_camera();
				gui::tick_time_when_called = tick_time;
			}
		}

		orig::baseplayer_client_input(baseplayer, state);

		auto model_state = baseplayer->get_model_state();

		//model_state->set_water_level(99999);

		if (settings::misc::spinbot) {
			state->set_aim_angles(vector3(100, my_rand() % 999 + -999, 100));
		}
		if (settings::misc::rayleigh_changer) {
			reinterpret_cast<void(__fastcall*)(float)>(mem::game_assembly_base + 0x392BB0)(settings::misc::rayleigh);
		}

	}
}