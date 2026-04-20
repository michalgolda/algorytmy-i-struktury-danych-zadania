clean:
	rm -rf ./build

build: clean
	mkdir ./build
	g++ main.cpp -o ./build/main


test: build
	./build/main ./data.txt

debug: clean
	mkdir ./build
	g++ -g main.cpp -o ./build/main
	gdb ./build/main
