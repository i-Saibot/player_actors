/*
	Author: Saibot
*/

#if defined _player_actors_inc
	#endinput
#endif
#define _player_actors_inc


#if !defined PAWNRAKNET_INC_
	#error "Please include Pawn.RakNet before player_actors"
#endif

#if !defined _streamer_included
	#error "Please include streamer before player_actors"
#endif

#if !defined _FOREACH_LOCAL_VERSION
	#error "Please include foreach before player_actors"
#endif

static const ORPC_CREATE_PLAYER_ACTOR = 171;

static
	bool:gPlayerActorsIsStreamActor[MAX_ACTORS],
	IteratorArray:PlayerActorsId[MAX_PLAYERS]<MAX_ACTORS>;


forward OnPlayerGiveDamagePlayerActor(playerid, actorid, Float:amount, WEAPON:weaponid, bodypart);

public OnGameModeInit()
{
	Iter_Init(PlayerActorsId);
#if defined spact_OnGameModeInit
	return spact_OnGameModeInit();
#else
	return 1;
#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit spact_OnGameModeInit
#if defined    spact_OnGameModeInit
	forward spact_OnGameModeInit();
#endif

public OnPlayerDisconnect(playerid, reason)
{
	foreach (PlayerActorsId[playerid], actorid)
	{
		gPlayerActorsIsStreamActor[actorid] = false;
		DestroyDynamicActor(actorid);
	}
	Iter_Clear(PlayerActorsId[playerid]);
#if defined spact_OnPlayerDisconnect
	return spact_OnPlayerDisconnect(playerid, reason);
#else
	return 1;
#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect spact_OnPlayerDisconnect
#if defined    spact_OnPlayerDisconnect
	forward spact_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerGiveDamageDynamicActor(playerid, STREAMER_TAG_ACTOR:actorid, Float:amount, weaponid, bodypart)
{
	if (gPlayerActorsIsStreamActor[actorid])
	{
		if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) == playerid)
		{
			CallLocalFunction(
				"OnPlayerGiveDamagePlayerActor",
				"ddfdd",
				playerid,
				actorid,
				amount,
				weaponid,
				bodypart
			);
			return 1;
		}
	}
#if defined spact_OnGiveDamageDynamicActor
	return spact_OnGiveDamageDynamicActor(playerid, STREAMER_TAG_ACTOR:actorid, Float:amount, weaponid, bodypart);
#else
	return 1;
#endif
}
#if defined _ALS_OnGiveDamageDynamicActor
	#undef OnPlayerGiveDamageDynamicActor
#else
	#define _ALS_OnGiveDamageDynamicActor
#endif
#define OnPlayerGiveDamageDynamicActor spact_OnGiveDamageDynamicActor
#if defined    spact_OnGiveDamageDynamicActor
	forward spact_OnGiveDamageDynamicActor(playerid, STREAMER_TAG_ACTOR:actorid, Float:amount, weaponid, bodypart);
#endif

ORPC:ORPC_CREATE_PLAYER_ACTOR(playerid, BitStream:bs)
{
	static wActorID;

	BS_ReadValue(bs, PR_INT16, wActorID);

	new streamer_actorid = Streamer_GetItemStreamerID(playerid, STREAMER_TYPE_ACTOR, wActorID);

	if (gPlayerActorsIsStreamActor[streamer_actorid])
	{
		new targetid = Streamer_GetIntData(STREAMER_TYPE_ACTOR, streamer_actorid, E_STREAMER_PLAYER_ID);

		if (targetid != playerid)
		{
			return 0;
		}
	}
	return 1;
}

/*

	functions

*/

stock CreatePlayerActor(playerid, modelid, Float:x, Float:y, Float:z, Float:rotation, Float:health = 100.0, bool:invulnerable = true, worldid = -1)
{
	new actorid = CreateDynamicActor(
		modelid,
		x,
		y,
		z,
		rotation,
		.invulnerable = invulnerable,
		.health = health,
		.worldid = worldid,
		.playerid = playerid
	);
	if (actorid == INVALID_ACTOR_ID)
	{
		return INVALID_ACTOR_ID;
	}
	Iter_Add(PlayerActorsId[playerid], actorid);
	gPlayerActorsIsStreamActor[actorid] = true;
	return actorid;
}

stock DestroyPlayerActor(playerid, actorid)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	Iter_Remove(PlayerActorsId[playerid], actorid);
	gPlayerActorsIsStreamActor[actorid] = false;
	return DestroyDynamicActor(actorid);
}

stock ApplyPlayerActorAnimation(playerid, actorid, const animlib[], const animname[], Float:fdelta, loop, lockx, locky, freeze, time)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	ApplyDynamicActorAnimation(
		actorid,
		animlib,
		animname,
		fdelta,
		loop,
		lockx,
		locky,
		freeze,
		time
	);
	return 1;
}

stock ClearPlayerActorAnimations(playerid, actorid)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	ClearDynamicActorAnimations(actorid);
	return 1;
}

stock IsValidPlayerActor(playerid, actorid)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return IsValidDynamicActor(actorid);
}

stock IsPlayerActorInvulnerable(playerid, actorid)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return IsDynamicActorInvulnerable(actorid);
}

stock IsPlayerActorStreamedIn(playerid, actorid)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return IsDynamicActorStreamedIn(actorid, playerid);
}

stock SetPlayerActorVirtualWorld(playerid, actorid, worldid)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return SetDynamicActorVirtualWorld(actorid, worldid);
}

stock SetPlayerActorFacingAngle(playerid, actorid, Float:rotation)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return SetDynamicActorFacingAngle(actorid, rotation);
}

stock SetPlayerActorPos(playerid, actorid, Float:x, Float:y, Float:z)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return SetDynamicActorPos(actorid, x, y, z);
}

stock SetPlayerActorHealth(playerid, actorid, Float:health)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return SetDynamicActorHealth(actorid, health);
}

stock SetPlayerActorInvulnerable(playerid, actorid, invulnerable = true)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return SetDynamicActorInvulnerable(actorid, invulnerable);
}

stock GetPlayerActorVirtualWorld(playerid, actorid)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return GetDynamicActorVirtualWorld(actorid);
}

stock GetPlayerActorFacingAngle(playerid, actorid, &Float:rotation)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return GetDynamicActorFacingAngle(actorid, rotation);
}

stock GetPlayerActorPos(playerid, actorid, &Float:x, &Float:y, &Float:z)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return GetDynamicActorPos(actorid, x, y, z);
}

stock GetPlayerActorHealth(playerid, actorid, &Float:health)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return GetDynamicActorHealth(actorid, health);
}

stock GetPlayerActorAnimation(playerid, actorid, animlib[], animname[], &Float:fdelta, &loop, &lockx, &locky, &freeze, &time, maxanimlib = sizeof animlib, maxanimname = sizeof animname)
{
	if (Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) != playerid)
	{
		return 0;
	}
	return GetDynamicActorAnimation(actorid, animlib, animname, fdelta, loop, lockx, locky, freeze, time, maxanimlib = sizeof animlib, maxanimname = sizeof animname);
}