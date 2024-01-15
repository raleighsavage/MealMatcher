# MealMatcher - Intelligent Restaurant Discoverer

## Basic Description, TLDR:

**Meal Matcher** works by, firstly, taking in information about restaurants. This information includes:
- The restaurant's name
- The type of cuisine that restaurant serves
- The average price of a meal
- When they're open and closed

It then stores that information in a text file and draws upon that information to help you decide where to eat based on what kind(s) of cuisine sound good to you and how much you're willing to spend. I've provided some of my personal favorites in my area, but try adding your own!

*Note that you will need to change the file path for MealMatcher to work on your machine*

### Inspiration

When meeting with friends, going out with family, or when planning a date, no question haunts me quite like the question: "Where do you want to eat?". When I hear that my brain just completely shuts down and I somehow just lose all memory of the restaurants I enjoy. However a strategy I learned to help with the decision process is asking certain questions like  "what style of food sounds good to you" and "how much are you willing to spend today" in order to narrow down the options. The only problem with that is I can't remember the hundreds of restaurants in my university town off hand. That's when I got the idea to make a program that could add and store as many restaurants as I wanted along with all their information. This accompanied by a function that could go through the decision process by only selecting restaurants that meet certain criteria (open, cuisine type, price) and having the option to select from that narrowed list at random. I've used this program a few times and allowed a few others to try it and have experienced only positive results so far.

### Reasoning Behind Code Specificities

The main components come in the form of the use and manipulation of **four variables**:
- A string variable that contains the *name* of a restaurant
- A string variable that contains the type of *cuisine* the restaurant serves
- An integer variable that contains the *average price* of a meal at the restaurant
- A map object where the key is the day of the week represented by a string and the value is a pair of two doubles that contains the *opening* and *closing* time of the restaurant

I felt a map object would be more appropriate than an array or array of arrays due to the fact that the format for the hours of a restaurant naturally follows a key-value formula where the day is the key and the hours are the value. It's also much more space and time efficient than an array of arrays or most other alternatives.

Due to the fact that I was taught Java originally, I still tend to follow Java norms which is the reason for camel case and the general organization of the program. I just think it looks the best and is the easiest for me to understand personally, however I'm always open to suggestions!

## Future Goals and Improvements for MealMatcher

The very first thing that I can think of when it comes to what I could do to improve MealMatcher is 100% introducting some form of **Web Scraping**. By far the most tedious part of this program is having to input every detail of the restaurant manually, and being able to pull a signficicant amount of restaurant data at once automatically would be a drastic improvement. I know python typically fares better with web scraping and I originally created this project in there before realizing a language that could handle more intricate class structures was needed, so I may try to implement it on that version.

I think that the *restaurants* vector that gets thrown between functions numerous times could be changed into some form of hash map which would make the program significantly faster especially when the program holds a higher number of restaurants.

I really hate (in the worst case) having to iterate over an entire array and I think that if I could find a way to reduce the number of iterations especially in the decision function, the program would be both more efficient and easier to read.

Lastly,w hile this is a great concept application and a very good start, I feel like this would make a really good and practicle web application, so I hope to one day translate this program into something that could be used on the web.
