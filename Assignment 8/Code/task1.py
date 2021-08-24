""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : task1.py
    Date : Mar 19, 2021
    Problem Statement : Crawling Rotten Tomatoes website, Given a user input of any of the 10 genres, 
                        list all the movies of that genre and ask user for movie name, then download that movie's HTML file
"""

# importing required modules
import sys
import urllib.request
import re
import itertools
import unicodedata

# Function to convert latin letters to English alphabet 
def latin_to_aplha(text):
    return ''.join(char for char in unicodedata.normalize('NFKD', text)
    if unicodedata.category(char) != 'Mn')

genre_list = ['Action &Adventure', 'Animation', 'Drama', 'Comedy', 'Mystery & Suspense', 'Horror', 'Sci-Fi', 'Documentary', 'Romance', 'Classics']
movie_list = []         # to save all top 100 movies 

genre_html = {}         # to save all genre's html files
index = 0

url_list = ['action__adventure_movies', 'animation_movies', 'drama_movies', 'comedy_movies', 'mystery__suspense_movies', 'horror_movies', 'science_fiction__fantasy_movies', 'documentary_movies', 'romance_movies', 'classics_movies']

# saving all genres html files in dictionary
print('\nCrawling Started....')
for genre in url_list:
    url = 'https://www.rottentomatoes.com/top/bestofrt/top_100_'
    url = url + genre
    url = url + '/'

    response = urllib.request.urlopen(url)
    content = response.read().decode()

    genre_html[genre_list[index]] = content
    index = index + 1
print('Crawing Completed.... susscesfully downloaded genres HTML files\n')

print('\t\tGenres List:')
print('1. Action &Adventure')
print('2. Animation')
print('3. Drama')
print('4. Comedy')
print('5. Mystery & Suspense')
print('6. Horror')
print('7. Sci-Fi')
print('8. Documentary')
print('9. Romance')
print('10. Classics')
val = input('\nEnter Any one of the genre number(Enter digit):   ')

x = 1
html = None
text = None
indx = None

# taking genre from user 
while(x):
    try:
        user_input = int(val)
        if user_input >= 1 and user_input <= 10:
            indx = genre_list[user_input-1]
            text = genre_html[indx]
            x = 0
        else:
            val = input('\nEnter number between 1-10 only:  ')
    except ValueError:
        val = input('\nEntered in wrong format!!!  Enter numeric value only:  ')
    
# converting html file in english 
html = latin_to_aplha(text)

# Regular expression to find movie 
regex = "<a href=\"\/m\/[a-zA-Z0-9_-]+\"\sclass=\"unstyled\sarticleLink\">\\n\s*([a-zA-z0-9\s().,\'-:?!&]+)<\/a>"

# finding all movies name in html file using Regular expression
movies_list = re.findall(regex, html)       

# printing the names to top 100 movies for user provided genre
print('\n')
print('\t\tList of 100 top movies\n')
i = 1
for movie in movies_list:
    movie_list.append(movie)
    print('{}. {}'.format(i,movie))
    i = i+1


movie_num = input('\nEnter corresponding Movie Number(1-100):   ')

y= 1
movie_name = None

# Taking movie name as input from  the user
while(y):
    try:
        num = int(movie_num)
        if num >= 1 and num <= 100:
            movie_name = movie_list[num-1]
            y = 0
        else:
            movie_num = input('\nEnter number between 1-10 only:  ')
    except ValueError:
        movie_num = input('\nEntered in wrong format!!!  Enter numeric value only:  ')

#print(movie_name)

movie_substr = ''
for i in range(0, len(movie_name)):
    if(movie_name[i] == '('):
        break
    else:
        movie_substr = movie_substr + movie_name[i]

#print(movie_substr)

# Regular expression to extract movie link
movie_regex = f"<a href=\"(\/m\/[a-zA-Z0-9_-]+)\" class=\"unstyled articleLink\">\\n\s*{movie_substr}.*?<\/a>"


# downloading user prvided movie name of a particular genre HTML file
output = re.findall(movie_regex, html)

url = 'https://www.rottentomatoes.com'
url = url + output[0]
#url = url + '/'

print('\n')
print(movie_name, ' Crawling Started.....')
response = urllib.request.urlopen(url)
content = response.read()

filename = movie_name + '.html'
f = open(filename , 'wb')
f.write(content)
f.close
print(movie_name, 'Crawling Completed.... Successfully downloaded HTML file \n')

# closing the file after saving it in html format

