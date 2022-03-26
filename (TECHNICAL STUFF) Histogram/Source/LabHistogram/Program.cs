using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabHistogram
{
    class Program
    {
        static void Main(string[] args)
        {
            int menuChoice = 0;
            string[] mainMenu = new string[]
            {
                "1: The Speech",
                "2: List of Words",
                "3: Show Histogram",
                "4: Search for Word",
                "5: Remove Word",
                "6: Exit"
            };

            string speech = GetSpeech();
            string[] words = speech.Split(new char[] { ' ', ',', '!', '.', ';' }, StringSplitOptions.RemoveEmptyEntries);
            List<string> wordList = words.ToList();

            string[] sentences = speech.Split(new char[] { '!', '.' });
            List<string> sentenceList = sentences.ToList();

            Dictionary<string, int> histogram = new Dictionary<string, int>(StringComparer.OrdinalIgnoreCase);
            for (int i = wordList.Count - 1; i >= 0; i--)
            {
                if (!histogram.ContainsKey(wordList[i]))
                {
                    histogram.Add(wordList[i], +1);
                }
                else
                {
                    histogram[wordList[i]] += 1;
                }
            }

            //menuloop:
            #region Main Menu
            while (menuChoice != 6)
            {
                ReadChoice("\nChoice: ", mainMenu, out menuChoice);

                switch (menuChoice)
                {
                    case 1:
                        Console.Clear();
                        Console.WriteLine($"{speech}");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    case 2:
                        Console.Clear();
                        foreach (var word in wordList)
                        {
                            Console.WriteLine(word);
                        }
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    case 3:
                        Console.Clear();

                        Print(histogram.OrderByDescending(x => x.Value).ToList());

                        Console.ReadKey();
                        Console.Clear();
                        break;
                    case 4:
                        string wordSearch = null;
                        ReadString("\nWhat word would you like to search for?", ref wordSearch);

                        if (histogram.ContainsKey(wordSearch))
                        {
                            Console.Clear();
                            int tmpVal;
                            string bar = null;

                            histogram.TryGetValue(wordSearch, out tmpVal);
                            for (int i = 0; i < tmpVal; i++)
                            {
                                bar += "#";
                            }
                            Console.Write($"{wordSearch} ");
                            Console.BackgroundColor = ConsoleColor.DarkBlue;
                            Console.ForegroundColor = ConsoleColor.DarkBlue;
                            Console.Write($"{bar}");
                            Console.ForegroundColor = ConsoleColor.White;
                            Console.BackgroundColor = ConsoleColor.Black;
                            Console.Write($" {tmpVal}");

                            List<string> sentencesFound = new List<string>();

                            foreach (string sentence in sentenceList)
                            {
                                if (sentence.Contains(wordSearch))
                                {
                                    Console.WriteLine($"\n{sentence}");
                                }
                            }
                        }
                        else
                        {
                            Console.WriteLine($"\n'{wordSearch}' was not found.");
                        }

                        Console.ReadKey();
                        Console.Clear();
                        break;
                    case 5:
                        string wordRemove = null;
                        ReadString("\nWhat word would you like to remove?", ref wordRemove);


                        if(histogram.Remove(wordRemove) == true)
                        {
                            Console.WriteLine("Word Removed.");
                        }
                        else
                        {
                            Console.WriteLine($"'{wordRemove}' not found.");
                        }

                        Console.ReadKey();
                        Console.Clear();
                        break;
                    case 6:
                        Environment.Exit(1);
                        break;
                }
            }
            #endregion


            Console.ReadKey();

        }

        //methods:
        #region Methods
        public static int ReadInteger(string prompt, int min, int max)
        {
            bool valid = false;
            int result = 0;

            while (valid == false)
            {
                Console.Write($"{prompt}");
                string tmp = Console.ReadLine();

                int.TryParse(tmp, out result);

                if (result > min & result < max)
                {
                    valid = true;
                }
                else
                {
                    Console.WriteLine("Error. Try again.");
                }
            }
            return result;
        }

        public static void ReadString(string prompt, ref string value)
        {
            bool valid = false;
            string tmp;

            while (valid == false)
            {
                Console.WriteLine($"{prompt}");
                tmp = Console.ReadLine();

                if (string.IsNullOrWhiteSpace(tmp) == false)
                {
                    value = tmp;
                    valid = true;
                }
                else
                {
                    Console.WriteLine("Error. Try again.");
                }
            }
        }

        public static void ReadChoice(string prompt, string[] options, out int selection)
        {
            for (int i = 0; i < options.Length; i++)
            {
                Console.WriteLine($"{options[i]}");
            }

            selection = ReadInteger(prompt, 0, options.Length + 1);
        }

        public static string GetSpeech()
        {
            string text = "\nI say to you today, my friends, so even though we face the difficulties of today and tomorrow, I still have a dream. It is a dream deeply rooted in the American dream. " +
            "I have a dream that one day this nation will rise up and live out the true meaning of its creed: We hold these truths to be self-evident: that all men are created equal. " +
            "I have a dream that one day on the red hills of Georgia the sons of former slaves and the sons of former slave owners will be able to sit down together at the table of brotherhood. " +
            "I have a dream that one day even the state of Mississippi, a state sweltering with the heat of injustice, sweltering with the heat of oppression, will be transformed into an oasis of freedom and justice. " +
            "I have a dream that my four little children will one day live in a nation where they will not be judged by the color of their skin but by the content of their character. " +
            "I have a dream today. I have a dream that one day, down in Alabama, with its vicious racists, with its governor having his lips dripping with the words of interposition and nullification; one day right there in Alabama, little black boys and black girls will be able to join hands with little white boys and white girls as sisters and brothers. " +
            "I have a dream today. I have a dream that one day every valley shall be exalted, every hill and mountain shall be made low, the rough places will be made plain, and the crooked places will be made straight, and the glory of the Lord shall be revealed, and all flesh shall see it together. " +
            "This is our hope. This is the faith that I go back to the South with. With this faith we will be able to hew out of the mountain of despair a stone of hope. With this faith we will be able to transform the jangling discords of our nation into a beautiful symphony of brotherhood. " +
            "With this faith we will be able to work together, to pray together, to struggle together, to go to jail together, to stand up for freedom together, knowing that we will be free one day. " +
            "This will be the day when all of God's children will be able to sing with a new meaning, My country, 'tis of thee, sweet land of liberty, of thee I sing. Land where my fathers died, land of the pilgrim's pride, from every mountainside, let freedom ring. " +
            "And if America is to be a great nation this must become true. So let freedom ring from the prodigious hilltops of New Hampshire. Let freedom ring from the mighty mountains of New York. Let freedom ring from the heightening Alleghenies of Pennsylvania! " +
            "Let freedom ring from the snowcapped Rockies of Colorado! Let freedom ring from the curvaceous slopes of California! But not only that; let freedom ring from Stone Mountain of Georgia! " +
            "Let freedom ring from Lookout Mountain of Tennessee! Let freedom ring from every hill and molehill of Mississippi. From every mountainside, let freedom ring. " +
            "And when this happens, when we allow freedom to ring, when we let it ring from every village and every hamlet, from every state and every city, we will be able to speed up that day when all of God's children, black men and white men, Jews and Gentiles, Protestants and Catholics, will be able to join hands and sing in the words of the old Negro spiritual, Free at last! free at last! thank God Almighty, we are free at last!";

            return text;
        }
        public static void Print(List<KeyValuePair<string, int>> list)
        {
            var max = list.Max(x => x.Key.Length);

            foreach (var item in list)
            {
                Console.Write(item.Key.PadLeft(max));

                Console.Write(" ");

                Console.BackgroundColor = ConsoleColor.DarkBlue;
                Console.ForegroundColor = ConsoleColor.DarkBlue;

                for (int i = 0; i < item.Value; i++)
                {
                    Console.Write("#");
                }

                Console.ForegroundColor = ConsoleColor.White;
                Console.BackgroundColor = ConsoleColor.Black;

                Console.Write(" ");
                Console.WriteLine(item.Value);
            }
        }

        #endregion
    }
}
