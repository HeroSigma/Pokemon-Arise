#include "constants/global.h"
#include "constants/layouts.h"
#include "constants/map_types.h"
#include "constants/maps.h"
#include "constants/weather.h"
#include "constants/region_map_sections.h"
#include "constants/songs.h"
#include "constants/trainer_hill.h"
	.include "asm/macros.inc"
	.include "constants/constants.inc"

	.section .rodata

	.include "data/layouts/layouts.inc"
	.include "data/layouts/layouts_table.inc"
	.include "data/maps/headers.inc"
	.include "data/maps/groups.inc"
	.include "data/maps/connections.inc"

	@ Include all map scripts.inc files so map script symbols are defined
	.include "data/maps/EternaForestA/scripts.inc"
	.include "data/maps/JubilifeCity/scripts.inc"
	.include "data/maps/OreburghGate2F/scripts.inc"
	.include "data/maps/OreburghCityA/scripts.inc"
	.include "data/maps/SendOffSpring/scripts.inc"
	.include "data/maps/LakeVerityCave/scripts.inc"
	.include "data/maps/LakeValorCave/scripts.inc"
	.include "data/maps/LakeAcuityCave/scripts.inc"
