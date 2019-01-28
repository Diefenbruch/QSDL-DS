#
# Makefile fuer die QUEST-Datenstruktur
#
#
# Author: Marc Diefenbruch
# $Date: 1998/02/19 17:03:08 $
#
# (C) 1995 Universitaet GH Essen
#
# Dieses Makefile stellt folgende Operationen zur Verfuegung:
#
# -) make [all]     : Library und Testprogramm erzeugen
# -) make lib       : Library erzeugen
# -) make test      : Testprogramm erzeugen (erzeugt auch Library falls noetig)
# -) make release   : Neue Release der DS fuer Benutzer zugaenglich machen
# -) make install   :  "      "     "   "   "     "         "         "
# -) make install-lib: Neue Version der DS-Bibiothek zugaenglich machen
# -) make install-includes: Neue Version der DS-Header_files zugaenglich machen
# -) make checkout  : alle Projektdateien auschecken
# -) make checkout-lock: alle Projektdateien zum Aendern auschecken
# -) make depend    : alle Abhaengigkeiten zwischen Projektdateien feststellen
# -) make clean     : Objektdateien (*.o) und temporaere Dateien entfernen
# -) make veryclean : make clean + rcsclean + alle Postscriptdateien entfernen
# -) make git-pull  : pull sources from github
# -) make git-push  : push sources to github
# -) make git-add   : add changed sources to git staging
# -) make git-commit: commit staged sources to git HEAD
# -) make postscript: Postscriptdateien aus alle *.h Dateien erzeugen
# -) make print     : alle *.h Dateien ausdrucken
# -) make backup    : Backup von allen *.cpp *.h Dateien und dem Makefile
# -) make find-error: Compilierungsfehler anzeigen
# -) make tags      : Source-Browser-Datei erzeugen
#
# Der Aufbau dieses Makefiles gliedert sich wie folgt:
#
#  0. Globale Umschalter (z.Z zwischen GNU- und SUN-Tools)
#  1. Makefiledirektiven
#  2. Pfade und Dateinamen
#  3. Programme, Kommandos, Kommandooptionen
#  4. Compilierungs- und Linkeroptionen
#  5. Quelldateien des Projekts
#  6. Objektdateien des Projekts
#  7. Makefileregeln (Operationen, s.o.)
#

##########################
# Check host system type #
##########################

## Don't rely on $HOSTTYPE being set correctly!
## Try to figure it out ourselves:

## Prevent make from interpreting special characters:
SCRIPT := \
	case `uname -s` in\
    	Linux)	case `uname -m` in\
					i?86) echo ix86-linux;;\
					arm*) echo arm-linux;;\
					sparc) echo sparc-linux;;\
					*) echo unknown-linux;;\
				esac;;\
		SunOS)	echo `uname -p`-SunOS;;\
		*) echo unknown-unknown;;\
	esac

## Run script and store result in variable:
QUEST_HOSTTYPE := $(shell $(SCRIPT))


##########################
# 0. Globale Umschalter: #
##########################

ifeq ($(QUEST_HOSTTYPE), sparc-SunOS)

#TOOLS = SUN
TOOLS = GNU

else

TOOLS = GNU

endif

#PROFILING = yes
PROFILING = no

##########################
# 1. Makefiledirektiven: #
##########################

.SILENT:
                         # alle Make Operationen ohne Ausgaben

.PHONY:	clean all release
                         # Welche Operationen sollen gespraechig sein?

.SUFFIXES: .cpp .h .o
                         # verwendete Dateiendungen 

############################
# 2. Pfade und Dateinamen: #
############################

INCDIR = ../../include
                         # Verzeichnis der DS-Includedateien fuer die
                         # Benutzer der DS (Generator, ...)

LIBDIR = ../../lib/$(QUEST_HOSTTYPE)
                         # Verzeichnis der DS-Library fuer die
                         # Benutzer der DS (Generator, ...)

BINDIR = ../../bin/$(QUEST_HOSTTYPE)
                         # Verzeichnis fuer binaries.

