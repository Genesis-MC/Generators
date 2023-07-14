#include "headers/global.h"
#include "headers/generator.h"
#include "headers/cnsl.h"
#include <string>
#include <iostream>
int main() {
	using namespace std;
	generator Generator;
	entity Entity;
	cnsl::clear();
	cnsl::color(ConsoleColorAttributes::Yellow_FG);
	cout << "NOTE: STAT INCREASES, WEIGHT LEVEL MULTIPLIER,\nSPAWN PACK,SPAWN PACK DISTANCE, BASE ENTITY AREN'T FUNCTIONAL YET IN THE DATAPACK\n";
	cout << "INT = Integer (whole number)\n";
	cout << "FLOAT = Floats (decimal number)\n";
	cout << "BOOLEAN = True or False value (0 or 1)\n";
	cout << "Thank You for downloading this garbage! I really don't care :smily_face:!\n";
	cout << "[FACT] writing this yourself will be faster lol so stop being lazy xD \n";
	cout << "There are some macros like 'INF' for the integer limit\n";
	cout << "Pro Tip! you don't need to type the minecraft namespace!\n";
	cout << "There aren\'t any easter eggs!\n";
	cnsl::reset_color();
	
	Generator.dialogue(Entity,json::keys::registry,"what mob will it use as it's spawning condition and replace in the world? (the registry type --help to get some spawning conditions) (STRING) ");
	Generator.dialogue(Entity,json::keys::name, "technical mob name (not actual CustomName) (STRING)? ");
	Generator.dialogue(Entity,json::keys::weight, "weight (INT)? ");
	Generator.dialogue(Entity,json::keys::weight_level_multiplier, "weight level multiplier(FLOAT '.' to skip)? ");
	Generator.dialogue(Entity,json::keys::base_entity,"Base entity (type '.' for same entity as the registry or first input) i register to zombie (to use zombies spawning conditions) but i want to spawn cows \nMy first input will be zombie and this input will be cow(STRING)");
#if __PUBLIC_RELEASE == false
	cnsl::print_colored_reset("uses binomial distribution where N is the amount of tries, \n P is the chance B is the base(amount added if success float)", ConsoleColorAttributes::Cyan_FG);
#endif
#if __PUBLIC_RELEASE == true
	cnsl::print_colored_reset("stat increases: ", ConsoleColorAttributes::Magenta_FG);
	cnsl::print_colored_reset("uses binomial distribution where N is the amount of tries, \n P is the chance B is the base(amount added if success float)", ConsoleColorAttributes::Cyan_FG);
	Generator.dialogue(Entity, json::keys::stat_increases,"");
	if (Entity.hasStatIncreases) {
#endif
		Generator.dialogue(Entity, json::keys::flat_stat_increases, "Flat Stats (Y / N '.' to skip)? ");
		if (Entity.hasFlatStatIncreases) {
			Generator.dialogue(Entity, json::keys::F_health, "Flat Health (n,p,b '.' to skip)?");
			Generator.dialogue(Entity, json::keys::F_damage, "Flat Damage (n,p,b '.' to skip)?");
			Generator.dialogue(Entity, json::keys::F_speed, "Flat Speed (n,p,b '.' to skip)?");
			Generator.dialogue(Entity, json::keys::F_armor,  "Flat  Armor  (n,p,b '.' to skip)?");
			Generator.dialogue(Entity, json::keys::F_armor_toughness, "Flat Armor Toughness (n,p,b '.' to skip)?");
			Generator.dialogue(Entity, json::keys::F_attack_speed, "Flat Attack Speed (n,p,b '.' to skip)?");
			Generator.dialogue(Entity, json::keys::F_sight_range, "Flat Sight Range (n,p,b '.' to skip)?");
		}
#if __PUBLIC_RELEASE == true
		Generator.dialogue(Entity, json::keys::percentage_stat_increases, "Percentage Stats ( Y / N '.' to skip)? ");
		if (Entity.hasPercentageStatIncreases) {
			Generator.dialogue(Entity, json::keys::P_health, "Percentage Health (n,p,b '.' to skip)?");
			Generator.dialogue(Entity, json::keys::P_damage, "Percentage Damage (n,p,b '.' to skip)?");
			Generator.dialogue(Entity, json::keys::P_speed, "Percentage Speed (n,p,b '.' to skip)?");
			Generator.dialogue(Entity, json::keys::P_armor, "Percentage Armor  (n,p,b '.' to skip)?");
			Generator.dialogue(Entity, json::keys::P_armor_toughness, "Percentage Armor Toughness (n,p,b '.' to skip)?");
			Generator.dialogue(Entity, json::keys::P_attack_speed, "Percentage Attack Speed (n,p,b '.' to skip)?");
			Generator.dialogue(Entity, json::keys::P_sight_range, "Percentage Sight Range (n,p,b '.' to skip)?"); 
		}
	}
#endif
	Generator.dialogue(Entity, json::keys::requirements, "requirements (Y / N)?");
	// i was going to write 'execute if' instead of if statement :facepalm:
	if (Entity.hasRequirements) {
		Generator.dialogue(Entity, json::keys::moon_phase, "Moon Phase (Y / N '.' to skip?)");
		Generator.dialogue(Entity, json::keys::level, "level (Y / N '.' to skip)?");
		Generator.dialogue(Entity, json::keys::dimension, "dimension(STRING '.' to skip)");
		Generator.dialogue(Entity, json::keys::biome, "biome(STRING '.' to skip)");
		Generator.dialogue(Entity, json::keys::block, "block(STRING '.' to skip)");
	}
	Generator.dialogue(Entity, json::keys::spawn_pack, "spawn pack size (INT)(Y / N)?");
	if(Entity.hasSpawnPack)
	Generator.dialogue(Entity, json::keys::spawn_pack_distance, "spawn pack distance (FLOAT)(Y / N)?");

	Generator.dialogue(Entity, json::keys::NBT, "NBT (do empty brackets {} for none): ");
	Entity.print();
	Entity.printCommand();
	std::string input;
	while (true) {
		cout << "\nMake Another Mob? (Y / N)";
		std::cin >> input;
		if (input == "Y" || input == "y")
			main();
		else if (input == "N" || input == "n") {
			std::cout << "Whyyyyyyyyyyyyy bad man ;( <--------------------- you made HereAfterDestruction sad\nDont you feel embrassed? you monster smh smh";
			exit(EXIT_SUCCESS);
		}
		else
			cout << "\nDummy enter (Y / N)!";
	}
}
