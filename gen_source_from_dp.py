import re
import requests
import json
import hjson
from PIL import Image
import os

datapack_path = r"../GenesisDatapack/"
resource_path = r"../GenesisResourcepack/"

# recipes: dict[str, list[dict[str, list[str] | str | dict[str, dict[str, str]]]]] = {}
files: dict[str, dict[str, str | dict[str, int]] | list[str] | int | list[dict[str, list[str] | str | dict[str, dict[str, str]]]]] = {}
loot_tables: dict[str, dict[str, str | int | dict[str, str] | list[str]]] = {}

# def to_snake_case(string: str) -> str:
#     string = re.sub(r"[^\d\w\s_]", "", string)
#     return re.sub(r"_?([A-Z])", r"_\1", string.replace(" ", "_")).removeprefix("_").lower()
# 
# def to_pascal_case(string: str) -> str:
#     return re.sub(r"(?:^|_)(.)", lambda m: ' ' + m.group(1).upper(), string).strip()

def snbt_str_to_json_str(snbt: str) -> dict:
    json = ""
    pntr = 0
    for next_str in re.finditer(r'(?<!\\)(\\{2})*(("(.*?(\\\n)?)+(?<!\\)(\\{2})*")|(\'(.*?(\\\n)?)+(?<!\\)(\\{2})*\'))', snbt): # find all strings to not check in them
        non_str = snbt[pntr:next_str.start()]
        non_str = re.sub(r'\[I;\s*(-?\d+),\s*(-?\d+),\s*(-?\d+),\s*(-?\d+)\]', r'"[I;\1,\2,\3,\4]"', non_str) # add quotes to uuid
        non_str = re.sub(r'([\d.]+[bsfd])', r'"\1"', non_str) # add quotes to numbers
        json += non_str
        json += next_str.group()
        pntr = next_str.end()
    non_str = re.sub(r'\[I;\s*(-?\d+),\s*(-?\d+),\s*(-?\d+),\s*(-?\d+)\]', r'"[I;\1,\2,\3,\4]"', snbt[pntr:]) # add quotes to uuid
    json += re.sub(r'([\d.]+[bsfd])', r'"\1"', snbt[pntr:]) # add quotes to numbers
    return json



def get_shaped_recipes():
    with open(f"{datapack_path}data/smithed.crafter/functions/v0.2.0/recipes/shaped.mcfunction", "r") as file:
        for line in file:
            if not line.startswith('execute store result score @s smithed.data if entity @s[scores={smithed.data=0}] if data storage smithed.crafter:input recipe'): continue

            recipe = re.findall(r"recipe{(.*?)} ", line)[0]
            a = 97
            legend = {" ": "minecraft:air"}
            pattern = []
            for ingredient in re.findall(r"{Slot:\wb,id:\"(.*?)\"(?:,tag:{gen:{name:\"(.*?)\")?", recipe):
                if ingredient[1]:
                    if f"gen:{ingredient[1]}" not in legend.values():
                        legend[chr(a)] = f"gen:{ingredient[1]}"
                        if not pattern or len(pattern[-1]) == 3:
                            pattern.append(chr(a))
                        else:
                            pattern[-1] += chr(a)
                        a += 1
                    else:
                        for key, value in legend.items():
                            if value == f"gen:{ingredient[1]}":
                                if not pattern or len(pattern[-1]) == 3:
                                    pattern.append(key)
                                else:
                                    pattern[-1] += key
                else:
                    if f"{ingredient[0]}" not in legend.values():
                        legend[chr(a)] = f"{ingredient[0]}"
                        if not pattern or len(pattern[-1]) == 3:
                            pattern.append(chr(a))
                        else:
                            pattern[-1] += chr(a)
                        a += 1
                    else:
                        for key, value in legend.items():
                            if value == f"{ingredient[0]}":
                                if not pattern or len(pattern[-1]) == 3:
                                    pattern.append(key)
                                else:
                                    pattern[-1] += key

            del legend[" "]
            result = f"gen:{line.split('/')[-1].strip()}"
            file = files.get(result, {})
            recipe = file.get("recipes", [])
            recipe.append({"pattern": pattern, "key": legend, "type": "heavy_workbench_shaped"})
            file["recipes"] = recipe
            file["id"] = result
            # base item needs to be gotten from loot table
            # stats need to be ripped from loot table
            # abilities also need to be ripped from loot table
            # nbt - the same thing
            # type - parsed from loot table lore?
            # rarity - parsed from loot table lore?
            # name - gotten from loot table
            # name_style - gotten from loot table
            # cmd - gotten from loot table
            # lore - gotten from loot table

            if result in loot_tables:
                if "base_item" in loot_tables[result]: file["base_item"] = loot_tables[result]["base_item"]
                if "stats" in loot_tables[result]: file["stats"] = loot_tables[result]["stats"]
                if "type" in loot_tables[result]: file["type"] = loot_tables[result]["type"]
                if "name" in loot_tables[result]: file["name"] = loot_tables[result]["name"]
                if "name_style" in loot_tables[result]: file["name_style"] = loot_tables[result]["name_style"]
                if "cmd" in loot_tables[result]: file["cmd"] = loot_tables[result]["cmd"]

            files[result] = file

