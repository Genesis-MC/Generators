import re
import requests
import json
from PIL import Image
import os

datapack_path = r"C:\\Users\\USERNAME\\AppData\\Roaming\\.minecraft\\saves\\WORLD\\datapacks\\ProjectGenesis\\"
resource_path = r"C:\\Users\\USERNAME\\AppData\\Roaming\\.minecraft\\resourcepacks\\GenesisResourcepack\\"

downloaded_textures = []
gen_loot_tables = []

def to_snake_case(string: str) -> str:
    string = re.sub(r"[^\d\w\s_]", "", string)
    return re.sub(r"_?([A-Z])", r"_\1", string.replace(" ", "_")).removeprefix("_").lower()

def to_pascal_case(string: str) -> str:
    return re.sub(r"(?:^|_)(.)", lambda m: ' ' + m.group(1).upper(), string).strip()

def texture_markdown(string: str) -> str:
    if string.startswith("minecraft:"):
        return f"![{string}](assets/textures/minecraft/{string.split(':')[1]}.png)"
    return f"[![{string}](assets/textures/gen/{string.split(':')[1]}.png)]({to_pascal_case(string.split(':')[1]).replace(' ','-')})"

def get_shaped_recipes(recipe_function: str) -> list[dict[str, list[str] | str]]:
    output: list[dict[str, list[str] | str]] = []
    with open(recipe_function, "r") as file:
        for line in file:
            if not line.startswith('execute store result score @s smithed.data if entity @s[scores={smithed.data=0}] if data storage smithed.crafter:input recipe'): continue

            recipe = re.findall(r"recipe{(.*?)} ", line)[0]
            ingredients = []
            for ingredient in re.findall(r"{Slot:\wb,id:\"(.*?)\"(?:,tag:{gen:{name:\"(.*?)\")?", recipe):
                if ingredient[1]:
                    ingredients.append("gen:" + to_snake_case(ingredient[1]))
                    if ingredient[1] not in gen_loot_tables:
                        gen_loot_tables.append(to_snake_case(ingredient[1]))
                else:
                    ingredients.append(ingredient[0])
                    if ingredient[0] not in downloaded_textures:
                        downloaded_textures.append(ingredient[0])
                        get_vanilla_texture(ingredient[0])
            result = line.split(" ")[-1]
            result = result.split(":")[0] + ":" + result.split("/")[-1].strip()
            output.append({"ingredients": ingredients, "result": result})
    return output

def get_markdown_recipe(recipes: list[dict[str, list[str] | str]], single_recipe: str = None) -> str:
    output = ""
    for recipe in recipes:
        if recipe["result"] != single_recipe and single_recipe is not None:
            continue

        output += f"<!-- start-craft={recipe['result']} -->"
        prefix = "> "
        for ingredient in recipe["ingredients"][:3]:
            output += f"\n{prefix}{texture_markdown(ingredient)}"
            prefix = ""
        output += "<br>"
        for ingredient in recipe["ingredients"][3:6]:
            output += f"\n{texture_markdown(ingredient)}"
        output += f"\n![crafting_arrow](assets/crafting_arrow.png)\n[![{recipe['result']}](assets/textures/{recipe['result'].split(':')[0]}/{recipe['result'].split(':')[1]}.png)](#)<br>"
        for ingredient in recipe["ingredients"][6:]:
            output += f"\n{texture_markdown(ingredient)}"
        output += f"\n<!-- end-craft={recipe['result']} -->\n"
    return output

def create_markdown_recipes(recipes: list[dict[str, list[str] | str]]) -> None:
    for recipe in recipes:
        with open(f"../GenesisDatapack.wiki/{to_pascal_case(recipe['result'].split(':')[1])}.md", "w") as file:
            file.write(f"""
## Crafting {to_pascal_case(recipe['result'].split(':')[1])}
{get_markdown_recipe(recipes, recipe["result"])}
""")

from PIL import Image

def create_air():
    img = Image.new('RGBA', (32, 32), (0, 0, 0, 0))
    img.save("../GenesisDatapack.wiki/assets/textures/minecraft/air.png")

def get_vanilla_texture(string: str):
    return #! this return is just here because I already downloaded all the textures
    url = f"https://raw.githubusercontent.com/misode/mcmeta/assets/assets/minecraft/textures/item/{string.split(':')[1]}.png"
    response = requests.get(url)

    if response.status_code == 200:
        # Save the downloaded image to a temporary file
        with open("temp.png", 'wb') as file:
            file.write(response.content)

        # Open the image and upscale it
        img = Image.open("temp.png")
        img = img.resize((32, 32), Image.NEAREST)

        # Save the upscaled image to the desired location
        img.save(f"../GenesisDatapack.wiki/assets/textures/minecraft/{string.split(':')[1]}.png")
    else:
        print(f"Failed to download image. HTTP response code: {response.status_code} {string}")

def get_gen_texture_paths(gen_vanilla_model_path: str) -> None:
    for dirpath, dirs, files in os.walk(gen_vanilla_model_path):
        for filename in files:
            if filename.endswith('.json'):
                with open(os.path.join(dirpath, filename), 'r') as file:
                    data = json.load(file)
                    predicates = data.get('overrides', [])
                    for predicate in predicates:
                        if 'predicate' in predicate and 'custom_model_data' in predicate['predicate']:
                            copy_gen_texture(predicate['model'])

def copy_gen_texture(path_id: str) -> None:
    if not ':' in path_id: path_id = f"minecraft:{path_id}"

    try:
        with open(f"{resource_path}assets/{path_id.split(':')[0]}/models/{path_id.split(':')[1]}.json") as json_file:
            data = json.load(json_file)
            textures = data.get('textures', {})
    except FileNotFoundError:
        print(f"Failed to open {path_id}")
        return

    for texture_path in textures.values():
        if not ':' in texture_path: texture_path = f"minecraft:{texture_path}"

        try:
            img = Image.open(f"{resource_path}assets/{texture_path.split(':')[0]}/textures/{texture_path.split(':')[1]}.png")
        except FileNotFoundError:
            print(f"Failed to open {texture_path}")
            continue
        img = img.resize((32, 32), Image.NEAREST)
        img.save(f"../GenesisDatapack.wiki/assets/textures/gen/{texture_path.split('/')[-1]}.png")

if __name__ == "__main__":
    # create_air() already did this
    create_markdown_recipes(get_shaped_recipes(datapack_path + "data/smithed.crafter/functions/v0.2.0/recipes/shaped.mcfunction"))
    loot_table_path = datapack_path + "data/gen/loot_tables/"
    gen_vanilla_model_path = resource_path + "assets/minecraft/models/item/"
    get_gen_texture_paths(gen_vanilla_model_path)