OBJBASEDIR = obj
                         # Verzeichnis unter dem die Objektdateien aller Hosts
                         # gespeichert werden sollen
OBJDIR = $(OBJBASEDIR)/$(QUEST_HOSTTYPE)

                         # Verzeichnis in dem die Objektdateien gespeichert
                         # werden sollen
PSDIR = ps
                         # Directory in dem die Postscriptversionen der
                         # Dateien gespeichert werden sollen
LOGFILE = $(USER).$(QUEST_HOSTTYPE).make.log
                         # Protokollierungsdatei fuer den make-Vorgang
DEPFILE = .depend.$(QUEST_HOSTTYPE)
                         # Dependency-Datei (automatisch generiert)
OUTPUT = $(OBJDIR)/libDS.a
                         # Name des erzeugten Programms/Library
TEST_OUTPUT = $(OBJDIR)/DSTest
                         # Name des Testprogramms
BACKUP = ds
                         # Name des Backupfiles (ohne Endungen!)


##############################################
# 3. Programme, Kommandos, Kommandooptionen: #
##############################################

SHELL = /bin/sh
                         # Shell
LEX = flex
                         # Kommando zum Starten des lexikalischen Analysators
LEXFLAGS = -i
                         # Flags fuer Lexer-Generator
YACC = bison
                         # Kommando zum Starten des Parser-Generators
YACCFLAGS = -d -v
                         # Flags fuer Parser-Generator
TAR = tar cf
                         # Befehl zum Erzeugen eines Sourcecode-Archievs
UNTAR = tar xf
                         # Befehl zum Expandieren eines Sourcecode-Archievs
TAR_SUFFIX = tar
                         # Endung welche das tar-Kommando verwendet
COMPRESS = gzip -9
                         # Befehl zum Komprimieren von Dateien
UNCOMPRESS = gzip -d
                         # Befehl zum Dekomprimieren von Dateien
COMPRESS_SUFFIX = gz
                         # Endung welche das Komprimierungsprogramm verwendet
EDITOR = nano
                         # Name des verwendeten Editors

GIT = git		 # git

TAGS = ctags -t
                         # Programm zum Erzeugen von Sourcebrowsing-Infos
                         # (wo ist eine bestimmte Funktion definiert?, etc)
MAKE_PS = a2ps
                         # Kommando zum Erzeugen von Postscript aus ASCII
MAKE_PS_FLAGS = -o
                         # Option fuer MAKE_PS
PS_SUFFIX = ps

PRINT = lp -c -d $(PRINTER)
                         # Druckkommando

ifeq ($(TOOLS), GNU)     # GNU-Version ?

CC = gcc
                         # Name des C-Compilers
C++ = g++
                         # Name des C++-Compilers

AR = ar
                         # Name des Archivers (zum Erzeugen von Libraries)
ARFLAGS = r
                         # Flags fuer den Archiver
else                     # SUN-Version

CC = cc
                         # Name des C-Compilers
C++ = CC
                         # Name des C++-Compilers
AR = $(C++)
                         # Name des Archivers (zum Erzeugen von Libraries)
ARFLAGS = -xar -o
                         # Flags fuer den Archiver
endif

RCSCLEAN = rcsclean
                         # Befehl zum "Aufraeumen" des Projekts (Loeschen
                         # der nicht mit Lock Option "ausgecheckten"
                         # Dateien
RM = /bin/rm -f
                         # Befehl zum Loeschen von Dateien
MV = /bin/mv
                         # Befehl zum Verschieben von Dateien
CP = /bin/cp -p
                         # Befehl zum Kopieren von Dateien
CHMOD = /bin/chmod
                         # Befehl zum Aendern der Dateiattribute
TOUCH = touch
                         # Befehl zum Aktualisieren des Dateidatums
MKDIR = mkdir
                         # Befehl zum Erzeugen von Directories
ifeq ($(TOOLS), GNU)

MAKE_DEPEND = $(C++) -M

else

MAKE_DEPEND = $(C++) -xM

