INC = -I src/include 
run:
	g++ $(INC) -o target/main.exe src/cpp/Main.cpp
