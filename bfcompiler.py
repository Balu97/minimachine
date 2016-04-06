if = open("program.bf", "r")

of = open("in.txt", "w")

of.write("LOADI 40000\n")
of.write("STORE 65535\n")

plus = 0
minus = 0

leftparen = 0
rightparen = 0

while char = if.read(1):
	if char == '>':
		plus += 1		
		of.write("LOAD 65535\n")
		of.write("ADDI 1\n")
		of.write("STORE 65535\n")

	elif char == '<':
		of.write("LOAD 65535\n")
		of.write("SUBI 1\n")
		of.write("STORE 65535\n")

	elif char == '+':
		plus += 1
		of.write("LOAD 65535\n")
		of.write("STORE plusload" + str(plus) + "\n")
		of.write("STORE plusstore" + str(plus) + "\n")
		of.write("LOAD plusload" + str(plus) + ": 0\n")
		of.write("ADDI 1")
		of.write("STORE plusstore" + str(plus) + ": 0\n")


	elif char == '-':
		plus += 1
		of.write("LOAD 65535\n")
		of.write("STORE minusload" + str(minus) + "\n")
		of.write("STORE minusstore" + str(minus) + "\n")
		of.write("LOAD minusload" + str(minus) + ": 0\n")
		of.write("ADDI 1")
		of.write("STORE minusstore" + str(minus) + ": 0\n")

	elif char == '[':
		leftparens += 1
		of.write("leftparen" + str(leftparen) + ": LOAD 65535\n")
		of.write("STORE leftparenload" + str(leftparen) + "\n")
		of.write("LOAD leftparenload" + str(leftparen) + ": 0\n")
		of.write("JMPZ rightparen" + str(leftparen) + ": 0\n")

	elif char == ']':
		rightparen += 1
		of.write("JMP leftparen" + str(rightparen) + "\n")
		of.write("rightparen" + str(rightparen) + ": ")
