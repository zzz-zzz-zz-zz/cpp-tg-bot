CPP=g++
CPPFLAGS=
LIBS= -lcurl
CXXFLAGS= -std=c++17

DEPS= $(wildcard tg-bot/*.hpp) $(wildcard tg-bot/objects/*.hpp)
SRCS= main.cpp $(wildcard tg-bot/*.cpp) $(wildcard tg-bot/objects/*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))


%.o: %.cpp $(DEPS)
	$(CPP) $(CXXFLAGS) -c -o $@ $< $(CPPFLAGS) $(LIBS)

bot: $(OBJS)
	$(CPP) $(CXXFLAGS) -o $@ $^ $(CPPFLAGS) $(LIBS)

run: bot
	./bot


.PHONY: default
default: run