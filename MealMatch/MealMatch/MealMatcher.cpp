#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;

class Restaurant
{
private:
    string name;
    string cuisine;
    int avgPrice;
    map<string, pair<double, double>> schedule;
public:
    // Getters, all are const to avoid modifying class members
    
    // Returns the name of the restaurant
    string getName() const
    {
        return name;
    }
    
    // Returns the type of cuisine of the restaurant
    string getCuisine() const
    {
        return cuisine;
    }
    
    // Returns the average price of menu items at the restaurant
    int getAvgPrice() const
    {
        return avgPrice;
    }
    
    // Returns the unordered map with the name of the restaurant as the key and
    // a pair of doubles of size two where the first element is the opening
    // time and the second element is the closing time
    map<string, pair<double, double>> getSchedule() const
    {
        return schedule;
    }
    
    // Setters
    
    // Sets a new name for the restaurant
    void setName(const string &newName)
    {
        name = newName;
    }
    
    // Sets a new cuisine type for the restaurant
    void setCuisine(const string &newCuisine)
    {
        cuisine = newCuisine;
    }
    
    // Sets a new average price for the restaurant
    void setAvgPrice(int newPrice)
    {
        avgPrice = newPrice;
    }
    
    // Sets a new key value pair, taking in the day of the week, opening time,
    // closing time, and adding it to the schedule unordered map
    void setSchedule(const string &day, double openTime, double closeTime)
    {
        schedule[day] = {openTime, closeTime};
    }
    
    // Prints all information to console for testing purposes
    void printInfo() const;
    
    // Default constructor
    Restaurant();
    
};

// Bank for the days of the week for iterative purposes and to avoid repetition
array<string, 7> getWeekDays()
{
    array<string, 7> weekDays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    
    return weekDays;
}

// Class functions

// Prints all information stored in a restaurant object to console, for debugging purposes
void Restaurant::printInfo() const
{
    // Prints out basic info
    cout << name << ", " << cuisine << ", " << avgPrice << ", ";
    
    // Iterates through map and prints out the day, open, and close
    // time for each day of the week. Searches for the in order day
    array<string, 7> weekDays = getWeekDays();
    
    for (const auto& day : weekDays)
        {
            // Find the schedule for each day
            auto it = schedule.find(day);
            if (it != schedule.end()) {
                // Print the schedule for that day
                cout << "\n" << day << ": Open at " << it->second.first << ", Closes at " << it->second.second;
            }
        }
    
    cout << endl;
}

Restaurant::Restaurant()
{
    // Initialization to avoid errors and debug
    name = "Default";
    cuisine = "Default";
    avgPrice = 0;
}

// General functions

// Prints out all restaurants in a Restaurant vector, mostly for testing purposes
void printRestaurants(vector<Restaurant> &restaurants)
{
    for(const Restaurant& restaurant : restaurants)
    {
        restaurant.printInfo();
        cout << endl;
    }
}

// Returns the current time based on your time zone
double getTime()
{
    time_t globalTime = time(0);
    tm *localTime = localtime(&globalTime);
    
    // Time will get returned as a double where the whole number is the hour and
    // the minute is the decimal
    double currentTime = localTime->tm_hour + (localTime->tm_min / 100.0);
    return currentTime;
}

// Returns the current day
string getDay()
{
    time_t globalTime = time(0);
    tm *localTime = localtime(&globalTime);
    array<string, 7> weekDays = getWeekDays();
    
    //fix to match current weekDays array
    int weekDay = localTime->tm_wday;
    if(weekDay == 0)
    {
        weekDay = 6;
    }
    else
    {
        --weekDay;
    }
    
    // Day is returned as a string
    return weekDays[weekDay];
    
}

// This function will be ran at the start and will fill the restaurant vector
vector<Restaurant> readFile()
{
    // Opening text file where restaurant data is stored
    vector<Restaurant> restaurants;
    ifstream file("/Users/crisis97/C++_Practice/MealMatch/MealMatch/restaurantBank.txt");
    string newLine;
    
    // Going through each line and extracting data
    while(getline(file, newLine))
    {
        stringstream bank(newLine);
        Restaurant newRestaurant;
        string name, cuisine, token;
        int avgPrice;
        
        getline(bank, name, ',');
        newRestaurant.setName(name);
        
        getline(bank, cuisine, ',');
        newRestaurant.setCuisine(cuisine);
        
        array<string, 7> weekDays = getWeekDays();
        
        for(const auto& day : weekDays)
        {
            double openTime, closeTime;
            
            getline(bank, token, ',');
            openTime = stod(token);
            
            getline(bank, token, ',');
            closeTime = stod(token);
            
            newRestaurant.setSchedule(day, openTime, closeTime);
        }
        
        getline(bank, token);
        avgPrice = stoi(token);
        newRestaurant.setAvgPrice(avgPrice);
        
        restaurants.push_back(newRestaurant);
    }
    
    return restaurants;
}

