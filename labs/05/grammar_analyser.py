import sys

file = open(sys.argv[1], "r")
isFirstLine = True

start = ""
productions = {}
for line in file:
	text = line.split("->")
	production = text[0].strip()
	products = list(map( str.strip ,text[1].split("|")))
	if isFirstLine:
		start = production
		isFirstLine = False
	productions[production] = products

queue=[start]
visited = set()
while len(queue) != 0:
	actual = queue.pop()
	for product in productions[actual]:
		for char in product:
			if char in productions and char not in visited:
				queue = [char] + queue
	visited.add(actual)

for production in productions:
	if production not in visited:
		print(production + " cannot be reached from " + start)

finalProductions = set()
for _ in range(len(productions)):
	for production in productions:
		for product in productions[production]:
			isFinal = True
			for char in product:
				if char in productions and char not in finalProductions:
					isFinal = False
			if isFinal:
				finalProductions.add(production)
				break
for production in productions:
	if production not in finalProductions:
		print(production + " cannot reach a final state")