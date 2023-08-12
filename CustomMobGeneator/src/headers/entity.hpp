#pragma once
#include <string>
#include <iostream>

struct binomial {
  int n = 0;
  int p = 0;
  int b = 0;
  friend std::ostream& operator<<(std::ostream& os, binomial& input);
  operator bool() const {
    return (n || p || b);
  }
  std::string toString(std::string name)
  {
    std::string C = name;
    C += ":[";
    C += std::to_string(n);
    C += ",";
    C += std::to_string(p);
    C += ",";
    C += std::to_string(b);
    C += "]";
    return C;
  }
};

inline std::ostream& operator<<(std::ostream& os, binomial& input)
{
  os << std::string("N: ");
  os << std::string(std::to_string(input.n));
  os << std::string(", P: ");
  os << std::string(std::to_string(input.p));
  os << std::string(", B: ");
  os << std::string(std::to_string(input.b));
  return os;
}

struct moon_phase {
  int  min = 0;
  int  max = 0;
  int  except = 0;
  int  exact = 0;
  bool on_odd_days = 0;
  bool on_even_days = 0;
  bool on_prime_days = 0;
  bool blood_moon = 0;

  operator bool() const {
    return (min || max || except || exact || on_odd_days || on_even_days || on_prime_days || blood_moon);
  }
};
struct stat_increases {
  //                              N  P  B
  char hasFStats = false;
  binomial P_Damage = { 0, 15, 1000 };
  binomial P_Health = { 0, 15, 1500 };
  binomial P_Armor = { 0, 0 , 0 };
  binomial P_ArmorToughness = { 0, 0 , 0 };
  binomial P_Attack_Speed = { 0, 0 , 0 };
  binomial P_KnockBack = { 0, 0 , 0 };
  binomial P_Speed = { 0, 15 , 500 };
  binomial P_FollowRange = { 0, 0 , 0 };

  char hasPStats = false;
  binomial F_Damage = { 0, 0, 0 };
  binomial F_Health = { 0, 0, 0 };
  binomial F_Armor = { 0, 15, 1 };
  binomial F_ArmorToughness = { 0, 15, 100 };
  binomial F_Attack_Speed = { 0, 0 , 0 };
  binomial F_KnockBack = { 0, 15, 25 };
  binomial F_Speed = { 0, 0 , 0 };
  binomial F_FollowRange = { 0, 15, 50 };
  friend std::ostream& operator<<(std::ostream& os, stat_increases& si);
  operator bool() const {
    return (P_Damage || P_Health || P_Armor || P_ArmorToughness || P_Attack_Speed || P_KnockBack || P_Speed || P_FollowRange || F_Damage || F_Health || F_Armor || F_ArmorToughness || F_Attack_Speed || F_KnockBack || F_Speed || F_FollowRange);
  }

  bool hasPercentageStats() const {
    return (P_Damage || P_Health || P_Armor || P_ArmorToughness || P_Attack_Speed || P_KnockBack || P_Speed || P_FollowRange);
  }

  bool hasFlatStats() const {
    return (F_Damage || F_Health || F_Armor || F_ArmorToughness || F_Attack_Speed || F_KnockBack || F_Speed || F_FollowRange);
  }
};
inline std::ostream& operator<<(std::ostream& os, stat_increases& si)
{
  os << "\nP_Damage: " << si.P_Damage;
  os << "\nP_Health: " << si.P_Health;
  os << "\nP_Armor: " << si.P_Armor;
  os << "\nP_ArmorToughness: " << si.P_ArmorToughness;
  os << "\nP_Attack_Speed: " << si.P_Attack_Speed;
  os << "\nP_KnockBack: " << si.P_KnockBack;
  os << "\nP_Speed: " << si.P_Speed;
  os << "\nP_FollowRange: " << si.P_FollowRange;
  os << "\nF_Damage: " << si.F_Damage;
  os << "\nF_Health: " << si.F_Health;
  os << "\nF_Armor: " << si.F_Armor;
  os << "\nF_ArmorToughness: " << si.F_ArmorToughness;
  os << "\nF_Attack_Speed: " << si.F_Attack_Speed;
  os << "\nF_KnockBack: " << si.F_KnockBack;
  os << "\nF_Speed: " << si.F_Speed;
  os << "\nF_FollowRange: " << si.F_FollowRange;
  return os;
}
struct type_tag {
  std::string name;
  bool isTag = false;
};

template <typename T>
struct min_max {
  T min = 0;
  T max = 0;

  operator bool() const {
    return (min || max);
  }
};



struct entity {
  std::string Registry;
  std::string Name;
  std::string SummonFuncion;
  std::string NBT;
  std::string BaseEntity;
  int Weight = 0;
  float WeightLevelMultiplier = 0.0F;
  stat_increases StatIncreases;
  min_max<int> SpawnPack;
  min_max<float> SpawnPackDistance;

  min_max<int> Level;
  moon_phase MoonPhase;
  type_tag Block;
  type_tag Dimension;
  type_tag Biome;
  
  bool hasRequirements = false;
  bool hasMoonPhase = false;
  bool hasLevel = false;
  bool hasBlock = false;
  bool hasBiome = false;
  bool hasDimension = false;

};

