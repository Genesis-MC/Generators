import React, { useState } from 'react';
import './App.css';

interface Item {
  genesisId: string;
  baseItem: string;
  tag: string;
}

interface MCLootTable {
  display: {
      icon: {
          item: string | undefined;
          nbt: string | undefined;
      };
      title: string;
      description: {
          text: string;
          color: string;
      };
      frame: string;
      show_toast: boolean;
      announce_to_chat: boolean;
      hidden: boolean;
  };
  parent: string;
  criteria: any;
  rewards?: {
      function: string;
  };
  requirements?: string[][];
}

const App: React.FC = () => {
  const [name, setName] = useState('');
  const [description, setDescription] = useState('');
  const [parent, setParent] = useState('');
  const [items, setItems] = useState<Item[]>([]);
  const [requireAll, setRequireAll] = useState(true);
  const [increaseLevel, setIncreaseLevel] = useState(false);
  const [lootTable, setLootTable] = useState('');
  const [displayItem, setDisplayItem] = useState('');
  const [frame, setFrame] = useState('task');
  const [output, setOutput] = useState('');

  const handleAddItem = () => {
    const data = JSON.parse(lootTable);
    const baseItem = data.pools[0].entries[0].name;
    const tag: string = (data.pools[0].entries[0].functions || data.pools[0].functions).find((func: any) => func.function === "minecraft:set_nbt").tag;
    const tagData = tag.match(/gen:\{.*?name:"(.*?)"/);
    const genesisId = tagData ? tagData[1] : '';

    const newItem: Item = {
      genesisId,
      baseItem,
      tag,
    };

    setItems([...items, newItem]);
    if (!displayItem) setDisplayItem(genesisId);
    setLootTable('');
  };

  const handleItemChange = (index: number, field: keyof Item, value: string) => {
    const updatedItems = [...items];
    updatedItems[index][field] = value;
    setItems(updatedItems);
  };

  const handleDisplayItemChange = (genesisId: string) => {
    setDisplayItem(genesisId);
  };

  const handleGenerate = () => {
    const criteria = items.reduce((acc: any, item) => {
      acc[item.genesisId.toLowerCase().replace(' ','_')] = {
        "trigger": "minecraft:inventory_changed",
        "conditions": {
          "items": [{
            "items": [ item.baseItem ],
            "nbt": `{gen:{name:"${item.genesisId}"}}`
      }]}};
      return acc;
    }, {});

    const displayNbtData: {
      CustomModelData?: number,
      display?: {
        color: number,
      },
      Trim?: {
        material: string,
        pattern: string,
      },
    } = {};

    const displayItemData = items.find((item) => item.genesisId === displayItem);

    const maybeCMD = displayItemData?.tag.match(/CustomModelData:(\d+)/);
    const maybeColor = displayItemData?.tag.match(/display:\{[^}]*color:(\d+)/);
    const maybeTrimMaterial = displayItemData?.tag.match(/Trim:\{[^}]*material:"(.*?)"/);
    const maybeTrimPattern = displayItemData?.tag.match(/Trim:\{[^}]*pattern:"(.*?)"/);

    if (maybeCMD) displayNbtData.CustomModelData = parseInt(maybeCMD[1]);
    if (maybeColor) displayNbtData.display = { color: parseInt(maybeColor[1]) };
    if (maybeTrimMaterial && maybeTrimPattern) displayNbtData.Trim = { material: maybeTrimMaterial[1], pattern: maybeTrimPattern[1] };

    const data: MCLootTable = {
      "display": {
          "icon": {
              "item": displayItemData?.baseItem,
              "nbt": JSON.stringify(displayNbtData),
          },
          "title": name,
          "description": {
              "text": description,
              "color": "gray"
          },
          "frame": frame,
          "show_toast": true,
          "announce_to_chat": true,
          "hidden": false
      },
      "parent": parent,
      "criteria": criteria,
  }

  if (increaseLevel) data.rewards = { "function": "gen:player_events/increase_level" };

  if (!requireAll) data.requirements = Object.keys(criteria).map((key) => [key]);

    setOutput(JSON.stringify(data, null, 2));
  };

  return (
    <div>
      <h3>Advancement Info:</h3>
      <label>
        Name:
        <input type="text" value={name} onChange={(e) => setName(e.target.value)} />
      </label>
      <br />
      <label>
        Description:
        <input type="text" value={description} onChange={(e) => setDescription(e.target.value)} />
      </label>
      <br />
      <label>
        Parent:
        <input type="text" value={parent} onChange={(e) => setParent(e.target.value)} />
      </label>
      <br />
      <label>
        Increase Level:
        <input
          type="checkbox"
          checked={increaseLevel}
          onChange={() => setIncreaseLevel(!increaseLevel)}
        />
      </label>
      <br />
      <h3>Items:</h3>
      {items.map((item, index) => (
        <div key={index}>
          <label>
            Genesis ID:
            <input
              type="text"
              value={item.genesisId}
              onChange={(e) => handleItemChange(index, 'genesisId', e.target.value)}
            />
          </label>
          <label>
            Base Item:
            <input
              type="text"
              value={item.baseItem}
              onChange={(e) => handleItemChange(index, 'baseItem', e.target.value)}
            />
          </label>
          <br />
        </div>
      ))}
      <div>
        <label>
          LootTable:
          <textarea value={lootTable} onChange={(e) => setLootTable(e.target.value)} />
        </label>
      </div>
      <button onClick={handleAddItem}>+ Add</button>
      <br />
      <label>
        Require All:
        <input
          type="checkbox"
          checked={requireAll}
          onChange={() => setRequireAll(!requireAll)}
        />
      </label>
      <br />
      <h3>Display:</h3>
      <div>
        {items.map((item) => (
          <label key={item.genesisId}>
            <input
              type="checkbox"
              checked={displayItem === item.genesisId}
              onChange={() => handleDisplayItemChange(item.genesisId)}
            />
            {item.genesisId}
          </label>
        ))}
      </div>
      <div>
        <label key={'task'}>
          <input
            type="checkbox"
            checked={frame === 'task'}
            onChange={() => setFrame("task")}
          />
          {'task'}
        </label>
        <label key={'goal'}>
          <input
            type="checkbox"
            checked={frame === 'goal'}
            onChange={() => setFrame("goal")}
          />
          {'goal'}
        </label>
        <label key={'challenge'}>
          <input
            type="checkbox"
            checked={frame === 'challenge'}
            onChange={() => setFrame("challenge")}
          />
          {'challenge'}
        </label>
      </div>
      <br />
      <button onClick={handleGenerate}>Generate</button>
      <br />
      <h3>Output:</h3>
      <pre><code>{output}</code></pre>
    </div>
  );
};

export default App;
