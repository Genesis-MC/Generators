#include "headers/generator.hpp"

// cs student moment
// kill me
using namespace sutils;
using std::cout,std::string,std::to_string;
using cnsl::clear,cnsl::print_colored,cnsl::print_colored_reset;

#define THROW_ERROR(error,function) \
cnsl::print_colored_reset(error,RED_ERROR);\
function;\
return -1

#define THROW_WARNING(warning) \
cnsl::print_colored_reset(warning, YELLOW_WARN)

static std::string input;
static std::string inputLowercase;
static std::string inputUppercase;
constexpr ConsoleColorAttributes RED_ERROR = ConsoleColorAttributes::Red_FG;
constexpr ConsoleColorAttributes YELLOW_WARN = ConsoleColorAttributes::Yellow_FG;

void getInput()
{
  std::getline(std::cin, input);
  inputLowercase = input;
  sutils::lowercase(inputLowercase);

  inputUppercase = input;
  sutils::uppercase(inputUppercase);
}

void Generator::start()
{
  registry();
  name();
  weight();
  weightLevelMultiplier();
  baseEntity();
  requirements();

  if (this->Entity.hasRequirements)
  {
    level();
    moonPhase();
    block();
    biome();
  }
  FstatIncreases();
  if (Entity.StatIncreases.hasFStats == 1) {
    statIncreases("\nDamage: ", &Entity.StatIncreases.F_Damage.n);
    statIncreases("\nHealth: ", &Entity.StatIncreases.F_Health.n);
    statIncreases("\nArmor: ", &Entity.StatIncreases.F_Armor.n);
    statIncreases("\nArmorToughness: ", &Entity.StatIncreases.F_ArmorToughness.n);
    statIncreases("\nAttack_Speed: ", &Entity.StatIncreases.F_Attack_Speed.n);
    statIncreases("\nKnockBack: ", &Entity.StatIncreases.F_KnockBack.n);
    statIncreases("\nSpeed: ", &Entity.StatIncreases.F_Speed.n);
    statIncreases("\nFollowRange: ", &Entity.StatIncreases.F_FollowRange.n);
  }
  PstatIncreases();
  if (Entity.StatIncreases.hasPStats == 1) {
    statIncreases("\nDamage: ", &Entity.StatIncreases.P_Damage.n);
    statIncreases("\nHealth: ", &Entity.StatIncreases.P_Health.n);
    statIncreases("\nArmor: ", &Entity.StatIncreases.P_Armor.n);
    statIncreases("\nArmorToughness: ", &Entity.StatIncreases.P_ArmorToughness.n);
    statIncreases("\nAttack_Speed: ", &Entity.StatIncreases.P_Attack_Speed.n);
    statIncreases("\nKnockBack: ", &Entity.StatIncreases.P_KnockBack.n);
    statIncreases("\nSpeed: ", &Entity.StatIncreases.P_Speed.n);
    statIncreases("\nFollowRange: ", &Entity.StatIncreases.P_FollowRange.n);
  }
  summonFunction();
  NBT();
  print();
  printCommand();

  while (true) {
    cnsl::print_colored_reset("\nWant To Make Another Mob? ", ConsoleColorAttributes::Cyan_FG);

    getInput();
    if (input == "y" || input == "Y")
      start();
    else
      break;
  }
}
void Generator::print()
{
  //cnsl::color(ConsoleColorAttributes::Blue_FG);
  //cout << "\nRegistry: " << Entity.Registry;
  //cnsl::color(ConsoleColorAttributes::Green_FG);
  //cout << "\nname: " << Entity.Name;
  //cnsl::color(ConsoleColorAttributes::Bright_Blue_FG);
  //cout << "\nweight: " << Entity.Weight;
  //cnsl::color(ConsoleColorAttributes::Red_FG);
  //cout << "\nspawn_pack_distance: " << Entity.SpawnPackDistance;
  //cnsl::color(ConsoleColorAttributes::Magenta_FG);
  //cout << "\nspawn_pack: " << Entity.SpawnPack;
  //cnsl::color(ConsoleColorAttributes::Yellow_FG);
  //cout << "\nweight_level_multiplier: " << Entity.WeightLevelMultiplier;
  //cnsl::color(ConsoleColorAttributes::Bright_Black_FG);
  //cout << "\nbase_entity: " << Entity.BaseEntity;
  //cnsl::color(ConsoleColorAttributes::Light_Gray_FG);
  //cout << "\nentity_data: " << Entity.NBT;
  //cnsl::color(ConsoleColorAttributes::Cyan_FG);
  //cout << "\nstat_increases: " << Entity.StatIncreases;
  //cnsl::print_colored_reset("\nrequirements: {", ConsoleColorAttributes::Blue_FG);
  //cnsl::color(ConsoleColorAttributes::Green_FG);
  //cout << "\nlevel " << Entity.Level;
  //cnsl::color(ConsoleColorAttributes::Light_Cyan_FG);
  ////cout << "\nmoon_phase" << Entity.MoonPhase;
  //cnsl::color(ConsoleColorAttributes::Red_FG);
  //cout << "\nbiome: " << Entity.Biome.name;
  //cnsl::color(ConsoleColorAttributes::Cyan_FG);
  //cout << "\ndimension: " << Entity.Dimension.name;
  //cnsl::color(ConsoleColorAttributes::Magenta_FG);
  //cout << "\nblock: " << Entity.Block.name;
  //cnsl::reset_color();
  //cnsl::print_colored_reset("\n}", ConsoleColorAttributes::Blue_FG);

}
void Generator::printCommand()
{
  entity& e = Entity;
  using namespace std;
  cnsl::color(ConsoleColorAttributes::Yellow_FG);
  std::string cmd = "";
  cout << "\n-----------------------------------------------\n";
  cout << "The Command :\n";
  cmd += "data modify storage gen:mobs registry.";
  cmd += Entity.Registry;
  cmd += " append value {name:\"";
  cmd += Entity.Name + '"';
  cmd += ",weight:";
  cmd += to_string(Entity.Weight);

  if (e.WeightLevelMultiplier) {
    cmd += ",weight_level_multiplier:{v:";
    cmd += to_string((int)(Entity.WeightLevelMultiplier * 100));
    cmd += "}";
  }

  if (!e.BaseEntity.empty()) {
    cmd += ",base_entity:\"";
    cmd += Entity.BaseEntity;
    cmd += '"';
  }


  if (e.hasRequirements) {
    cmd += ",requirements:{";

    if (e.Level) {
      cmd += ",level:{";
      if (e.Level.min) {
        cmd += ",min:";
        cmd += to_string(e.Level.min);
      }
      if (e.Level.max) {
        cmd += ",max:";
        cmd += to_string(e.Level.max);
      }
      cmd += "}";
    }
    if (e.MoonPhase) {
      cmd += ",moon_phase:{";
      if (e.MoonPhase.exact) {
        cmd += ",exact:";
        cmd += std::to_string(e.MoonPhase.exact);
        cmd += "b,";
      }
      else {
        if (e.MoonPhase.min) {
          cmd += ",min:";
          cmd += std::to_string(e.MoonPhase.min);
          cmd += "b,";
        }

        if (e.MoonPhase.max) {
          cmd += ",max:";
          cmd += std::to_string(e.MoonPhase.max);
          cmd += "b";
        }

        if (e.MoonPhase.except) {
          cmd += ",except:";
          cmd += std::to_string(e.MoonPhase.except);
          cmd += "b";
        }

        if (e.MoonPhase.on_even_days) {
          cmd += ",on_even_days:";
          cmd += std::to_string(e.MoonPhase.on_even_days);
          cmd += "b";
        }

        if (e.MoonPhase.on_odd_days) {
          cmd += ",on_odd_days:1b";
        }

        if (e.MoonPhase.on_prime_days) {
          cmd += "on_prime_days:1b";
        }

        if (e.MoonPhase.blood_moon) {
          cmd += ",blood_moon:1b";
        }
      }
      cmd += "}";
    }

    if (!e.Block.name.empty()) {
      cmd += ",block:\"";
      cmd += Entity.Block.name;
      cmd += '"';
      
      if (e.Block.isTag)
        cmd += ",blockTag:1b";
    }

    if (!e.Dimension.name.empty()) {
      cmd += ",dimension:\"";
      cmd += Entity.Dimension.name;
      cmd += '"';

      if (e.Dimension.isTag)
        cmd += ",dimensionTag:1b";
    }

    if (!e.Biome.name.empty()) {
      cmd += ",biome:\"";
      cmd += Entity.Biome.name;
      cmd += '"';

      if (e.Biome.isTag)
        cmd += ",biomeTag:1b";
    }

    cmd += "}";
  }

  if (e.StatIncreases) {
    cmd += ",stat_increases:{";
    if (e.StatIncreases.hasFlatStats()) {
      cmd += ",flat:{";
      stat_increases& es = e.StatIncreases;
      if (es.F_Armor)
        cmd += es.F_Armor.toString(",armor");
      
      if (es.F_ArmorToughness)
        cmd += es.F_ArmorToughness.toString(",armor_toughness");

      if (es.F_Attack_Speed)
        cmd += es.F_Attack_Speed.toString(",attack_speed");
      
      if (es.F_Damage)
        cmd += es.F_Damage.toString(",damage");
      
      if (es.F_FollowRange)
        cmd += es.F_FollowRange.toString(",follow_range");
      
      if (es.F_Health)
        cmd += es.F_Health.toString(",health");
      
      if (es.F_KnockBack)
        cmd += es.F_KnockBack.toString(",knockback_resistance");

      if (es.F_Speed)
        cmd += es.F_Speed.toString(",speed");

      cmd += "}";
    }
    
    if (e.StatIncreases.hasPercentageStats()) {
      cmd += ",percentage:{";
      stat_increases& es = e.StatIncreases;
      if (es.P_Armor)
        cmd += es.P_Armor.toString(",armor");

      if (es.P_ArmorToughness)
        cmd += es.P_ArmorToughness.toString(",armor_toughness");

      if (es.P_Attack_Speed)
        cmd += es.P_Attack_Speed.toString(",attack_speed");

      if (es.P_Damage)
        cmd += es.P_Damage.toString(",damage");

      if (es.P_FollowRange)
        cmd += es.P_FollowRange.toString(",follow_range");

      if (es.P_Health)
        cmd += es.P_Health.toString(",health");

      if (es.P_KnockBack)
        cmd += es.P_KnockBack.toString(",knockback_resistance");

      if (es.P_Speed)
        cmd += es.P_Speed.toString(",speed");

      cmd += "}";
    }

    cmd += "}";
  }


  if (!e.NBT.empty()) {
    cmd += ",nbt:";
    cmd += e.NBT;
  }
  cmd += "}";
  while (cmd.find(",}") != string::npos) {
    int pos = cmd.find(",}");
    cmd[pos - 1] = '}';
    cmd.erase(pos,1);
  }

  while (cmd.find("{,") != string::npos) {
    int pos = cmd.find("{,");
    cmd.erase(pos+1, 1);
  }
  cout << cmd;
}
int Generator::registry()
{

  const char* tell = "\nwhat mob will it use as it\'s spawning condition and replace in the world? (STRING) ";
  cnsl::print_colored_reset(tell, ConsoleColorAttributes::Cyan_FG);
  getInput();
  if (input.empty())
  {
    THROW_ERROR("[!ERROR!] Dummy this can't be skipped!", registry());
  }

  if (isValidEntity(inputLowercase) == false)
  {
    THROW_ERROR("\n[!ERROR!] Invalid Entity!", registry());
  }

  Entity.Registry = inputLowercase;
  return 0;
}

