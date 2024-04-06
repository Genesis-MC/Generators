from dataclasses import dataclass
import json
import os
from typing import Union
from config import data_pack_path
from snbt_util import parse

@dataclass
class Item:
    cmd: int
    base_id: str
    gen_id: str

    hideflags: int

    name: str
    lore: list

    gen_type: list|str
    gen_stats: dict
    when_eaten_function: str
    saturation: int
    count: int

    is_mineral: bool
    is_enhancement_crystal: bool
    is_unbreakable: bool
    is_dev_stone: bool
    custom_head_data: dict
    block_entity_data: dict
    entity_data: dict
    stored_enchantments: dict
    enchantments: list
    trim: dict
    attributes: list

    def from_loot_table(loot_table) -> Union['Item', None]:
        try:
            if loot_table["pools"][0]["rolls"] != 1: return
            if len(loot_table["pools"][0]["entries"]) != 1: return
            entry: dict = loot_table["pools"][0]["entries"][0]
            if entry["type"] != "minecraft:item": return

            base_id: str = entry["name"]

            functions: list[dict] = entry["functions"]
        except:
            return

        gen_id: str = None
        cmd: int = None
        hideflags: int = None
        name: str = None
        lore: list = None
        gen_type: list|str = None
        custom_head_data: dict = None
        is_mineral: bool = None
        block_entity_data: dict = None
        entity_data: dict = None
        stored_enchantments: dict = None
        is_enhancement_crystal: bool = None
        enchantments: list = None
        gen_stats: dict = None
        is_unbreakable: bool = None
        trim: dict = None
        attributes: list = None
        when_eaten_function: str = None
        saturation: int = None
        is_dev_stone: bool = None
        count: int = None

        a = []

        for function in functions:
            if function["function"].endswith("set_nbt"):
                nbt = parse(function["tag"])
                gen_id = nbt.get_path("gen.id", gen_id)
                gen_id = nbt.get_path("gen.name", gen_id)
                gen_type = nbt.get_path("gen.type", gen_type)
                gen_stats = nbt.get_path("gen.stat", gen_stats)
                cmd = nbt.get_path("CustomModelData", cmd)
                enchantments = nbt.get_path("Enchantments", enchantments)
                hideflags = nbt.get_path("HideFlags", hideflags)
                name = nbt.get_path("display.Name", name)
                lore = nbt.get_path("display.Lore", lore)
                if nbt.get_path("genesis.phead.detect", 0) == 1:
                    custom_head_data = nbt.get_path("SkullOwner", custom_head_data)
                is_mineral = nbt.get_path("gen.mineral", is_mineral) == 1
                is_enhancement_crystal = nbt.get_path("gen.EnhancementCrystal", is_enhancement_crystal)
                block_entity_data = nbt.get_path("BlockEntityTag", block_entity_data)
                entity_data = nbt.get_path("EntityTag", entity_data)
                stored_enchantments = nbt.get_path("StoredEnchantments", stored_enchantments)
                is_unbreakable = nbt.get_path("Unbreakable", is_unbreakable) == 1
                trim = nbt.get_path("Trim", trim)
                attributes = nbt.get_path("AttributeModifiers", attributes)
                when_eaten_function = nbt.get_path("gen.when_eaten_function", when_eaten_function)
                saturation = nbt.get_path("gen.on_eat.saturation", saturation)
                is_dev_stone = nbt.get_path("gen.on_click.dev.dev_stone", is_dev_stone) == 1
            elif function["function"].endswith("set_name"):
                name = function["name"]
            elif function["function"].endswith("set_lore"):
                lore = function["lore"]
            elif function["function"].endswith("set_count"):
                count = function["count"]
            else:
                a.append(function["function"])


        if gen_id:
            return Item(
                cmd=cmd,
                base_id=base_id,
                gen_id=gen_id,
                hideflags=hideflags,
                name=name,
                lore=lore,
                gen_type=gen_type,
                is_mineral=is_mineral,
                is_enhancement_crystal=is_enhancement_crystal,
                custom_head_data=custom_head_data,
                block_entity_data=block_entity_data,
                entity_data=entity_data,
                stored_enchantments=stored_enchantments,
                enchantments=enchantments,
                gen_stats=gen_stats,
                is_unbreakable=is_unbreakable,
                trim=trim,
                attributes=attributes,
                when_eaten_function=when_eaten_function,
                saturation=saturation,
                is_dev_stone=is_dev_stone,
                count=count,
            )
    
    def to_json(self):
        output = {}
        for key, value in self.__dict__.items():
            if value is not None and value is not False:
                output[key] = value
        return output


def print_remaining_tags(nbt: dict, *tags) -> bool:
    success = False
    for key in nbt.keys():
        if key not in tags:
            print(key, nbt[key])
            success = True
    return success


def get_all():
    items = []
    loot_table_path = data_pack_path + "data/gen/loot_tables/"

    for root, dirs, files in os.walk(loot_table_path):
        for file in files:
            if file.endswith(".json"):
                with open(os.path.join(root, file), encoding='utf-8') as f:
                    loot_table = json.load(f)
                    if item := Item.from_loot_table(loot_table):
                        items.append(item)
    # with open("items.json", "w") as f:
    #     f.write(json.dumps([item.to_json() for item in items], default=lambda x: x.__str__(), indent=4))
    # print(len(items))
