#pragma once
#include "headers/global.h"
#include <string>
#include <iostream>
#include <array>
#include "headers/string_utils.h"
#include "headers/cnsl.h"
#define THROW_ERROR(x) \
cnsl::print_colored_reset(x,ConsoleColorAttributes::Red_FG);\
this->dialogue(Entity, key, saying);\
return 1;\

constexpr int INT_LIMIT = 2147483647;
constexpr std::array<const char*, 8> EntitiesHelpList = {
	"zombies/skeletons/creepers: extremely common spawns in light of 0 required space 1 block wide 2 high spawns on any block",
	"spiders: extremely common spawns in light of 0 required space 2 block wide 1 high spawns on any block",
	"endermen: slightly less common spawns on any block only in light of 0 requied space 1 block wide 3 high",
	"witches: slightly less common (very high in witch huts) spawns on any block only in light of 0 requied space 1 block wide 2 high",
	"pillagers: very rare (unless raids) spawns on any block",
	"polar bears: not common but only spawns on ice and snow in snowy biomes in light of 8 or greater",
	"cows/pigs/chickens/horses: not common but only spawns on grass only in light of 8 or greater",
	"foxes: not common but only spawns on dirt blocks and powder snow and normal snow in tiaga biomes and snowy biomes only in light of 8 or greater",
};

