CLIENT_TARGET			:= client
SERVER_TARGET			:= server
NAME				:= $(CLIENT_TARGET) $(SERVER_TARGET) 

CLIENT_DIR:= mini_client
SERVER_DIR:= mini_server

DEPEND_DIR			= ./Dependencies
INT_DIR				= ./obj

ifndef config
	config := release
endif

ifeq ($(config),debug)
	client_config = debug
	server_config = debug
else ifeq ($(config),release)
	client_config = release
	server_config = release
else ifeq ($(config),distr)
	client_config = distr
	server_config = distr
else
	$(error "invalid config $(config)")
endif

.PHONY: all clean fclean re $(CLIENT_TARGET) $(SERVER_TARGET)

all: $(NAME)

$(CLIENT_TARGET):
	@echo $(MAKE_DIR)
	@echo "=== Building client ($(client_config)) ==="
	@${MAKE} -C $(CLIENT_DIR) -f Makefile config=$(client_config) --debug

$(SERVER_TARGET):
	@echo "=== Building server ($(server_config)) ==="
	@${MAKE} -C $(SERVER_DIR) -f Makefile config=$(server_config) --debug

clean:
	@${MAKE} -C $(CLIENT_DIR) clean
	@${MAKE} -C $(SERVER_DIR) clean

fclean:
	@${MAKE} -C $(CLIENT_DIR) fclean
	@${MAKE} -C $(SERVER_DIR) fclean

re: fclean all