int Generator::name()
{
  const char* tell = "\nTechnical Mob Name: ";
  print_colored_reset(tell, ConsoleColorAttributes::Cyan_FG);
  
  getInput();
  
  if (input.empty())
  {
    print_colored_reset("\nDummy this can't be skipped!", RED_ERROR);
    name();
    return -1;
  }
  if (containsIllegalCharacter(input)) {
    print_colored("\n[!ERROR!] Techinical Name can't contain the character ", RED_ERROR);
    cout << '\'' << containsIllegalCharacter(input) << "\' !";
    cnsl::reset_color();
    name();
    return -1;
  }
  if (input.length() < 6)
  {
    THROW_WARNING("\n[!WARNING!] It is recommended to for the name to be longer than 6 characters!");
  }
  if (has_uppercase_letter(input))
  {
    THROW_WARNING("\n[!WARNING!] It is recommended to have the name and namespace be in all lowercase with '_' seperating between different words!");
  }
  if (contains_a_number(input))
  {
    THROW_WARNING("\n[!WARNING!] It is recommended to not have numbers in the techinical name have a unique name if possible!");
  }
  if (how_many(input, ':') > 1)
  {
    THROW_ERROR("[!ERROR!] No More than one namepace allowed!", name());
  }
  if (how_many(input, ':') != 1)
  {
    THROW_WARNING("\n[!WARNING!] It is recommended to add a namespace!");
  }
  Entity.Name = input;
  return 0;
}