constexpr std::array<const char*, 3> DimensionList = { "overworld","the_nether","the_end",};
constexpr std::array<const char*,352> BlockList ={ "acacia_log","acacia_planks","acacia_wood","amethyst_block","ancient_debris","andesite","azalea","bamboo","bamboo_block","bamboo_mosaic","bamboo_planks","barrel","basalt","beacon","bee_nest","beehive","birch_log","birch_planks","birch_wood","black_concrete","black_concrete_powder","black_glazed_terracotta","black_shulker_box","black_terracotta","black_wool","blackstone","blast_furnace","blue_concrete","blue_concrete_powder","blue_glazed_terracotta","blue_ice","blue_shulker_box","blue_terracotta","blue_wool","bone_block","bookshelf","brewing_stand","bricks","brown_concrete","brown_concrete_powder","brown_glazed_terracotta","brown_mushroom","brown_mushroom_block","brown_shulker_box","brown_terracotta","brown_wool","calcite","cartography_table","carved_pumpkin","chain","cherry_log","cherry_planks","cherry_wood","chiseled_bookshelf","chiseled_deepslate","chiseled_nether_bricks","chiseled_polished_blackstone","chiseled_quartz_block","chiseled_red_sandstone","chiseled_sandstone","chiseled_stone_bricks","clay","coal_block","coal_ore","coarse_dirt","cobbled_deepslate","cobblestone","copper_block","copper_ore","cracked_deepslate_bricks","cracked_deepslate_tiles","cracked_nether_bricks","cracked_polished_blackstone_bricks","cracked_stone_bricks","crafting_table","crimson_hyphae","crimson_nylium","crimson_planks","crimson_roots","crying_obsidian","cut_copper","cut_red_sandstone","cut_sandstone","cyan_concrete","cyan_concrete_powder","cyan_glazed_terracotta","cyan_shulker_box","cyan_terracotta","cyan_wool","dandelion","dark_oak_log","dark_oak_planks","dark_oak_wood","dark_prismarine","deepslate","deepslate_bricks","deepslate_coal_ore","deepslate_copper_ore","deepslate_diamond_ore","deepslate_emerald_ore","deepslate_gold_ore","deepslate_iron_ore","deepslate_lapis_ore","deepslate_redstone_ore","deepslate_tiles","diamond_block","diamond_ore","diorite","dirt","dispenser","dried_kelp_block","dripstone_block","dropper","emerald_block","emerald_ore","end_stone","end_stone_bricks","exposed_copper","exposed_cut_copper","fletching_table","frogspawn","frosted_ice","furnace","gilded_blackstone","gold_block","gold_ore","granite","grass_block","gravel","gray_concrete","gray_concrete_powder","gray_glazed_terracotta","gray_shulker_box","gray_terracotta","gray_wool","green_concrete","green_concrete_powder","green_glazed_terracotta","green_shulker_box","green_terracotta","green_wool","hay_block","honey_block","honeycomb_block","hopper","ice","infested_chiseled_stone_bricks","infested_cobblestone","infested_cracked_stone_bricks","infested_deepslate","infested_mossy_stone_bricks","infested_stone","infested_stone_bricks","iron_bars","iron_block","iron_ore","jukebox","jungle_log","jungle_planks","jungle_wood","kelp","ladder","lapis_block","lapis_ore","lava","lime_concrete","lime_concrete_powder","lime_glazed_terracotta","lime_shulker_box","lime_terracotta","lime_wool","lodestone","loom","magenta_concrete","magenta_concrete_powder","magenta_glazed_terracotta","magenta_shulker_box","magenta_terracotta","magenta_wool","magma_block","mangrove_log","mangrove_planks","mangrove_propagule","mangrove_roots","mangrove_wood","melon","moss_block","mossy_cobblestone","mossy_stone_bricks","moving_piston","mud","mud_bricks","muddy_mangrove_roots","mycelium","nether_bricks","nether_gold_ore","nether_quartz_ore","nether_sprouts","nether_wart","nether_wart_block","netherite_block","netherrack","note_block","oak_log","oak_planks","oak_wood","observer","obsidian","orange_concrete","orange_concrete_powder","orange_glazed_terracotta","orange_shulker_box","orange_terracotta","orange_wool","oxidized_copper","oxidized_cut_copper","packed_ice","packed_mud","pink_concrete","pink_concrete_powder","pink_glazed_terracotta","pink_petals","pink_shulker_box","pink_terracotta","pink_wool","piston","pitcher_crop","podzol","polished_andesite","polished_basalt","polished_blackstone","polished_blackstone_bricks","polished_deepslate","polished_diorite","polished_granite","powder_snow","prismarine","prismarine_bricks","pumpkin","purple_concrete","purple_concrete_powder","purple_glazed_terracotta","purple_shulker_box","purple_terracotta","purple_wool","purpur_block","purpur_pillar","quartz_block","quartz_bricks","quartz_pillar","raw_copper_block","raw_gold_block","raw_iron_block","red_concrete","red_concrete_powder","red_glazed_terracotta","red_mushroom","red_mushroom_block","red_nether_bricks","red_sand","red_sandstone","red_shulker_box","red_terracotta","red_wool","redstone_block","redstone_lamp","redstone_ore","redstone_wire","reinforced_deepslate","rooted_dirt","sand","sandstone","sculk","sculk_catalyst","sculk_vein","shulker_box","slime_block","smithing_table","smoker","smooth_basalt","smooth_quartz","smooth_red_sandstone","smooth_sandstone","smooth_stone","snow","snow_block","soul_sand","soul_soil","spawner","sponge","spore_blossom","spruce_log","spruce_planks","spruce_wood","sticky_piston","stone","stone_bricks","stonecutter","stripped_acacia_log","stripped_acacia_wood","stripped_bamboo_block","stripped_birch_log","stripped_birch_wood","stripped_cherry_log","stripped_cherry_wood","stripped_crimson_hyphae","stripped_dark_oak_log","stripped_dark_oak_wood","stripped_jungle_log","stripped_jungle_wood","stripped_mangrove_log","stripped_mangrove_wood","stripped_oak_log","stripped_oak_wood","stripped_spruce_log","stripped_spruce_wood","stripped_warped_hyphae","suspicious_gravel","suspicious_sand","target","terracotta","tnt","tuff","warped_hyphae","warped_nylium","warped_planks","warped_roots","warped_wart_block","water","waxed_copper_block","waxed_cut_copper","waxed_exposed_copper","waxed_exposed_cut_copper","waxed_oxidized_copper","waxed_oxidized_cut_copper","waxed_weathered_copper","waxed_weathered_cut_copper","weathered_copper","weathered_cut_copper","wet_sponge","white_concrete","white_concrete_powder","white_glazed_terracotta","white_shulker_box","white_terracotta","white_wool","yellow_concrete","yellow_concrete_powder","yellow_glazed_terracotta","yellow_shulker_box","yellow_terracotta", "yellow_wool"};
constexpr std::array<const char*,78> EntityList = {"allay","axolotl","bat","bee","blaze","camel","cat","cave_spider","chicken","cod","cow","creeper","dolphin","donkey","drowned","elder_guardian","ender_dragon","enderman","endermite","evoker","fox","frog","ghast","glow_squid","goat","guardian","hoglin","horse","husk","illusioner","iron_golem","llama","magma_cube","mooshroom","mule","ocelot","panda","parrot","phantom","pig","piglin","piglin_brute","pillager","polar_bear","pufferfish","rabbit","ravager","salmon","sheep","shulker","silverfish","skeleton","skeleton_horse","slime","sniffer","snow_golem","spider","squid","stray","strider","tadpole","trader_llama","tropical_fish","turtle","vex","villager","vindicator","wandering_trader","warden","witch","wither","wither_skeleton","wolf","zoglin","zombie","zombie_horse","zombie_villager","zombified_piglin"};
constexpr std::array<const char*, 65> BiomeList = { "the_void","plains","sunflower_plains","forest","flower_forest","birch_forest","dark_forest","swamp","mangrove_swamp","jungle","sparse_jungle","bamboo_jungle","beach","mushroom_fields","meadow","stony_peaks","windswept_hills","windswept_gravelly_hills","windswept_forest","taiga","stony_shore","snowy_plains","ice_spikes","snowy_taiga","snowy_beach","grove","snowy_slopes","jagged_peaks","frozen_peaks","desert","savanna","savanna_plateau","windswept_savanna","badlands","wooded_badlands","eroded_badlands","river","frozen_river","ocean","warm_ocean","lukewarm_ocean","deep_lukewarm_ocean","cold_ocean","deep_ocean","deep_cold_ocean","frozen_ocean","deep_frozen_ocean","soul_sand_valley","warped_forest","nether_wastes","basalt_deltas","crimson_forest","the_end","small_end_islands","end_barrens","end_midlands","end_highlands","dripstone_caves","lush_caves","deep_dark","old_growth_birch_forest","old_growth_pine_taiga","old_growth_spruce_taiga","old_growth_spruce_taiga","cherry_grove" };
namespace json {
	enum keys : char {
		registry,
		name,
		weight,
		spawn_pack_distance,
		weight_level_multiplier,
		base_entity,
		entity_data,
		spawn_pack,
		stat_increases,
		level,
		moon_phase,
		block,
		biome,
		dimension,
		requirements,
		flat_stat_increases,
		percentage_stat_increases,
		P_health,
		P_damage,
		P_speed,
		P_sight_range,
		P_attack_speed,
		P_armor,
		P_armor_toughness,