endif
                         # Befehl zum Erzeugen der Abhaengigkeiten
STRIP = strip
                         # Befehl zum entfernen von Symbolen aus Binaerfiles
SED = sed
                         # Name des Stream-Editors sed
COFLAGS += -M -q
                         # Flags for checkout program

#########################################
# 4. Compilierungs- und Linkeroptionen: #
#########################################

ifeq ($(TOOLS), GNU)     # GNU-Version ?

DEFINES = 
# -DDMALLOC -DDEBUG -DDMALLOC_FUNC_CHECK
                         # Defines fuer die Compiler
INCLUDES = -I. -I$(INCDIR)
                         # Include-Verzeichnisse fuer die Compiler
CDEBUG = -O3 -pipe
                         # Debug-/Optimierungsoptionen
CFLAGS = $(CDEBUG) -Wall -pedantic-errors
                         # Compiler-Flags
TFLAGS = -fno-implicit-templates
                         # Template-Flags

ifeq ($(PROFILING), yes) # Profiling einschalten ?

PFLAGS = -pg

endif

LIBS = -L$(OBJDIR) -L$(LIBDIR) -lDS # -ldmalloc
                         # Libraries die zum Projekt gelinkt werden sollen

else                     # Sun-Version !

DEFINES = # -DDEBUG -DGNU_STRING
                         # Defines fuer die Compiler
INCLUDES = -I$(INCDIR)
                         # Include-Verzeichnisse fuer die Compiler
CDEBUG = -O
                         # Debug-/Optimierungsoptionen
CFLAGS = -sb  
CFLAGS += $(CDEBUG)
                         # Compiler-Flags
TFLAGS = 
                         # Template-Flags

ifeq ($(PROFILING), yes) # Profiling einschalten ?

PFLAGS = -xpg

endif

LIBS = -L$(LIBDIR) -lDS
                         # Libraries die zum Projekt gelinkt werden sollen

endif

#################################
# 5. Quelldateien des Projekts: #
#################################

LIST_HEADERS =\
	DSBaseList.h\
	DSBaseList.tmpl.h\
	DSBaseListElem.h\
	DSBaseListElem.tmpl.h\
	DSList.h\
	DSList.tmpl.h\
	DSListElem.h\
	DSListElem.tmpl.h\
	DSRefList.h\
	DSRefList.tmpl.h\
	DSRefListElem.h\
	DSRefListElem.tmpl.h\
	DSKeyList.h\
	DSKeyList.tmpl.h\
	DSKeyListElem.h\
	DSKeyListElem.tmpl.h\
	DSStack.h\
	DSStack.tmpl.h