int Generator::weight()
{

  const char* tell = "\nMob Weight (WHOLE NUMBER): ";
  print_colored_reset(tell, ConsoleColorAttributes::Cyan_FG);
  getInput();
  if (input.empty())
  {
    THROW_ERROR("\n[!ERROR!] Dummy this can't be skipped!", weight());
  }
  if (!all_number(input) || input[0] == '-')
  {
    THROW_ERROR("\n[!ERROR!] Dummy this has to be a positive number!", weight());
  }
  Entity.Weight = to_number(input);
  return 0;
}

int Generator::weightLevelMultiplier()
{

  const char* tell = "\nWeight Level Multiplier (DECIMAL NUMBER): ";
  print_colored_reset(tell, ConsoleColorAttributes::Cyan_FG);
  getInput();
  if (input.empty())
  {
    Entity.WeightLevelMultiplier = 0;
    return -1;
  }
  if (how_many(input, '.') > 1 || input[0] == '-')
  {
    THROW_ERROR("\n[!ERROR!] Dummy this has to be a positive number!", weightLevelMultiplier());
  }
  else if (input == ".")
  {
    THROW_ERROR("\n[!ERROR!] Type a decimal Number not just a dot!", weightLevelMultiplier());
  }
  else if (!all_number_float(input))
  {
    THROW_ERROR("\n[!ERROR!] Enter a decimal Number!", weightLevelMultiplier());
  }
  
  Entity.WeightLevelMultiplier = stof(input);
  return 0;
}

