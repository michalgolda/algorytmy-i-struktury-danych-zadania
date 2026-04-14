clean:
	rm -rf ./build

build: clean
	mkdir ./build
	g++ main.cpp -o ./build/main


test: build
	./build/main
