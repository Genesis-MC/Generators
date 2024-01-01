import argparse
import pathlib
import os
import json
import hjson
import glob
import re
from collections import OrderedDict


class NbtTag:
    def __init__(self):
        self._tag = OrderedDict()
    
    @staticmethod
    def from_string(s):
        t = NbtTag()
        s = re.sub(':\s?(-?[0-9]+[bs])', r':"@\1"', s) # change numbers with suffixes to strings
        s = re.sub(':\s?(-?[0-9]*.[0-9]*[fd])', r':"@\1"', s) # change numbers with suffixes to strings
        t._tag = hjson.loads(s)
        return t
    
    def __repr__(self):
        s = json.dumps(self._tag, indent=None)
        s = re.sub(r'(?<!: )"(\S*?)":', r'\1:', s) # remove quotes from keys
        s = re.sub(':\s?"@(-?[0-9]+[bs])"', r': \1', s) # change back to numbers with suffixes
        s = re.sub(':\s?"@(-?[0-9]*.[0-9]*[fd])"', r': \1', s) # change back to numbers with suffixes
        s = re.sub(':\s?"@(\[(I;)?[0-9,-]*\])"', r': \1', s) # change back to list
        return s
    
    def set(self, path, value):
        keys = path.split('.')
        stack = [self._tag]
        for key in keys:
            if key in stack[-1] and isinstance(stack[-1][key], dict):
                stack.append(stack[-1][key])
            else:
                stack.append({})
        stack[-1] = value
        for key in reversed(keys):
            value = stack.pop(-1)
            stack[-1][key] = value
        self._tag = stack[-1]
    
    def get(self, path):
        keys = path.split('.')
        temp = self._tag
        for key in keys:
            if key in temp and isinstance(temp[key], dict):
                temp = temp[key]
            else:
                return None
        return temp



class GearAbility:
    def __init__(self, obj, id):
        assert obj['type'] in ["passive"], f"Invalid ability type in '{id}': {obj['type']}"

        self.type = obj['type']
        self.id = id
        self.name = obj['name']
        self.description = obj['description']
        self.lore = [{'text':self.name, 'italic':False,'color':'gold'}, {'text':self.type.capitalize()+' Ability', 'italic':False,'color':'dark_gray'}] + split_text_component(self.description, default_style={'color':'gray'})



def register_abilities(args):
    global ABILITY_REGISTRY 
    ABILITY_REGISTRY = dict()
    for filename in glob.glob(os.path.join(os.path.join(args.source_dir, 'abilities', '**', '*.json')), recursive = True):
        if args.verbose:
            print(filename)
        ability_id = os.path.splitext(os.path.basename(filename))[0]
        with open(filename, 'r') as file:
            ABILITY_REGISTRY[ability_id] = GearAbility(json.load(file), ability_id)



def read_or_new_json(filename):
    """
    Reads a json file if it exists, otherwise returns an empty dictionary.
    """
    if os.path.isfile(filename):
        with open(filename, 'r') as file:
            return json.load(file)
    return {}



def split_text_component(inp, *, max_length=40, default_style={}):
    """
    Reads a string or dict and returns a list of dicts.
    A way of wrapping long sentences in the lore of an item.
    """
    if isinstance(inp, str):
        inp = dict(text=inp)
    for key, value in default_style.items():
        if key not in inp:
            inp[key] = value

    outp_words = [[]]
    inp_words = inp['text'].split(' ')

    l = 0
    for word in inp_words:
        l += len(word)
        if l > max_length:
            # new line
            outp_words.append([])
            l = len(word)
        else:
            # 1 extra length for space
            l += 1
        outp_words[-1].append(word)
    
    outp = []
    for words in outp_words:
        text_component = inp.copy()
        text_component['text'] = ' '.join(words)
        outp.append(text_component)
    return outp