int Generator::requirements()
{

  const char* tell = "\nRequirements? (type Y): ";
  print_colored_reset(tell, ConsoleColorAttributes::Cyan_FG);
  getInput();
  if (input.empty())
  {
    Entity.hasRequirements = false;
    return -1;
  }
  if (input[0] != 'Y' && input[0] != 'y')
  {
    THROW_ERROR("\n[!ERROR!] Invalid Input press enter to skip or type 'Y'", requirements());
  }
 
  Entity.hasRequirements = true;
  return 0;
}

int Generator::level(LevelBranches branch)
{

  if (branch == LevelBranches::ALL) {
  const char* tell = "\nLevel? (type Y): ";
  print_colored_reset(tell, ConsoleColorAttributes::Cyan_FG);
  getInput();
    if (input.empty())
    {
      Entity.hasRequirements = false;
      return -1;
    }
    if (input[0] != 'Y' && input[0] != 'y')
    {
      print_colored_reset("\n[!ERROR!] Invalid Input press enter to skip or type 'Y'", RED_ERROR);
      level();
      return -1;
    }

    print_colored_reset("\nMin: ", ConsoleColorAttributes::Cyan_FG);
    getInput();
    
    if (input.empty())
      Entity.Level.min = 0;
    else
      Entity.Level.min = to_number(input);
  }
  if (branch == LevelBranches::MAX || branch == LevelBranches::ALL)
  {
    print_colored_reset("\nMax: ", ConsoleColorAttributes::Cyan_FG);
    getInput();
    if (input.empty())
      Entity.Level.max = 0;
    else {
      if (to_number(input) < Entity.Level.min)
      {
        THROW_ERROR("\n[!ERROR!] The max is the less than the min", level(LevelBranches::MAX));
      }
      else
        Entity.Level.max = to_number(input);
    }
  }
  //Entity.Level.min = (Entity.Level.min != Entity.Level.max);
  return 0;
}

