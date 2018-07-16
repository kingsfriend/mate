# build and run all test
all: script-run json-run

clean c: script-clean json-clean

## SCRIPT module ------------------------------------------ 

src_dir = mate
src_ast_dir = mate/ast
src_ast_expression_dir = mate/ast/expression
src_ast_block_dir = mate/ast/block
src_script_dir = mate/script
test_script_dir = test/script

script-build script-b: script-build-base script-build-test

script-build-base script-bb :
	flex -o $(src_script_dir)/ScriptScanner.cpp $(src_script_dir)/ScriptScanner.ll
	bison -o $(src_script_dir)/ScriptParser.cpp $(src_script_dir)/ScriptParser.yy -d

script-build-test script-bt  : script-build-base
	mkdir -p $(test_script_dir)/output/
	g++ -g 	$(test_script_dir)/script_test.cpp \
			$(src_script_dir)/ScriptParser.cpp \
			$(src_script_dir)/ScriptScanner.cpp \
			$(src_script_dir)/ScriptInterpreter.cpp \
			$(src_ast_dir)/Command.cpp \
			$(src_ast_dir)/Json.cpp \
			$(src_ast_dir)/Context.cpp \
			-o $(test_script_dir)/output/script_test.out

	
script-run script-r script-rt: script-build-test
	./$(test_script_dir)/output/script_test.out

script-clean script-c: script-clean-test script-clean-base

script-clean-base script-cb:
	rm -f $(src_script_dir)/ScriptScanner.cpp
	rm -f $(src_script_dir)/location.hh $(src_script_dir)/position.hh $(src_script_dir)/stack.hh
	rm -f $(src_script_dir)/ScriptParser.cpp $(src_script_dir)/ScriptParser.hpp 

script-clean-test script-ct:
	rm -rf $(test_script_dir)/output/


## END SCRIPT module -------------------------------------- 
##
## JSON module -------------------------------------------- 

#json_base_dir = mate/json
test_json_dir = test/json

json-build json-b:
	mkdir -p $(test_json_dir)/output/
	g++ $(test_json_dir)/json_test.cpp \
		$(src_ast_dir)/Command.cpp \
		$(src_ast_block_dir)/ConditionalBlock.cpp \
		$(src_ast_dir)/Context.cpp \
		$(src_ast_dir)/Json.cpp \
		$(src_ast_dir)/ContextStack.cpp \
		$(src_ast_block_dir)/BreakableBlock.cpp \
		$(src_ast_block_dir)/ContinueableBlock.cpp \
		$(src_ast_expression_dir)/CmpExpression.cpp \
		$(src_ast_expression_dir)/BoolExpression.cpp \
		$(src_ast_expression_dir)/DateExpression.cpp \
		$(src_ast_expression_dir)/ExpressionCommand.cpp \
		$(src_ast_expression_dir)/NumExpression.cpp \
		$(src_ast_expression_dir)/StringExpression.cpp \
		-o $(test_json_dir)/output/json_test.out

json-run json-r: json-b
	./$(test_json_dir)/output/json_test.out

json-clean json-c: json-test-c

json-test-clean json-test-c:
	rm -rf $(test_json_dir)/output/

## END JSON module ----------------------------------------- script-base-build