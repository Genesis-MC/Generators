
from os import walk

start_dir = input("Add the full path to the folder containing all the loot tables (C:\\Users\\...)\n")

start_reference = ""
seperator = '/'
ssd = start_dir.split('\\')
ssd.reverse()
for folder in ssd:
    if folder == 'loot_tables':
        seperator = ':'
        continue
    start_reference = folder + seperator + start_reference
    if seperator == ':': break

pools = ""

for (path, dirs, files) in walk(start_dir):
    if path == start_dir: continue
    for file in files:
        loot_table_reference = "gen:gear/" + path.removeprefix(start_dir)[1:].replace("\\","/") + '/' + file[:-5]
        pools += '{"rolls":1,"entries":[{"type":"minecraft:loot_table","name":"' + loot_table_reference + '"}]},'

print('{"pools":[' + pools[:-1] + ']}')
