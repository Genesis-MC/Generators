import java.util.Scanner;  // Import the Scanner class

class GenesisGearGenerator
{
    public static void main (String[] args) 
    {
        GenesisGearGenerator guh = new GenesisGearGenerator();
        guh.output();
    }

    private void output()
    {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Genesis Custom Item NBT Generator by Electross\nPlease follow all input instructions closely");
        System.out.print("What would you like NBT generated for? (Item = 1; Gear = 2): ");
        int choice = scanner.nextInt();
        scanner.nextLine();
        System.out.println("===================================================================================");
        if(choice == 1)
            System.out.print("\n{" + outputItem(scanner) + ",HideFlags:195}");
        else
            System.out.print("\n{" + outputGear(scanner) + ",HideFlags:195}");
        scanner.close();
    }

    private String outputItem(Scanner scanner)
    {
        String name;
        String color;
        boolean italic;
        boolean bold;
        boolean underlined;
        String CustomModelData;

        String output = "gen:{name:\\\"";

        //NAME
        System.out.print("Item Name: ");
        name = scanner.nextLine();
        System.out.print("\nColor (Please enter valid color code or Hexcode): ");
        color = scanner.nextLine();
        System.out.print("\nItalic (true/false): ");
        italic = scanner.nextBoolean();
        System.out.print("\nBold (true/false): ");
        bold = scanner.nextBoolean();
        System.out.print("\nUnderlined (true/false): ");
        underlined = scanner.nextBoolean();
        output += name + "\\\"},display:{";
        output += itemName(name, color, italic, bold, underlined) + "Lore:[";
        output += rarityAndType(scanner) + "]}";

        //TEXTURES
        System.out.print("\nCustom Model Data (If not applicable, input 0; Else input last 3 values: 982---): ");
        CustomModelData = scanner.nextLine();
        if(CustomModelData.equals("0")==false)
            output += ",CustomModelData:982" + CustomModelData;
        output += addGlint(scanner);
        
        return output;
    }