int Generator::moonPhase(MoonPhaseBranches branch)
{
  if (branch == MoonPhaseBranches::ALL) {
    const char* tell = "\nMoon Phase? (type Y): ";
    print_colored_reset(tell, ConsoleColorAttributes::Cyan_FG);
    getInput();
    if (input.empty())
    {
      Entity.hasMoonPhase = false;
      return -1;
    }
    if (input[0] != 'Y' && input[0] != 'y')
    {
      THROW_ERROR("\n[!ERROR!] Invalid Input press enter to skip or type 'Y'", moonPhase());
    }
  }

  if (branch == MoonPhaseBranches::EXACT || branch == MoonPhaseBranches::ALL)
  {
    print_colored_reset("\nExact: ", ConsoleColorAttributes::Cyan_FG);
    getInput();
    if (input.empty())
      Entity.MoonPhase.exact = 0;
    else if (to_number(input) > 8 || to_number(input) < 1)
    {
      THROW_ERROR("\n[!ERROR!] The exact cannot be more than 8 or less than 1!",
        moonPhase(MoonPhaseBranches::EXACT));
    }
    else {
      Entity.MoonPhase.exact = to_number(input);
      branch = MoonPhaseBranches::BLOOD_MOON;
    }
  }

  if (branch == MoonPhaseBranches::MIN || branch == MoonPhaseBranches::ALL)
  {
    print_colored_reset("\nMin: ", ConsoleColorAttributes::Cyan_FG);
    getInput();

    if (input.empty())
      Entity.MoonPhase.min = 0;
    else if (to_number(input) > 8 || to_number(input) < 1)
    {
      THROW_ERROR("\n[!ERROR!] The min cannot be more than 8 or less than 1!",
        moonPhase(MoonPhaseBranches::MIN));
    }

    else {
      Entity.MoonPhase.min = to_number(input);
    }
  }

  if (branch == MoonPhaseBranches::MAX || branch == MoonPhaseBranches::ALL)
  {
    print_colored_reset("\nMax: ", ConsoleColorAttributes::Cyan_FG);
    getInput();
    if (input.empty())
      Entity.MoonPhase.max = 0;
    else {
      if (to_number(input) < Entity.MoonPhase.min)
      {
        THROW_ERROR("\n[!ERROR!] The max is the less than the min", moonPhase(MoonPhaseBranches::MAX));
      }
      if (to_number(input) > 8)
      {
        THROW_ERROR("\n[!ERROR!] The max cannot be more than 8!", moonPhase(MoonPhaseBranches::MAX));
      }
      else
        Entity.MoonPhase.max = to_number(input);
    }
  }
  
  if (branch == MoonPhaseBranches::EXCEPT || branch == MoonPhaseBranches::ALL)
  {
    print_colored_reset("\nExcept: ", ConsoleColorAttributes::Cyan_FG);
    getInput();
    if (input.empty())
      Entity.MoonPhase.except = 0;
    else {
      if (to_number(input) < Entity.MoonPhase.except)
      {
        THROW_ERROR("\n[!ERROR!] The max is the less than the min", moonPhase(MoonPhaseBranches::EXCEPT));
      }
      if (to_number(input) > 8)
      {
        THROW_ERROR("\n[!ERROR!] The max cannot be more than 8!", moonPhase(MoonPhaseBranches::EXCEPT));
      }
      else {
        Entity.MoonPhase.except = to_number(input);
      }
    }
  }

  if (branch == MoonPhaseBranches::ON_EVEN_DAYS || branch == MoonPhaseBranches::ALL) {
    print_colored_reset("\nOn Even Days?  ", ConsoleColorAttributes::Cyan_FG);
    getInput();

    if (input.empty()) {
      Entity.MoonPhase.on_even_days = false;
    }
    else if (inputLowercase != "y") {
      THROW_ERROR("\n[!ERROR!] Invalid Input press enter to skip or type 'Y' for yes ",moonPhase(MoonPhaseBranches::ON_EVEN_DAYS));
    }
    else {
      Entity.MoonPhase.on_even_days = true;
    }
  }

  if ( !Entity.MoonPhase.on_even_days && 
    (branch == MoonPhaseBranches::ON_ODD_DAYS || branch == MoonPhaseBranches::ALL)
    ) {
    print_colored_reset("\nOn Odd Days?  ", ConsoleColorAttributes::Cyan_FG);
    getInput();

    if (input.empty()) {
      Entity.MoonPhase.on_odd_days = false;
    }
    else if (inputLowercase != "y") {
      THROW_ERROR("\n[!ERROR!] Invalid Input press enter to skip or type 'Y' for yes ", moonPhase(MoonPhaseBranches::ON_ODD_DAYS));
    }
    else {
      Entity.MoonPhase.on_odd_days = true;
    }
  }

  if (!Entity.MoonPhase.on_even_days && !Entity.MoonPhase.on_odd_days &&
    (branch == MoonPhaseBranches::ON_PRIME_DAYS || branch == MoonPhaseBranches::ALL)
    ) {
    print_colored_reset("\nOn Prime Days?  ", ConsoleColorAttributes::Cyan_FG);
    getInput();

    if (input.empty()) {
      Entity.MoonPhase.on_prime_days = false;
    }
    else if (inputLowercase != "y") {
      THROW_ERROR("\n[!ERROR!] Invalid Input press enter to skip or type 'Y' for yes ", moonPhase(MoonPhaseBranches::ON_PRIME_DAYS));
    }
    else {
      Entity.MoonPhase.on_prime_days = true;
    }
  }

  if (branch == MoonPhaseBranches::BLOOD_MOON || branch == MoonPhaseBranches::ALL)
  {
    print_colored_reset("\nBlood Moon: ", ConsoleColorAttributes::Cyan_FG);
    getInput();
    if (input.empty()) {
      Entity.MoonPhase.max = 0;
    }
    else {
      if (inputLowercase != "y")
      {
        THROW_ERROR("\n[!ERROR!] The input must be Y or press enter to skip!", moonPhase(MoonPhaseBranches::BLOOD_MOON));
      }
      else {
        Entity.MoonPhase.blood_moon = true;
      }
    }
  }
  
  
  return 0;
}