SDL_HEADERS =\
	DSAction.h\
	DSActionList.h\
	DSActualParam.h\
	DSActualParamComponent.h\
	DSActualParamList.h\
	DSAssert.h\
	DSAtom.h\
	DSAtomComponent.h\
	DSAtomList.h\
	DSBasicTypes.h\
	DSBlock.h\
	DSBlockComponent.h\
	DSBlockList.h\
	DSBlockSubstructure.h\
	DSCall.h\
	DSChannel.h\
	DSChannelList.h\
	DSChannel2ChannelConnection.h\
	DSChannel2ChannelConnectionComponent.h\
	DSChannel2ChannelConnectionList.h\
	DSChannel2RouteConnection.h\
	DSChannel2RouteConnectionComponent.h\
	DSChannel2RouteConnectionList.h\
	DSChannelComponent.h\
	DSChannelRefComponent.h\
	DSCreate.h\
	DSDecision.h\
	DSExpression.h\
	DSExpressionList.h\
	DSFormalParam.h\
	DSFormalParamComponent.h\
	DSFormalParamList.h\
	DSGenerator.h\
	DSInput.h\
	DSInputList.h\
	DSInputSignal.h\
	DSInputSignalList.h\
	DSInputTimerSignal.h\
	DSInputTimerSignalList.h\
	DSJoin.h\
	DSNamedObject.h\
	DSNameSort.h\
	DSNameSortList.h\
	DSNextState.h\
	DSObject.h\
	DSObjectList.h\
	DSObjectStack.h\
	DSOperand.h\
	DSOperandConstant.h\
	DSOperandExpression.h\
	DSOperandLiteral.h\
	DSOperandMachineService.h\
	DSOperandOperator.h\
	DSOperandProcedureCall.h\
	DSOperandProcessAccess.h\
	DSOperandSensor.h\
	DSOperandSignal.h\
	DSOperandState.h\
	DSOperandSynonym.h\
	DSOperandVariableAccess.h\
	DSOperator.h\
	DSOperatorList.h\
	DSOutput.h\
	DSProcedure.h\
	DSProcedureComponent.h\
	DSProcedureList.h\
	DSProcess.h\
	DSProcessAccess.h\
	DSProcessComponent.h\
	DSProcessList.h\
	DSProcessRefComponent.h\
	DSRange.h\
	DSRangeList.h\
	DSRef.h\
	DSReset.h\
	DSReturn.h\
	DSSave.h\
	DSSaveList.h\
	DSSet.h\
	DSSignal.h\
	DSSignalComponent.h\
	DSSignalItemList.h\
	DSSignalslist.h\
	DSSignalslistComponent.h\
	DSSignalslistList.h\
	DSSignalList.h\
	DSSignalRefComponent.h\
	DSSignalRoute.h\
	DSSignalRouteComponent.h\
	DSSignalRouteList.h\
	DSSignalRouteRefComponent.h\
	DSSort.h\
	DSSortComponent.h\
	DSSortList.h\
	DSSortExtended.h\
	DSSortRefComponent.h\
	DSState.h\
	DSStateComponent.h\
	DSStateList.h\
	DSStop.h\
	DSStream.h\
	DSString.h\
	DSStringList.h\
	DSStruct.h\
	DSSynonym.h\
	DSSyntype.h\
	DSSystem.h\
	DSTask.h\
	DSTimer.h\
	DSTimerComponent.h\
	DSTimerList.h\
	DSTransition.h\
	DSTransitionList.h\
	DSVariable.h\
	DSVariableComponent.h\
	DSVariableList.h\
	DSVariableAccess.h\
	DSVariableAccessComponent.h\
	DSVariableAccessList.h\
	DSVariableAccessElem.h\
	DSVariableAccessElemList.h\
	DSVariableAccessField.h\
	DSVariableAccessIndex.h\
	DSWriter.h

QSDL_HEADERS =\
	DSClear.h\
	DSLink.h\
	DSLinkComponent.h\
	DSLinkList.h\
	DSLinkRefComponent.h\
	DSMachine.h\
	DSMachineComponent.h\
	DSMachineList.h\
	DSMachineService.h\
	DSMachineServiceList.h\
	DSMachineServiceComponent.h\
	DSMachineServiceRefComponent.h\
	DSMachineServiceSpeed.h\
	DSMachineServiceSpeedList.h\
	DSPipe.h\
	DSPipeList.h\
	DSPipe2LinkBinding.h\
	DSPipe2LinkBindingComponent.h\
	DSPipe2LinkBindingList.h\
	DSPipe2PipeBinding.h\
	DSPipe2PipeBindingComponent.h\
	DSPipe2PipeBindingList.h\
	DSPipeComponent.h\
	DSPipeRefComponent.h\
	DSRequest.h\
	DSSensor.h \
	DSSensorComponent.h \
	DSSensorList.h \
	DSSensorMachineService.h \
	DSSensorSignal.h \
	DSSensorProcess.h\
	DSSensorState.h\
	DSUpdate.h

DS_HEADERS = $(SDL_HEADERS) $(QSDL_HEADERS)

HEADERS = $(LIST_HEADERS) $(DS_HEADERS)

TEMPLATES_SRCS =\
	DSTemplates.cpp

