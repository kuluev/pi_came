all: send grab

grab:
	gcc -Wall -o grab grab.c -lwiringPi
send:
	gcc -Wall -o send send.c -lwiringPi
clean:
	rm -rf grab send
