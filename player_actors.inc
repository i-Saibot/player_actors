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


static
	CUSTOM_PLAYER_ACTORS 				= 0xFF999;
	const ORPC_CREATE_PLAYER_ACTOR		= 171;


forward OnPlayerGiveDamagePlayerActor(playerid, actorid, Float:amount, weaponid, bodypart);


public OnPlayerGiveDamageDynamicActor(playerid, STREAMER_TAG_ACTOR:actorid, Float:amount, weaponid, bodypart)
{
	if (IsPlayerActor(actorid))
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

	if (IsPlayerActor(streamer_actorid))
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
	if (actorid == INVALID_STREAMER_ID)
	{
		return INVALID_ACTOR_ID;
	}
	SetPlayerActorValue(actorid, true);
	return actorid;
}

stock DestroyPlayerActor(playerid, actorid)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	SetPlayerActorValue(actorid, false);
	return DestroyDynamicActor(actorid);
}

stock ApplyPlayerActorAnimation(playerid, actorid, const animlib[], const animname[], Float:fdelta, loop, lockx, locky, freeze, time)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
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
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	ClearDynamicActorAnimations(actorid);
	return 1;
}

stock IsValidPlayerActor(playerid, actorid)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return IsValidDynamicActor(actorid);
}

stock IsPlayerActorInvulnerable(playerid, actorid)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return IsDynamicActorInvulnerable(actorid);
}

stock IsPlayerActorStreamedIn(playerid, actorid)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return IsDynamicActorStreamedIn(actorid, playerid);
}

stock SetPlayerActorVirtualWorld(playerid, actorid, worldid)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return SetDynamicActorVirtualWorld(actorid, worldid);
}

stock SetPlayerActorFacingAngle(playerid, actorid, Float:rotation)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return SetDynamicActorFacingAngle(actorid, rotation);
}

stock SetPlayerActorPos(playerid, actorid, Float:x, Float:y, Float:z)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return SetDynamicActorPos(actorid, x, y, z);
}

stock SetPlayerActorHealth(playerid, actorid, Float:health)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return SetDynamicActorHealth(actorid, health);
}

stock SetPlayerActorInvulnerable(playerid, actorid, invulnerable = true)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return SetDynamicActorInvulnerable(actorid, invulnerable);
}

stock GetPlayerActorVirtualWorld(playerid, actorid)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return GetDynamicActorVirtualWorld(actorid);
}

stock GetPlayerActorFacingAngle(playerid, actorid, &Float:rotation)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return GetDynamicActorFacingAngle(actorid, rotation);
}

stock GetPlayerActorPos(playerid, actorid, &Float:x, &Float:y, &Float:z)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return GetDynamicActorPos(actorid, x, y, z);
}

stock GetPlayerActorHealth(playerid, actorid, &Float:health)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return GetDynamicActorHealth(actorid, health);
}

stock GetPlayerActorAnimation(playerid, actorid, animlib[], animname[], &Float:fdelta, &loop, &lockx, &locky, &freeze, &time, maxanimlib = sizeof animlib, maxanimname = sizeof animname)
{
	if (!IsPlayerActorForPlayer(playerid, actorid))
	{
		return 0;
	}
	return GetDynamicActorAnimation(actorid, animlib, animname, fdelta, loop, lockx, locky, freeze, time, maxanimlib = sizeof animlib, maxanimname = sizeof animname);
}


/*

	static functions

*/

static stock SetPlayerActorValue(actorid, bool:value)
{
	Streamer_SetIntData(
		STREAMER_TYPE_ACTOR,
		actorid,
		E_STREAMER_CUSTOM(CUSTOM_PLAYER_ACTORS),
		value
	);
	return 1;
}

static stock GetPlayerActorValue(actorid)
{
	return Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_CUSTOM(CUSTOM_PLAYER_ACTORS));
}

static stock IsPlayerActorForPlayer(playerid, actorid)
{
	return Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_PLAYER_ID) == playerid);
}

static stock IsPlayerActor(actorid)
{
	return GetPlayerActorValue(actorid) != 0;
}