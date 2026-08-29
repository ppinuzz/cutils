SRC_FILE := example.c ../src/cutils.c
EXE_FILE := example.exe
CC := gcc

# these targets represent actions, not actual files; marking them phony ensures
# that 'make' always executes their recipes even if files with the same names exist
.PHONY: strict warnerrors clean

# options from
# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

# ------------------------------------------------------------------------------
# 								GCC OPTIONS
# ------------------------------------------------------------------------------
# -std=c17		use C17

# WARNINGS:
# -Wall						enable warnings for anything unexpected, but syntactically correct
# -Wextra					enable additional warnings
# -Wconversion				warn when narrowing conversion or data loss is likely to occurr
# -Wshadow					warn if a local variable/type declaration shadows another variable or parameter	
# -Wpedantic				enable warning for stricter ISO C (extra strict)
# -Wformat					check calls to printf(), scanf(), etc., to make sure that 
#								- supplied arguments types match the format string
#								- conversions specified in the format string make sense
# -Winit-self				warn about uninitialized variables that are initialized with themselves (e.g. int x = x;)
# -Wmissing-include-dirs	warn if a user-supplied include directory does not exist
# -Wswitch-default			warn whenever a switch statement does not have a default case
# -Wunused					warns about unused values/variables/etc
# -Wduplicated-branches		warn when an if-else has identical branches
# -Wduplicated-cond			warn about duplicated conditions in an if-else-if chain
#							(e.g. 1st if has the same condition as the else-if)
# -Wfloat-equal				warn if floating-point values are used in equality comparisons
# -Wlogical-op				warn about suspicious uses of logical operators in expressions
# -Wstrict-prototypes		warn if a function is declared or defined without specifying the argument types
WARN_FLAGS := -Wall -Wextra -Wconversion -Wshadow -Wpedantic -Wformat -Winit-self -Wmissing-include-dirs -Wswitch-default -Wunused -Wduplicated-branches -Wduplicated-cond -Wfloat-equal -Wlogical-op -Wstrict-prototypes

# ERRORS:
# -Werror			turn all warnings into errors
# -Wfatal-errors 	abort compilation at 1st error, without printing other errors
# -pedantic-errors	turns pedantic warnings (-Wpedantic) into errors
ERROR_FLAGS := -Werror -Wfatal-errors -pedantic-errors

# -o myExe		create executable with given name (default: a.out)
# -shared		create a shared library, not a standalone executable
# -O2			optimise the compiled code AND perform error checks to avoid optimisation errors
# -O			same as O2, but without error checks
# -g			produce compiled file with info for debugging
# -DNDEBUG		define NDEBUG, which disables assert() checks from <assert.h>

# -lm			link the libm library (for mathematical functions)
LIBS := 
# if you don't need the libraries, leave the variable empty
#LIBS := 


# this rule is VERY STRICT and likely to complaing about things which you know
# are safe, but maybe not best practice => will still compile
strict: $(SRC_FILE)
	$(CC) -std=c17 $(WARN_FLAGS) -O2 -o $(EXE_FILE) $(SRC_FILE) $(LIBS)

# won't compile if there are any warnings
warnerrors: $(SRC_FILE)
	$(CC) -std=c17 $(WARN_FLAGS) $(ERROR_FLAGS) -O2 -o $(EXE_FILE) $(SRC_FILE) $(LIBS)

clean:
	# if executable doesn't exist, -f silences the error
	rm -f $(EXE_FILE)