def stats_to_lore(stats):
    """
    Input: dictionary
    Output: list of text components
    """
    elements = []
    for key, value in stats.items():
        elements.append({
            'translate': f'genesis.stats.wrapper.{key}.{len(str(value))}',
            'color': 'white' if value >= 0 else 'red',
            'with': [value]
        })
    return [dict(
        font='genesis:stats',
        text='',
        extra=elements,
        italic=False
    ), dict(text='')]



def generate_item_loot_table(conf):
    """
    Generates a loot table giving a single item.
    """
    assert conf['rarity'] >= 0 and conf['rarity'] <= 6, f"Error in {conf['id']}: rarity must be between 0 and 6"
    # common, uncommon, rare, epic, legendary, mythical, transcendent
    rarity_colours = ["white","aqua","yellow","light_purple","#3b2b06","#211905","#403303"]

    namespaced_item_id = conf['id']
    item_id = namespaced_item_id.split(':')[-1]
    base_item = conf['base_item']

    lore = []
    if 'lore' in conf:
        for line in conf['lore']:
            lore += split_text_component(line, default_style={'color':'gray'})
    
    name = {'translate':f"item.gen.{item_id}",'italic':False}
    if 'name_style' in conf:
        for key, value in conf['name_style'].items():
            name[key] = value

    nbt = NbtTag.from_string(conf['nbt']) if 'nbt' in conf else NbtTag()
    nbt.set('gen.id', namespaced_item_id)
    if 'cmd' in conf:
        nbt.set('CustomModelData', conf['cmd'])
    if 'stats' in conf:
        item_type = 'weapon'
        if 'helmet' in base_item or 'head' in base_item:
            item_type = 'helmet'
        elif 'chestplate' in base_item:
            item_type = 'chestplate'
        elif 'leggings' in base_item:
            item_type = 'leggings'
        elif 'boots' in base_item:
            item_type = 'boots'
        nbt.set('gen.type', item_type)
        nbt.set('gen.stat', conf['stats'])
        slot = {'weapon':'mainhand','helmet':'head','chestplate':'chest','leggings':'legs','boots':'feet'}[item_type]
        nbt.set('AttributeModifiers', [{'Amount':"@-0.000000000001d",'Name':f"tungsten.{slot}",'Operation':0,'UUID':"@[I;12,42069,0,{}]".format({'head':12,'chest':13,'legs':14,'feet':15}[slot]),'AttributeName':'minecraft:generic.luck','Name':f"tungsten.{slot}",'Slot':slot}])
        nbt.set('HideFlags', 255)
        lore = stats_to_lore(conf['stats']) + lore
    if 'abilities' in conf:
        for ability in conf['abilities']:
            lore += ABILITY_REGISTRY[ability].lore
    

    entry = dict(
        type = "minecraft:item",
        name = base_item,
        functions = [
            dict(
                function = "minecraft:set_nbt",
                tag = str(nbt)
            ),
            dict(
                function = "minecraft:set_name",
                name = name
            ),
            dict(
                function = "minecraft:set_lore",
                lore = [{'translate':f"genesis.lore.rarity.{conf['rarity']}",'italic':False,'color':rarity_colours[conf['rarity']],'with':[
                        {'text':"A",'font':"genesis:icon",'color':"white"},{'translate':f"genesis.lore.type.{conf['type']}"}]}] + lore
            )
        ]
    )
    loottable = dict(
        pools = [
            dict(
                rolls = 1,
                entries = [entry]
            )
        ]
    )
    return loottable



