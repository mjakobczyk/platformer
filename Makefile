application=program
generator=

build:
	mkdir -p build; cd build; cmake ../.; make; cd ../.;

build-params:
	mkdir -p build; cd build; cmake -G $(generator) ../.; make; cd ../.;

run:
	cd build; ./$(application);

clean:
	rm -rf build/;

application:
	echo Current application name is: $(application)