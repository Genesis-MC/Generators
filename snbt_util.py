import re
from typing import Union

class UUID:
    value: str
    def __init__(self, value: str):
        self.value = value

    def is_next(snbt: str) -> bool:
        return re.match(r'\[ *I *; *-?\d+ *, *-?\d+ *, *-?\d+ *, *-?\d+ *\]', snbt) is not None

    def parse(snbt: str) -> tuple['UUID', str]:
        match = re.match(r'\[ *I *; *-?\d+ *, *-?\d+ *, *-?\d+ *, *-?\d+ *\]', snbt)
        if match is None: raise ValueError("Invalid uuid", snbt)
        return UUID(match.group(0).replace(' ','')), snbt[match.end():]

    def __str__(self): return self.value
    def __repr__(self): return self.__str__()


class Byte:
    value: int
    def __init__(self, value: int):
        self.value = value

    def is_next(snbt: str) -> bool:
        return re.match(r'(-?\d+)[bB](?![0-9a-zA-Z_\+\.\-])', snbt) is not None
    
    def parse(snbt: str) -> tuple['Byte', str]:
        match = re.match(r'(-?\d+)[bB](?![0-9a-zA-Z_\+\.\-])', snbt)
        if match is None: raise ValueError("Invalid byte", snbt)
        return Byte(int(match.group(1))), snbt[match.end():]

    def __str__(self): return f'{self.value}b'
    def __repr__(self): return self.__str__()


class Short:
    value: int
    def __init__(self, value: int):
        self.value = value

    def is_next(snbt: str) -> bool:
        return re.match(r'(-?\d+)[sS](?![0-9a-zA-Z_\+\.\-])', snbt) is not None

    def parse(snbt: str) -> tuple['Short', str]:
        match = re.match(r'(-?\d+)[sS](?![0-9a-zA-Z_\+\.\-])', snbt)
        if match is None: raise ValueError("Invalid short", snbt)
        return Short(int(match.group(1))), snbt[match.end():]

    def __str__(self): return f'{self.value}s'
    def __repr__(self): return self.__str__()


class Int:
    value: int
    def __init__(self, value: int):
        self.value = value

    def is_next(snbt: str) -> bool:
        return re.match(r'(-?\d+)(?![0-9a-zA-Z_\+\.\-])', snbt) is not None

    def parse(snbt: str) -> tuple['Int', str]:
        match = re.match(r'(-?\d+)(?![0-9a-zA-Z_\+\.\-])', snbt)
        if match is None: raise ValueError("Invalid int", snbt)
        return Int(int(match.group(1))), snbt[match.end():]

    def __str__(self): return f'{self.value}'
    def __repr__(self): return self.__str__()


class Double:
    value: float
    def __init__(self, value: float):
        self.value = value

    def is_next(snbt: str) -> bool:
        return re.match(r'(\d*\.\d+|\d+\.?)[dD](?![0-9a-zA-Z_\+\.\-])', snbt) is not None

    def parse(snbt: str) -> tuple['Double', str]:
        match = re.match(r'(\d*\.\d+|\d+\.?)[dD](?![0-9a-zA-Z_\+\.\-])', snbt)
        if match is None: raise ValueError("Invalid double", snbt)
        return Double(float(match.group(1))), snbt[match.end():]

    def __str__(self): return f'{self.value}d'
    def __repr__(self): return self.__str__()


class Float:
    value: float
    def __init__(self, value: float):
        self.value = value

    def is_next(snbt: str) -> bool:
        return re.match(r'(\d*\.\d+|\d+\.)(?![0-9a-zA-Z_\+\.\-])', snbt) is not None

    def parse(snbt: str) -> tuple['Float', str]:
        match = re.match(r'(\d*\.\d+|\d+\.)(?![0-9a-zA-Z_\+\.\-])', snbt)
        if match is None: raise ValueError("Invalid float", snbt)
        return Float(float(match.group(1))), snbt[match.end():]
    
    def __str__(self): return f'{self.value}'
    def __repr__(self): return self.__str__()


class String:
    value: str
    def __init__(self, value: str):
        self.value = value

    def is_next(snbt: str) -> bool:
        return snbt.startswith('"') or snbt.startswith("'") or re.match(r'[0-9a-zA-Z_\.\+\-]', snbt) is not None

    def parse(snbt: str) -> tuple['String', str]:
        match = (re.match(r'"(.*?(?<!\\)(?:\\\\)?)"', snbt) if snbt.startswith('"') else
                re.match(r"'(.*?(?<!\\)(?:\\\\)?)'", snbt) if snbt.startswith("'") else
                re.match(r'([0-9a-zA-Z_\.\+\-]+)', snbt))
        if match is None:
            raise ValueError("Invalid string", snbt)
        return String(match.group(1)), snbt[match.end():]

    def __str__(self): return self.value
    def __repr__(self): return self.__str__()


class Key:
    def parse(snbt: str) -> tuple[str, str]:
        key, snbt = String.parse(snbt)
        return key.value, snbt


class Compound:
    value: dict[str, Union[UUID,Byte,Short,Int,Double,Float,String,'Compound','List']]
    def __init__(self, value: dict):
        self.value = value

    def is_next(snbt: str) -> bool:
        return snbt.startswith('{')
    
    def parse(snbt: str) -> tuple:
        snbt = snbt[1:].strip()
        value = {}
        while snbt:
            key, snbt = Key.parse(snbt)
            snbt = snbt.strip()[1:].strip() # remove colon
            value[key], snbt = get_value(snbt)
            snbt = snbt.strip()
            if snbt.startswith(','):
                snbt = snbt[1:].strip()
            elif snbt.startswith('}'):
                return Compound(value), snbt[1:].strip()
            else:
                raise ValueError("Invalid compound", snbt)

    def __getitem__(self, key): return self.value[key]
    def __str__(self): return '{' + ', '.join([f'{key}: {value}' for key, value in self.value.items()]) + '}'
    def __repr__(self): return self.__str__()


