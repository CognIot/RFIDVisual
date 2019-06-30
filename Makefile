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


all: $(TARGETDIR)/rfidVisual $(TARGETDIR)/rfidReader


# ----------------------------------------------------------------------------------------------------------------
#       Common Objects
# ----------------------------------------------------------------------------------------------------------------
OBJS_common = \
	$(TARGETDIR)/rfid.o \
	$(TARGETDIR)/rfidPrivate.o
	
## Target: rfidVisual
OBJS_rfidVisual =  \
	$(OBJS_common) \
	$(TARGETDIR)/rfidVisual.o
USERLIBS_rfidVisual =   
DEPLIBS_rfidVisual =  
LDLIBS_rfidVisual = $(PTHREAD) $(GTKLIB) -export-dynamic -lwiringPi

## Target: rfidReader
OBJS_rfidReader =  \
	$(OBJS_common) \
	$(TARGETDIR)/rfidReader.o
USERLIBS_rfidReader =   
DEPLIBS_rfidReader =  
LDLIBS_rfidReader = $(PTHREAD) -lwiringPi

# Link or archive
$(TARGETDIR)/rfidVisual: $(TARGETDIR) $(OBJS_rfidVisual) $(DEPLIBS_rfidVisual)
	$(LINK.c) $(CFLAGS_rfidVisual) -o $@ $(OBJS_rfidVisual) $(LDLIBS_rfidVisual)

$(TARGETDIR)/rfidReader: $(TARGETDIR) $(OBJS_rfidReader) $(DEPLIBS_rfidReader)
	$(LINK.c) $(CFLAGS) -o $@ $(OBJS_rfidReader) $(LDLIBS_rfidReader)


# Compile source files into .o files
$(TARGETDIR)/rfidVisual.o: $(TARGETDIR) rfidVisual.c
	$(COMPILE.c) $(CFLAGS_rfidVisual) $(GTKLIB) -o $@ rfidVisual.c

$(TARGETDIR)/rfidReader.o: $(TARGETDIR) rfidReader.c
	$(COMPILE.c) $(CFLAGS) $(GTKLIB) -o $@ rfidReader.c
	
$(TARGETDIR)/rfid.o: $(TARGETDIR) lib_rfid/src/rfid.c
	$(COMPILE.c) $(CFLAGS) $(GTKLIB) -o $@ lib_rfid/src/rfid.c

$(TARGETDIR)/rfidPrivate.o: $(TARGETDIR) lib_rfid/src/rfidPrivate.c
	$(COMPILE.c) $(CFLAGS) $(GTKLIB) -o $@ lib_rfid/src/rfidPrivate.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR)/rfidReader \
		$(TARGETDIR)/rfidReader.o \
		$(TARGETDIR)/rfidVisual \
		$(TARGETDIR)/rfidVisual.o \
		$(TARGETDIR)/rfid.o \
		$(TARGETDIR)/rfidPrivate.o
	rm -f -r $(TARGETDIR)


# Create the target directory (if needed)
$(TARGETDIR):
	mkdir -p $(TARGETDIR)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-x86_64-MacOSX

