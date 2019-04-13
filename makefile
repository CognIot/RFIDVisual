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
TARGETDIR=build


all: $(TARGETDIR)/rfidVisual


# ----------------------------------------------------------------------------------------------------------------
#       Common Objects
# ----------------------------------------------------------------------------------------------------------------
OBJS_common = \
	$(TARGETDIR_ALL)/rfid.o
	
## Target: rfidVisual
OBJS_rfidVisual =  \
	$(TARGETDIR_gladewin)/rfidVisual.o
USERLIBS_rfidVisual =   
DEPLIBS_rfidVisual =  
LDLIBS_rfidVisual = $(PTHREAD) $(GTKLIB) -export-dynamic


# Link or archive
$(TARGETDIR)/rfidVisual: $(TARGETDIR) $(OBJS_rfidVisual) $(DEPLIBS_rfidVisual)
	$(LINK.c) $(CFLAGS_rfidVisual) -o $@ $(OBJS_rfidVisual) $(LDLIBS_rfidVisual)


# Compile source files into .o files
$(TARGETDIR)/rfidVisual.o: $(TARGETDIR) rfidVisual.c
	$(COMPILE.c) $(CFLAGS_rfidVisual) $(GTKLIB) -o $@ rfidVisual.c

$(TARGETDIR)/rfid.o: $(TARGETDIR) rfid.c
	$(COMPILE.c) $(CFLAGS_rfidVisual) $(GTKLIB) -o $@ rfid.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR)/rfidVisual \
		$(TARGETDIR)/rfidVisual.o \
		$(TARGETDIR)/rfid.o
	rm -f -r $(TARGETDIR)


# Create the target directory (if needed)
$(TARGETDIR):
	mkdir -p $(TARGETDIR)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-x86_64-MacOSX

