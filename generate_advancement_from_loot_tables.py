import sys
import os
import json
import re

# How to use:
# python generate_advancement_from_loot_tables.py <path to loot tables> <path to output folder>
# > You can omit the output folder to print the advancements to the console instead of writing them to a file
# Example:
# python generate_advancement_from_loot_tables.py <path to repo>/data/gen/loot_tables/gear/armorsets <path to repo>/data/gen/advancements/story/armorsets
# or
# python generate_advancement_from_loot_tables.py <path to repo>/data/gen/loot_tables/gear/armorsets

def create_advancement(parent:str, display_nbt:str, display_id:str, head_id:str, head_name:str, chest_id:str, chest_name:str, legs_id:str, legs_name:str, feet_id:str, feet_name:str) -> dict:
    set_name = chest_name.split(" ")[0]
    
    advancement = {
        "display": {
            "icon": {
                "item": display_id,
                "nbt": display_nbt
            },
            "title": f"Obtain the {set_name}-Set",
            "description": f"Collect a full set of {set_name} armor",
            "frame": "goal",
            "show_toast": True,
            "announce_to_chat": True,
            "hidden": False
        },
        "parent": parent,
        "criteria": {
            "head": {
                "trigger": "minecraft:inventory_changed",
                "conditions": {
                    "items": [
                        {
                            "items": [
                                head_id
                            ],
                            "nbt": "{gen:{name:\"" + head_name + "\"}}"
                        }
                    ]
                }
            },
            "chest": {
                "trigger": "minecraft:inventory_changed",
                "conditions": {
                    "items": [
                        {
                            "items": [
                                chest_id
                            ],
                            "nbt": "{gen:{name:\"" + chest_name + "\"}}"
                        }
                    ]
                }
            },
            "legs": {
                "trigger": "minecraft:inventory_changed",
                "conditions": {
                    "items": [
                        {
                            "items": [
                                legs_id
                            ],
                            "nbt": "{gen:{name:\"" + legs_name + "\"}}"
                        }
                    ]
                }
            },
            "feet": {
                "trigger": "minecraft:inventory_changed",
                "conditions": {
                    "items": [
                        {
                            "items": [
                                feet_id
                            ],
                            "nbt": "{gen:{name:\"" + feet_name + "\"}}"
                        }
                    ]
                }
            }
        }
    }
    return advancement



def generate(path:str, destination:str = None):
    for folder in os.listdir(path):
        if not os.path.isdir(os.path.join(path, folder)):
            continue

        items:dict = {}

        for filename in os.listdir(os.path.join(path, folder)):
            if not filename.endswith(".json"):
                continue

            with open(os.path.join(path, folder, filename), "r", encoding='utf-8') as f:
                raw = f.read()
                loot_table = json.loads(raw)

                try:
                    item_entry:dict = loot_table["pools"][0]["entries"][0]
                    functions:list[str] = item_entry["functions"]
                except KeyError:
                    continue

                if item_entry.get("type") == "minecraft:item":
                    item_id = item_entry["name"]
                    kind = (
                        "helmet"      in item_id and "head"  or
                        "player_head" in item_id and "head"  or
                        "chestplate"  in item_id and "chest" or
                        "leggings"    in item_id and "legs"  or
                        "boots"       in item_id and "feet"  or
                        None
                    )
                else:
                    continue
                
                name = ""
                nbt_tag = ""
                for function in functions:
                    if function["function"] == "minecraft:set_nbt":
                        nbt_tag = function["tag"]
                        match = re.match(r'\{.*?gen:\{.*?name:\"(.*?)\"', nbt_tag)
                        if match and match.group(1):
                            name = match.group(1)
                            break
                
                if name == "":
                    continue

                items[kind] = {
                    "id": item_id,
                    "name": name,
                    "nbt": nbt_tag
                }

        if destination:
            with open(os.path.join(destination, folder + ".json"), "w", encoding='utf-8') as f:
                json.dump(create_advancement(
                    "gen:story/armorsets",
                    "player_head" in items["head"]["id"] and items["head"]["nbt"] or items["chest"]["nbt"],
                    "player_head" in items["head"]["id"] and items["head"]["id"] or items["chest"]["id"],
                    items["head"]["id"], items["head"]["name"],
                    items["chest"]["id"], items["chest"]["name"],
                    items["legs"]["id"], items["legs"]["name"],
                    items["feet"]["id"], items["feet"]["name"]),
                    f, indent=4)
        else:
            print()
            print(json.dumps(create_advancement(
                "gen:story/armorsets",
                "player_head" in items["head"]["id"] and items["head"]["nbt"] or items["chest"]["nbt"],
                "player_head" in items["head"]["id"] and items["head"]["id"] or items["chest"]["id"],
                items["head"]["id"], items["head"]["name"],
                items["chest"]["id"], items["chest"]["name"],
                items["legs"]["id"], items["legs"]["name"],
                items["feet"]["id"], items["feet"]["name"]),
                indent=4))

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("No path given")
        exit(1)
    if len(sys.argv) == 2:
        generate(sys.argv[1])
    else:
        generate(sys.argv[1], sys.argv[2])
