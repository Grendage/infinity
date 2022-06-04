#pragma once
#include <array>
#include <cstdint>

#include "../../memory/il2cpp.hpp"
#include "../../settings.hpp"

#include "../classes.hpp"
#include "../rust.hpp"
namespace gui222
{
	class Color {
	public:
		float r;
		float g;
		float b;
		float a;

		Color()
		{
			r = 0;
			g = 0;
			b = 0;
			a = 0;
		}

		Color(float r, float g, float b, float a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		Color GetUnityColor()
		{
			return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
		}
	};
	
}

namespace esp {
	uintptr_t client_entities;
	base_player* local_player;
	VMatrix matrix;

	struct bounds_t {
		float left, right, top, bottom;
	};

	struct rust_str
	{
		char zpad[ 128 ];
	};

	bool out_w2s(const vector3& position, vector2& screen_pos) {
		if (!matrix.m) {
			return false;
		}

		vector2 out;
		const auto temp = matrix.transpose( );

		auto translation_vector = vector3{temp[ 3 ][ 0 ], temp[ 3 ][ 1 ], temp[ 3 ][ 2 ]};
		auto up = vector3{temp[ 1 ][ 0 ], temp[ 1 ][ 1 ], temp[ 1 ][ 2 ]};
		auto right = vector3{temp[ 0 ][ 0 ], temp[ 0 ][ 1 ], temp[ 0 ][ 2 ]};

		float w = translation_vector.dot(position) + temp[ 3 ][ 3 ];

		if (w < 0.098f) {
			return false;
		}

		float x = up.dot(position) + temp._24;
		float y = right.dot(position) + temp._14;

		out.x = (static_cast<float>(unity::get_width( )) / 2) * (1 + y / w);
		out.y = (static_cast<float>(unity::get_height( )) / 2) * (1 - x / w);

		screen_pos = out;

		return true;
	}

	void draw_heli(float x, float y, float w, float h);

	void draw_tool_cupboard(vector2 w2s_position, wchar_t* label, gui222::Color color, rust::list<PlayerNameID*>* authorizedPlayers_list);

	void draw_item(vector2 w2s_position, wchar_t* label, gui222::Color color, wchar_t* name = _(L""));

	void draw_player(base_player* player, bool is_npc);
	void draw_target_hotbar(aim_target target);
	void draw_name(vector3 position, wchar_t* name);



	void draw_weapon_icon(weapon* item, vector2 w2s_position);

	uintptr_t shader;