def generate_heavy_workbench_shaped_recipe(recipe, result):
    item_id = result.split(':')[-1]
    legend = dict()
    for key, value in recipe['legend'].items():
        entry = dict()
        nbt = NbtTag.from_string(value['nbt']) if 'nbt' in value else NbtTag()
        if 'id' in value:
            namespace = value['id'].split(':')[0]
            if namespace == 'minecraft':
                entry['id'] = value['id']
            elif namespace == 'gen':
                nbt.set('gen.id', value['id'])
            else:
                raise ValueError(f"Bad namespace: '{namespace}': must be 'minecraft' or 'gen'.")
        elif 'tag' in value:
            entry['item_tag'] = [f"#{value['tag']}"]
        if len(nbt._tag.keys()) > 0:
            entry['tag'] = nbt._tag
        legend[key] = entry
    
    pattern = recipe['pattern']
    recipe_nbt = NbtTag()
    for i in range(len(pattern)):
        pattern_row = pattern[i]
        row = []
        for j in range(len(pattern_row)):
            key = pattern_row[j]
            entry = legend[key].copy()
            entry['Slot'] = f"@{j}b"
            row.append(entry)
        recipe_nbt.set(str(i), row)

    return "execute store result score @s smithed.data if entity @s[scores={smithed.data=0}] if data storage smithed.crafter:input recipe"\
    + str(recipe_nbt) + f" run loot replace block ~ ~ ~ container.16 loot gen:item/{item_id}\n"



def main(args):
    register_abilities(args)

    # read all config files
    confs = []
    for filename in glob.glob(os.path.join(os.path.join(args.source_dir, 'items', '**', '*.json')), recursive = True):
        if args.verbose:
            print(filename)
        with open(filename, 'r') as file:
            confs.append(json.load(file))

    # generate loot tables
    item_lt_dir = os.path.join(args.datapack_dir, 'data', 'gen', 'loot_tables', 'item')
    os.makedirs(item_lt_dir, exist_ok=True)
    for conf in confs:
        namespaced_item_id = conf['id']
        item_id = namespaced_item_id.split(':')[-1]
        with open(os.path.join(item_lt_dir, f"{item_id}.json"), 'w') as file:
            json.dump(generate_item_loot_table(conf), file, indent=2)
    
    # generate heavy workbench recipes
    func_dir = os.path.join(args.datapack_dir, 'data', 'gen', 'functions', 'generated')
    os.makedirs(func_dir, exist_ok=True)
    recipe_filename = os.path.join(func_dir, 'heavy_workbench_shaped_recipes.mcfunction')
    with open(recipe_filename, 'w') as file:
        for conf in confs:
            if 'recipes' in conf:
                for recipe in conf['recipes']:
                    if recipe['type'] == 'heavy_workbench_shaped':
                        file.write(generate_heavy_workbench_shaped_recipe(recipe, conf['id']))

    # generate en_us
    lang_dir = os.path.join(args.resourcepack_dir, 'assets', 'minecraft', 'lang')
    os.makedirs(lang_dir, exist_ok=True)
    lang_filename = os.path.join(lang_dir, 'en_us.json')
    lang = read_or_new_json(lang_filename)
    for conf in confs:
        if 'name' in conf:
            namespaced_item_id = conf['id']
            lang[f"item.{namespaced_item_id.replace(':','.')}"] = conf['name']
    with open(lang_filename, 'w') as file:
        json.dump(lang, file, indent=2)




if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                    prog='Genesis Item Generator',
                    description='Generates loot tables for items')
    parser.add_argument('datapack_dir', type=pathlib.Path,
                    help='source dir for the Genesis datapack')
    parser.add_argument('resourcepack_dir', type=pathlib.Path,
                    help='source dir for the Genesis resourcepack')
    parser.add_argument('--source_dir', type=pathlib.Path,
                    help='source dir for the data generator config files', default='source')
    parser.add_argument('-v', '--verbose',
                    action='store_true')
    args = parser.parse_args()

    args.datapack_dir = os.path.expanduser(args.datapack_dir)
    args.resourcepack_dir = os.path.expanduser(args.resourcepack_dir)
    args.source_dir = os.path.expanduser(args.source_dir)

    assert os.path.isfile(os.path.join(args.datapack_dir, 'pack.mcmeta')), f"Could not find pack.mcmeta in specified datapack directory."
    assert os.path.isfile(os.path.join(args.resourcepack_dir, 'pack.mcmeta')), f"Could not find pack.mcmeta in specified resourcepack directory."
    assert os.path.isdir(args.source_dir), f"Could not find specified source directory."

    main(args)