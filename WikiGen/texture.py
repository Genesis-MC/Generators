
from config import wiki_path, mcmeta_assets, resource_pack_path
import os
import requests
import json
from PIL import Image
from io import BytesIO


def create_texture(texture_id: str):
    if does_texture_exist(texture_id): return
    if texture_id.startswith("minecraft:"):
        download_texture(texture_id)
    elif texture_id.startswith("gen:"):
        copy_gen_texture(texture_id)
    else:
        print(f"Invalid texture id: {texture_id} -> skipping")


def does_texture_exist(texture_id: str) -> bool:
    return os.path.isfile(f"{wiki_path}assets/textures/{texture_id.split(':')[0]}/{texture_id.split(':')[1]}.png")


def download_texture(texture_id: str):
    url = f"{mcmeta_assets}assets/minecraft/textures/item/{texture_id.split(':')[1]}.png"
    response = requests.get(url, stream=True)

    if response.status_code == 200:
        img = Image.open(BytesIO(response.content))
        img = make_wiki_ready(img)
        img.save(f"{wiki_path}assets/textures/minecraft/{texture_id.split(':')[1]}.png")
    else:
        print(f"Failed to download image. HTTP response code: {response.status_code} ({texture_id})")


def copy_gen_texture(gen_id: str):
    # get the texture path from the model
    textures = []
    for dirpath, dirs, files in os.walk(f"{resource_pack_path}assets/genesis/models/"):
        for filename in files:
            if not filename.endswith(f"{gen_id.split(':')[1]}.json"): continue #! this is only needed while source doesnt contain model paths
            with open(os.path.join(dirpath, filename), 'r') as file:
                data = json.load(file)
                textures = [v for v in data['textures'].values() if ':' in v and not v.startswith("minecraft:")]
    if len(textures) == 0:
        print(f"Failed to find texture for {gen_id}, placing missing texture")
        img = Image.open(f"{wiki_path}assets/textures/missing.png")
        img.save(f"{wiki_path}assets/textures/gen/{gen_id.split(':')[1]}.png")
        return
    texture_path = textures[0] #! only take lowest texture, alything more would need understanding of every model ...
    img = Image.open(f"{resource_pack_path}assets/{texture_path.split(':')[0]}/textures/{texture_path.split(':')[1]}.png")
    img = make_wiki_ready(img)
    img.save(f"{wiki_path}assets/textures/gen/{gen_id.split(':')[1]}.png")


def make_wiki_ready(img: Image) -> Image:
    air = Image.open(f"{wiki_path}assets/textures/minecraft/air.png")
    img = img.resize((img.width * 2, img.height * 2), Image.NEAREST)
    air = air.resize(img.size)
    if img.mode != 'RGBA': img = img.convert('RGBA')
    if air.mode != 'RGBA': air = air.convert('RGBA')
    img = Image.alpha_composite(air, img)
    return img