// Writes data from all restaurants in restaurants vector to a text file
void writeFile(vector<Restaurant> restaurants)
{
    // Getting weekdays and opening desired file
    array<string, 7> weekDays = getWeekDays();
    ofstream restaurantBank;
    restaurantBank.open("/Users/crisis97/C++_Practice/MealMatch/MealMatch/restaurantBank.txt");
    
    // Going through each restaurant and recording data
    for(const Restaurant& restaurant : restaurants)
    {
        restaurantBank << restaurant.getName() << "," << restaurant.getCuisine() << ",";
        map<string, pair<double, double>> schedule = restaurant.getSchedule();
        
        // Going through each day of the week and recording open and closing times
        for (const auto& day : weekDays)
        {
            // Find the schedule for each day
            auto it = schedule.find(day);
            if (it != schedule.end()) {
                // Print the schedule for that day
                restaurantBank << it->second.first << "," << it->second.second << ",";
            }
        }
        
        // Recording avgPrice and stopping file from writing a new line if we are at the last element in the vector
        restaurantBank << restaurant.getAvgPrice();
        
        if(restaurant.getName() != restaurants[restaurants.size() - 1].getName())
        {
            restaurantBank << endl;
        }
    }
    
}

// Iterates through restaurant vector and creates new vector filled with open restaurant based on current time and date
// Used primarily in the decider function
vector<Restaurant> getOpenRestaurants(vector<Restaurant> restaurants)
{
    // Getting the date and time from respective functions, initializing new vector
    string day = getDay();
    double time = getTime();
    vector<Restaurant> openRestaurants;
    
    // Going through restaurants linearly and comparing times
    for(const Restaurant &restaurant : restaurants)
    {
        if(restaurant.getSchedule()[day].first < time && restaurant.getSchedule()[day].second > time)
        {
            openRestaurants.push_back(restaurant);
        }
    }
    
    return openRestaurants;
}

// Utility function for the Decider function that checks for a maching cuisine
bool checkCuisine(vector<string> cuisineTypes, Restaurant restaurant)
{
    bool checker = false;
    for(const string &cuisine : cuisineTypes)
    {
        if(restaurant.getCuisine() == cuisine)
        {
            checker = true;
            break;
        }
    }
    
    return checker;
}

// Goes through the actual process of matching a restaurant based on criteria
void Decider(vector<Restaurant> restaurants)
{
    vector <Restaurant> openRestaurants = getOpenRestaurants(restaurants);
    vector <Restaurant> openerRestaurants;
    vector<string> cuisineTypes;
    string cuisine;
    int maxPrice;
    
    // Collecting cusine data
    int checker = 1;
    while(checker != 0)
    {
        cout << "Please enter one type of cuisine you are interested in in one word, please make sure it is capitalized:\n";
        cin >> cuisine;
        cuisineTypes.push_back(cuisine);
        cout << "Enter 1 to continue adding cuisine types or 0 to move on:\n";
        
        // Fail safe for if incorrect input is entered
        if(!(cin >> checker))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter either 1 or 0\n";
            checker = 1;
        }
    }
    
    // Getting the maximum user is willing to spend
    cout << "Please enter the most you are willing to spend on a meal today:\n";
    cin >> maxPrice;
    
    // Going through and creating a new vector holding only restaurants that match the criteria
    for(const Restaurant &restaurant : openRestaurants)
    {
        if(checkCuisine(cuisineTypes, restaurant) && maxPrice >= restaurant.getAvgPrice())
        {
            openerRestaurants.push_back(restaurant);
        }
    }
    
    if(openerRestaurants.empty())
    {
        cout << "No restaurants matched the criteria provided, please try again.\n";
        return;
    }
    
    cout << "Restaurants that meet your criteria are:" << endl;
    for(const Restaurant &restaurant : openerRestaurants)
    {
        cout << restaurant.getName() << endl;
    }
    
    checker = 0;
    cout << "Please enter 0 if you have made a decision and 1 if you would like me to pick for you at random\n";
    cin >> checker;
    
    // Providing an option to randomly select a restaurant
    if(checker == 1)
    {
        random_device randomDevice;
        mt19937 gen(randomDevice());
        uniform_int_distribution<> distributor(0, static_cast<int>(openerRestaurants.size() - 1));
        int randomIndex = distributor(gen);
        
        cout << "At random, I have decided you should go to " << openerRestaurants[randomIndex].getName() << ", hope you enjoy!\n";
    }
    
    cout << "Enjoy your meal!\n";
}

