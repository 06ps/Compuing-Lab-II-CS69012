===================================================================================================
Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
Roll No : 20CS60R12
===================================================================================================


Coding Language Used : Python (python3)
Code Run : On Ubuntu 20.04.2 LTS
Status : Code was running fine in my computer system


====================================================================================================

To run files use command : make

Code Flow:

1. Run "make" command. It will crawl all 10 genre link and save the genre page.
2. user is then asked to enter any of the genre from the genre list by entering corresponding genre number.
3. After this, the program will display the top 100 movie list from the genre that user has choosen. And will ask further to enter any movie(number).
4. upon entering movie number, the program will save that movie html file. Program will then display the list of fields that can be extracted and will ask from user to select any field.
5. for fields: movie name, Director, Writers, producer, original Language, storyline, box office collection, runtime and where to watch, program will simply display the result of corresponding query field
6. for 'cast with the character name' field, it will ask user to enter any cast member number and then will download that cast member's html page.
    6.1 It will then again display the list of fields. The user can get corresponding field information by providing the field number as input
    6.2 for 'His/her other movies, program will ask user to enter year and then will display the list of movie on or after that year
    6.3 On pressing 'B' the user can go back to the previous menu
7. for 'you might also like' field, program will display a list of movies and ask user to enter movie number to further explore information about that movie
8. can press 'E' anytime in program to exit the program