SDL_SRCS =\
	DSAction.cpp\
	DSActualParamComponent.cpp\
	DSAssert.cpp\
	DSAtom.cpp\
	DSAtomComponent.cpp\
	DSBlock.cpp\
	DSBlockSubstructure.cpp\
	DSBlockComponent.cpp\
	DSCall.cpp\
	DSChannel.cpp\
	DSChannel2ChannelConnection.cpp\
	DSChannel2ChannelConnectionComponent.cpp\
	DSChannel2RouteConnection.cpp\
	DSChannel2RouteConnectionComponent.cpp\
	DSChannelComponent.cpp\
	DSChannelRefComponent.cpp\
	DSCreate.cpp\
	DSDecision.cpp\
	DSExpression.cpp\
	DSFormalParamComponent.cpp\
	DSGenerator.cpp\
	DSInput.cpp\
	DSInputSignal.cpp\
	DSInputTimerSignal.cpp\
	DSJoin.cpp\
	DSNamedObject.cpp\
	DSNameSort.cpp\
	DSNextState.cpp\
	DSObject.cpp\
	DSOperand.cpp\
	DSOperandConstant.cpp\
	DSOperandExpression.cpp\
	DSOperandLiteral.cpp\
	DSOperandMachineService.cpp\
	DSOperandOperator.cpp\
	DSOperandProcedureCall.cpp\
	DSOperandProcessAccess.cpp\
	DSOperandSensor.cpp\
	DSOperandSignal.cpp\
	DSOperandState.cpp\
	DSOperandSynonym.cpp\
	DSOperandVariableAccess.cpp\
	DSOperator.cpp\
	DSOutput.cpp\
	DSProcedure.cpp\
	DSProcedureComponent.cpp\
	DSProcess.cpp\
	DSProcessAccess.cpp\
	DSProcessComponent.cpp\
	DSProcessRefComponent.cpp\
	DSRange.cpp\
	DSReset.cpp\
	DSReturn.cpp\
	DSSave.cpp\
	DSSet.cpp\
	DSSignal.cpp\
	DSSignalComponent.cpp\
	DSSignalItemList.cpp\
	DSSignalslist.cpp\
	DSSignalslistComponent.cpp\
	DSSignalRefComponent.cpp\
	DSSignalRoute.cpp\
	DSSignalRouteComponent.cpp\
	DSSignalRouteRefComponent.cpp\
	DSSort.cpp\
	DSSortComponent.cpp\
	DSSortExtended.cpp\
	DSSortRefComponent.cpp\
	DSState.cpp\
	DSStateComponent.cpp\
	DSStop.cpp\
	DSString.cpp\
	DSStruct.cpp\
	DSSynonym.cpp\
	DSSyntype.cpp\
	DSSystem.cpp\
	DSTask.cpp\
	DSTimer.cpp\
	DSTimerComponent.cpp\
	DSTransition.cpp\
	DSVariable.cpp\
	DSVariableComponent.cpp\
	DSVariableAccess.cpp\
	DSVariableAccessComponent.cpp\
	DSVariableAccessElem.cpp\
	DSVariableAccessIndex.cpp\
	DSVariableAccessField.cpp

QSDL_SRCS =\
	DSClear.cpp\
	DSLink.cpp\
	DSLinkComponent.cpp\
	DSLinkRefComponent.cpp\
	DSMachine.cpp\
	DSMachineComponent.cpp\
	DSMachineService.cpp\
	DSMachineServiceComponent.cpp\
	DSMachineServiceRefComponent.cpp\
	DSMachineServiceSpeed.cpp\
	DSPipe.cpp\
	DSPipe2LinkBinding.cpp\
	DSPipe2LinkBindingComponent.cpp\
	DSPipe2PipeBinding.cpp\
	DSPipe2PipeBindingComponent.cpp\
	DSPipeComponent.cpp\
	DSPipeRefComponent.cpp\
	DSRequest.cpp\
	DSSensor.cpp \
	DSSensorComponent.cpp \
	DSSensorMachineService.cpp \
	DSSensorSignal.cpp \
	DSSensorProcess.cpp \
	DSSensorState.cpp\
	DSUpdate.cpp