class List:
    value: list[Union[UUID,Byte,Short,Int,Double,Float,String,Compound,'List']]
    def __init__(self, value: list):
        self.value = value

    def is_next(snbt: str) -> bool:
        return snbt.startswith('[')

    def parse(snbt: str) -> tuple:
        snbt = snbt[1:].strip()
        value = []
        while snbt:
            val, snbt = get_value(snbt)
            value.append(val)
            snbt = snbt.strip()
            if snbt.startswith(','):
                snbt = snbt[1:].strip()
            elif snbt.startswith(']'):
                return List(value), snbt[1:].strip()
            else:
                raise ValueError("Invalid list", snbt)

    def __getitem__(self, index): return self.value[index]
    def __str__(self): return '[' + ', '.join([str(value) for value in self.value]) + ']'
    def __repr__(self): return self.__str__()


def get_value(snbt: str) -> tuple:
    if Double.is_next(snbt):
        return Double.parse(snbt)
    elif Float.is_next(snbt):
        return Float.parse(snbt)
    elif Byte.is_next(snbt):
        return Byte.parse(snbt)
    elif Short.is_next(snbt):
        return Short.parse(snbt)
    elif Int.is_next(snbt):
        return Int.parse(snbt)
    elif UUID.is_next(snbt):
        return UUID.parse(snbt)
    elif String.is_next(snbt):
        return String.parse(snbt)
    elif Compound.is_next(snbt):
        return Compound.parse(snbt)
    elif List.is_next(snbt):
        return List.parse(snbt)

    raise ValueError("Invalid value", snbt)


def parse(snbt: str) -> Compound|List:
    if List.is_next(snbt):
        return List.parse(snbt)[0]
    elif Compound.is_next(snbt):
        return Compound.parse(snbt)[0]
    else:
        raise ValueError("Invalid snbt", snbt)

# final_boss = "{gen:{name:\"vorpol\",type:[\"Dagger\",\"Void\"],stat:{physical_power:50,attack_speed:100,speed:100},ability:{function:\"gen:ability/data/blitzkrieg\"}},AttributeModifiers:[{AttributeName:\"minecraft:generic.luck\",Name:\"tungsten.mainhand\",Amount:-0.000000000001,Operation:0,UUID:[I;12,42069,-0,10],Slot:\"mainhand\"},{AttributeName:\"minecraft:generic.luck\",Name:\"tungsten.offhand\",Amount:-0.000000000001,Operation:0,UUID:[I;12,42069,-0,11],Slot:\"offhand\"}],display:{Name:'{\"translate\":\"Vorpol\",\"color\":\"light_purple\",\"italic\":false,\"bold\":false,\"underlined\":false}',Lore:['[{\"translate\":\"A\",\"font\":\"genesis:icon\",\"color\":\"white\",\"italic\":false},{\"translate\":\"Legendary Void Dagger\",\"font\":\"minecraft:default\",\"color\":\"#3b2b06\",\"italic\":false}]','{\"translate\":\"\",\"font\":\"genesis:stats\",\"color\":\"white\",\"italic\":false,\"extra\":[{\"translate\":\"genesis.stats.wrapper.physical_power.2\",\"with\":[50]},{\"translate\":\"genesis.stats.wrapper.attack_speed.3\",\"with\":[100]},{\"translate\":\"genesis.stats.wrapper.speed.3\",\"with\":[100]}]}','{\"translate\":\"\"}','[{\"translate\":\"❁\",\"color\":\"#403303\",\"bold\":true,\"italic\":false},{\"translate\":\" Blitzkrieg\",\"color\":\"gold\",\"bold\":false,\"italic\":false}]','{\"translate\":\"Activated Ability\",\"color\":\"dark_gray\"}','[{\"translate\":\"J\",\"font\":\"genesis:icon\",\"color\":\"white\",\"italic\":false},{\"translate\":\"Cooldown: \",\"font\":\"minecraft:default\",\"color\":\"dark_gray\"},{\"translate\":\"7s\",\"font\":\"minecraft:default\",\"color\":\"white\"}]','[{\"translate\":\"I\",\"font\":\"genesis:icon\",\"color\":\"white\",\"italic\":false},{\"translate\":\"Mana: \",\"font\":\"minecraft:default\",\"color\":\"dark_gray\"},{\"translate\":\"12\",\"font\":\"minecraft:default\",\"color\":\"blue\"}]','{\"translate\":\"Releases a shockwave in the direction\",\"color\":\"gray\",\"bold\":false,\"italic\":false}','{\"translate\":\"you are facing, dealing 8 damage to\",\"color\":\"gray\",\"bold\":false,\"italic\":false}','{\"translate\":\"opponents caught in the explosion.\",\"color\":\"gray\",\"bold\":false,\"italic\":false}','{\"translate\":\"\"}','[{\"translate\":\"❂\",\"color\":\"#403303\",\"bold\":true,\"italic\":false},{\"translate\":\" Time Dilation\",\"color\":\"gold\",\"bold\":false,\"italic\":false}]','{\"translate\":\"Passive Ability\",\"color\":\"dark_gray\"}','{\"translate\":\"Gain +0.7 Ability Haste for\",\"color\":\"gray\",\"italic\":false}','{\"translate\":\"every point of Speed.\",\"color\":\"gray\",\"italic\":false}']},CustomModelData:982032,HideFlags:195}"
# col: Compound|List = parse(final_boss)
# print(col["gen"])