    private String outputGear(Scanner scanner)
    {
        //NAME
        String name;
        String itemType;
        String color;
        boolean italic;
        boolean bold;
        boolean underlined;

        String CustomModelData;

        //STATS
        int[] stats = new int[13];
        String[] statVal = {"physical_power","magic_power","attack_speed","health","armor","armor_toughness","knockback_resistance","mana_pool","mana_regen","speed","luck","relic_power","ability_haste"};

        //TUNGSTEN ITEM UUID
        int tung;
        String[] tungVal = {"mainhand","head","chest","legs","feet"};
        
        for(int i = 0; i<13; i++)
            stats[i] = 0;
        String output = "gen:{name:\\\"";
        //INPUT ITEM NAME REQ
        System.out.print("Item Name: ");
        name = scanner.nextLine();
        System.out.print("\nItem Type (Ingredient, Mineral, etc): ");
        itemType = scanner.nextLine();
        System.out.print("\nColor (Please enter valid color code or Hexcode): ");
        color = scanner.nextLine();
        System.out.print("\nItalic (true/false): ");
        italic = scanner.nextBoolean();
        System.out.print("\nBold (true/false): ");
        bold = scanner.nextBoolean();
        System.out.print("\nUnderlined (true/false): ");
        underlined = scanner.nextBoolean();
        output += name + "\\\",type:\\\"" + itemType + "\\\",stat:{";

        //INPUT CUSTOM STATS
        System.out.print("Input item slot as an integer (Mainhand = 1; Helmet = 2; Chestplate = 3; Leggings = 4; Boots = 5): ");
        tung = scanner.nextInt();
        System.out.print("\nInput gear stats as an integer; If the gear does not have said stat, input 0\nPhysical Power: ");
        stats[0] = scanner.nextInt();
        System.out.print("Magic Power: ");
        stats[1] = scanner.nextInt();
        System.out.print("Attack Speed: ");
        stats[2] = scanner.nextInt();
        System.out.print("Health: ");
        stats[3] = scanner.nextInt();
        System.out.print("Armor: ");
        stats[4] = scanner.nextInt();
        System.out.print("Armor Toughness: ");
        stats[5] = scanner.nextInt();
        System.out.print("Knockback Resistance: ");
        stats[6] = scanner.nextInt();
        System.out.print("Mana Pool: ");
        stats[7] = scanner.nextInt();
        System.out.print("Mana Regen: ");
        stats[8] = scanner.nextInt();
        System.out.print("Movement Speed: ");
        stats[9] = scanner.nextInt();
        System.out.print("Luck: ");
        stats[10] = scanner.nextInt();
        System.out.print("Relic Power: ");
        stats[11] = scanner.nextInt();
        System.out.print("Ability Haste: ");
        stats[12] = scanner.nextInt();
        
        //FORMATTING CUSTOM STATS AND CHECKING IF CERTAIN GROUPS OF STATS EXIST
        for(int i = 0; i<13; i++)
        {
            if(stats[i] != 0)
            {
                output += statVal[i] + ":" + stats[i] + ",";
            }
        }
        if(output.substring(output.length()-1).equals(","))
            output = output.substring(0,output.length()-1);
        
        //FORMATTING TUNGSTEN
        if(tung > 1)
        {
            //if armor
            output += "}},AttributeModifiers:[{AttributeName:\\\"minecraft:generic.luck\\\",Name:\\\"tungsten." + tungVal[tung-1] + "\\\",Amount:-0.000000000001,Operation:0,UUID:[I;12,42069,-0,";
            output += 10 + tung + "],Slot:";
            output += "\\\"" + tungVal[tung-1] + "\\\"";
        }
        else
        {
            //if weapon
            output += "}},AttributeModifiers:[{AttributeName:\\\"minecraft:generic.luck\\\",Name:\\\"tungsten.mainhand\\\",Amount:-0.000000000001,Operation:0,UUID:[I;12,42069,-0,10],Slot:\\\"mainhand\\\"";
            //Add this for offhand weapon calculations: },{AttributeName:\\\"minecraft:generic.luck\\\",Name:\\\"tungsten.offhand\\\",Amount:-0.000000000001,Operation:0,UUID:[I;12,42069,-0,11],Slot:\\\"offhand\\\"
        }
        output += "}],display:{" + itemName(name, color, italic, bold, underlined) + "Lore:[" + rarityAndType(scanner,itemType) + ",'{\\\"translate\\\":\\\"\\\",\\\"font\\\":\\\"genesis:stats\\\",\\\"color\\\":\\\"white\\\",\\\"italic\\\":false,\\\"extra\\\":[";

        //FORMATTING CUSTOM GLYPHS AND BORDERS FOR LORE
        int count = 0;
        for(int i = 0; i<13; i++)
        {
            if(stats[i] > 0)
            {
                count++;
                output += "{\\\"translate\\\":\\\"genesis.stats.wrapper." + statVal[i] + "." + getLen(stats[i]) + "\\\",\\\"with\\\":[" + stats[i] + "]},";
                stats[i] = 0;
                if(count > 5)
                {
                    count = 0;
                    output = output.substring(0,output.length()-1);
                    output += "]}','{\\\"translate\\\":\\\"\\\"}','{\\\"translate\\\":\\\"\\\",\\\"font\\\":\\\"genesis:stats\\\",\\\"color\\\":\\\"white\\\",\\\"italic\\\":false,\\\"extra\\\":[";
                }
            }
        }
        for(int i = 0; i<13; i++)
        {
            if(stats[i] < 0)
            {
                count++;
                output += "{\\\"translate\\\":\\\"genesis.stats.wrapper." + statVal[i] + "." + getLen(stats[i]) + "\\\",\\\"with\\\":[" + stats[i] + "],\\\"color\\\":\\\"red\\\"},";
                stats[i] = 0;
                if(count > 5)
                {
                    count = 0;
                    output = output.substring(0,output.length()-1);
                    output += "]}','{\\\"translate\\\":\\\"\\\"}','{\\\"translate\\\":\\\"\\\",\\\"font\\\":\\\"genesis:stats\\\",\\\"color\\\":\\\"white\\\",\\\"italic\\\":false,\\\"extra\\\":[";
                }
            }
        }
        if(output.substring(output.length()-1).equals(","))
            output = output.substring(0,output.length()-1);
        output += "]}','{\\\"translate\\\":\\\"\\\"}']}";

        //TEXTURES
        System.out.print("\nCustom Model Data (If not applicable, input 0; Else input last 3 values: 982---): ");
        CustomModelData = scanner.nextLine();
        if(CustomModelData.equals("0")==false)
            output += ",CustomModelData:982" + CustomModelData;
          
        return output;
    }