def get_loot_tables():
    loot_table_path = f"{datapack_path}data/gen/loot_tables/"
    for dirpath, dirs, files in os.walk(loot_table_path):
        for filename in files:
            with open(os.path.join(dirpath, filename), 'r', encoding='utf-8') as file:
                data = json.load(file)
                if "pools" not in data or not data["pools"] or "entries" not in data["pools"][0]: continue
                item = data["pools"][0]["entries"][0]
                if item["type"] != "minecraft:item": continue
                if "functions" not in item and "functions" not in data["pools"][0]: continue
                functions = item["functions"] if "functions" in item else data["pools"][0]["functions"]
                out = {}

                out["base_item"] = item["name"]

                for function in functions:
                    if function["function"] != "minecraft:set_nbt": continue

                    stats = re.search(r"stat:{(.*?)}", function["tag"])
                    stats_dict = {}
                    if stats:
                        for stat in re.findall(r"(\w+):(\d+)", stats.group(1)):
                            stats_dict[stat[0]] = int(stat[1])
                        out["stats"] = stats_dict

                    type_match = re.search(r"\"type\":\[(.*?)\]", function["tag"])
                    if type_match:
                        out["type"] = [t for t in re.findall(r'"(.*?)"', type_match.group(1))]
                    elif (type_match := re.search(r"\"type\":\"(.*?)\"", function["tag"])):
                        out["type"] = type_match.group(1)

                    if (name_data := re.search(r"Name:'(.*?)(?<!\\)(\\{2})*'", function["tag"])):
                        name_data = json.loads(name_data.group(1).replace("\\'", "'"))
                        if not "translate" in name_data and not "text" in name_data: continue
                        out["name"] = name_data.get("translate", name_data.get("text"))
                        name_style = {}
                        if "color" in name_data: name_style["color"] = name_data["color"]
                        if "bold" in name_data: name_style["bold"] = name_data["bold"]
                        if "italic" in name_data: name_style["italic"] = name_data["italic"]
                        if "underlined" in name_data: name_style["underlined"] = name_data["underlined"]
                        if "strikethrough" in name_data: name_style["strikethrough"] = name_data["strikethrough"]
                        if "obfuscated" in name_data: name_style["obfuscated"] = name_data["obfuscated"]
                        out["name_style"] = name_style

                    if (cmd := re.search(r"CustomModelData:(\d+)", function["tag"])):
                        out["cmd"] = int(cmd.group(1))

                    clean_nbt = re.sub(r'CustomModelData:\d+', '', function["tag"])
                    clean_nbt = re.sub(r'display:{Name:\'.*?(?<!\\)(\\{2})*\',?', 'display:{', clean_nbt)
                    clean_nbt = clean_nbt.replace("display:{}", "")
                    clean_nbt = re.sub(r',,+', r',', clean_nbt)
                    clean_nbt = clean_nbt.replace("{,", "{")
                    clean_nbt = clean_nbt.replace(",}", "}")
                    out["nbt"] = clean_nbt

                loot_tables[f"gen:{filename[:-5]}"] = out

if __name__ == "__main__":
    get_loot_tables()
    get_shaped_recipes()
    for file in files.values():
        print(json.dumps(file, indent=2))
        print('---------------------------------')
    # jsnstr = snbt_str_to_json_str(
    #             "{gen:{name:\"shaded_dagger\",type:\"Dagger\",stat:{physical_power:40,attack_speed:100,speed:15}},AttributeModifiers:[{AttributeName:\"minecraft:generic.luck\",Name:\"tungsten.mainhand\",Amount:-0.000000000001,Operation:0,UUID:[I;12,42069,-0,10],Slot:\"mainhand\"}],display:{Name:'{\"translate\":\"Shaded Dagger\",\"color\":\"dark_purple\",\"italic\":false,\"bold\":false,\"underlined\":false}',Lore:['[{\"translate\":\"A\",\"font\":\"genesis:icon\",\"color\":\"white\",\"italic\":false},{\"translate\":\"Rare Dagger\",\"font\":\"minecraft:default\",\"color\":\"yellow\",\"italic\":false}]','{\"translate\":\"\",\"font\":\"genesis:stats\",\"color\":\"white\",\"italic\":false,\"extra\":[{\"translate\":\"genesis.stats.wrapper.physical_power.2\",\"with\":[40]},{\"translate\":\"genesis.stats.wrapper.attack_speed.3\",\"with\":[100]},{\"translate\":\"genesis.stats.wrapper.speed.2\",\"with\":[15]}]}','{\"translate\":\"\"}']},CustomModelData:982008,HideFlags:195}"
    #         )
    # print(jsnstr)
    # json.dumps(hjson.loads(jsnstr), indent=2)