int Generator::block()
{
  print_colored_reset("\nBlock: ",ConsoleColorAttributes::Cyan_FG);
  getInput();
  if (input.empty()) {
    return -1;
  }
  
  if (inputLowercase[0] == '#') {
    Entity.Block.isTag = true;

    if (how_many(input, ':') == 0)
      inputLowercase.insert(1, "minecraft:");

    Entity.Block.name = inputLowercase;
    return -1;
  }


  if (isValidBlock(inputLowercase)) {
    Entity.Block.isTag = false;
    
    if (how_many(input, ':') == 0)
      inputLowercase.insert(0, "minecraft:");
    
    Entity.Block.name = inputLowercase;
  }
  else {
    THROW_ERROR("\n[!ERROR!] not a valid block!", block());
  }
  return 0;
}

int Generator::biome()
{
  print_colored_reset("\nBiome: ", ConsoleColorAttributes::Cyan_FG);
  getInput();
  if (input.empty()) {
    return -1;
  }

  if (inputLowercase[0] == '#') {
    Entity.Biome.isTag = true;

    if (how_many(input, ':') == 0)
      inputLowercase.insert(1, "minecraft:");

    Entity.Biome.name = inputLowercase;
    return -1;
  }


  if (isValidBiome(inputLowercase)) {
    Entity.Biome.isTag = false;

    if (how_many(input, ':') == 0)
      inputLowercase.insert(0, "minecraft:");

    Entity.Biome.name = inputLowercase;
  }
  else {
    THROW_ERROR("\n[!ERROR!] not a valid biome!", biome());
  }
  return 0;
}

