# build and run all test
all: script-run json-run

clean c: script-clean json-clean

## SCRIPT module ------------------------------------------ 

src_dir = mate
script_base_dir = mate/script
script_test_dir = test/script

script-build script-b: script-build-base script-build-test

script-build-base script-bb :
	flex -o $(script_base_dir)/ScriptScanner.cpp $(script_base_dir)/ScriptScanner.ll
	bison -o $(script_base_dir)/ScriptParser.cpp $(script_base_dir)/ScriptParser.yy -d

script-build-test script-bt  : script-build-base
	mkdir -p $(script_test_dir)/output/
	g++ -g 	$(script_test_dir)/script_test.cpp \
			$(script_base_dir)/ScriptParser.cpp \
			$(script_base_dir)/ScriptScanner.cpp \
			$(script_base_dir)/ScriptInterpreter.cpp \
			$(src_dir)/Command.cpp \
			$(src_dir)/Context.cpp \
			-o $(script_test_dir)/output/script_test.out

	
script-run script-r script-rt: script-build-test
	./$(script_test_dir)/output/script_test.out

script-clean script-c: script-clean-test script-clean-base

script-clean-base script-cb:
	rm -f $(script_base_dir)/ScriptScanner.cpp
	rm -f $(script_base_dir)/location.hh $(script_base_dir)/position.hh $(script_base_dir)/stack.hh
	rm -f $(script_base_dir)/ScriptParser.cpp $(script_base_dir)/ScriptParser.hpp 

script-clean-test script-ct:
	rm -rf $(script_test_dir)/output/


## END SCRIPT module -------------------------------------- 
##
## JSON module -------------------------------------------- 

#json_base_dir = mate/json
json_test_dir = test/json

json-build json-b:
	mkdir -p $(json_test_dir)/output/
	g++ $(json_test_dir)/json_test.cpp \
		$(src_dir)/NumExpression.cpp \
		$(src_dir)/Command.cpp \
		-o $(json_test_dir)/output/json_test.out

json-run json-r: json-b
	./$(json_test_dir)/output/json_test.out

json-clean json-c: json-test-c

json-test-clean json-test-c:
	rm -rf $(json_test_dir)/output/

## END JSON module ----------------------------------------- script-base-build