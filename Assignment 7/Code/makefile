.PHONY: all Query1 Query2 Query3

all: Query1 Query2 Query3

Query1:
	{ cat ../chatLogs/day1.txt | python3 mapper1.py | sort -k 1 -k 2 -n | python3 combiner1.py \
	&& cat ../chatLogs/day2.txt | python3 mapper1.py | sort -k 1 -k 2 -n | python3 combiner1.py \
	&& cat ../chatLogs/day3.txt | python3 mapper1.py | sort -k 1 -k 2 -n | python3 combiner1.py \
	&& cat ../chatLogs/day4.txt | python3 mapper1.py | sort -k 1 -k 2 -n | python3 combiner1.py \
	&& cat ../chatLogs/day5.txt | python3 mapper1.py | sort -k 1 -k 2 -n | python3 combiner1.py \
	&& cat ../chatLogs/day6.txt | python3 mapper1.py | sort -k 1 -k 2 -n | python3 combiner1.py \
	&& cat ../chatLogs/day7.txt | python3 mapper1.py | sort -k 1 -k 2 -n | python3 combiner1.py \
	&& cat ../chatLogs/day8.txt | python3 mapper1.py | sort -k 1 -k 2 -n | python3 combiner1.py \
	&& cat ../chatLogs/day9.txt | python3 mapper1.py | sort -k 1 -k 2 -n | python3 combiner1.py \
	&& cat ../chatLogs/day10.txt | python3 mapper1.py | sort -k 1 -k 2 -n | python3 combiner1.py \
	; } | sort -k 1 -k 2 -n | python3 reducer1.py > network.txt

	@echo "	"
	@echo "network.txt file created"
	@echo "	"

Query2:
	cat network.txt | python3 mapper2.py | sort -k 1 -k 2 -k 3 -n | python3 reducer2.py > friends.txt

	@echo "	"
	@echo "friends.txt file created"
	@echo "	"

Query3:
	python3 mapper3.py | sort -k 1 -k 2 -k 3 -n | python3 reducer3.py > triangles.txt

	@echo "	"
	@echo "triangles.txt file created"
	@echo " "