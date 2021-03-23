# Set project directory one level above of Makefile directory. $(CURDIR) is a GNU make variable containing the path to the current working directory
PROJDIR ?= $(realpath $(CURDIR)/..)
BUILDDIR ?= $(PROJDIR)/build

# Name of the final executable
TARGET ?= main.exe

# Decide whether the commands will be shwon or not
VERBOSE ?= FALSE

# Create the list of directories
DIRS = src IraPohlCourseLibrary/misc IraPohlCourseLibrary/LinkedList IraPohlCourseLibrary/Graph IraPohlCourseLibrary/PriorityQueue IraPohlCourseLibrary/GraphShortestPathAlgo IraPohlCourseLibrary/MinimumSpanningTree
SOURCEDIRS ?= $(foreach dir, $(DIRS), $(addprefix $(PROJDIR)/, $(dir)))
TARGETDIRS ?= $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))

# Generate the GCC includes parameters by adding -I before each source folder
INCLUDES ?= $(foreach dir, $(SOURCEDIRS), $(addprefix -I, $(dir)))

# Add this list to VPATH, the place make will look for the source files
VPATH ?= $(SOURCEDIRS)

# Create a list of *.c sources in DIRS
SOURCES ?= $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.cpp))

# Define objects for all sources
OBJS ?= $(subst $(PROJDIR),$(BUILDDIR),$(SOURCES:.cpp=.o))

# Define dependencies files for all objects
DEPS ?= $(OBJS:.o=.d)

# Name the compiler
CXX ?= g++

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS ?= -Wall -g -Wextra -Werror $(INC_FLAGS) -MMD -MP

# OS specific part
ifeq ($(OS),Windows_NT)
	RM ?= del /F /Q 
	RMDIR ?= -RMDIR /S /Q
	MKDIR ?= -mkdir
	ERRIGNORE ?= 2>NUL || true
	SEP=\\
else
	RM ?= rm -rf 
	RMDIR ?= rm -rf 
	MKDIR ?= mkdir -p
	ERRIGNORE ?= 2>/dev/null
	SEP=/
endif

# Remove space after separator
PSEP ?= $(strip $(SEP))

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
	HIDE ?=  
else
	HIDE ?= @
endif

# Define the function that will generate each rule
define generateRules
$(1)/%.o: %.cpp
	@echo BUILDING... $$@
	$(HIDE)$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $$(INCLUDES) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<)
endef

.PHONY: all clean directories 

all: directories $(TARGET)

$(TARGET): $(OBJS)	
	@echo LINKING: $@
	$(HIDE)$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Include dependencies
-include $(DEPS)

# Generate rules
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

directories: 
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)

# Remove all objects, dependencies and executable files generated during the build
clean:
	$(HIDE)$(RMDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)
	$(HIDE)$(RM) $(TARGET) $(ERRIGNORE)
	@echo Cleaning done ! 