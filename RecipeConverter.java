import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;
import java.io.File;
import java.io.FileWriter;

//Converts old genesis recipes to new ones
class RecipeConverter 
{
    public static void main(String[] args) throws IOException
    {
        RecipeConverter foo = new RecipeConverter();
        //File oldRecipes = new File("oldRecipes.txt");
        //Scanner scanner = new Scanner(oldRecipes);
        FileWriter myWriter = new FileWriter("newRecipes.txt");
        Scanner scanner = new Scanner(System.in);
        System.out.print("Input old Genesis item NBT or -1 to stop: ");
        String userInput = scanner.nextLine();

        while(!userInput.equals("-1")) {
            foo.convertLootTableGear(userInput, myWriter);
            System.out.print("Input old Genesis item NBT or -1 to stop: ");
            userInput = scanner.nextLine();
        }

        /*while(scanner.hasNextLine())
        {
            String data = scanner.nextLine();
            foo.convertRecipe(data, myWriter);
        }*/
        scanner.close();
        myWriter.close();
    }

    private void convertRecipe(String input, FileWriter myWriter) throws IOException
    {
        if(input.length() == 0 || input.substring(0,1).equals("#"))
            return;
        
        //Gets item name in Pascal Case
        String itemName = input.substring(input.lastIndexOf("/")+1);
        itemName = snakeToPascal(itemName);

        //Split recipe into array of individual ingredients
        input = input.substring(input.indexOf("{0:[{Slot:") + 13, input.indexOf("]} ") - 1);
        String regex = "\\},\\{Slot:\\d+b,|}\\],\\d+:\\[\\{Slot:\\d+b,";
        String[] ingredients = input.split(regex);

        //Print out new recipe
        myWriter.write("# " + itemName + "\n");
        myWriter.write("@add_custom_recipe([\n");
        for(int i = 0; i<ingredients.length; i++) {
            String ingredient = ingredients[i];

            if(i%3==0) myWriter.write("    [");

            if(ingredient.indexOf("tag:") != -1) 
                myWriter.write(snakeToPascal(ingredient.substring(ingredient.indexOf("name:")+6, ingredient.length()-3)));
            else 
                myWriter.write("\"" + ingredient.substring(ingredient.indexOf("minecraft:")+10, ingredient.length()-1) + "\"");

            if(i%3==2) myWriter.write("],\n");
            else myWriter.write(", ");
        }
        myWriter.write("])\n");
    }

    //Does not completely convert the loot table to new custom item format, but saves some grunt work
    private void convertLootTableGear(String input, FileWriter myWriter) throws IOException
    {
        String itemName = input.substring(input.indexOf("name:\\")+7,input.indexOf("\\\",type:"));
        //myWriter.write("@add_loot_table\n@bolt_item\nclass ");
        myWriter.write("@add_loot_table\n@bolt_item\nclass " + snakeToPascal(itemName) + "(GenesisItem):\n");
        myWriter.write("    item_name = (\"" + snakeToPascal(itemName) + "\", {\"color\":\"COLOR\"})\n");
        myWriter.write("    rarity = \"RARITY\"\n");
        myWriter.write("    category = [\"" + input.substring(input.indexOf("type:\\\"")+7,input.indexOf(",stat:{")-2).toLowerCase() + "\"]\n");
        myWriter.write("    stats = (\"mainhand\", {" + parseStats(input.substring(input.indexOf(",stat:{")+7,input.indexOf("},"))) + "})\n");
        myWriter.write("    item_model = texture_path_to_item_model(\"genesis:item/dagger/" + itemName + "\", True)\n");

        if(input.indexOf("ability:") != -1) {
            myWriter.write("    @right_click_ability(\n");
            myWriter.write("        name = \"" + input.substring(input.indexOf("ability/data/")+13,input.indexOf("\\\"}}")) + "\",\n");
            myWriter.write("        description = ,\n");
            myWriter.write("        mana = ,\n");
            myWriter.write("        cooldown = ,\n    )\n");
            myWriter.write("    def " + input.substring(input.indexOf("ability/data/")+13,input.indexOf("\\\"}}")) + "():\n");
        }
    }

    private void convertLootTableNotGear(String input, FileWriter myWriter) throws IOException
    {
        return;
    }

    private String snakeToPascal(String str) {
        StringBuilder pascalCase = new StringBuilder();
        
        for (String word : str.split("_")) {
            if (!word.isEmpty()) {
                pascalCase.append(Character.toUpperCase(word.charAt(0)))
                          .append(word.substring(1).toLowerCase());
            }
        }
        return pascalCase.toString();
    }

    private String parseStats(String stats)
    {
        StringBuilder output = new StringBuilder();
        output.append("\"");
        for(int i = 0; i<stats.length(); i++)
        {
            if(stats.substring(i,i+1).equals(":")) 
                output.append("\"");
            output.append(stats.substring(i,i+1));
            if(stats.substring(i,i+1).equals(",")) 
                output.append("\"");
        }
        return output.toString();
    }
    //physical_power:50,attack_speed:110,armor_toughness:60,speed:30
}