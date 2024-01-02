% Use this query to run the generator:
% ?- run.


askForInput(Query, Answer, Confirmation) :-
    !,
    write(Query),
    nl,
    read(Answer),
    write(Confirmation),
    write(Answer),
    nl.


askForInput(Query, Answer) :-
    !,
    write(Query),
    nl,
    read(Answer).


format(CropName, GrowthStages, MinGrowthTime, MaxGrowthTime, ModelItem, CropCustomModelData,
    SeedCustomModelData, XP, MinBonemeal, MaxBonemeal) :-
    !,
    write('{id:"genesis:'),
    write(CropName),
    write('",growth:{time:{min:'),
    write(MinGrowthTime),
    write(',max:'),
    write(MaxGrowthTime),
    write('},stages:'),
    write(GrowthStages),
    write(',display:{stages_per_model:1,models:{id:"minecraft:'),
    write(ModelItem),
    write('",custom_model_data_start:'),
    write(CropCustomModelData),
    write('}},seed_item:{preprocessing:{show_growth_time:1b,apply_default_skin:1b},Count:1b,id:"minecraft:player_head",tag:{SkullOwner:{Name:"genesis.block.crop.seed.genesis:'),
    write(CropName),
    write('"},genesis:{phead:{detect:1b}},CustomModelData:'),
    write(SeedCustomModelData),
    write(',display:{Name:\'{"translate":"item.gen.crops.seed.foo","italic":false}\'}}},harvest:{loot_table:"gen:crops/harvest/'),
    write(CropName),
    write('",xp:'),
    write(XP),
    write('},bone_meal:{stages:{min:'),
    write(MinBonemeal),
    write(',max:'),
    write(MaxBonemeal),
    write('}},requirements:{soil:["minecraft:farmland"]}}')
    .


run :-
    askForInput('Input the ID of the custom crop, ending with a full stop. e.g. "tomato."', CropName, 'Your crop name is: genesis:'),
    askForInput('How many growth stages does the crop have? e.g. "8."', GrowthStages),
    askForInput('What is the minimum time (in ticks) to advance one stage? e.g. "200."', MinGrowthTime),
    askForInput('What is the maximum time (in ticks) to advance one stage? e.g. "300."', MaxGrowthTime),
    askForInput('What is the item used to display the crop models? e.g. "sunflower."', ModelItem),
    askForInput('What is the CustomModelData for the first growth stage model? e.g. "982001."', CropCustomModelData),
    askForInput('What is the CustomModelData for the seed item? e.g. "982001."', SeedCustomModelData),
    askForInput('How much farming XP do you get from harvesting the crop? e.g. "10."', XP),
    askForInput('How many stages will the crop grow at minimum when bone-mealing? e.g. "0."', MinBonemeal),
    askForInput('How many stages will the crop grow at maximum when bone-mealing? e.g. "4."', MaxBonemeal),
    format(CropName, GrowthStages, MinGrowthTime, MaxGrowthTime, ModelItem, CropCustomModelData,
    SeedCustomModelData, XP, MinBonemeal, MaxBonemeal).