		F_health,
		F_damage,
		F_speed,
		F_sight_range,
		F_attack_speed,
		F_armor,
		F_armor_toughness,
		NBT
	};
}
struct binomial {
	short n = 0 ;
	char p = 0;
	float b =0.0f;
	friend bool operator==(const binomial B1, const binomial B2);
	bool hasValue() {
		return this->b != 0 || this->n != 0 || this->p != 0;
	}
};
struct stat_increases{
public:
	binomial P_health = {0,0,0};
	binomial P_damage = {0,0,0};
	binomial P_speed = {0,0,0};
	binomial P_sight_range = {0,0,0};
	binomial P_attack_speed = {0,0,0};
	binomial P_armor = {0,0,0};
	binomial P_armor_toughness = {0,0,0};

	binomial F_health = {0,0,0};
	binomial F_damage = {0,0,0};
	binomial F_speed = {0,0,0};
	binomial F_sight_range = {0,0,0};
	binomial F_attack_speed = {0,0,0};
	binomial F_armor = {0,0,0};
	binomial F_armor_toughness = {0,0,0};
	// {flat:{health:{n:0,p:50b}}}
	friend std::ostream& operator <<(std::ostream& os, const stat_increases& m);
};
struct min_max {
public:
	float min = 1.5;
	float max = 1.75;
	friend std::ostream& operator <<(std::ostream& os, const min_max& m); 
};
struct level {
public:
	int min = 0;
	int max = INT_LIMIT;
	friend std::ostream& operator <<(std::ostream& os, const level& m);
};
struct spawn_pack {
public:
	int min = 0;
	int max = 0;
	int exact = 0 ;
	friend std::ostream& operator <<(std::ostream& os, const spawn_pack& s);
};
struct moon_phase {
public:
	char min =0 ;
	char max =0 ;
	char exact = 0;
	char except =0;
	bool on_even_days = false;
	bool on_odd_days = false;
	bool on_prime_days = false;
	bool blood_moon = false;
	friend std::ostream& operator <<(std::ostream& os, const moon_phase& m);
};
class entity {
public:
	std::string m_Registry = "";
	std::string m_Name = "";
	int m_Weight = 0;
	min_max m_Spawn_pack_distance;
	float m_Weight_level_multiplier = 0.0f;
	std::string m_Base_entity = "";
	std::string m_Entity_data = "";
	spawn_pack m_Spawn_pack;
	stat_increases m_Stat_increases;
	level m_Level;
	moon_phase m_Moon_phase;
	std::string m_Block = "";
	std::string m_Biome = "";
	std::string m_Dimension = "";
	std::string m_NBT = "";

