OUTPUTNAME = tiktaktoe
BUILD = build
BIN = bin

SRCFILES := $(shell find src/ -name *.cpp)
OBJFILES := $(patsubst %.cpp,%.o,$(SRCFILES))
OBJFILES := $(foreach dir,$(OBJFILES),$(subst src/,,$(dir)))
DIR := $(dir $(OBJFILES))

TARGETLIST = $(foreach f,$(OBJFILES),$(BUILD)/$(f))

$(foreach d,$(DIR),$(shell mkdir -p $(BUILD)/$(d)))
$(shell mkdir -p $(BIN))

CC = g++ 
CFLAGS  = -g -std=c++11
LIBS=-lsfml-graphics -lsfml-window -lsfml-system


$(info Source: $(SRCFILES))
$(info Targets: $(TARGETLIST))

default: $(BIN)/$(OUTPUTNAME)


$(BIN)/$(OUTPUTNAME): $(TARGETLIST)
	$(CC) $(CFLAGS) $(TARGETLIST) $(LIBS) $(CUSTOMLIB) -o $(BIN)/$(OUTPUTNAME)


$(BUILD)/%.o: $(SRCFILES)
	$(CC) -c $(CFLAGS) $(INCLUDE) $(filter %$(notdir $(patsubst %.o,%.cpp,$@)),$(SRCFILES)) -o $@