int Generator::summonFunction()
{
  print_colored_reset("\nWhat Command to run when succeeding to spawn it? ", ConsoleColorAttributes::Yellow_FG);
  getInput();

  if (input.empty()) {
    Entity.SummonFuncion = "";
    return -1;
  }

  if (input[0] == '/') {
    THROW_ERROR("\n[!ERROR!] Cannot start command with a '/' !", summonFunction());
  }
  string keyword;
  for (char i : input)
  {
    if (i == ' ')
      break;
    else
      keyword += i;
  }

  if (isValidCommand(keyword) == false) {
    THROW_ERROR("\n[!ERROR!] Not a valid command!",summonFunction());
  }

  if (keyword != "function") 
  {
    THROW_WARNING("\n[!WARNING!] It is recommended for the command to be a function!");
  }
  if ((keyword == "execute") && 
    ((input.find("execute at @s") != string::npos) || (input.find("execute as @s") != string::npos)))
  {
    THROW_WARNING("[!WARNING!] It is unnecesary to execute 'at @s' or 'as @s' \nthe function already executes as it and at it!");
  }


  Entity.SummonFuncion = keyword;
  return 0;
}

int Generator::baseEntity()
{
  const char* tell = "\nBase entity I register to zombie (to use zombies spawning conditions) but I want to spawn cows \nMy first input will be zombie and this input will be cow (STRING) ";
  cnsl::print_colored_reset(tell, ConsoleColorAttributes::Cyan_FG);
  getInput();
  if (input.empty())
  {
    return -1;
  }
  if (isValidEntity(inputLowercase) == false)
  {
    THROW_ERROR("\n[!ERROR!] Invalid Entity!", baseEntity());
  }

  Entity.BaseEntity = inputLowercase;
  return 0;
}

int Generator::NBT()
{
  const char* tell = "\nEntity Data or NBT (must be in brackets or press enter to skip) ";
  cnsl::print_colored_reset(tell, ConsoleColorAttributes::Cyan_FG);
  getInput();
  if (input.empty())
  {
    return -1;
  }
  if ((input[0] != '{' && input[input.length() - 1] != '}' )|| input.length() <= 1)
  {
    THROW_ERROR("\n[!ERROR!] The NBT must be in brackets!", NBT());
  }
  Entity.NBT = input;
  return 0;
}