	bool hasSpawnPack = false;
	bool hasSpawnPackDistance = false;
	bool hasWeightLevelMultiplier = false;
	bool hasMoonPhase = false;
	bool hasRequirements = false;
	bool hasLevel = false;
	bool hasBiome = false;
	bool hasBlock = false;
	bool hasDimension = false;

	bool hasStatIncreases = false;
	bool hasFlatStatIncreases = false;
	bool hasPercentageStatIncreases = false;
	bool hasNBT = false;
	void print();
	void printCommand();
};



class generator
{
private:
	enum Help : unsigned char{
		Registry
	};
	//std::string input;
	int weight;
	void printHelp(Help help) {
		switch (help) {
		case Help::Registry:
			std::cout << "Some Entities Info;\n";
			for (int i = 0; i < EntitiesHelpList.size(); ++i) {
				cnsl::print_colored_reset(EntitiesHelpList[i], ConsoleColorAttributes::Blue_FG);
				std::cout << '\n';
			}
			break;
		default:
			cnsl::print_colored_reset("Unknown help command.",ConsoleColorAttributes::Red_FG);
		}
	}

	bool valid_entity(const std::string& input) {
		bool flag = false;
		for (int i = 0; i < EntityList.size() && flag == false; ++i)
			if(input == EntityList[i])
				flag = true;
		return flag;
	}
	bool valid_block(const std::string& input) {
		bool flag = false;
		for (int i = 0; i < BlockList.size() && flag == false; ++i)
			if (input == BlockList[i])
				flag = true;
		return flag;
	}
	bool valid_biome(const std::string& input) {
		bool flag = false;
		for (int i = 0; i < BiomeList.size() && flag == false; ++i)
			if (input == BiomeList[i])
				flag = true;
		return flag;
	}
	bool valid_dimension(const std::string& input) {
		bool flag = false;
		for (int i = 0; i < DimensionList.size() && flag == false; ++i)
			if (input == DimensionList[i])
				flag = true;
		return flag;
	}

public:
	int inputInt = 0;
	int dialogue(entity& Entity, int key, const std::string& saying);
};
