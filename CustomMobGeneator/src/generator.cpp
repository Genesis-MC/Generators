#include "headers/generator.h"

void entity::print() {
	using namespace std;
	cnsl::color(ConsoleColorAttributes::Blue_FG);
	cout << "\nRegistry: " << m_Registry;
	cnsl::color(ConsoleColorAttributes::Green_FG);
	cout << "\nname: " << m_Name;
	cnsl::color(ConsoleColorAttributes::Bright_Blue_FG);
	cout << "\nweight: " << m_Weight;
	cnsl::color(ConsoleColorAttributes::Red_FG);
	cout << "\nspawn_pack_distance" << m_Spawn_pack_distance;
	cnsl::color(ConsoleColorAttributes::Magenta_FG);
	cout << "\nspawn_pack" << m_Spawn_pack;
	cnsl::color(ConsoleColorAttributes::Yellow_FG);
	cout << "\nweight_level_multiplier" << m_Weight_level_multiplier;
	cnsl::color(ConsoleColorAttributes::Bright_Black_FG);
	cout << "\nbase_entity: " << m_Base_entity;
	cnsl::color(ConsoleColorAttributes::Light_Gray_FG);
	cout << "\nentity_data: " << m_Entity_data;
	cnsl::color(ConsoleColorAttributes::Cyan_FG);
	cout << "\nstat_increases" << m_Stat_increases;
	cnsl::print_colored_reset("\nrequirements: {", ConsoleColorAttributes::Blue_FG);
	cnsl::color(ConsoleColorAttributes::Green_FG);
	cout << "\nlevel" << m_Level;
	cnsl::color(ConsoleColorAttributes::Light_Cyan_FG);
	cout << "\nmoon_phase" << m_Moon_phase;
	cnsl::color(ConsoleColorAttributes::Red_FG);
	cout << "\nbiome: " << m_Biome;
	cnsl::color(ConsoleColorAttributes::Cyan_FG);
	cout << "\ndimension: " << m_Dimension;
	cnsl::color(ConsoleColorAttributes::Magenta_FG);
	cout << "\nblock: " << m_Block;
	cnsl::reset_color();
	cnsl::print_colored_reset("\n}", ConsoleColorAttributes::Blue_FG);
}
void entity::printCommand() {
	using namespace std;
	cnsl::color(ConsoleColorAttributes::Yellow_FG);
	std::cout << "\n-----------------------------------------------\n";
	std::cout << "The Command :\n";
	std::cout << "data modify storage gen:mobs registry.";
	std::cout << m_Registry;
	std::cout << " append value {name:\"";
	std::cout << m_Name << '"';
	std::cout << ",weight:";
	std::cout << m_Weight;
	if (m_Weight_level_multiplier != 0.0f)
		std::cout << ",wieght_level_multiplier:{value:" << to_string(m_Weight_level_multiplier) << "f}";
	if (m_Base_entity != m_Registry)
		std::cout << ",base_entity:\"" << m_Base_entity << '"';
	string Command = "";
	int SavedSize;
	if (hasSpawnPack) {
		Command += ",spawn_pack:";
		SavedSize = (int)Command.size();
		if (m_Spawn_pack.min != 0)Command += ",min:" + to_string(m_Spawn_pack.min);
		if (m_Spawn_pack.max != 0)Command += ",max:" + to_string(m_Spawn_pack.max);
		if (Command[SavedSize] == ',')
			Command[SavedSize] = '{';
		Command += "}";
	}
	if (hasSpawnPackDistance) {
		Command += ",spawn_pack_distance:";
		SavedSize = (int)Command.size();
		if (m_Spawn_pack_distance.min != 0)Command += ",min:" + to_string(m_Spawn_pack_distance.min) + "f";
		if (m_Spawn_pack_distance.max != 0)Command += ",max:" + to_string(m_Spawn_pack_distance.max) + "f";
		if (Command[SavedSize] == ',')
			Command[SavedSize] = '{';
		Command += "}";
	}
	if (hasFlatStatIncreases || hasPercentageStatIncreases) {
		Command += ",stat_increases:{";
		if (hasFlatStatIncreases) {
			Command += "flat:";
			SavedSize = (int)Command.size();
			if (m_Stat_increases.F_health.hasValue())
				Command += ",health:{n:" + to_string(m_Stat_increases.F_health.n) + "s,p:" + to_string(m_Stat_increases.F_health.p) + "b,b:" + to_string(m_Stat_increases.F_health.b) + "f}";
			if (m_Stat_increases.F_damage.hasValue())
				Command += ",damage:{n:" + to_string(m_Stat_increases.F_damage.n) + "s,p:" + to_string(m_Stat_increases.F_damage.p) + "b,b:" + to_string(m_Stat_increases.F_damage.b) + "f}";
			if (m_Stat_increases.F_armor.hasValue())
				Command += ",armor:{n:" + to_string(m_Stat_increases.F_armor.n) + "s,p:" + to_string(m_Stat_increases.F_armor.p) + "b,b:" + to_string(m_Stat_increases.F_armor.b) + "f}";
			if (m_Stat_increases.F_armor_toughness.hasValue())
				Command += ",armor_toughness:{n:" + to_string(m_Stat_increases.F_armor_toughness.n) + "s,p:" + to_string(m_Stat_increases.F_armor_toughness.p) + "b,b:" + to_string(m_Stat_increases.F_armor_toughness.b) + "f}";
			if (m_Stat_increases.F_attack_speed.hasValue())
				Command += ",attack_speed:{n:" + to_string(m_Stat_increases.F_attack_speed.n) + "s,p:" + to_string(m_Stat_increases.F_attack_speed.p) + "b,b:" + to_string(m_Stat_increases.F_attack_speed.b) + "f}";
			if (m_Stat_increases.F_sight_range.hasValue())
				Command += ",sight_range:{n:" + to_string(m_Stat_increases.F_sight_range.n) + "s,p:" + to_string(m_Stat_increases.F_sight_range.p) + "b,b:" + to_string(m_Stat_increases.F_sight_range.b) + "f}";
			if (m_Stat_increases.F_speed.hasValue())
				Command += ",speed:{n:" + to_string(m_Stat_increases.F_speed.n) + "s,p:" + to_string(m_Stat_increases.F_speed.p) + "b,b:" + to_string(m_Stat_increases.F_speed.b) + "f}";
			if (m_Stat_increases.P_knockback_resistance.hasValue())
				Command += ",knockback_resistance:{n:" + to_string(m_Stat_increases.P_knockback_resistance.n) + "s,p:" + to_string(m_Stat_increases.P_knockback_resistance.p) + "b,b:" + to_string(m_Stat_increases.P_knockback_resistance.b) + "f}";
			if (Command[SavedSize] == ',')
				Command[SavedSize] = '{';
			Command += '}';
		}
		if (hasPercentageStatIncreases && hasFlatStatIncreases)
			Command += ',';
		if (hasPercentageStatIncreases) {
			Command += "percentage:";
			SavedSize = (int)Command.size();
			if (m_Stat_increases.P_health.hasValue())
				Command += ",health:{n:" + to_string(m_Stat_increases.P_health.n) + "s,p:" + to_string(m_Stat_increases.P_health.p) + "b,b:" + to_string(m_Stat_increases.P_health.b) + "f}";
			if (m_Stat_increases.P_damage.hasValue())
				Command += ",damage:{n:" + to_string(m_Stat_increases.P_damage.n) + "s,p:" + to_string(m_Stat_increases.P_damage.p) + "b,b:" + to_string(m_Stat_increases.P_damage.b) + "f}";
			if (m_Stat_increases.P_armor.hasValue())
				Command += ",armor:{n:" + to_string(m_Stat_increases.P_armor.n) + "s,p:" + to_string(m_Stat_increases.P_armor.p) + "b,b:" + to_string(m_Stat_increases.P_armor.b) + "f}";
			if (m_Stat_increases.P_armor_toughness.hasValue())
				Command += ",armor_toughness:{n:" + to_string(m_Stat_increases.P_armor_toughness.n) + "s,p:" + to_string(m_Stat_increases.P_armor_toughness.p) + "b,b:" + to_string(m_Stat_increases.P_armor_toughness.b) + "f}";
			if (m_Stat_increases.P_attack_speed.hasValue())
				Command += ",attack_speed:{n:" + to_string(m_Stat_increases.P_attack_speed.n) + "s,p:" + to_string(m_Stat_increases.P_attack_speed.p) + "b,b:" + to_string(m_Stat_increases.P_attack_speed.b) + "f}";
			if (m_Stat_increases.P_sight_range.hasValue())
				Command += ",sight_range:{n:" + to_string(m_Stat_increases.P_sight_range.n) + "s,p:" + to_string(m_Stat_increases.P_sight_range.p) + "b,b:" + to_string(m_Stat_increases.P_sight_range.b) + "f}";
			if (m_Stat_increases.P_speed.hasValue())
				Command += ",speed:{n:" + to_string(m_Stat_increases.P_speed.n) + "s,p:" + to_string(m_Stat_increases.P_speed.p) + "b,b:" + to_string(m_Stat_increases.P_speed.b) + "f}";
			if (m_Stat_increases.P_knockback_resistance.hasValue())
				Command += ",knockback_resistance:{n:" + to_string(m_Stat_increases.P_knockback_resistance.n) + "s,p:" + to_string(m_Stat_increases.P_knockback_resistance.p) + "b,b:" + to_string(m_Stat_increases.P_knockback_resistance.b) + "f}";
			if (Command[SavedSize] == ',')
				Command[SavedSize] = '{';
			Command += '}';
		}
		Command += '}';
	}
	if (hasRequirements) {
		Command += ",requirements:{";
		if (hasMoonPhase) {
			Command += "moon_phase:{";
			if (m_Moon_phase.min != 0) Command += "min:" + to_string(m_Moon_phase.min) + "b,";
			if (m_Moon_phase.max != 0) Command += "max:" + to_string(m_Moon_phase.max) + "b,";
			if (m_Moon_phase.except != 0) Command += "except:" + to_string(m_Moon_phase.except) + "b,";
			if (m_Moon_phase.exact != 0) Command += "exact:" + to_string(m_Moon_phase.exact) + "b,";
			if (m_Moon_phase.on_even_days != 0) Command += "on_even_days:1b";
			if (m_Moon_phase.on_odd_days != 0) Command += "on_odd_days:1b";
			if (m_Moon_phase.on_prime_days != 0) Command += "on_prime_days:1b";
			if (m_Moon_phase.blood_moon != 0) Command += "blood_moon:1b";
			Command[Command.size() - 1] = '}';
		}
		if (hasLevel) {
			if (Command[Command.size() - 1] == '}') Command += ',';
			Command += "level:{";
			if (m_Level.min != 0) Command += "min:" + to_string(m_Level.min) + ",";
			if (m_Level.max != INT_LIMIT) Command += "max:" + to_string(m_Level.max) + ",";
			Command[Command.size() - 1] = '}';
		}
		if (hasDimension) {
			if (Command[Command.size() - 1] == '}') Command += ',';
			Command += "dimension:\"" + m_Dimension + "\",";
			if (m_Dimension[0] == '#')
				Command += "dimensionTag:1b,";
		}
		if (hasBlock) {
			if (Command[Command.size() - 1] == '}') Command += ',';
			Command += "block:\"" + m_Block + "\",";
			if (m_Block[0] == '#')
				Command += "blockTag:1b,";
		}
		if (hasBiome) {
			if (Command[Command.size() - 1] == '}') Command += ',';
			Command += "biome:\"" + m_Biome + "\",";
			if (m_Biome[0] == '#')
				Command += "biomeTag:1b,";
		}
		Command[Command.size() - 1] = '}';
	}
	if (hasNBT) {
		Command += ",entity_data:";
		Command += m_NBT;
	}
	std::cout << Command;
	std::cout << "}";
	cnsl::reset_color();
}
int generator::dialogue(entity& Entity, int key, const std::string& saying) {
	using namespace std;
	std::string input;
	if (saying != "")
		std::cout << '\n';
	std::cout << saying;
	std::cin >> input;
	std::string inputLowercase = input;
	std::string inputUppercase = input;
	sutils::lowercase(inputLowercase);
	sutils::uppercase(inputUppercase);
	if (key == json::keys::registry) { // ik switch exists it is just that i can't hide it unlike if which is annoying
		if (inputLowercase == "-- help" || inputLowercase == "--help") {
			printHelp(Help::Registry);
			this->dialogue(Entity, key, saying);
		}
		else if (!valid_entity(inputLowercase)) {
			THROW_ERROR("Invalid Entity");
		}
		else
			Entity.m_Registry = inputLowercase;
	}
	else if (key == json::keys::name) {
			Entity.m_Name = inputLowercase;
			if (inputLowercase == "dad")
				Entity.m_Name = nullptr;
			else if (inputLowercase == "hereafterdestruction")
				Entity.m_Name = "Hi whats up guys I am EDP445 subscribe to my onlyfans at HereAfterThePoliceRaidedMyHouse and donate me cupcakes and kidneys I also like chil- chilli they are so hot and tasty!!!!!!!";
			else if (inputLowercase == "puckisilver")
				Entity.m_Name = "PuckiSilver you so cringe smh sucking at English man has a 'B' Profile Pic while his name has a 'P' learn some english mate boom roasted:sunglasses:!";
			else if (inputLowercase == "eroxen")
				Entity.m_Name = "oh oh Eroxen more like ripoff Enard from Wish.com silly goose!";
			else if (inputLowercase == "electross")
				Entity.m_Name = "Electross i can't say anything bad about you or i will get banned!";
			else if (inputLowercase == "flyrr_" || inputLowercase == "flyrr")
				Entity.m_Name = "whats up guys before starting this video i am going to tell you about my sponser BisectHosting_TM it is so good I am tottally not held at gunpoint!";
			else if (inputLowercase == "klloo")
				Entity.m_Name = "oh it is Klloo the clueless!";
			else if (inputLowercase == "dynia")
				Entity.m_Name = "can't find something :/!";
			else if (inputLowercase == "silabear")
				Entity.m_Name = "I can't BEAR him he is so annoying!!!!!!!!!!!!!!!!!!!!!!!!";
			else if (inputLowercase == "wuflian")
				Entity.m_Name = "ripoff moxvallix";
			else if (inputLowercase == "moxvallix")
				Entity.m_Name = "ripoff wuflian";
			else if (inputLowercase == "failure")
				Entity.m_Name = "HereAfterDestruction";
			else if (inputLowercase == "chimedragon")
				Entity.m_Name = "chimeez deez nuts";
			else if (inputLowercase == "yandev")
				Entity.m_Name = "HereAfterDestruction is going to become the new yandev with this source code!";
			else if (inputLowercase == "__foxman__")
				Entity.m_Name = "time to make a zelda remake! HereAfterDestruction :cry:";
			else if (inputLowercase == "amongus")
				Entity.m_Name = "yes i did waste alot of time making these!";
			else if (inputLowercase == "c++")
				Entity.m_Name = "positive pain";
			else if (inputLowercase == "c--")
				Entity.m_Name = "negative pain?";
			else if (inputLowercase == "c")
				Entity.m_Name = "pain?";
	}
	else if (key == json::keys::weight) {
		if (!sutils::all_number(input) || input[0] == '-') {
			THROW_ERROR("Invalid Input: The input must be a positive number!");
		}
		else if (input.size() > 10) {
			THROW_ERROR("Invalid Input: The input must not be greater than 2,147,483,647!");
		}
		else if (input == "INF") {
			Entity.m_Weight = INT_LIMIT;
		}
		else {
			Entity.m_Weight = sutils::convert_to_number(input);
			if (Entity.m_Weight < 0) Entity.m_Weight *= -1;
			//int number = convert_to_number(input);
			//cout << "weight : " << number;
		}
	}
	else if (key == json::keys::weight_level_multiplier) {
		if (input == ".") Entity.m_Weight_level_multiplier = 0.0f;
		else if (input[0] == '-') {
			THROW_ERROR("Invalid Input: The input must be a positive number!");
		}
		else if (input[0] <= '0' || input[0] >= '9') {
			THROW_ERROR("Dummy enter a decimal number!");
		}
		else if (input.size() > 10) {
			THROW_ERROR("Invalid Input: The input must not be greater than 2,147,483,647!");
		}
		else if (input == "INF") {
			Entity.m_Weight_level_multiplier = (float)INT_LIMIT;
		}
		else {
			Entity.m_Weight_level_multiplier = std::stof(input);
		}
	}

	else if (key == json::keys::base_entity) {
		if (inputLowercase == ".")
			Entity.m_Base_entity = Entity.m_Registry;
		else
			if (!valid_entity(inputLowercase)) {
				THROW_ERROR("Invalid Entity");
			}
			else
				Entity.m_Base_entity = inputLowercase;
	}
	else if (key == json::keys::stat_increases) {
		Entity.hasStatIncreases = inputUppercase == "Y";
		if (Entity.hasStatIncreases) {
			cnsl::print_colored_reset("NOTE: \n( N = INT, P = INT ,B = INT/100)\nExample if I Type 10,30,50 N = 10, P= 30%, Base = 0.5\n", ConsoleColorAttributes::Cyan_FG);
		}
		else if (inputLowercase == "." || inputUppercase == "N" && Entity.hasFlatStatIncreases == false) Entity.hasStatIncreases = false;
		else {
			THROW_ERROR("Dummy type Y / N!");
		}
	}
	else if (key == json::keys::flat_stat_increases) {
		Entity.hasFlatStatIncreases = inputUppercase == "Y";
		// 1 less string comparison performance stonks
		if (inputLowercase != "." && inputUppercase != "N" && Entity.hasFlatStatIncreases == false) {
			THROW_ERROR("Dummy type Y / N!");
		}
	}
	else if (key == json::keys::percentage_stat_increases) {
		Entity.hasPercentageStatIncreases = inputUppercase == "Y";
		// 1 less string comparison performance stonks
		if (inputLowercase != "." && inputUppercase != "N" && Entity.hasPercentageStatIncreases == false) {
			THROW_ERROR("Dummy type Y / N!");
		}
	}
	else if (key == json::keys::requirements) {
		Entity.hasRequirements = inputUppercase == "Y";
		// 1 less string comparison performance stonks
		if (inputUppercase != "N" && inputUppercase != "." && Entity.hasRequirements == false) {
			THROW_ERROR("Dummy type Y / N!");
		}
	}
	else if (key == json::keys::moon_phase) {
		Entity.hasMoonPhase = inputUppercase == "Y";
		if (inputUppercase != "N" && inputUppercase != "." && Entity.hasMoonPhase == false) {
			THROW_ERROR("Dummy type Y / N!");
		}
		else if (Entity.hasMoonPhase == true) {

			bool CanHaveExact = true;
			cout << "Min (1-8 '.' to skip):";
			std::cin >> input;
			if (input == ".")Entity.m_Moon_phase.min = 0;
			else if (sutils::convert_to_number(input) > 8 || sutils::convert_to_number(input) < 1) { THROW_ERROR("Dummy enter the range is 1-8 it is litterally there!"); }
			else if (!sutils::all_number(input)) { THROW_ERROR("Dummy enter a fricking number!"); }
			else { Entity.m_Moon_phase.min = sutils::convert_to_number(input); CanHaveExact = false; }


			cout << "Max (1-8 '.' to skip):";
			std::cin >> input;
			if (input == ".") { Entity.m_Moon_phase.max = 0; }
			else if (sutils::convert_to_number(input) > 8 || sutils::convert_to_number(input) < 1) {
				THROW_ERROR("Dummy enter the range is 1-8 it is litterally there!");
			}
			else if (sutils::convert_to_number(input) <= Entity.m_Moon_phase.min) {
				THROW_ERROR("Dummy enter the max can't be less than the min or equal to it!!");
			}
			else if (sutils::all_number(input)) {
				Entity.m_Moon_phase.max = sutils::convert_to_number(input);
				CanHaveExact = false;
			}
			else { THROW_ERROR("Dummy enter a fricking number!"); }


			cout << "Except (1-8 '.' to skip):";
			std::cin >> input;
			if (input == ".") Entity.m_Moon_phase.except = 0;
			else if (sutils::convert_to_number(input) > 8 || sutils::convert_to_number(input) < 1) { THROW_ERROR("Dummy enter the range is 1-8 it is litterally there!"); }
			else if (Entity.m_Moon_phase.min != 0 && Entity.m_Moon_phase.max != 0 && (sutils::convert_to_number(input) < Entity.m_Moon_phase.min || sutils::convert_to_number(input) > Entity.m_Moon_phase.max))
			{
					THROW_ERROR("Dummy the exception must be in the range of the min and max!");
			}
			else if (sutils::all_number(input)) {
				Entity.m_Moon_phase.except = sutils::convert_to_number(input);
				CanHaveExact = false;
			}
			else { THROW_ERROR("Dummy enter a fricking number!"); }

			// me thought 1 was prime :skull: when you skip basic math class
			cout << "On Prime Days (2,3,5,7 '.' to skip 0 / 1):"; 
			std::cin >> input;
			if (input == ".") Entity.m_Moon_phase.on_prime_days = false;
			else if (sutils::convert_to_number(input) < 0 || sutils::convert_to_number(input) > 1) { THROW_ERROR("Dummy enter it is a boolean value!"); }
			else if (sutils::all_number(input)) {
				Entity.m_Moon_phase.on_prime_days = (bool)sutils::convert_to_number(input);
				CanHaveExact = false;
			}
			else { THROW_ERROR("Dummy enter a boolean value 0 or 1"); }

			if (!Entity.m_Moon_phase.on_prime_days) {
				cout << "On Even Days (2,4,6,8 '.' to skip 0 / 1):";
				std::cin >> input;
				if (input == ".") Entity.m_Moon_phase.on_even_days = false;
				else if (sutils::convert_to_number(input) < 0 || sutils::convert_to_number(input) > 1) { THROW_ERROR("Dummy enter it is a boolean value!"); }
				else if (sutils::all_number(input)) {
					Entity.m_Moon_phase.on_even_days = (bool)sutils::convert_to_number(input);
					CanHaveExact = false;
				}
				else { THROW_ERROR("Dummy enter a boolean value 0 or 1"); }
			}

			// 0 1 2 3 4 5 6 7
			//   1 2 3 4 5 6 7 8
			if (!Entity.m_Moon_phase.on_prime_days && !Entity.m_Moon_phase.on_even_days) {
				cout << "On Odd Days (1,3,5,7 '.' to skip, 0 / 1):";
				std::cin >> input;
				if (input == ".") Entity.m_Moon_phase.on_odd_days = false;
				else if (sutils::convert_to_number(input) < 0 || sutils::convert_to_number(input) > 1) { THROW_ERROR("Dummy enter it is a boolean value!"); }
				else if (sutils::all_number(input)) {
					Entity.m_Moon_phase.on_prime_days = (bool)sutils::convert_to_number(input);
					CanHaveExact = false;
				}
				else { THROW_ERROR("Dummy enter a boolean value 0 or 1!"); }
			}


			if (CanHaveExact) {
				cout << "Exact (1-8):";
				std::cin >> input;
				if (input == ".") Entity.m_Moon_phase.except = 0;
				else if (sutils::convert_to_number(input) > 8 || sutils::convert_to_number(input) < 1) { THROW_ERROR("Dummy enter the range is 1-8 it is litterally there!"); }
				else if (sutils::all_number(input)) Entity.m_Moon_phase.exact = sutils::convert_to_number(input);
				else { THROW_ERROR("Dummy enter a fricking number!"); }
			}
			cout << "Blood Moon (boolean 0 / 1 '.' to skip):";
			std::cin >> input;
			if (input == ".") Entity.m_Moon_phase.blood_moon = false;
			else if (sutils::convert_to_number(input) < 0 || sutils::convert_to_number(input) > 1) { THROW_ERROR("Dummy enter a boolean value true or false (0 / 1)!"); }
			else Entity.m_Moon_phase.blood_moon = sutils::convert_to_number(input);
		}
	}
	else if (key == json::keys::level) {
		Entity.hasLevel = inputUppercase == "Y";
		if (Entity.hasLevel == true) {
			cout << "Min ('.' to skip):";
			std::cin >> input;
			if (input == ".") {
				Entity.m_Level.min = 0;
			}
			else if (sutils::convert_to_number(input) < -1) {
				THROW_ERROR("Dummy the number can't be negative!");
			}
			else if (!sutils::all_number(input)) {
				THROW_ERROR("Dummy enter a fricking number!");
			}
			else Entity.m_Level.min = sutils::convert_to_number(input);

			cout << "Max ('.' to skip):";
			std::cin >> input;

			if (input == ".") Entity.m_Level.max = INT_LIMIT;
			else if (sutils::convert_to_number(input) < 0) { THROW_ERROR("Dummy the number can't be negative!"); }			else if (sutils::all_number(input)) Entity.m_Level.max = sutils::convert_to_number(input);
			else { THROW_ERROR("Dummy enter a fricking number!"); }
		}
		else if (inputUppercase != "N" && inputUppercase != "." && Entity.hasRequirements == false) { THROW_ERROR("Dummy enter Y / N!"); }
	}
	else if (key == json::keys::spawn_pack) {
		Entity.hasSpawnPack = inputUppercase == "Y";
		if (Entity.hasSpawnPack == true) {
			std::cout << "Min: ";
			std::cin >> input;
			if (sutils::convert_to_number(input) <= 0) { THROW_ERROR("Dummy the number can't be negative or equal to zero!"); }
			else if (!sutils::all_number(input)) { THROW_ERROR("Dummy enter a fricking number!"); }
			else Entity.m_Spawn_pack.min = sutils::convert_to_number(input);

			std::cout << "Max: ";
			std::cin >> input;

			if (sutils::convert_to_number(input) <= 0) { THROW_ERROR("Dummy the number can't be negative or equal to zero!"); }
			else if (!sutils::all_number(input)) { THROW_ERROR("Dummy enter a fricking number!"); }
			else if (sutils::convert_to_number(input) <= Entity.m_Spawn_pack.min) { THROW_ERROR("Dummy the max can't be less or equal to the min!"); }
			else Entity.m_Spawn_pack.max = sutils::convert_to_number(input);
		}
		else if (inputUppercase != "N" && inputUppercase != "." && Entity.hasSpawnPack == false) { THROW_ERROR("Dummy enter Y / N!"); }
	}
	else if (key == json::keys::spawn_pack_distance) {
		Entity.hasSpawnPackDistance = inputUppercase == "Y";
		if (Entity.hasSpawnPackDistance == true) {
			std::cout << "Min: ";
			std::cin >> input;
			if (std::stof(input) <= 0) { THROW_ERROR("Dummy the number can't be negative or equal to zero!"); }
			else Entity.m_Spawn_pack_distance.min = std::stof(input);

			std::cout << "Max: ";
			std::cin >> input;

			if (std::stof(input) <= 0) { THROW_ERROR("Dummy the number can't be negative or equal to zero!"); }
			else if(std::stof(input) <= Entity.m_Spawn_pack_distance.min){ THROW_ERROR("Dummy the max can't be less or equal to the min!"); }
			else Entity.m_Spawn_pack_distance.max = std::stof(input);
		}
		else if (inputUppercase != "N" && inputUppercase != "." && Entity.hasSpawnPackDistance == false) { THROW_ERROR("Dummy enter Y / N!"); }
	}
	else if (key == json::keys::block) {
		if (input == ".") Entity.m_Block = '\0';
		else if (input[0] == '#')
		{
			if (sutils::find_char(inputLowercase, ':')) {
				Entity.m_Block = inputLowercase;
				Entity.hasBlock = true;
			}
			else {
				Entity.hasBlock = true;
				Entity.m_Block += "#minecraft:";
				for (int i = 1; i < inputLowercase.size(); ++i)
					Entity.m_Block += inputLowercase[i];
			}
		}
		else {
			if (!valid_block(inputLowercase)) {
				THROW_ERROR("Invalid Block");
			}
			if (sutils::find_char(inputLowercase, ':')) {
				Entity.hasBlock = true;
				Entity.m_Block = inputLowercase;
			}
			else {
				Entity.m_Block = "minecraft:" + inputLowercase;
				Entity.hasBlock = true;
			}
		}
	}
	else if (key == json::keys::biome) {
		if (input == ".") Entity.m_Biome = '\0';
		else if (input[0] == '#')
		{
			if (sutils::find_char(inputLowercase, ':')) {
				Entity.hasBiome = true;
				Entity.m_Biome = inputLowercase;
			}
			else {
				Entity.hasBiome = true;
				Entity.m_Biome += "#minecraft:";
				for (int i = 1; i < inputLowercase.size(); ++i)
					Entity.m_Biome += inputLowercase[i];
			}
		}
		else {
			if (sutils::find_char(inputLowercase, ':')) {
				Entity.m_Biome = inputLowercase;
				Entity.hasBiome = true;
			}
			else {
				if (!valid_biome(inputLowercase)) {
					THROW_ERROR("Invalid Biome");
				}
				Entity.hasBiome = true;
				Entity.m_Biome = "minecraft:" + inputLowercase;
			}
		}
	}
	else if (key == json::keys::dimension) {
		if (input == ".") Entity.m_Dimension = '\0';
		else if (input[0] == '#')
		{
			if (sutils::find_char(inputLowercase, ':')) {
				Entity.m_Dimension = inputLowercase;
				Entity.hasDimension = true;
			}
			else {
				Entity.hasDimension = true;
				Entity.m_Dimension += "#minecraft:";
				for (int i = 1; i < inputLowercase.size(); ++i)
					Entity.m_Dimension += inputLowercase[i];
			}
		}
		else {
			if (!valid_dimension(inputLowercase)) {
				THROW_ERROR("Invalid Dimension");
			}
			if (sutils::find_char(inputLowercase, ':')) {
				Entity.hasDimension = true;
				Entity.m_Dimension = inputLowercase;
			}
			else {
				Entity.m_Dimension = "minecraft:" + inputLowercase;
				Entity.hasDimension = true;
			}
		}
	}
	else if (key == json::keys::F_knockback_resistance) {
		if (inputUppercase == ".") Entity.m_Stat_increases.F_knockback_resistance = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] <= 0 || In[1] <= 0 || In[2] <= 0) {
				THROW_ERROR("Dummy this accepts whole numbers only bigger than 1 only!");
			}
			Entity.m_Stat_increases.F_knockback_resistance = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
		}
	else if (key == json::keys::P_knockback_resistance) {
			if (inputUppercase == ".") Entity.m_Stat_increases.P_knockback_resistance = { 0,0,0 };
			else {
				int In[3];
				for (int i = 0; i < 3; ++i)
					In[i] = 0;
				sutils::split_convert(In, 3, input, ',');
				if (In[0] <= 0 || In[1] <= 0 || In[2] <= 0) {
					THROW_ERROR("Dummy this accepts whole numbers only bigger than 1 only!");
				}
				Entity.m_Stat_increases.P_knockback_resistance = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
			}
		}
	else if (key == json::keys::F_health) {
		if (inputUppercase == ".") Entity.m_Stat_increases.F_health = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] <= 0 || In[1] <= 0 || In[2] <= 0) {
				THROW_ERROR("Dummy this accepts whole numbers only bigger than 1 only!");
			}
			Entity.m_Stat_increases.F_health = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}
	else if (key == json::keys::F_damage) {
		if (inputUppercase == ".") Entity.m_Stat_increases.F_damage = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] == 0 || In[1] == 0 || In[2] == 0) {
				THROW_ERROR("Dummy this accepts whole numbers bigger than 1 only!");
			}
			Entity.m_Stat_increases.F_damage = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}
	else if (key == json::keys::F_armor) {
		if (inputUppercase == ".") Entity.m_Stat_increases.F_armor = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] == 0 || In[1] == 0 || In[2] == 0) {
				THROW_ERROR("Dummy this accepts whole numbers bigger than 1 only!");
			}
			Entity.m_Stat_increases.F_armor = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}
	else if (key == json::keys::F_armor_toughness) {
		if (inputUppercase == ".") Entity.m_Stat_increases.F_armor_toughness = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] == 0 || In[1] == 0 || In[2] == 0) {
				THROW_ERROR("Dummy this accepts whole numbers bigger than 1 only!");
			}
			Entity.m_Stat_increases.F_armor_toughness = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}
	else if (key == json::keys::F_attack_speed) {
		if (inputUppercase == ".") Entity.m_Stat_increases.F_attack_speed = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] == 0 || In[1] == 0 || In[2] == 0) {
				THROW_ERROR("Dummy this accepts whole numbers bigger than 1 only!");
			}
			Entity.m_Stat_increases.F_attack_speed = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}
	else if (key == json::keys::F_sight_range) {
		if (inputUppercase == ".") Entity.m_Stat_increases.F_sight_range = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] == 0 || In[1] == 0 || In[2] == 0) {
				THROW_ERROR("Dummy this accepts whole numbers bigger than 1 only!");
			}
			Entity.m_Stat_increases.F_sight_range = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}
	else if (key == json::keys::F_speed) {
		if (inputUppercase == ".") Entity.m_Stat_increases.F_speed = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] == 0 || In[1] == 0 || In[2] == 0) {
				THROW_ERROR("Dummy this accepts whole numbers bigger than 1 only!");
			}
			Entity.m_Stat_increases.F_speed = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}

	else if (key == json::keys::P_health) {
		if (inputUppercase == ".") Entity.m_Stat_increases.P_health = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] <= 0 || In[1] <= 0 || In[2] <= 0) {
				THROW_ERROR("Dummy this accepts whole numbers only bigger than 1 only!");
			}
			Entity.m_Stat_increases.P_health = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}
	else if (key == json::keys::P_damage) {
		if (inputUppercase == ".") Entity.m_Stat_increases.P_damage = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] == 0 || In[1] == 0 || In[2] == 0) {
				THROW_ERROR("Dummy this accepts whole numbers bigger than 1 only!");
			}
			Entity.m_Stat_increases.P_damage = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}
	else if (key == json::keys::P_armor) {
		if (inputUppercase == ".") Entity.m_Stat_increases.P_armor = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] == 0 || In[1] == 0 || In[2] == 0) {
				THROW_ERROR("Dummy this accepts whole numbers bigger than 1 only!");
			}
			Entity.m_Stat_increases.P_armor = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}
	else if (key == json::keys::P_armor_toughness) {
		if (inputUppercase == ".") Entity.m_Stat_increases.P_armor_toughness = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] == 0 || In[1] == 0 || In[2] == 0) {
				THROW_ERROR("Dummy this accepts whole numbers bigger than 1 only!");
			}
			Entity.m_Stat_increases.P_armor_toughness = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}
	else if (key == json::keys::P_attack_speed) {
		if (inputUppercase == ".") Entity.m_Stat_increases.P_attack_speed = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] == 0 || In[1] == 0 || In[2] == 0) {
				THROW_ERROR("Dummy this accepts whole numbers bigger than 1 only!");
			}
			Entity.m_Stat_increases.P_attack_speed = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}
	else if (key == json::keys::P_sight_range) {
		if (inputUppercase == ".") Entity.m_Stat_increases.P_sight_range = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] == 0 || In[1] == 0 || In[2] == 0) {
				THROW_ERROR("Dummy this accepts whole numbers bigger than 1 only!");
			}
			Entity.m_Stat_increases.P_sight_range = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}
	else if (key == json::keys::P_speed) {
		if (inputUppercase == ".") Entity.m_Stat_increases.P_speed = { 0,0,0 };
		else {
			int In[3];
			for (int i = 0; i < 3; ++i)
				In[i] = 0;
			sutils::split_convert(In, 3, input, ',');
			if (In[0] == 0 || In[1] == 0 || In[2] == 0) {
				THROW_ERROR("Dummy this accepts whole numbers bigger than 1 only!");
			}
			Entity.m_Stat_increases.P_speed = { (short)In[0],(char)In[1] ,(float)In[2] / 100 };
		}
	}

	else if (key == json::keys::NBT) {
		if (input[0] != '{' || input[input.size() - 1] != '}') { THROW_ERROR("The NBT must be in brackets!"); }
		else if (input[0] == '{' && input[1] == '}') { Entity.hasNBT = false; }
		else { Entity.m_NBT = input, Entity.hasNBT = true; }
	}

	return 0;
}