DS_SRCS = $(SDL_SRCS) $(QSDL_SRCS)

SRCS = $(TEMPLATES_SRCS) $(DS_SRCS)

TEST_SRCS =\
	DSTest.cpp
#  dmalloc.cpp

##################################
# 6. Objektdateien des Projekts: #
##################################

TEMPLATES_OBJS = $(addprefix $(OBJDIR)/, $(TEMPLATES_SRCS:.cpp=.o))
SDL_OBJS = $(addprefix $(OBJDIR)/, $(SDL_SRCS:.cpp=.o))
QSDL_OBJS = $(addprefix $(OBJDIR)/, $(QSDL_SRCS:.cpp=.o))
TEST_OBJS = $(addprefix $(OBJDIR)/, $(TEST_SRCS:.cpp=.o))

OBJS = $(TEMPLATES_OBJS) $(SDL_OBJS) $(QSDL_OBJS)

######################
# 7. Makefileregeln: #
######################

default: clean-rubbish $(OBJDIR) $(OUTPUT)

$(OUTPUT): $(OBJS)
	@echo Constructing $(OUTPUT) ...
	$(AR) $(ARFLAGS) $(OUTPUT)\
		$(OBJS)\
		2>> $(LOGFILE)

all: $(OUTPUT) test

$(OBJDIR)/%.o: %.cpp 
	@echo Compiling $< ...
	$(C++) -c $(CFLAGS) $(TFLAGS) $(PFLAGS) $(DEFINES) $(INCLUDES) $< -o $@ 2>> $(LOGFILE)

test: clean-rubbish $(OUTPUT) $(TEST_OBJS)
	@echo Linking $(TEST_OUTPUT) ...
	$(C++) $(CDEBUG) -o $(TEST_OUTPUT)\
		$(TEST_OBJS)\
		$(OUTPUT)\
    2>> $(LOGFILE)

$(OBJBASEDIR):
	@if [ ! \( -d $(OBJBASEDIR) \) ]; then \
		echo Creating $(OBJBASEDIR) ...; \
		$(MKDIR) $(OBJBASEDIR); fi

$(OBJDIR): $(OBJBASEDIR)
	@if [ ! \( -d $(OBJDIR) \) ]; then \
		echo Creating $(OBJDIR) ...; \
		$(MKDIR) $(OBJDIR); fi

$(BINDIR): 
	@if [ ! \( -d $(BINDIR) \) ]; then \
		echo Creating $(BINDIR) ...; \
		$(MKDIR) $(BINDIR); fi

$(LIBDIR): 
	@if [ ! \( -d $(LIBDIR) \) ]; then \
		echo Creating $(LIBDIR) ...; \
		$(MKDIR) $(LIBDIR); fi

$(PSDIR): 
	@if [ ! \( -d $(PSDIR) \) ]; then \
		echo Creating $(PSDIR) ...; \
		$(MKDIR) $(PSDIR); fi

$(INCDIR): 
	@if [ ! \( -d $(INCDIR) \) ]; then \
		echo Creating $(INCDIR) ...; \
		$(MKDIR) $(INCDIR); fi

$(INCDIR)/DS: $(INCDIR)
	@if [ ! \( -d $(INCDIR)/DS \) ]; then \
		echo Creating $(INCDIR)/DS ...; \
		$(MKDIR) $(INCDIR)/DS; fi

$(DEPFILE):
	$(TOUCH) $(DEPFILE)

install-lib: $(OUTPUT) $(LIBDIR)
	@echo Deleting old library from $(LIBDIR) ...
	-$(RM) $(LIBDIR)/$(OUTPUT)
	@echo Installing new library in $(LIBDIR) ...
	$(CP)  $(OUTPUT) $(LIBDIR)

