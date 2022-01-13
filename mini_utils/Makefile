TARGET			:= mini_utils.a 

PARENT_DIR 		:= ..
DEPEND_DIR 		:= $(PARENT_DIR)/Dependencies
INT_DIR 		:= ./obj

LIBFT_DIR		:= $(DEPEND_DIR)/libft
LIBFT_LIB		:= $(LIBFT_DIR)/libft.a

SRC_DIR			:= ./src

SRC_FILES		:= mini_assert.c
OBJ_FILES		:= $(addprefix $(INT_DIR)/,$(SRC_FILES:%.c=%.o))

VPATH			:= $(SRC_DIR)

DEFINES			:=
INCLUDE_DIRS		:= -I ./include -I $(LIBFT_DIR)/include
LIBRARIES		:= $(LIBFT_LIB)

CC			:= clang
LINK_CMD		:= clang

ALL_CFLAGS		:= -std=c89 -Wall -Wextra -Werror -pedantic $(INCLUDE_DIRS)
ALL_LINKFLAGS		:=

DEBUG_CFLAGS		:= -g -O0 -fsanitize=address -fsanitize=undefined
DEBUG_LINKFLAGS		:= -fsanitize=address -fsanitize=undefined
DEBUG_DEFINES		:= -DMINI_UTILS_DEBUG

RELEASE_CFLAGS		:= -g -O2 -fsanitize=address -fsanitize=undefined
RELEASE_LINKFLAGS	:= -fsanitize=address -fsanitize=undefined
RELEASE_DEFINES		:= -DMINI_UTILS_RELEASE

DISTR_CFLAGS		:= -Ofast -g0
DISTR_LINKFLAGS		:=
DISTR_DEFINES		:= -DMINI_UTILS_DISTRIBUTION

SILENT		:= @
ifdef verbose
	SILENT	:=
endif

ifndef config
	config := debug
endif

ifeq ($(config), debug)
	ALL_CFLAGS += $(DEBUG_CFLAGS)
	ALL_LINKFLAGS += $(DEBUG_LINKFLAGS)
	DEFINES += $(DEBUG_DEFINES)
else ifeq ($(config), release)
	ALL_CFLAGS += $(RELEASE_CFLAGS)
	ALL_LINKFLAGS += $(RELEASE_LINKFLAGS)
	DEFINES += $(RELEASE_DEFINES)
else ifeq ($(config), distribution)
	ALL_CFLAGS += $(DISTR_CFLAGS)
	ALL_CFLAGS += $(DISTR_DEFINES)
	ALL_LINKFLAGS += $(DISTR_LINKFLAGS)
endif

all: $(TARGET)

$(TARGET): $(OBJ_FILES) 
	$(SILENT)echo Archiving $@
	$(SILENT)ar rcs $@ $(OBJ_FILES)

$(INT_DIR)/%.o: %.c
	$(SILENT)echo $(notdir $<)
	$(SILENT)mkdir -p $(INT_DIR)
	$(SILENT)$(CC) $(ALL_CFLAGS) -c $< -o $@

clean:
	$(SILENT)echo Cleaning object files
	$(SILENT)rm -f $(OBJ_FILES)

fclean: clean
	$(SILENT)echo Cleaning $(TARGET)
	$(SILENT)rm -f $(TARGET)

re: fclean all
