from dataclasses import dataclass
import os
import requests
from get_all_custom_items import Item, get_all
from config import resource_pack_path, mcmeta_assets
import json


texture_cache = {}
model_cache = {}
gen_texture_cache = {}


@dataclass
class Texture:
    path: str
    data: bytes

    def save(self, path: str):
        file_path = f"{path}{self.path.split(':')[0]}/{self.path.split(':')[1]}.png"
        if os.path.isfile(file_path): return
        os.makedirs(os.path.dirname(file_path), exist_ok=True)
        with open(file_path, 'wb') as file:
            file.write(self.data)

    def from_path(path: str, mc_path: str) -> 'Texture':
        with open(path, 'rb') as file:
            data = file.read()
            tx = Texture(path=mc_path, data=data)
            texture_cache[mc_path] = tx
            return tx

    def from_link(link: str, mc_path: str) -> 'Texture':
        response = requests.get(link)
        if response.status_code != 200: raise ValueError(f"Failed to get texture from link: {link}")
        data = response.content
        tx = Texture(path=mc_path, data=data)
        texture_cache[mc_path] = tx
        return tx

    def from_mc_path(mc_path: str) -> 'Texture':
        if mc_path in texture_cache: return texture_cache[mc_path]
        mc_path = clean_path(mc_path)
        local_path = f"{resource_pack_path}assets/{mc_path[0]}/textures/{mc_path[1]}.png"
        if os.path.isfile(local_path): return Texture.from_path(local_path, ':'.join(mc_path))
        if mc_path[0] != 'minecraft': raise ValueError(f"Unknown texture: {mc_path[0]}:{mc_path[1]}")
        link = f"{mcmeta_assets}assets/minecraft/textures/{mc_path[1]}.png"
        return Texture.from_link(link, ':'.join(mc_path))


@dataclass
class Model:
    parent: str
    textures: dict[str, str]
    overrides: list[dict]
    elements: list[dict]
    display: dict

    def get_textures(self) -> dict[str, 'Texture']:
        return {k: Texture.from_mc_path(v) for k, v in self.textures.items()}

    def from_json(data: dict, mc_path: str) -> 'Model':
        mdl = Model(
            parent=data.get('parent'),
            textures=data.get('textures'),
            overrides=data.get('overrides'),
            elements=data.get('elements'),
            display=data.get('display'),
        )
        model_cache[mc_path] = mdl
        return mdl

    def from_file(file_path: str, mc_path: str) -> 'Model':
        with open(file_path, 'r') as file:
            data = json.load(file)
            return Model.from_json(data, mc_path)

    def from_link(link: str, mc_path: str) -> 'Model':
        response = requests.get(link)
        if response.status_code != 200: raise ValueError(f"Failed to get model from link: {link}")
        data = response.json()
        return Model.from_json(data, mc_path)

    def from_mc_path(mc_path: str) -> 'Model':
        if mc_path in model_cache: return model_cache[mc_path]
        mc_path = clean_path(mc_path)
        local_path = f"{resource_pack_path}assets/{mc_path[0]}/models/{mc_path[1]}.json"
        if os.path.isfile(local_path): return Model.from_file(local_path, ':'.join(mc_path))
        if mc_path[0] != 'minecraft': raise ValueError(f"Unknown model: {mc_path[0]}:{mc_path[1]}")
        link = f"{mcmeta_assets}assets/minecraft/models/{mc_path[1]}.json"
        return Model.from_link(link, ':'.join(mc_path))


def clean_path(mc_path: str) -> tuple[str, str]:
    if ':' not in mc_path: mc_path = f"minecraft:{mc_path}"
    mc_path = mc_path.split(':')
    if (mc_path[0] == 'minecraft' and
        not (
            mc_path[1].startswith('item/') or
            mc_path[1].startswith('block/')
        )):
        mc_path[1] = f"item/{mc_path[1]}"
    return mc_path


def get_texture(item: Item) -> Texture:
    if item.gen_id in gen_texture_cache: return gen_texture_cache[item.gen_id]
    model: Model = Model.from_mc_path(item.base_id)
    if item.cmd and model.overrides:
        custom_model_path = None
        for override in model.overrides:
            if override['predicate'].get('custom_model_data') == item.cmd:
                custom_model_path = override['model']
                break
        if not custom_model_path: raise ValueError(f"Failed to find custom model for {item.gen_id} ({item.base_id} >>> {item.cmd})")
        model = Model.from_mc_path(custom_model_path)
    if not model.textures:
        model = Model.from_mc_path(model.parent)
    textures: list[Texture] = model.get_textures()
    # if len(textures) != 1: print(f'!!! WARNING !!! Multiple textures found for {item.gen_id}:\n', [v.path for v in textures.values()])
    texture = [t for t in textures.values()][0]
    gen_texture_cache[item.gen_id] = texture
    return texture


if __name__ == "__main__":
    items = get_all()
    for item in items:
        get_texture(item).save("test/")
    # This handles all but trim and custom head textures
    # It also struggles with 3d models but I dont think we have any of those yet