int Generator::FstatIncreases()
{
  const char* tell = "\nFlat Stat Increases? (D = Default increases | Y for customizing | enter to skip ) ";
  cnsl::print_colored_reset(tell, ConsoleColorAttributes::Yellow_FG);
  getInput();
  if (input.empty())
  {
    stat_increases& e = Entity.StatIncreases;
    e.hasFStats = false;
    e.F_Damage = { 0, 0, 0 };
    e.F_Health = { 0, 0, 0 };
    e.F_Armor = { 0, 0, 0 };
    e.F_ArmorToughness = { 0, 0, 0 };
    e.F_Attack_Speed = { 0, 0 , 0 };
    e.F_KnockBack = { 0, 0, 0 };
    e.F_Speed = { 0, 0 , 0 };
    e.F_FollowRange = { 0, 0, 0 };
    return -1;
  }


  if (inputLowercase == "d") {
    stat_increases& e = Entity.StatIncreases;
    e.hasFStats = -1;
    e.P_Damage = { 0, 15, 1000 };
    e.P_Health = { 0, 15, 1500 };
    e.P_Armor = { 0, 0 , 0 };
    e.P_ArmorToughness = { 0, 0 , 0 };
    e.P_Attack_Speed = { 0, 0 , 0 };
    e.P_KnockBack = { 0, 0 , 0 };
    e.P_Speed = { 0, 15 , 500 };
    e.P_FollowRange = { 0, 0 , 0 };

    e.F_Damage = { 0, 0, 0 };
    e.F_Health = { 0, 0, 0 };
    e.F_Armor = { 0, 15, 1 };
    e.F_ArmorToughness = { 0, 15, 100 };
    e.F_Attack_Speed = { 0, 0 , 0 };
    e.F_KnockBack = { 0, 15, 25 };
    e.F_Speed = { 0, 0 , 0 };
    e.F_FollowRange = { 0, 15, 50 };
    return -1;
  }

  if (inputLowercase == "y") {
    Entity.StatIncreases.hasFStats = true;
    return -1;
  }
  
  THROW_ERROR("\n[!ERROR!] Input must be either 'D' for default stat increases or \n'Y' for customizing it yourself\n or press enter to skip", FstatIncreases());
}

int Generator::PstatIncreases()
{
  const char* tell = "\nPercentage Stat Increases? (D = Default increases | Y for customizing | enter to skip ) ";
  cnsl::print_colored_reset(tell, ConsoleColorAttributes::Yellow_FG);
  getInput();
  if (input.empty())
  {
    stat_increases& e = Entity.StatIncreases;
    e.hasPStats = false;
    e.P_Damage = { 0, 0, 0 };
    e.P_Health = { 0, 0, 0 };
    e.P_Armor = { 0, 0, 0 };
    e.P_ArmorToughness = { 0, 0, 0 };
    e.P_Attack_Speed = { 0, 0 , 0 };
    e.P_KnockBack = { 0, 0, 0 };
    e.P_Speed = { 0, 0 , 0 };
    e.P_FollowRange = { 0, 0, 0 };
    return -1;
  }


  if (inputLowercase == "d") {
    stat_increases& e = Entity.StatIncreases;
    e.hasPStats = -1;
    e.P_Damage = { 0, 0, 0 };
    e.P_Health = { 0, 0, 0 };
    e.P_Armor = { 0, 15, 1 };
    e.P_ArmorToughness = { 0, 15, 100 };
    e.P_Attack_Speed = { 0, 0 , 0 };
    e.P_KnockBack = { 0, 15, 25 };
    e.P_Speed = { 0, 0 , 0 };
    e.P_FollowRange = { 0, 15, 50 };
    return -1;
  }

  if (inputLowercase == "y") {
    Entity.StatIncreases.hasPStats = 1;
    return -1;
  }

  THROW_ERROR("\n[!ERROR!] Input must be either 'D' for default stat increases or \n'Y' for customizing it yourself\n or press enter to skip", FstatIncreases());
}
int Generator::statIncreases(const char* msg, int* ptr)
{
  std::array<int,3> InNumbers = { 0,0,0 };
  print_colored_reset(msg,ConsoleColorAttributes::Cyan_FG);
  getInput();
  split_convert(InNumbers.data(), 3 , input, ',');


  if (input.empty()) {
    for (int i = 0; i < InNumbers.size(); i++)
      *(ptr + i) = 0;
    return -1;
  }
  if (inputLowercase == "d") {
    return -1;
  }
  for (auto i : InNumbers) {
    if (i <= 0)
    {
      THROW_ERROR("\n[!ERROR!] None of the inputs can be less or equal to than 0", statIncreases(msg, ptr));
    }
  }
  for (int i = 0; i < InNumbers.size(); i++)
    *(ptr + i) = InNumbers[i];

  return 0;
}





