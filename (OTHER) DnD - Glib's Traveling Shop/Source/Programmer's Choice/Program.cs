using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Programmer_s_Choice
{
    class Program
    {
        static void Main(string[] args)
        {

            //Intro from shopkeep:

            Console.WriteLine("Welcome to Glib's Traveling Store");
            Console.WriteLine("----------------------------------------------------");

            int rationcost = 2;
            int arroworboltcost = 5;
            int dartcost = 2;
            int minorhealthcost = 25;
            int majorhealthcost = 60;
            int cureafflictioncost = 100;
            int antidotecost = 10;
            int bandagecost = 10;
            int bedrollcost = 30;
            int tinderboxcost = 5;
            int repairkitcost = 40;
            int torchcost = 5;
            int lanterncost = 10;
            int bulllanterncost = 35;
            int oilcost = 5;
            int waterskincost = 15;
            int craftmatcost = 7;
            int enchantedcost = 0;

            string glib = @" 
          (                       )
          |\    _,--------._    / |
          | `.,'            `. /  |
          `  '              ,-'   '
           \/_         _   (     /
          (,-.`.    ,',-.`. `__,'
           |/#\ ),-','#\`= ,'.` |
           `._/)  -'.\_,'   ) ))|
           /  (_.)\     .   -'//
          (  /\____/\    ) )`'\
           \ |V----V||  ' ,    \
            |`- -- -'   ,'   \  \      _____
     ___    |         .'    \ \  `._,-'     `-
        `.__,`---^---'       \ ` -'
           -.______  \ . /  ______,-
                   `.     ,'            ";

            Console.WriteLine(glib); //glib header/ascii art

            Console.WriteLine("----------------------------------------------------");

            Console.WriteLine("\nA shifty Demon of some kind stands before you. He says 'What can I interest you in?'");

            Console.WriteLine("\nPress any key to continue...");
            Console.ReadKey();

            Console.Clear();

            //rng for %chance of enchanted item in wares:

            Random r = new Random();
            int rng = r.Next(1, 100);
            string enchanttype = null;
            int rng2 = r.Next(1, 100);
            if (rng2 > 0 && rng2 < 26)
            {
                enchanttype = "Ring";
            }
            else if (rng2 > 25 && rng2 < 51)
            {
                enchanttype = "Armor";
            }
            else if (rng2 > 50 && rng2 < 76)
            {
                enchanttype = "Amulet";
            }
            else if (rng2 > 75 && rng2 < 101)
            {
                enchanttype = "Weapon";
            }

            //menu of goods available:

            Console.WriteLine("Goods available: ");
            Console.WriteLine("1) Ration of Food - 2 gold");
            Console.WriteLine("2) Arrows or Bolts(10) - 5 gold");
            Console.WriteLine("3) Darts(10) - 2 gold");
            Console.WriteLine("4) Minor Health Potion - 25 gold");
            Console.WriteLine("5) Major Health Potion - 60 gold");
            Console.WriteLine("6) Potion of Cure Afflictions - 100 gold");
            Console.WriteLine("7) Antidote - 10 gold");
            Console.WriteLine("8) Bandages - 10 gold");
            Console.WriteLine("9) Bedroll - 30 gold");
            Console.WriteLine("10) Tinderbox(5) - 5 gold");
            Console.WriteLine("11) Repair Kit - 40 gold");
            Console.WriteLine("12) Torch - 5 gold");
            Console.WriteLine("13) Lantern - 10 gold");
            Console.WriteLine("14) Bullseye Lantern - 35 gold");
            Console.WriteLine("15) Oil Flask - 5 gold");
            Console.WriteLine("16) Waterskin - 15 gold");
            Console.WriteLine("17) Crafting Material(Basic) - 7 gold");
            if (rng > 50)
            {
                Console.WriteLine("18) Enchanted Item(" + enchanttype + ") - (Custom Price) gold");
            }
            Console.WriteLine("0) Finish Shopping and Checkout");

            int exit = 1;
            int totalcost = 0;
            string[] shoppingcart = new string[20];
            int totalgoodsavailable = 18;
            int userchoice = 25000;
            bool discount = false;

            //shopping loop:

            do
            {
                Console.WriteLine("\nWhat item are you interested in?: ");
                string userchoice1 = Console.ReadLine();

                if (userchoice1 == "glibglob") //discount activator
                {
                    discount = true;
                }

                bool valid = Int32.TryParse(userchoice1, out userchoice); //input validation

                if (valid == false)
                {
                    continue;
                }
                else if (userchoice == 0)
                {
                    exit = 0;
                    break;
                }
                else if (userchoice <= totalgoodsavailable && userchoice >= 0)
                {
                    Console.WriteLine("\nHow many would you like?: ");
                    int userchoiceamt = Int32.Parse(Console.ReadLine());

                    switch (userchoice) //actual shopping loop execution
                    {
                        case 0:
                            break;
                        case 1:
                            int rations = userchoiceamt;
                            int InCartRation = (rationcost * userchoiceamt);
                            shoppingcart[1] = (+rations + " Ration of Food - " + InCartRation + " gold");
                            totalcost += InCartRation;
                            break;
                        case 2:
                            int arrowsorbolts = userchoiceamt;
                            int InCartArrowOrBolt = (arroworboltcost * userchoiceamt);
                            shoppingcart[2] = (+arrowsorbolts + " Arrows or Bolts(10) - " + InCartArrowOrBolt + " gold");
                            totalcost += InCartArrowOrBolt;
                            break;
                        case 3:
                            int darts = userchoiceamt;
                            int InCartDart = (dartcost * userchoiceamt);
                            shoppingcart[3] = (+darts + " Darts(10) - " + InCartDart + " gold");
                            totalcost += InCartDart;
                            break;
                        case 4:
                            int minorhealth = userchoiceamt;
                            int InCartMinorHealth = (minorhealthcost * userchoiceamt);
                            shoppingcart[4] = (+minorhealth + " Minor Health Potion - " + InCartMinorHealth + " gold");
                            totalcost += InCartMinorHealth;
                            break;
                        case 5:
                            int majorhealth = userchoiceamt;
                            int InCartMajorHealth = (majorhealthcost * userchoiceamt);
                            shoppingcart[5] = (+majorhealth + " Major Health Potion - " + InCartMajorHealth + " gold");
                            totalcost += InCartMajorHealth;
                            break;
                        case 6:
                            int cureaffliction = userchoiceamt;
                            int InCartCureAffliction = (cureafflictioncost * userchoiceamt);
                            shoppingcart[6] = (+cureaffliction + " Potion of Cure Afflictions - " + InCartCureAffliction + " gold");
                            totalcost += InCartCureAffliction;
                            break;
                        case 7:
                            int antidote = userchoiceamt;
                            int InCartAntidote = (antidotecost * userchoiceamt);
                            shoppingcart[7] = (+antidote + " Antidote - " + InCartAntidote + " gold");
                            totalcost += InCartAntidote;
                            break;
                        case 8:
                            int bandages = userchoiceamt;
                            int InCartBandages = (bandagecost * userchoiceamt);
                            shoppingcart[8] = (+bandages + " Bandages - " + InCartBandages + " gold");
                            totalcost += InCartBandages;
                            break;
                        case 9:
                            int bedrolls = userchoiceamt;
                            int InCartBedrolls = (bedrollcost * userchoiceamt);
                            shoppingcart[9] = (+bedrolls + " Bedroll - " + InCartBedrolls + " gold");
                            totalcost += InCartBedrolls;
                            break;
                        case 10:
                            int tinderbox = userchoiceamt;
                            int InCartTinderbox = (tinderboxcost * userchoiceamt);
                            shoppingcart[10] = (+tinderbox + " Tinderbox(5) - " + InCartTinderbox + " gold");
                            totalcost += InCartTinderbox;
                            break;
                        case 11:
                            int repairkit = userchoiceamt;
                            int InCartRepairKit = (repairkitcost * userchoiceamt);
                            shoppingcart[11] = (+repairkit + " Repair Kit - " + InCartRepairKit + " gold");
                            totalcost += InCartRepairKit;
                            break;
                        case 12:
                            int torch = userchoiceamt;
                            int InCartTorch = (torchcost * userchoiceamt);
                            shoppingcart[12] = (+torch + " Torch - " + InCartTorch + " gold");
                            totalcost += InCartTorch;
                            break;
                        case 13:
                            int lantern = userchoiceamt;
                            int InCartLantern = (lanterncost * userchoiceamt);
                            shoppingcart[13] = (+lantern + " Lantern - " + InCartLantern + " gold");
                            totalcost += InCartLantern;
                            break;
                        case 14:
                            int bulllantern = userchoiceamt;
                            int InCartBullLantern = (bulllanterncost * userchoiceamt);
                            shoppingcart[14] = (+bulllantern + " Bullseye Lantern - " + InCartBullLantern + " gold");
                            totalcost += InCartBullLantern;
                            break;
                        case 15:
                            int oil = userchoiceamt;
                            int InCartOil = (oilcost * userchoiceamt);
                            shoppingcart[15] = (+oil + " Oil Flask - " + InCartOil + " gold");
                            totalcost += InCartOil;
                            break;
                        case 16:
                            int waterskin = userchoiceamt;
                            int InCartWaterskin = (waterskincost * userchoiceamt);
                            shoppingcart[16] = (+waterskin + " Waterskin - " + InCartWaterskin + " gold");
                            totalcost += InCartWaterskin;
                            break;
                        case 17:
                            int craftmat = userchoiceamt;
                            int InCartCraftMat = (craftmatcost * userchoiceamt);
                            shoppingcart[17] = (+craftmat + " Crafting Materials(Basic) - " + InCartCraftMat + " gold");
                            totalcost += InCartCraftMat;
                            break;
                        case 18:
                            int enchanted = userchoiceamt;
                            Console.WriteLine("\nAsk your DM for price of Enchanted Item: ");
                            enchantedcost = Int32.Parse(Console.ReadLine());
                            int InCartEnchanted = (enchantedcost * userchoiceamt);
                            shoppingcart[18] = (+enchanted + " Enchanted Item(" + enchanttype + ") - " + InCartEnchanted + " gold");
                            totalcost += InCartEnchanted;
                            break;
                    }
                } 
            } while (exit > 0);

            //reciept printer and totalcost:

            Console.Clear();
            Console.Write("Receipt:");
            Console.WriteLine("\n---------------------------");

            PrintArray(shoppingcart); //call to shopping cart array printer to display goods being purchased

            Console.WriteLine("\n---------------------------");
            Console.WriteLine("Total Cost: " + totalcost + " gold");

            Console.WriteLine("\nPress any key to pay and exit the store...");
            Console.ReadKey();

            Console.Clear();

            //exitscreen 1 (taxed) and exitscreen 2 (untaxed/discounted):

            Console.WriteLine("Welcome to Glib's Traveling Store"); //glib header/ascii art
            Console.WriteLine("----------------------------------------------------");
            Console.WriteLine(glib);
            Console.WriteLine("----------------------------------------------------");

            if (discount == false) //screen 1 - taxed
            {
                Console.WriteLine("\nAs you move to leave, Glib stops you with a greedy look in his eyes.");
                Console.WriteLine("\n'Since I seem to be the only provider of goods out here I think it's only fair...'");
                Console.WriteLine("'TO CHARGE YOU TAX! That will be a 10% tax for my distinguished efforts, and charming company.'");
                Console.WriteLine("'...I take tips too, you know!'");

                double tmp = totalcost * 0.10;
                int taxcost = (int)Math.Round(tmp, 1);

                Console.WriteLine("\nGlib charges you " + taxcost + " gold in taxes.");

                Console.WriteLine("\nPress any key to pay your tax and exit the shop.. Quickly!");
                Console.ReadKey();
            }
            else if (discount == true) //screen 2 - preferred customer; untaxed/discounted
            {
                Console.WriteLine("\nAs you move to leave, Glib stops you with an eerie smile on his face.");
                Console.WriteLine("\n'Since you're a favorite customer of mine, I'll let you slip away tax free...'");
                Console.WriteLine("'THIS TIME!'");
                Console.WriteLine("'By the way, thanks for the tips. I'm saving up for a new mask!'");
                Console.WriteLine("'I'm always happy to take more tips.. if you're ever feeling generous, that is..'");

                Console.WriteLine("\nGlib moves out of the way and lets you exit the store.");

                Console.WriteLine("\nPress any key to exit happily...");
                Console.ReadKey();
            }

        }

        //shopping cart:

        static void PrintArray(string[] shoppingcart)
        {


            for (int i = 0; i < shoppingcart.Length; i++)
            {
                string tmp = shoppingcart[i];
                
                Console.WriteLine(tmp);
               
                
            }
        }
    }
}
