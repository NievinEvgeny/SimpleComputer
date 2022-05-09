APP_NAME = main
LIB_NAME = lib
SAT_NAME = sat

CFLAGS = -Wall
CPPFLAGS = -I src -MP -MMD

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
SAT_DIR = sat

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a
SAT_PATH = $(BIN_DIR)/$(SAT_NAME)

SRC_EXT = c

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

SAT_SOURCES = $(shell find $(SRC_DIR)/$(SAT_NAME) -name '*.$(SRC_EXT)')
SAT_OBJECTS = $(SAT_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d) $(SAT_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/%.o: $(SRC_DIR)/$(APP_NAME)/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/%.o: $(SRC_DIR)/$(LIB_NAME)/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(APP_PATH) $(LIB_PATH) $(SAT_PATH) bin/sat.o
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;

.PHONY: sat
sat: $(SAT_PATH)

-include $(DEPS)

$(SAT_PATH): $(SAT_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(OBJ_DIR)/$(SRC_DIR)/$(SAT_NAME)/%.o: $(SRC_DIR)/$(SAT_NAME)/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@