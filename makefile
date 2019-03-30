## -*- Makefile -*-
##
## User: matthew
## Time: 24-Mar-2019 09:11:30
## Makefile created by Oracle Developer Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = gcc
BASICOPTS = -g -Wall 
CFLAGS = $(BASICOPTS)
GTKLIB =`pkg-config --cflags --libs gtk+-3.0`
PTHREAD=-pthread

# Define the target directories.
TARGETDIR_gladewin=.


all: $(TARGETDIR_gladewin)/gladewin

## Target: gladewin
OBJS_gladewin =  \
	$(TARGETDIR_gladewin)/main.o
USERLIBS_gladewin =   
DEPLIBS_gladewin =  
LDLIBS_gladewin = $(PTHREAD) $(GTKLIB) -export-dynamic


# Link or archive
$(TARGETDIR_gladewin)/gladewin: $(TARGETDIR_gladewin) $(OBJS_gladewin) $(DEPLIBS_gladewin)
	$(LINK.c) $(CFLAGS_gladewin) -o $@ $(OBJS_gladewin) $(LDLIBS_gladewin)


# Compile source files into .o files
$(TARGETDIR_gladewin)/main.o: $(TARGETDIR_gladewin) main.c
	$(COMPILE.c) $(CFLAGS_gladewin) $(GTKLIB) -o $@ main.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_gladewin)/gladewin \
		$(TARGETDIR_gladewin)/main.o
	rm -f -r $(TARGETDIR_gladewin)


# Create the target directory (if needed)
$(TARGETDIR_gladewin):
	mkdir -p $(TARGETDIR_gladewin)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-x86_64-MacOSX

