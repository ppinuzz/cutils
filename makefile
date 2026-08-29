# these targets represent actions, not actual files; marking them phony ensures
# that 'make' always executes their recipes even if files with the same names exist
.PHONY: docs

docs:
	doxygen Doxyfile

cleandocs:
	# if a file doesn't exist, -f silences the error
	rm -fr docs/html docs/latex
