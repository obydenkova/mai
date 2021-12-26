import random

f = open('data/list_of_words.txt', 'rt')
f_out = open('data/random_words.txt', 'wt')
list_w = []

for line in f:
	list_w.append(list(map(str, line.split('\n')))[0])

for i in range(20000):
	f_out.write(random.choice(list_w) + ' ')