    private String rarityAndType(Scanner scanner)
    {

        String rarity;
        String itemType = "";

        String output = "'[{\\\"translate\\\":\\\"A\\\",\\\"font\\\":\\\"genesis:icon\\\",\\\"color\\\":\\\"white\\\",\\\"italic\\\":false},{\\\"translate\\\":\\\"";
        scanner.nextLine();
        //LORE
        System.out.print("\nRarity (Common, Uncommon, Rare, etc): ");
        rarity = scanner.nextLine();
        System.out.print("\nItem Type (Ingredient, Mineral, etc): ");
        itemType = scanner.nextLine();
        output += rarity + " " + itemType + "\\\",\\\"font\\\":\\\"minecraft:default\\\",\\\"color\\\":\\\"";

        if(rarity.equals("Common"))
            output += "white\\\",\\\"italic\\\":false}]'";
        else if(rarity.equals("Uncommon"))
            output += "aqua\\\",\\\"italic\\\":false}]'";
        else if(rarity.equals("Rare"))
            output += "yellow\\\",\\\"italic\\\":false}]'";
        else if(rarity.equals("Epic"))
            output += "light_purple\\\",\\\"italic\\\":false}]'";
        else if(rarity.equals("Legendary"))
            output += "#3b2b06\\\",\\\"italic\\\":false}]'";
        else if(rarity.equals("Mythical"))
            output += "#211905\\\",\\\"italic\\\":false}]'";
        else
            output += "#403303\\\",\\\"italic\\\":false}]'";

        return output;
    }

    private String rarityAndType(Scanner scanner, String type)
    {

        String rarity;
        String itemType = type;

        String output = "'[{\\\"translate\\\":\\\"A\\\",\\\"font\\\":\\\"genesis:icon\\\",\\\"color\\\":\\\"white\\\",\\\"italic\\\":false},{\\\"translate\\\":\\\"";
        scanner.nextLine();
        //LORE
        System.out.print("\nRarity (Common, Uncommon, Rare, etc): ");
        rarity = scanner.nextLine();
        output += rarity + " " + itemType + "\\\",\\\"font\\\":\\\"minecraft:default\\\",\\\"color\\\":\\\"";

        if(rarity.equals("Common"))
            output += "white\\\",\\\"italic\\\":false}]'";
        else if(rarity.equals("Uncommon"))
            output += "aqua\\\",\\\"italic\\\":false}]'";
        else if(rarity.equals("Rare"))
            output += "yellow\\\",\\\"italic\\\":false}]'";
        else if(rarity.equals("Epic"))
            output += "light_purple\\\",\\\"italic\\\":false}]'";
        else if(rarity.equals("Legendary"))
            output += "#3b2b06\\\",\\\"italic\\\":false}]'";
        else if(rarity.equals("Mythical"))
            output += "#211905\\\",\\\"italic\\\":false}]'";
        else
            output += "#403303\\\",\\\"italic\\\":false}]'";

        return output;
    }

    private String itemName(String name, String color, boolean italic, boolean bold, boolean underlined)
    {
        return "Name:'{\\\"translate\\\":\\\"" + name + "\\\",\\\"color\\\":\\\"" + color + "\\\",\\\"italic\\\":" + italic + ",\\\"bold\\\":" + bold + ",\\\"underlined\\\":" + underlined + "}',";
    }

    private String addGlint(Scanner scanner)
    {
        boolean glint;
        System.out.print("\nAdd enchant glint (true/false, Note: Enchant glint prevents gear from being enchanting table interactable): ");
        glint = scanner.nextBoolean();
        scanner.nextLine();
        if(glint)
            return ",Enchantments:[{}]";
        return "";
    }

    private int getLen(int x)
    {
        return ("" + x).length();
    }
}