	void iterate_players(bool draw = true) {
		aim_target best_target = aim_target( );

		auto get_client_entities = [ & ]( ) {
			client_entities = il2cpp::value(_("BaseNetworkable"), _("clientEntities"), false);
		};
		if (!client_entities)
			get_client_entities( );

		rust::classes::list* entity_list = (rust::classes::list*)client_entities;

		auto list_value = entity_list->get_value<uintptr_t>( );
		if (!list_value) {
			get_client_entities( );
			return;
		}

		auto size = entity_list->get_size( );
		if (!size) {
			get_client_entities( );
			return;
		}

		auto buffer = entity_list->get_buffer<uintptr_t>( );
		if (!buffer) {
			get_client_entities( );
			return;
		}

		for (int i = 0; i <= size; i++) {
			auto current_object = *reinterpret_cast<uintptr_t*>(buffer + 0x20 + (i * 0x8));
			if (!current_object || current_object <= 100000)
				continue;

			auto base_object = *reinterpret_cast<uintptr_t*>(current_object + 0x10);
			if (!base_object || base_object <= 100000)
				continue;

			auto object = *reinterpret_cast<uintptr_t*>(base_object + 0x30);
			if (!object || object <= 100000)
				continue;

			WORD tag = *reinterpret_cast<WORD*>(object + 0x54);

			auto do_melee_attack = [ & ](base_projectile* baseprojectile)
			{
				auto ent = *reinterpret_cast<uintptr_t*>(base_object + 0x28);

				auto ent_class = *reinterpret_cast<uintptr_t*>(ent);
				auto entity_class_name = (char*)*reinterpret_cast<uintptr_t*>(ent_class + 0x10);

				auto attack = [ & ](bool is_tree) {
					auto _class = *reinterpret_cast<uintptr_t*>(base_object + 0x30);

					auto game_object = *reinterpret_cast<uintptr_t*>(_class + 0x30);

					auto transform = *reinterpret_cast<uintptr_t*>(game_object + 0x8);
					auto visual_state = *reinterpret_cast<uintptr_t*>(transform + 0x38);


					auto world_position = *reinterpret_cast<vector3*>(visual_state + 0x90);

					auto local = ClosestPoint(esp::local_player, world_position);
					if (local.get_3d_dist(world_position) >= 5)
						return;

					auto gathering = baseprojectile->Gathering( );

					if (is_tree) {
						if (!(gathering->tree( )->gatherDamage( ) > 1)) {
							return;
						}
					}
					else {
						if (!(gathering->ore( )->gatherDamage( ) > 1)) {
							return;
						}
					}

					aim_target target;

					target.pos = world_position;
					target.player = (base_player*)ent;
					target.visible = true;
					attack_melee(target, baseprojectile);
				};

				auto name = *(int*)(entity_class_name);

				if (name == 'eerT') {
					attack(true);
				}
				else if (name == 'HerO') {
					attack(false);
				}
			};

			auto ent = *reinterpret_cast<uintptr_t*>(base_object + 0x28);
			if (!ent)
				continue;

			auto ent_class = *reinterpret_cast<uintptr_t*>(ent);
			if (!ent_class)
				continue;

			auto entity_class_name = (char*)*reinterpret_cast<uintptr_t*>(ent_class + 0x10);
			if (!entity_class_name)
				continue;

			gui222::Color esp_color(1, 0, 1, 1);
			wchar_t* esp_name;

			auto game_object = *reinterpret_cast<uintptr_t*>(object + 0x30);
			if (!game_object)
				continue;

			auto transform = *reinterpret_cast<uintptr_t*>(game_object + 0x8);
			if (!transform)
				continue;

			auto visual_state = *reinterpret_cast<uintptr_t*>(transform + 0x38);
			if (!visual_state)
				continue;

			auto world_position = *reinterpret_cast<vector3*>(visual_state + 0x90);
			if (world_position.is_empty( ))
				continue;

			uintptr_t object_name_ptr = mem::read<uintptr_t>(object + 0x60);
			if (!object_name_ptr)
				continue;

			auto object_name = *reinterpret_cast<rust_str*>(object_name_ptr);
			if (!object_name.zpad)
				continue;

			//if (*(int*)(entity_class_name) == 'kcaH' && *(int*)(entity_class_name + 14) == 'tarC') {
			//	auto flag = *reinterpret_cast<int*>(ent + 0x128);
			//	if (flag != 128 && flag != 256)
			//		continue;

			//	vector2 w2s_position = {};
			//	if (out_w2s(world_position, w2s_position))
			//		esp::draw_hackable_crate(w2s_position, ent, {0.45, 0.72, 1, 0.8});
			//}
			if (*(int*)(entity_class_name) == 'porD') {
				if (!settings::visuals::dropped_items)
					continue;

				if (*(int*)(entity_class_name + 40) == 'kcab')
					continue;

				if (*(int*)(object_name.zpad) == 'orra')
					continue;

				if (*(int*)(object_name.zpad + 12) == 'ian.')
					continue;

				auto Item = *reinterpret_cast<uintptr_t*>(ent + 0x168);//	public Item item; public class WorldItem : BaseEntity
				if (!Item)
					continue;

				auto item = reinterpret_cast<weapon*>(Item);

				auto item_name = item->get_weapon_name( );

				esp_color = gui222::Color(196, 124, 0, 255);

				vector2 w2s_position = {};
				if (out_w2s(world_position, w2s_position))
					draw_weapon_icon(item, w2s_position);
				//esp::draw_item(w2s_position, 0, esp_color, item_name);

				continue;
			}

			if (settings::visuals::tc_esp && *(int*)(entity_class_name) == 'liuB' && *(int*)(entity_class_name + 8) == 'virP') {
				auto authorizedPlayers_wrapper = *reinterpret_cast<uintptr_t*>(ent + 0x590);//public List<PlayerNameID> authorizedPlayers;   public class BuildingPrivlidge : StorageContainer
				if (!authorizedPlayers_wrapper)
					continue;
				const auto authorizedPlayers_list = *reinterpret_cast<rust::list<PlayerNameID*>**>(authorizedPlayers_wrapper + 0x10);
				if (!authorizedPlayers_list)
					continue;

				vector2 w2s_position = {};
				if (out_w2s(world_position, w2s_position))
					esp::draw_tool_cupboard(w2s_position, _(L"Tool Cupboard"), gui222::Color(255, 0, 0, 255), authorizedPlayers_list);
			}


			if (*(int*)(entity_class_name + 4) == 'ileH' && settings::visuals::heli_esp && settings::visuals::vehicle) {
				auto base_heli = reinterpret_cast<base_player*>(ent);

				vector2 rearrotor, beam, mainrotor;
				out_w2s(base_heli->get_bone_transform(22)->get_bone_position( ), rearrotor);
				out_w2s(base_heli->get_bone_transform(19)->get_bone_position( ), mainrotor);
				out_w2s(base_heli->get_bone_transform(56)->get_bone_position( ), beam);
				esp_name = _(L"Heli Copter");
				esp_color = gui222::Color(232, 232, 232, 255);

				uintptr_t transform = mem::read<uintptr_t>(base_heli->get_model( ) + 0x48); //boneTransforms; // 0x48

				const vector2 diff = {(beam.x + rearrotor.x) / 2, (beam.y + rearrotor.y) / 2};

				const float h = max(beam.y, rearrotor.y) - min(beam.y, rearrotor.y);
				const float y = diff.y;
				const float w = (max(beam.x, rearrotor.x) - min(beam.x, rearrotor.x));
				float x = diff.x - h / 4;

				vector2 w2s_position = {};
				if (out_w2s(world_position, w2s_position))
					esp::draw_item(w2s_position, esp_name, esp_color);

				draw_heli(x, y, w, h);
			}

			if (settings::visuals::stash && *(int*)(object_name.zpad + 46) == '_hsa') {
				esp_name = _(L"Stash");
				esp_color = gui222::Color(232, 232, 232, 255);
			}
			else if (settings::visuals::stone_ore && (*(int*)(object_name.zpad + 52) == 'nots' || *(int*)(object_name.zpad + 47) == 'nots')) {
				esp_name = _(L"Stone Ore");
				esp_color = gui222::Color(232, 232, 232, 255);
			}
			else if (settings::visuals::sulfur_ore && (*(int*)(object_name.zpad + 52) == 'flus' || *(int*)(object_name.zpad + 47) == 'flus')) {
				esp_name = _(L"Sulfur Ore");
				esp_color = gui222::Color(203, 207, 0, 255);
			}
			else if (settings::visuals::metal_ore && (*(int*)(object_name.zpad + 52) == 'atem' || *(int*)(object_name.zpad + 47) == 'atem')) {
				esp_name = _(L"Metal Ore");
				esp_color = gui222::Color(145, 145, 145, 255);
			}
			else if (settings::visuals::traps && (*(int*)(object_name.zpad + 36) == 'terr' || *(int*)(object_name.zpad + 43) == 'tnug' || *(int*)(object_name.zpad + 38) == 'rtra')) {
				if (*(int*)(object_name.zpad + 36) == 'terr')
					esp_name = _(L"Auto Turret*");
				else if (*(int*)(object_name.zpad + 43) == 'tnug')
					esp_name = _(L"Shotgun Trap*");
		
				else if (*(int*)(object_name.zpad + 38) == 'rtra')
					esp_name = _(L"Bear Trap*");
				

				esp_color = gui222::Color(255, 166, 0, 255);
			}
			else if (settings::visuals::vehicles && settings::visuals::vehicle && *(int*)(entity_class_name + 4) == 'iheV') {
				esp_name = _(L"Vehicle");
				esp_color = gui222::Color(0, 161, 219, 255);
			}
			else if (settings::visuals::airdrops && *(int*)(object_name.zpad + 39) == 'pord') {
				esp_name = _(L"Airdrop");
				esp_color = gui222::Color(0, 161, 219, 255);
			}
			else if (settings::visuals::cloth && *(int*)(object_name.zpad + 52) == 'c-pm') {
				esp_name = _(L"Cloth");
				esp_color = gui222::Color(0, 219, 58, 255);
			}
			else if (settings::visuals::corpses && *(int*)(object_name.zpad + 29) == 'proc') {
				//esp_name = il2cpp::methods::new_string(_("Player Corpse"));
				esp_name = _(L"Corpse");
				esp_color = gui222::Color(230, 230, 230, 255);
			}
			else if (tag != 6)
				continue;

			if (tag != 6) {
				if (*(int*)(entity_class_name) == 'satS') {
					auto flag = *reinterpret_cast<int*>(ent + 0x130);//private float traveledDistance;
					if (flag != 2048)
						continue;
				}

				vector2 w2s_position = {};
				if (out_w2s(world_position, w2s_position))
					esp::draw_item(w2s_position, esp_name, esp_color);

				continue;
			}
		else if (tag != 6)
			continue;

			esp::matrix = unity::get_view_matrix( );

			if (tag == 6 && !settings::visuals::player_esp)
				continue;


			auto player = reinterpret_cast<base_player*>(ent);

			auto hit_player = [ & ]( ) {
				auto weapon = esp::local_player->get_active_weapon( );
				if (weapon) {
					auto baseprojectile = weapon->get_base_projetile( );
					if (baseprojectile) {
						auto class_name = baseprojectile->get_class_name( );
						if (*(int*)(class_name + 4) == 'eleM' || *(int*)(class_name + 4) == 'mmah') {
							auto world_position = player->get_bone_transform(48)->get_bone_position( );
							auto local = ClosestPoint(esp::local_player, world_position);
							auto camera = esp::local_player->get_bone_transform(48)->get_bone_position( );

							if (camera.get_3d_dist(world_position) >= 1.0f)
								return;

							aim_target target = esp::local_player->get_aimbot_target(camera);

							attack_melee(target, baseprojectile, true);
						}
					}
				}
			};

			if (!player->is_alive( ))
				continue;

			if (player->is_sleeping( ) && !settings::visuals::sleeper_esp)
				continue;

			bool is_npc = false;

			if (get_IsNpc(player->get_player_model( ))) {
				is_npc = true;

				if (!settings::visuals::npc_esp)
					continue;
			}

			if (player->is_local_player( ))
				local_player = reinterpret_cast<base_player*>(ent);
			else {
				if (esp::local_player != NULL) {
					auto target = aim_target( );
					//target.pos = player->get_bone_transform(19)->get_bone_position( );

					//auto distance = esp::local_player->get_bone_transform(48)->get_bone_position( ).get_3d_dist(target.pos);
					//target.distance = distance;
                	auto fov = unity::get_fov(target.pos);
				    target.fov = fov;

					target.player = player;

					if (target < best_target)
						best_target = target;
				}

				
				if (draw) {
					if (settings::visuals::chams) {
						static int cases = 0;
						static float r = 1.00f, g = 0.00f, b = 1.00f;
						switch (cases) {
						case 0: { r -= 0.05f; if (r <= 0) cases += 1; break; }
						case 1: { g += 0.05f; b -= 0.05f; if (g >= 1) cases += 1; break; }
						case 2: { r += 0.05f; if (r >= 1) cases += 1; break; }
						case 3: { b += 0.05f; g -= 0.05f; if (b >= 1) cases = 0; break; }
						default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
						}
						auto _multiMesh = mem::read<uintptr_t>(player->get_player_model( ) + 0x2D0); //SkinnedMultiMesh _multiMesh;
						if (_multiMesh) {
							auto render = get_Renderers(_multiMesh);

							for (int i = 0; i < render->get_size( ); i++) {
								auto renderer = render->get_value(i);

								//////// CHAMMINGS ///////€€

								if (renderer) {
									auto material = get_material(renderer);
									if (material) {
										if (!shader)
											shader = Find(_(L"Standard"));
										unity::set_shader(material, shader);	
										SetInt(material, (L"_ZTest"), 8); // through walls
										SetColor(material, _(L"_Color"), col(settings::visuals::xc, settings::visuals::yc, settings::visuals::zc, 1));
									}
								}
							}
						}
					}
					if (settings::visuals::transparent_chams) {
						auto _multiMesh = mem::read<uintptr_t>(player->get_player_model() + 0x2D0); //SkinnedMultiMesh _multiMesh;
						if (_multiMesh) {
							auto render = get_Renderers(_multiMesh);

							for (int i = 0; i < render->get_size(); i++) {
								auto renderer = render->get_value(i);

								if (renderer) {
									auto material = get_material(renderer);
									if (material) {
										if (shader != unity::get_shader(material)) {
											if (!shader)
												shader = Find(_(L"Hidden/Internal-Colored"));
											unity::set_shader(material, shader);
											SetColor(material, _(L"_Color"), col(1, 0.5, 1, 0.2));
										}
									}
								}
							}
						}
					}
					//if (settings::visuals::lamp_chams) {
					//	auto _multiMesh = mem::read<uintptr_t>(player->get_player_model() + 0x2D0); //SkinnedMultiMesh _multiMesh;
					//	if (_multiMesh) {
					//		auto render = get_Renderers(_multiMesh);

					//		for (int i = 0; i < render->get_size(); i++) {
					//			auto renderer = render->get_value(i);

					//			if (renderer) {
					//				auto material = get_material(renderer);
					//				if (material) {
					//					if (shader != unity::get_shader(material)) {
					//						if (!shader)
					//							shader = Find(_(L"Hidden/Internal-Colored"));
					//						unity::set_shader(material, shader);
					//						SetColor(material, _(L"_Color"), col(1, 0.5, 0, 5));
					//					}
					//				}
					//			}
					//		}
					//	}
					//}
					if (settings::visuals::rainbow_chams) {
						static int cases = 0;
						static float r = 1.00f, g = 0.00f, b = 1.00f;
						switch (cases) {
						case 0: { r -= 0.05f; if (r <= 0) cases += 1; break; }
						case 1: { g += 0.05f; b -= 0.05f; if (g >= 1) cases += 1; break; }
						case 2: { r += 0.05f; if (r >= 1) cases += 1; break; }
						case 3: { b += 0.05f; g -= 0.05f; if (b >= 1) cases = 0; break; }
						default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
						}
						auto _multiMesh = mem::read<uintptr_t>(player->get_player_model() + 0x2D0); //SkinnedMultiMesh _multiMesh;
						if (_multiMesh) {
							auto render = get_Renderers(_multiMesh);

							for (int i = 0; i < render->get_size(); i++) {
								auto renderer = render->get_value(i);

								//////// CHAMMINGS ///////

								if (renderer) {
									auto material = get_material(renderer);
									if (material) {
										if (!shader)
											shader = Find(_(L"Hidden/Internal-Colored"));
										unity::set_shader(material, shader);
										SetInt(material, (L"_ZTest"), 8); // through walls
										SetColor(material, _(L"_Color"), col(r, g, b, 1));
									}
								}
							}
						}
					}
					if (settings::visuals::pulse_chams) { // типа пульс :)
						static int cases = 0;
						static float r = 0.00f, g = 0.00f, b = 4.00f;
						switch (cases) {
						case 0: { r -= 0.07f; if (r <= 0) cases += 1; break; }
						case 1: { g += 0.07f; b -= 0.07f; if (g >= 1) cases += 1; break; }
						case 2: { r += 0.07f; if (r >= 1) cases += 1; break; }
						case 3: { b += 0.07f; g -= 0.07f; if (b >= 1) cases = 0; break; }
						default: { r = 0.00f; g = 0.00f; b = 4.00f; break; }
						}
						auto _multiMesh = mem::read<uintptr_t>(player->get_player_model() + 0x2D0); //SkinnedMultiMesh _multiMesh;
						if (_multiMesh) {
							auto render = get_Renderers(_multiMesh);

							for (int i = 0; i < render->get_size(); i++) {
								auto renderer = render->get_value(i);

								//////// CHAMMINGS ///////

								if (renderer) {
									auto material = get_material(renderer);
									if (material) {
										if (!shader)
											shader = Find(_(L"Hidden/Internal-Colored"));
										unity::set_shader(material, shader);
										SetInt(material, (L"_ZTest"), 8); // through walls
										SetColor(material, _(L"_Color"), col(r, g, b, 1));
									}
								}
							}
						}
					}
					if (settings::visuals::health_chams) {
						static int cases = 0;
						static float r = 1.00f, g = 0.00f, b = 1.00f;
						switch (cases) {
						case 0: { r -= 0.05f; if (r <= 0) cases += 1; break; }
						case 1: { g += 0.05f; b -= 0.05f; if (g >= 1) cases += 1; break; }
						case 2: { r += 0.05f; if (r >= 1) cases += 1; break; }
						case 3: { b += 0.05f; g -= 0.05f; if (b >= 1) cases = 0; break; }
						default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
						}
						auto _multiMesh = mem::read<uintptr_t>(player->get_player_model() + 0x2D0); //SkinnedMultiMesh _multiMesh;
						if (_multiMesh) {
							auto render = get_Renderers(_multiMesh);

							for (int i = 0; i < render->get_size(); i++) {
								auto renderer = render->get_value(i);

								//////// CHAMMINGS ///////

								if (renderer) {
									auto material = get_material(renderer);
									if (material) {
										if (!shader)
											shader = Find(_(L"Hidden/Internal-Colored"));
										unity::set_shader(material, shader);
										SetInt(material, (L"_ZTest"), 8); // through walls
										int health = (int)player->get_health();
										float maxheal = 100.f;
										if ((int)player->get_health() <= 33) {
											SetColor(material, (L"_Color"), col(3, 0, 0, 1));
										}
										if ((int)player->get_health() >= 34 && (int)player->get_health() <= 66) {
											SetColor(material, (L"_Color"), col(3, 3, 0, 1));
										}
										if ((int)player->get_health() >= 67) {
											SetColor(material, (L"_Color"), col(0, 3, 0, 1));
										}
									}
								}
							}
						}
					}


					draw_player(player, is_npc);

					if (settings::weapon::silent_melee)
						hit_player( );
				}
			}
		}
		esp::draw_target_hotbar(best_target);
	}


	void start( ) {
		iterate_players( );
	}
}