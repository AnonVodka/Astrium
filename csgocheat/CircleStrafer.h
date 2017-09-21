//#pragma once
//#include "stdafx.h"
//#include <chrono>
//#include <ctime>
//#include <time.h>
//
//#define KEY_DOWN(VK_NNM) ((GetAsyncKeyState(VK_NNM) & 0x8000) ? 1:0)
//
//auto sv_jump_impulse = Interfaces.g_ICVars->FindVar("sv_jump_impulse");
//auto sv_gravity = Interfaces.g_ICVars->FindVar("sv_gravity");
//
//struct c_state {
//	Vector m_origin;
//	vec_t m_angle;
//	Vector m_veloctiy;
//	float m_fraction;
//
//};
//vec_t GetOptimalAngle(vec_t currentAngle, int dir, Vector &velocity, int &sdir)
//{
//	return 0;
//}
//
//class c_child {
//	Vector m_origin, m_velocity;
//	vec_t m_angle;
//	vec_t GetOptimalAngle(vec_t currentAngle, int dir, Vector &velocity, int &sdir);
//public:
//
//	c_child(Vector origin, Vector velocity, vec_t angle) : m_origin(origin), m_velocity(velocity), m_angle(angle) { }
//
//	int run(int &total, int sub) {
//		if (total > (96000 * Interfaces.pGlobalVars->interval_per_tick)) // Too many traces, i found 1500 traces for 64 tick and 750 traces for 128 to be suitible so it doesnt lag
//			return 0;
//		//How many states there will be
//		const int segments = (0.0625f / Interfaces.pGlobalVars->interval_per_tick);
//		if (sub > 200 / segments) // Path long enough, about 200 ticks ahead is enough. TODO: Should make this depend on the tick rate
//			return 1;
//
//		float options[2] = { 0,0 };
//		Ray_t ray;
//		CTraceWorldOnly filter;
//		trace_t tr;
//		int sdir;
//
//		bool hit = false;
//
//		for (int i = 0; i <= 1; i++) {
//			Vector new_velocity = m_velocity;
//			Vector new_origin = m_origin;
//			vec_t temp = m_angle;
//			c_state states[20];
//
//			//Create multiple states to trace through all in 1 to save traces
//			for (auto z = 0; z < segments; z++) {
//				states[z].m_origin = new_origin;
//				temp = GetOptimalAngle(temp, i == 0 ? 1 : -1, new_velocity, sdir);
//				new_origin += new_velocity * Interfaces.pGlobalVars->interval_per_tick;
//				new_velocity[2] -= sv_gravity->GetFloat() * Interfaces.pGlobalVars->interval_per_tick;
//				states[z].m_angle = temp;
//				states[z].m_veloctiy = new_velocity;
//			}
//
//			//Get all the fraction of difference each state covers
//			const vec_t delta_final = new_origin[2] - m_origin[2];
//
//			for (auto z = 0; z < segments; z++) {
//				const vec_t delta_state = states[z].m_origin[2] - m_origin[2];
//				states[z].m_fraction = (delta_state / delta_final);
//			}
//
//			ray.Init(m_origin, new_origin/*, Hacks.LocalPlayer->BBMax(), Hacks.LocalPlayer->BBMax()*/);
//
//			//Add onto total traces
//			Interfaces.pTrace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &tr);
//			total++;
//
//			int temp_sub = sub;
//			float distance_traveled = 0.f;
//
//			//See which state hit the ground
//			if (tr.plane.normal.z >= 0.7f) {
//				for (auto z = segments - 1; z >= 0; z--) {
//					//find the trace that matches the fraction best
//					if (states[z].m_fraction < tr.fraction) {
//						new_velocity = states[z].m_veloctiy;
//						temp = states[z].m_angle;
//						if (z != segments - 1) {
//							const float distance_delta = states[z + 1].m_fraction - states[z].m_fraction;
//							distance_traveled = (tr.fraction - states[z].m_fraction) / distance_delta;
//						}
//						temp_sub += z;
//						goto end_loop;
//					}
//				}
//				//restore the first velocity if none found
//				new_velocity = states[0].m_veloctiy;
//				temp = states[0].m_angle;
//				temp_sub += 1;
//			}
//			else
//				temp_sub += 4;
//		end_loop:
//			//TODO: Not the correct way to check if we hit the ground and not a wall but works for now
//			if (tr.fraction == 1.f || tr.plane.normal.z >= 0.7f) {
//
//				// Add Gravity and attempt jumping if needed
//				Vector predicted_origin = new_origin;
//				if (tr.plane.normal.z >= 0.7f) {
//					new_velocity[2] = sv_jump_impulse->GetFloat();
//					//set add the estimated travel distance
//					predicted_origin += new_velocity * distance_traveled * Interfaces.pGlobalVars->interval_per_tick;
//				}
//
//				//Recurse
//				c_child* child = new c_child(predicted_origin, new_velocity, temp);
//				options[i] = child->run(total, temp_sub);
//				delete[]child;
//				child = nullptr;
//			}
//			else
//			{
//				// i do this part so that it avoids walls a bit better
//				hit = true;
//				break;
//			}
//		}
//
//		if (hit) {
//			//delete[]paths;
//			return 0;
//		}
//
//		//Return the best option
//		if (options[1] > options[0])
//			return options[1] + 1;
//		return options[0] + 1;
//	}
//};
//
//static void CircleStrafer(Vector &orig_ang) {
//	if (!KEY_DOWN(0x56)) // v key
//		return;
//	if (!sv_jump_impulse)
//		sv_jump_impulse = Interfaces.g_ICVars->FindVar("sv_jump_impulse");
//	if (!sv_gravity)
//		sv_gravity = Interfaces.g_ICVars->FindVar("sv_gravity");
//
//	static Vector last_ang = orig_ang;
//	int option = 0;
//
//	Ray_t ray;
//	trace_t tr;
//	CTraceWorldOnly filter;
//	int sdir;
//	int total = 0;
//	Vector origin = Hacks.LocalPlayer->GetAbsOrigin();
//	const Vector velocity = Hacks.LocalPlayer->GetVecVelocity();
//
//	for (int i = 0; i <= 1; i++) {
//		Vector new_velocity = velocity;
//		Vector new_origin = origin;
//		vec_t temp = last_ang.y;
//
//		c_state states[10];
//
//		//Create multiple states to trace through all in 1 to save traces
//		const int segments = 0.0625f / Interfaces.pGlobalVars->interval_per_tick;
//		for (auto z = 0; z < segments; z++) {
//			states[z].m_origin = new_origin;
//			temp = GetOptimalAngle(temp, i == 0 ? 1 : -1, new_velocity, sdir);
//			new_origin += new_velocity * Interfaces.pGlobalVars->interval_per_tick;
//			new_velocity[2] -= sv_gravity->GetFloat() * Interfaces.pGlobalVars->interval_per_tick;
//			states[z].m_angle = temp;
//			states[z].m_veloctiy = new_velocity;
//		}
//
//		//Get all the fraction of difference each state covers
//		const vec_t delta_final = new_origin[2] - origin[2];
//
//		for (auto z = 0; z < segments; z++) {
//			const vec_t delta_state = states[z].m_origin[2] - origin[2];
//			states[z].m_fraction = (delta_state / delta_final);
//		}
//
//		ray.Init(origin, new_origin/*, Hacks.LocalPlayer->BBMin(), Hacks.LocalPlayer->BBMax()*/);
//
//		//Add onto total traces
//		Interfaces.pTrace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &tr);
//		total++;
//
//		float distance_traveled = 0.f;
//
//		//See which state hit the ground
//		if (tr.plane.normal.z >= 0.7f) {
//			for (auto z = segments - 1; z >= 0; z--) {
//				//find the trace that matches the fraction best
//				if (states[z].m_fraction < tr.fraction) {
//					new_velocity = states[z].m_veloctiy;
//					temp = states[z].m_angle;
//					if (z != segments - 1) {
//						const float distance_delta = states[z + 1].m_fraction - states[z].m_fraction;
//						distance_traveled = (tr.fraction - states[z].m_fraction) / distance_delta;
//					}
//					goto endloop;
//				}
//			}
//			//restore the first velocity if none found
//			new_velocity = states[0].m_veloctiy;
//			temp = states[0].m_angle;
//		}
//	endloop:
//		//TODO: Not the correct way to check if we hit the ground and not a wall but works for now
//		if (tr.fraction == 1.f || tr.plane.normal.z >= 0.7f) {
//			// Add Gravity and attempt jumping if needed
//			new_velocity[2] -= sv_gravity->GetFloat() * Interfaces.pGlobalVars->interval_per_tick;
//			Vector predicted_origin = new_origin;
//			if (tr.plane.normal.z >= 0.7f) {
//				new_velocity[2] = sv_jump_impulse->GetFloat();
//				predicted_origin += new_velocity * distance_traveled * Interfaces.pGlobalVars->interval_per_tick;
//			}
//
//			//Start recursions
//			c_child* child = new c_child(predicted_origin, new_velocity, temp);
//			const float sub = child->run(total, 1);
//			if (sub > option) {
//				option = sub;
//
//				//Set to best angle
//				orig_ang.y = states[0].m_angle;
//				Hacks.CurrentCmd->sidemove = sdir * 450.f;
//			}
//			delete[]child;
//			child = nullptr;
//		}
//	}
//	last_ang = orig_ang;
//}