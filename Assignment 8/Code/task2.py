""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : task1.py
    Date : Mar 25, 2021
    Problem Statement : Creating grammer and parsing the files and saving the result in logfile.txt
"""

#importing required modules
import ply.lex as lex
import ply.yacc as yacc
import sys
import unicodedata
import task1
import re

# creating dictionary class
class my_dictionary(dict):

    def __init__(self):
        self = dict()

    # function to add key value pair
    def add(self, key, value):
        self[key] = value
    
    
# creating a dictionary
result = my_dictionary()

field_list = ['Movie_Name', 'Director', 'Writer', 'Producer', 'Original Language', 'Cast with the Character name', 'Storyline', 'Box office collection', 'Runtime']
#list to store all cast and crew names
cast_char_name = []
dir_name = []

# initialzing all key value of dictonary as ''(empty string)
for i in field_list:
    result.add(i, '')

#print(result)


# token list used
tokens = [
    'MOVIE_S', 'MOVIE_E',
    'DIRECTOR', 'DIR_CLOSE',
    'WHITE_SPACE',
    'NAME',
    'WRITER', 'CLOSE',
    'ESTART',
    'PRODUCER',
    'LANG',
    'STORY',
    'BOXOFFICE',
    'RUNTIME', 'REND',
    'RNAME', 'CEND', 'MID'
]

# Regular expression for each tokens
def t_MOVIE_S(t):
    r'<meta\sproperty=\"og:title\"\scontent=\"'
    return t

def t_MOVIE_E(t):
    r'\">'
    return t

def t_DIRECTOR(t):
    r'\"movie-info-director\">'
    return t

def t_ESTART(t):
    r'\s*<a\shref=\"[\/a-zA-Z_0-9-:]+\">'
    return t

def t_DIR_CLOSE(t):
    r'<\/a>\s*,*'
    return t

def t_WRITER(t):
    r'Writer:<\/div>\s*.*\">\s*'
    return t

def t_PRODUCER(t):
    r'Producer:<\/div>\s*.*\">\s*'
    return t

def t_LANG(t):
    r'Original\sLanguage:<\/div>\s*.*\">'
    return t

def t_STORY(t):
    r'data-qa=\"movie-info-synopsis\">\s*'
    return t

def t_BOXOFFICE(t):
    r'Box\sOffice\s\(Gross\sUSA\):<\/div>\s*.*\">'
    return t

def t_RUNTIME(t):
    r'<time\sdatetime=\"P.*M\">\s*'
    return t

def t_REND(t):
    r'\s*<\/time>'
    return t

def t_RNAME(t):
    r'span\stitle=\"[\u00C0-\u00CF\u00D0-\u00DF\u00E0-\u00EF\u00F0-\u00FFa-zA-z0-9\s\-_&#;\'.]+\">\s*'
    return t

def t_MID(t):
    r'\s*<\/span>\s*.*\s*<span\sclass=\"characters\ssubtle\ssmaller\"\stitle=\"[\u00C0-\u00CF\u00D0-\u00DF\u00E0-\u00EF\u00F0-\u00FFa-zA-Z0-9&#;\s\-_&\'.]+\">\s*<br\/>\s*'
    return t

def t_CEND(t):
    r'\s*<(br\/|\/span)>'
    return t

def t_CLOSE(t):
    r'\s*<\/div>'
    return t

def t_NAME(t):
    #r'[a-zA-Z]+'
    r'[\u00C0-\u00CF\u00D0-\u00DF\u00E0-\u00EF\u00F0-\u00FFa-zA-z0-9,.\(\)$\-&!?:_\';#]+'
    return t


t_WHITE_SPACE = r'[\ \t]+'

def t_error(t):
    #print("Illegal Characters")
    t.lexer.skip(1)

# Parser Rules
def p_start(var):
    '''
    start : movie_name
          | dir_name
          | writer_name
          | producer_name
          | language
          | cast
          | cast_only_name
          | storyline
          | boxoffice
          | runtime
    '''

# Extracting movie name
def p_movie_name(var):
    'movie_name : MOVIE_S name MOVIE_E'
    result.add('Movie_Name', var[2])

# Extracting director names
def p_dir_name(var):
    'dir_name : DIRECTOR name DIR_CLOSE'
    res = var[2]
    dir_name.insert(len(dir_name), res)

# Extracting Writer names
def p_writer_name(var):
    'writer_name : WRITER expression CLOSE'
    result.add('Writer', var[2])

# Extracting producer names
def p_producer_name(var):
    'producer_name : PRODUCER expression CLOSE'
    result.add('Producer', var[2])

# Extracting language
def p_language(var):
    'language : LANG name CLOSE'
    result.add('Original Language', var[2])

# Extracting Cast and Crew names
def p_cast(var):
    'cast : RNAME name MID name CEND'
    res = var[2] + ' as ' + var[4]
    cast_char_name.insert(len(cast_char_name), res)

def p_cast_only_name(var):
    'cast_only_name : RNAME name MID CEND'
    res = var[2] 
    cast_char_name.insert(len(cast_char_name), res)

# Extracting storyline
def p_storyline(var):
    'storyline : STORY name CLOSE'
    result.add('Storyline', var[2])

# Extracting boxoffice 
def p_boxoffice(var):
    'boxoffice : BOXOFFICE name CLOSE'
    result.add('Box office collection', var[2])

# Extracting runtime
def p_runtime(var):
    'runtime : RUNTIME name REND'
    result.add('Runtime', var[2])

# Recurssive way of extraction
def p_expression_multi(var):
    'expression : expression expression'
    var[0] = var[1] + ',' + var[2]

def p_expression_single(var):
    'expression : expression'
    var[0] = var[1]

def p_expression(var):
    'expression : ESTART name DIR_CLOSE'
    var[0] = var[2]

# Extracting names using recurssive method
def p_name_one(var):
    'name : NAME'
    var[0] = var[1]

def p_name_mid(var):
    'name : NAME name'
    var[0] = var[1] + ' ' + var[2]

def p_name_multi(var):
    'name : NAME wspaces name'
    var[0] = var[1] + var[2] + var[3]


def p_wspaces(var):
    '''
    wspaces : WHITE_SPACE
            | WHITE_SPACE wspaces
    '''
    var[0] = ' '

def p_error(var):
    pass


# building lexer and parser
lexer = lex.lex()
parser = yacc.yacc()

# opening the html file of movie from task1
f = open(task1.filename)
txt = f.read()

lex.input(txt)

#for tok in iter(lex.token, None):
#    print(repr(tok.type), repr(tok.value))

parser.parse(txt)

result.add('Director', dir_name )
result.add('Cast with the Character name', cast_char_name)

print('\t\tExtract Following Fields:')
print('1. Movie Name')
print('2. Director')
print('3. Writers')
print('4. Producer')
print('5. Original Language')
print('6. Cast with the character name')
print('7. Storyline')
print('8. Box Office Collection')
print('9. Runtime')

# opening file in append mode to write all the query fields 
file_name = open('logfile.txt', 'a')


while(True):
    val = input('\nEnter Any one of the fields(Enter digit) or press \'E\' to exit:   ')

    if val == '1' or val == '3' or val == '4' or val == '5' or val == '8' or val == '9':
        user_ip = int(val)
        idx = field_list[user_ip-1]
        print('\n', idx, ':')
        if(bool(result[idx])):
            val_list = result[idx].split(',')
            for i in val_list:
                print(i)
                file_name.write('<%s> <%s> <%s> <%s>\n' %(task1.indx, task1.movie_name, idx, i))
        else:
            print('Data Unavailable for this field')
            file_name.write('<%s> <%s> <%s> <%s>\n' %(task1.indx, task1.movie_name, idx, 'Data Unavailable'))

    elif val == '7':
        user_ip = int(val)
        idx = field_list[user_ip-1]
        print('\n', idx, ':')
        if(bool(result[idx])):
            print(result[idx])
            file_name.write('<%s> <%s> <%s> <%s>\n' %(task1.indx, task1.movie_name, idx, result[idx]))
        else:
            print('Data Unavailable for this field')
            file_name.write('<%s> <%s> <%s> <%s>\n' %(task1.indx, task1.movie_name, idx, 'Data Unavailable'))

    elif val == '2' or val == '6':
        user_ip = int(val)
        idx = field_list[user_ip-1]
        print('\n', idx, ':')
        if(bool(result[idx])):
            for i in result[idx]:
                print(i)
                file_name.write('<%s> <%s> <%s> <%s>\n' %(task1.indx, task1.movie_name, idx, i))
        else:
            print('Data Unavailable for this field')
            file_name.write('<%s> <%s> <%s> <%s>\n' %(task1.indx, task1.movie_name, idx, 'Data Unavailable'))

    elif val == 'E':
        print("Closing......")
        break

    else:
        print('Incorrect format... choose a valid number')

# closing all the files
file_name.close
f.close