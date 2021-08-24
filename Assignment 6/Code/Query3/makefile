all:
	cat network.txt | python3 mapper.py | sort -k 1 -n | python3 reducer.py > result.txt