bool checkValidString(const string word)
{
    for(const char ch : word)
    {
        if(!isalpha(ch) && !isspace(ch))
        {
            return false;
        }
    }
    
    return true;
}


// Adds restaurants to the localy stored list of restaurants
void addRestaurants(vector<Restaurant> &restaurants)
{
    // Initializing variables
    Restaurant newRestaurant;
    string name, cuisine;
    int avgPrice;
    double openTime, closeTime;
    array<string, 7> weekDays = getWeekDays();
    
    // Getting and setting name, using get line in case a restaurant has more than one word
    cout << "What is the name of the new Restaurant?\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    newRestaurant.setName(name);
    
    // Getting and setting cuisine
    cout << "What kind of cuisine does this restaurant have?\n";
    getline(cin, cuisine);
    newRestaurant.setCuisine(cuisine);
    
    // Getting and setting avgPrice
    cout << "What is an estimate of the average price of a meal in this restaurant?\n";
    cin >> avgPrice;
    newRestaurant.setAvgPrice(avgPrice);
    
    // Going through each day of the week and getting opening and closing time
    for (const auto& day : weekDays)
    {
        cout << "On " << day << ", what time does " << name << " open?\n";
        cin >> openTime;
        cout << "On " << day << ", what time does " << name << " close?\n";
        cin >> closeTime;
        newRestaurant.setSchedule(day, openTime, closeTime);
    }
    
    restaurants.push_back(newRestaurant);
    cout << newRestaurant.getName() << " has been added\n";
}

// Removes restaurants from the localy stored list of restaurants
void removeRestaurants(vector<Restaurant> &restaurants)
{
    string name;
    cout << "Please enter the name of the restaurant you wish to remove\n";
    
    // Clearing input stream and getting full line for names that are more than one word
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    
    // Going through restaurants vector and trying to find desired restaurant
    int removeIndex = -1;
    
    for(int i = 0; i < restaurants.size(); ++i)
    {
        if(restaurants[i].getName() == name)
        {
            removeIndex = i;
            break;
        }
    }
    
    // If not found, don't do anything and report error, else remove restaurant
    if(removeIndex == -1)
    {
        cout << "Restaurant not found\n";
        return;
    }
    
    cout << "Removed " << name << endl;
    restaurants.erase(restaurants.begin() + removeIndex);
}

void introduction()
{
    cout << "Welcome to MealMatcher 1.0!\n";
    cout << "Using MealMatcher, simply add your favorite restaurants, input the kind of meal you're looking for, "
         << "And we'll match you with the right restaurant!" << endl;
}


int main()
{
    vector<Restaurant> restaurants = readFile();
    introduction();
    int input = -1;
    
    //Main user interface
    while(input != 5)
    {
        cout << "===========================================================\n";
        cout << "Please input a number for one of the following options:\n";
        cout << "Enter 1 to go through the process of matching your meal\n";
        cout << "Enter 2 to add a restaurant\n";
        cout << "Enter 3 to remove a restaurant\n";
        cout << "Enter 4 to print all restaurants\n";
        cout << "Enter 5 to exit MealMatcher\n";
        
        if(!(cin >> input))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number 1-5" << endl;
            input = -1;
            continue;
        }
        
        switch(input)
        {
            case 1:
            {
                Decider(restaurants);
                break;
            }
            case 2:
            {
                addRestaurants(restaurants);
                break;
            }
            case 3:
            {
                removeRestaurants(restaurants);
                break;
            }
            case 4:
            {
                printRestaurants(restaurants);
                break;
            }
            case 5:
            {
                cout << "Thank you for using MealMatcher, goodbye!" << endl;
                break;
            }
            default:
            {
                cout << "Invalid input, please enter a number 1-5" << endl;
                break;
            }
        }
    }
    
    // Writing to text file before exiting program
    writeFile(restaurants);
    return 0;
}
