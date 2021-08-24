all:
	cat network.txt | python mapper.py | sort -k 1 -n | python reducer.py > result.txt