inline std::ostream& operator <<(std::ostream& os, const moon_phase& m) {
	os << "\nExact: " << (int)m.exact;
	os << "\nExcept: " << (int)m.except;
	os << "\nOn Even Days: " << (int)m.on_even_days;
	os << "\nOn Odd Days: " << (int)m.on_odd_days;
	os << "\nOn Prime Days: " << (int)m.on_prime_days;
	os << "\nMin: " << (int)m.min << " | Max: " << (int)m.max;
	return os;
}
inline std::ostream& operator <<(std::ostream& os, const spawn_pack& s) {
	os << "\nExact: " << s.exact;
	os << "\nMin: " << s.min << " | Max: " << s.max;
	return os;
}
inline std::ostream& operator <<(std::ostream& os, const level& m) {
	os << "\nMin: " << (int)m.min << " | Max: " << (int)m.max;
	return os;
}
inline std::ostream& operator <<(std::ostream& os, const min_max& m) {
	os << "\nMin: " << (int)m.min << " | Max: " << (int)m.max;
	return os;
}
inline std::ostream& operator <<(std::ostream& os, const stat_increases& s) {
	os << "\n F = Flat";
	os << "\n F Health               N: " << s.F_health.n << " | P: " << (float)s.F_health.p / 100 << " | B: " << s.F_health.b;
	os << "\n F Damage               N: " << s.F_damage.n << " | P: " << (float)s.F_damage.p / 100 << " | B: " << s.F_damage.b;
	os << "\n F Speed                N: " << s.F_speed.n << " | P: " << (float)s.F_speed.p / 100 << " | B: " << s.F_speed.b;
	os << "\n F Sight Range          N: " << s.F_sight_range.n << " | P: " << (float)s.F_sight_range.p / 100 << " | B: " << s.F_sight_range.b;
	os << "\n F Attack Speed         N: " << s.F_attack_speed.n << " | P: " << (float)s.F_attack_speed.p / 100 << " | B: " << s.F_attack_speed.b;
	os << "\n F Armor                N: " << s.F_armor.n << " | P: " << (float)s.F_armor.p / 100 << " | B: " << s.F_armor.b;
	os << "\n F Armor Toughness      N: " << s.F_armor_toughness.n << " | P: " << (float)s.F_armor_toughness.p / 100 << " | B: " << s.F_armor_toughness.b;
	os << "\n F Knockback Resistance N: " << s.F_knockback_resistance.n << " | P: " << (float)s.F_knockback_resistance.p / 100 << " | B: " << s.F_knockback_resistance.b;
#if __PUBLIC_RELEASE == true
	os << "\n--------------------------------------------";
	os << "\n % = Percentage";
	os << "\n % Health               N: " << s.P_health.n << " | P: " << (float)s.P_health.p / 100 << " | B: " << s.P_health.b;
	os << "\n % Damage               N: " << s.P_damage.n << " | P: " << (float)s.P_damage.p / 100 << " | B: " << s.P_damage.b;
	os << "\n % Speed                N: " << s.P_speed.n << " | P: " << (float)s.P_speed.p / 100 << " | B: " << s.P_speed.b;
	os << "\n % Sight Range          N: " << s.P_sight_range.n << " | P: " << (float)s.P_sight_range.p / 100 << " | B: " << s.P_sight_range.b;
	os << "\n % Attack Speed         N: " << s.P_attack_speed.n << " | P: " << (float)s.P_attack_speed.p / 100 << " | B: " << s.P_attack_speed.b;
	os << "\n % Armor                N: " << s.P_armor.n << " | P: " << (float)s.P_armor.p / 100 << " | B: " << s.P_armor.b;
	os << "\n % Armor Toughness      N: " << s.P_armor_toughness.n << " | P: " << (float)s.P_armor_toughness.p / 100 << " | B: " << s.P_armor_toughness.b;
	os << "\n % Knockback Resistance N: " << s.P_knockback_resistance.n << " | P: " << (float)s.P_knockback_resistance.p / 100 << " | B: " << s.P_knockback_resistance.b;
#endif
	return os;
}
inline bool operator==(const binomial B1, const binomial B2) {
	return (B1.n == B2.n && B1.p == B2.p);
}