install-includes:  $(SDL_HEADERS) $(QSDL_HEADERS) $(LIST_HEADERS) $(INCDIR)/DS
	@echo Deleting old include files from $(INCDIR)/DS ...
	-$(RM) $(INCDIR)/DS/*.h
	@echo Installing new include files in $(INCDIR)/DS ...
	for X in $(SDL_HEADERS); do \
		$(CP)  $${X} $(INCDIR)/DS; done
	for X in $(QSDL_HEADERS); do \
		$(CP)  $${X} $(INCDIR)/DS; done
	for X in $(LIST_HEADERS); do \
		$(CP)  $${X} $(INCDIR)/DS; done

install: install-includes install-lib

release: install

git-pull:
	@echo Pulling sources form github...
	$(GIT) pull

git-add:
	@echo Staging changed local sources...
	$(GIT) add -A

git-commit:
	@echo Committing changed local sources...
	$(GIT) commit

git-push:
	@echo Pushing sources to github...
	$(GIT) push 

postscript: $(DS_HEADERS) $(PSDIR)
	@for X in $(DS_HEADERS); do \
		echo Generating $$X.$(PS_SUFFIX) from $$X ...; \
		$(MAKE_PS) $(MAKE_PS_FLAGS) $(PSDIR)/$$X.$(PS_SUFFIX) $$X; done

print: postscript
	@for X in $(DS_HEADERS); do \
		echo Printing $(PSDIR)/$$X.$(PS_SUFFIX) ...; \
		$(PRINT) $(PSDIR)/$$X.$(PS_SUFFIX) ; done

backup: $(DS_SRCS) $(DS_HEADERS) $(TEMPLATES_SRCS) $(LIST_HEADERS) $(TEST_SRCS)
	-$(RM) $(BACKUP).$(TAR_SUFFIX) $(BACKUP).$(TAR_SUFFIX).$(COMPRESS_SUFFIX)
	$(TAR) $(BACKUP).$(TAR_SUFFIX)\
		$(DS_SRCS) $(DS_HEADERS) $(TEMPLATES_SRCS) $(LIST_HEADERS) $(TEST_SRCS) Makefile*
	$(COMPRESS) $(BACKUP).$(TAR_SUFFIX)
	-$(MV) $(BACKUP).$(TAR_SUFFIX).$(COMPRESS_SUFFIX) $(BACKUP).taz

fe find-error:
	$(EDITOR) -p $(LOGFILE)

tags: $(SRCS)
	-$(TAGS) $(SRCS)

clean-rubbish:
	-$(RM) *~ core* *.bak $(LOGFILE)

clean-objects:
	-$(RM) $(OBJDIR)/*.o $(OUTPUT) $(TEST_OUTPUT) *.o

clean-rcs:
	-@$(RCSCLEAN) 2> /dev/null

clean: clean-rubbish clean-objects

veryclean: clean clean-rcs 
	-$(RM) $(PSDIR)/*.$(PS_SUFFIX) *.$(PS_SUFFIX) *.$(TAR_SUFFIX) *.$(COMPRESS_SUFFIX) *.taz *tags 2> /dev/null

checkout:
	-@$(CO) -q $(HEADERS)\
			$(SRCS)

checkout-lock:
	-@$(CO) -l $(HEADERS)\
			$(SRCS)

replace-headers: $(DS_HEADERS)
	for X in $(DS_HEADERS); do \
		$(MV) $$X $$X.old; \
		$(SED) 's/DSSignallist/DSSignalslist/g' $$X.old >> $$X ; done

replace-sources: $(DS_SRCS)
	for X in $(DS_SRCS); do \
		$(MV) $$X $$X.old; \
		$(SED) 's/DSSignallist/DSSignalslist/g' $$X.old >> $$X ; done

depend: $(HEADERS) $(SRCS)
	@echo Building dependency file $(DEPFILE) ...
	$(MAKE_DEPEND) $(DEFINES) $(SRCS) $(INCLUDES) > $(DEPFILE)
	$(SED) 's/^\(.*\)\.o/\$$(OBJDIR)\/\1\.o/g' $(DEPFILE) > $(DEPFILE).sed
	$(MV) $(DEPFILE).sed $(DEPFILE)


-include $(DEPFILE)

