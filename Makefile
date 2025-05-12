CFLAGS = -g -Wall -O0 -I/usr/local/include -I/opt/homebrew/include -L/opt/homebrew/lib -lgmp -lssl -lcrypto -std=c++20

all: main.cpp wes.cpp rsa.cpp lib.cpp vdf.cpp 
	g++ $(CFLAGS) main.cpp wes.cpp rsa.cpp lib.cpp vdf.cpp -o proj



