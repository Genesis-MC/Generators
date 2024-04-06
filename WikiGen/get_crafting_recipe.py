
from dataclasses import dataclass
from config import data_pack_path
from snbt_util import parse
import json

shaped_function_path = data_pack_path + "data/smithed.crafter/functions/v0.2.0/recipes/shaped.mcfunction"
shapeless_function_path = data_pack_path + "data/smithed.crafter/functions/v0.2.0/recipes/shapeless.mcfunction"

@dataclass
class ShapedIngredient:
    base_id: str
    gen_id: str
    item_tag: list

    def __str__(self) -> str:
        if self.gen_id:
            return f'gen:{self.gen_id}'
        if self.item_tag:
            return self.item_tag[0].value
        return f'minecraft:{self.base_id}'

@dataclass
class ShapedRecipe:
    grid: list[list[ShapedIngredient]]
    output: str

    def to_dict(self) -> dict:
        return {
            "pattern": [[str(ingredient) for ingredient in row] for row in self.grid],
            "output": self.output
        }


@dataclass
class ShapelessIngredient:
    base_id: str
    gen_id: str
    item_tag: list
    count: int

    def to_dict(self) -> dict:
        return {
            "item": str(self),
            "count": self.count,
        }

    def __str__(self) -> str:
        if self.gen_id:
            return f'gen:{self.gen_id}'
        if self.item_tag:
            return self.item_tag[0].value
        return f'minecraft:{self.base_id}'

@dataclass
class ShapelessRecipe:
    grid: list[ShapelessIngredient]
    output: str

    def to_dict(self) -> dict:
        return {
            "pattern": [ingredient.to_dict() for ingredient in self.grid],
            "output": self.output
        }


def get_all_shaped_recipes() -> list[ShapedRecipe]:
    recipes = []
    with open(shaped_function_path, 'r') as file:
        for line in file.readlines():
            if not line.startswith('execute store result score @s smithed.data if entity @s[scores={smithed.data=0}] if data storage smithed.crafter:input recipe{'):
                continue
            input_snbt = line[125:].split(' run ')[0]
            input_compound = parse(input_snbt).value

            grid = []
            for row in input_compound:
                grid_row = []
                for col in input_compound[row].value:
                    base_id = col.get_path("id")
                    item_tag = col.get_path("item_tag")
                    gen_id = col.get_path("tag.gen.name")
                    grid_row.append(ShapedIngredient(base_id, gen_id, item_tag))
                grid.append(grid_row)

            output_table = line.split(' ')[-1].strip()
            recipes.append(ShapedRecipe(grid, output_table))
    return recipes


def get_all_shapeless_recipes() -> list[ShapelessRecipe]:
    recipes = []
    with open(shapeless_function_path, 'r') as file:
        for line in file.readlines():
            if not line.startswith('execute store result score @s smithed.data if entity @s[scores={smithed.data=0}] if score count smithed.data matches '):
                continue
            count = line[117:118]
            input_snbt = line[157:].split(' run ')[0]
            input_compound = parse(input_snbt).value
            ingedients = []
            for inpt in input_compound["recipe"].value:
                count = inpt.get_path("Count")
                base_id = inpt.get_path("id")
                item_tag = inpt.get_path("item_tag")
                gen_id = inpt.get_path("tag.gen.name")
                ingedients.append(ShapelessIngredient(base_id, gen_id, item_tag, count))

            output_table = line.split(' ')[-1].strip()
            recipes.append(ShapelessRecipe(ingedients, output_table))
    return recipes


def get_all_recipes() -> list[ShapelessRecipe|ShapedRecipe]:
    return get_all_shaped_recipes() + get_all_shapeless_recipes()


if __name__ == '__main__':
    # print("ALL RECIPES :")
    # print(json.dumps([r.to_dict() for r in get_all_recipes()], indent=4))
    with open("recipes.json", "w") as f:
        f.write(json.dumps([r.to_dict() for r in get_all_recipes()], indent=4))
