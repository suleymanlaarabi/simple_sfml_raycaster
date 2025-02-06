

LIB = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE = $(shell find include -type d)
SRC := $(shell find src -name '*.cpp') main.cpp
BUILD_DIR = build
OBJS := $(SRC:%.cpp=$(BUILD_DIR)/%.o)
OBJDEBUG := $(SRC:%.cpp=$(BUILD_DIR)-debug/%.o)
NAME = raycast
DEBUG_NAME = debug
CFLAGS += $(INCLUDE:%=-I%)

all: $(NAME)

run: all
	./$(NAME)
	rm -f $(NAME)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@g++ $(LIB) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)-debug/%.o: %.cpp
	@mkdir -p $(dir $@)
	@g++ -g3 -fsanitize=address $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@g++ $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

$(DEBUG_NAME): $(OBJDEBUG)
	@g++ -g3 -fsanitize=address $(CFLAGS) $(OBJDEBUG) $(LIB) -o $(DEBUG_NAME)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BUILD_DIR)-debug

fclean: clean
	rm -f $(NAME)

re: fclean run
