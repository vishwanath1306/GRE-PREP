from prettytable import PrettyTable
import random
import csv

word_table = PrettyTable(['Word', 'Meaning']) 
fil = open('wordlist.csv')
csv_f = csv.reader(fil)
p = random.randint(1,1163)

my_csv_word = list(csv_f)

word = my_csv_word[p][0]
meaning = my_csv_word[p][1]

word_table.add_row([word,meaning])

#print p

print word_table



