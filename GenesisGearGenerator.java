import java.util.Scanner;  // Import the Scanner class

class GenesisGearGenerator
{
    //STATS
    private int[] stats = new int[13];
    private String[] statVal = {"physical_power","magic_power","attack_speed","health","armor","armor_toughness","knockback_resistance","mana_pool","mana_regen","speed","luck","artifact_power","ability_haste"};
    private boolean hasPow = false;
    private boolean hasDef = false;
    private boolean hasMana = false;
    private boolean hasUtil = false;

    //TUNGSTEN ITEM UUID
    private String[] tungVal = {"mainhand","head","chest","legs","feet"};

    public static void main (String[] args) 
    {
        GenesisGearGenerator guh = new GenesisGearGenerator();
        guh.output();
    }

    private void output()
    {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Genesis Custom Item NBT Generator by Electross\nPlease follow all input instructions closely");
        System.out.print("Input what you would like NBT generated for (Item = 1; Gear = 2): ");
        int choice = scanner.nextInt();
        if(choice == 1)
            System.out.print("\n" + outputItem());
        else
            System.out.print("\n" + outputGear());
        scanner.close();
    }

    //{Name:'{"text":"temp","color":"gray","italic":false}',Lore:['{"text":"Uncommon Ingredient","color":"#3B2B06","italic":false}']}}
    private String outputItem()
    {
        String output = "{Name:'{\"text\":\"";
        return output;
    }

    private String outputGear()
    {
        Scanner scanner = new Scanner(System.in);
        
        for(int i = 0; i<13; i++)
            stats[i] = 0;
        String output = "{gen:{stat:{";

        //INPUT CUSTOM STATS
        System.out.print("Input item slot as an integer (Mainhand = 1; Helmet = 2; Chestplate = 3; Leggings = 4; Boots = 5): ");
        int tung = scanner.nextInt();
        System.out.print("\nInput gear stats as an integer; If the gear does not have said stat, input 0\nPhysical Power: ");
        stats[0] = scanner.nextInt();
        System.out.print("Magic Power: ");
        stats[1] = scanner.nextInt();
        System.out.print("Attack Speed: ");
        stats[2] = scanner.nextInt();
        System.out.print("\nHealth: ");
        stats[3] = scanner.nextInt();
        System.out.print("Armor: ");
        stats[4] = scanner.nextInt();
        System.out.print("Armor Toughness: ");
        stats[5] = scanner.nextInt();
        System.out.print("Knockback Resistance: ");
        stats[6] = scanner.nextInt();
        System.out.print("\nMana Pool: ");
        stats[7] = scanner.nextInt();
        System.out.print("Mana Regen: ");
        stats[8] = scanner.nextInt();
        System.out.print("\nMovement Speed: ");
        stats[9] = scanner.nextInt();
        System.out.print("Luck: ");
        stats[10] = scanner.nextInt();
        System.out.print("Artifact Power: ");
        stats[11] = scanner.nextInt();
        System.out.print("Ability Haste: ");
        stats[12] = scanner.nextInt();
        
        //FORMATTING CUSTOM STATS AND CHECKING IF CERTAIN GROUPS OF STATS EXIST
        for(int i = 0; i<13; i++)
        {
            if(stats[i] > 0)
            {
                output += statVal[i] + ":" + stats[i] + ",";
                if(i >= 0 && i <= 2)
                    hasPow = true;
                else if(i >= 3 && i <= 6)
                    hasDef = true;
                else if(i >= 7 && i <= 8)
                    hasMana = true;
                else if(i >= 9 && i <= 12)
                    hasUtil = true;
            }
        }
        if(output.substring(output.length()-1).equals(","))
            output = output.substring(0,output.length()-1);
        
        //FORMATTING TUNGSTEN
        if(tung > 1)
        {
            //if armor
            output += "}},AttributeModifiers:[{AttributeName:\"minecraft:generic.luck\",Name:\"tungsten." + tungVal[tung-1] + "\",Amount:-0.000000000001,Operation:0,UUID:[I;12,42069,-0,";
            output += 10 + tung + "],Slot:";
            output += "\"" + tungVal[tung-1] + "\"";
        }
        else
        {
            //if weapon
            output += "}},AttributeModifiers:[{AttributeName:\"minecraft:generic.luck\",Name:\"tungsten.mainhand\",Amount:-0.000000000001,Operation:0,UUID:[I;12,42069,-0,10],Slot:\"mainhand\"},{AttributeName:\"minecraft:generic.luck\",Name:\"tungsten.offhand\",Amount:-0.000000000001,Operation:0,UUID:[I;12,42069,-0,11],Slot:\"offhand\"";
        }
        output += "}],display:{Lore:['{\"text\":\"\",\"font\":\"genesis:stats\",\"color\":\"white\",\"italic\":false,\"extra\":[";

        //FORMATTING CUSTOM GLYPHS AND BORDERS FOR LORE
        for(int i = 0; i<13; i++)
        {
            if(stats[i] > 0)
                output += "{\"translate\":\"genesis.stats.wrapper." + statVal[i] + "." + getLen(stats[i]) + "\",\"with\":[" + stats[i] + "]},";

            if(i == 2 && hasPow && (hasDef || hasMana || hasUtil) )
            {
                output = output.substring(0,output.length()-1);
                output += "]}','{\"text\":\"\"}','{\"text\":\"\",\"font\":\"genesis:stats\",\"color\":\"white\",\"italic\":false,\"extra\":[";
            }
            else if(i == 6 && hasDef && (hasMana || hasUtil))
            {
                output = output.substring(0,output.length()-1);
                output += "]}','{\"text\":\"\"}','{\"text\":\"\",\"font\":\"genesis:stats\",\"color\":\"white\",\"italic\":false,\"extra\":[";
            }
            else if(i == 8 && hasMana && hasUtil)
            {
                output = output.substring(0,output.length()-1);
                output += "]}','{\"text\":\"\"}','{\"text\":\"\",\"font\":\"genesis:stats\",\"color\":\"white\",\"italic\":false,\"extra\":[";
            }
        }
        if(output.substring(output.length()-1).equals(","))
            output = output.substring(0,output.length()-1);
        output += "]}','{\"text\":\"\"}']},HideFlags:3}";
          
        scanner.close();
        return output;
    }

    private int getLen(int x)
    {
        return ("" + x).length();
    }
}