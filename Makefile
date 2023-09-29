build:
	mkdir -p out
	g++ main.cpp LedCube.cpp -o out/program -llua

run:
	chmod 777 ./out/program
	printf "\n\n\n" && ./out/program