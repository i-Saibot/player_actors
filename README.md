# Player Actors
This library helps you create actors that will be visible only to a specific player.

>Dependencies: Pawn.RakNet, streamer, and foreach.

**Callback: Triggered when a player deals damage to player actors.**
```pawn
forward OnPlayerGiveDamagePlayerActor(playerid, actorid, Float:amount, weaponid, bodypart);
```

**Functions: I think the names are self-explanatory.**
```pawn
CreatePlayerActor(playerid, modelid, Float:x, Float:y, Float:z, Float:rotation, Float:health = 100.0, bool:invulnerable = true, worldid = -1);
DestroyPlayerActor(playerid, actorid);

ApplyPlayerActorAnimation(playerid, actorid, const animlib[], const animname[], Float:fdelta, loop, lockx, locky, freeze, time);
ClearPlayerActorAnimations(playerid, actorid);

IsValidPlayerActor(playerid, actorid);
IsPlayerActorInvulnerable(playerid, actorid);
IsPlayerActorStreamedIn(playerid, actorid);

SetPlayerActorVirtualWorld(playerid, actorid, worldid);
SetPlayerActorFacingAngle(playerid, actorid, Float:rotation);
SetPlayerActorPos(playerid, actorid, Float:x, Float:y, Float:z);
SetPlayerActorHealth(playerid, actorid, Float:health);
SetPlayerActorInvulnerable(playerid, actorid, invulnerable = true);

GetPlayerActorVirtualWorld(playerid, actorid);
GetPlayerActorFacingAngle(playerid, actorid, &Float:rotation);
GetPlayerActorPos(playerid, actorid, &Float:x, &Float:y, &Float:z);
GetPlayerActorHealth(playerid, actorid, &Float:health);
GetPlayerActorAnimation(playerid, actorid, animlib[], animname[], &Float:fdelta, &loop, &lockx, &locky, &freeze, &time, maxanimlib = sizeof animlib, maxanimname = sizeof animname);
```

>The actors are automatically NOT removed after the player exits.
