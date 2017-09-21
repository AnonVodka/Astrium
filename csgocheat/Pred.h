//#include "stdafx.h"
//#include "Tools/Utils/Hitbox.h"
//#include "Tools/Menu/Menu.h"
//#include "Tools/Utils/Playerlist.h"
//#include "Tools/Menu/SettingsManager.h"
//#include "Tools/Utils/HitboxLists.h"
//#include "Utils/Utils.h"
//#include "checksum_md5.h"
//
//
//float m_flOldCurtime;
//float m_flOldFrametime;
//CMoveData m_MoveData;
//
//int* m_pPredictionRandomSeed;
//
//class Pred
//{
//public:
//
//	static void StartPrediction()
//	{
//		static bool bInit = false;
//		if (!bInit) {
//			m_pPredictionRandomSeed = *(int**)(Utils.PatternScan("client.dll", "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04") + 2);
//			bInit = true;
//		}
//
//
//		*m_pPredictionRandomSeed = MD5_PseudoRandom(Hacks.CurrentCmd->command_number) & 0x7FFFFFFF;//Hacks.UserCmd->random_seed;
//
//		m_flOldCurtime = Interfaces.pGlobalVars->curtime;
//		m_flOldFrametime = Interfaces.pGlobalVars->frametime;
//
//		Interfaces.pGlobalVars->curtime = Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
//		Interfaces.pGlobalVars->frametime = Interfaces.pGlobalVars->interval_per_tick;
//
//		Interfaces.g_pGameMovement->StartTrackPredictionErrors(Hacks.LocalPlayer);
//
//		memset(&m_MoveData, 0, sizeof(m_MoveData));
//		Interfaces.g_pMoveHelper->SetHost(Hacks.LocalPlayer);
//		Interfaces.g_pPred->SetupMove(Hacks.LocalPlayer, Hacks.CurrentCmd, Interfaces.g_pMoveHelper, &m_MoveData);
//		Interfaces.g_pGameMovement->ProcessMovement(Hacks.LocalPlayer, &m_MoveData);
//		Interfaces.g_pPred->FinishMove(Hacks.LocalPlayer, Hacks.CurrentCmd, &m_MoveData);
//	}
//	static void EndPrediction()
//	{
//		Interfaces.g_pGameMovement->FinishTrackPredictionErrors(Hacks.LocalPlayer);
//		Interfaces.g_pMoveHelper->SetHost(0);
//
//		*m_pPredictionRandomSeed = -1;
//		Interfaces.pGlobalVars->curtime = m_flOldCurtime;
//		Interfaces.pGlobalVars->frametime = m_flOldFrametime;
//	}
//};
//
//extern Pred* PredSystem;
