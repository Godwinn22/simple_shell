#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer sizes for I/O operations */
#define BUFFER_SIZE_READ 1024
#define BUFFER_SIZE_WRITE 1024
#define BUFFER_CLEAR -1

/* Command chaining types */
#define COMMAND_EXECUTE 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

/* Number conversion flags */
#define CONVERT_TO_LOWERCASE 1
#define CONVERT_TO_UNSIGNED 2

/* Configuration flags */
#define ENABLE_GETLINE 0
#define ENABLE_STRTOK 0

/* History file settings */
#define HISTORY_FILE_NAME	".simple_shell_history"
#define HISTORY_MAX_SIZE	4096

extern char **environment;

/* Linked list structure for strings and numbers */

/**
 * struct StringNumberListstr - singly linked list
 * @number: the number of field
 * @string: a normal string
 * @next: points to the next node
 */

typedef struct StringNumberListstr
{
	int number;
	char *string;
	struct StringNumberListstr *next;
} StringNumberList;

/* Structure for passing information throughout the shell */

/**
 * struct PassShellInfo - a Struct for passing of arguments to a function
 * description: this struct is for passing arguments to functions
 * @input_line: the command line arguments from getline
 * @arguments: an array of arguments generated from input_line
 * @command_path: the path of the current command
 * @argument_count: the Count of arguments
 * @line_number: for Counting of errors
 * @exit_code: the error code for exit() calls
 * @count_line_flag: Flag to count this line of input
 * @program_name: the Program's filename
 * @environment_list: the Local copy of environ
 * @history_list: the History node
 * @alias_list: the Alias node
 * @modified_environment: the modified copy of environ
 * from linked list environment_list
 * @environment_changed_flag: the Flag to check if environ was changed
 * @last_command_status: the Return status of the last executed command
 * @command_buffer: the address of pointer to command_buffer, on if chaining
 * @command_buffer_type: the Type of command (||, &&, ;)
 * @input_file_descriptor: the file descriptor to read line input from
 * @history_line_count: the count of history lines
 */

typedef struct PassShellInfo
{
	char *input_line;
	char **arguments;
	char *command_path;
	int argument_count;
	unsigned int line_number;
	int exit_code;
	int count_line_flag;
	char *program_name;
	StringNumberList *environment_list;
	StringNumberList *history_list;
	StringNumberList *alias_list;
	char **modified_environment;
	int environment_changed_flag;
	int last_command_status;

	char **command_buffer;
	int command_buffer_type;
	int input_file_descriptor;
	int history_line_count;
} ShellInfo;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* Structure for built-in commands */

/**
 *struct BuiltInCommand - a struct that
 *contains a builtin string and related function
 *@command_name: the builtin command name
 *@execute: the execute function
 */

typedef struct BuiltInCommand
{
	char *command_name;
	int (*execute)(ShellInfo *);
} BuiltInCommandTable;

/* Function prototypes for various shell operations */

/* shell.c */
int run_shell(ShellInfo *shellinfo, char **args);
int execute_builtin_command(ShellInfo *shellinfo);
void execute_path(ShellInfo *shellinfo);
void executeCommand(ShellInfo *shellinfo);

/* getinfos.c */
void initializeShellInfo(ShellInfo *shellInfo);
void setShellInfo(ShellInfo *shellInfo, char **argVector);
void freeShellInfo(ShellInfo *shellInfo, int freeall);

/* parse.c */
int isExecutable(ShellInfo *shellInfo, char *filePath);
char *duplicateCharacters(char *inputStr, int startIndex, int endIndex);
char *findCommandInPath(ShellInfo *shellInfo, char *pathStr, char *command);

/* errors files */
void e_puts(char *strToPrint);
int e_putchar(char charToPrint);
int put_fd(char charToWrite, int fileDescriptor);
int puts_fd(char *strToWrite, int fileDescriptor);
int err_atoi(char *strToConvert);
void printError(ShellInfo *shellInfo, char *errorStr);
int printDecimal(int numToPrint, int fileDescriptor);
char *convertNum(long int number, int base, int flags);
void stripComments(char *buffer);

/* strings files */
int strn_len(char *inputString);
int str_cmp(char *string1, char *string2);
char *startsWith(const char *fullString, const char *substring);
char *strn_cat(char *destStr, char *srcStr);
char *strn_cpy(char *destStr, char *srcStr);
char *strn_dup(const char *stringToDuplicate);
void _puts(char *stringToPrint);
int _putchar(char characterToPrint);
char *_strn_cpy(char *destStr, char *srcStr, int numberOfCharacters);
char *_strn_cat(char *destStr, char *srcStr, int numberOfCharacters);
char *_str_chr(char *stringToSearch, char characterToFind);

/* asciitoint.c */
int isInteractive(ShellInfo *shellInfo);
int isDelimiter(char character, char *delimiters);
int is_alpha(int character);
int _atoi(char *stringToConvert);

/* lexers.c */
char **_strtow(char *inputString, char *delimiters);
char **_strn_tow(char *inputString, char delimiter);

/* reallocation.c */
char *mem_set(char *memoryArea, char byteToFill, unsigned int numberOfBytes);
void freeStrs(char **strOfStrs);
void *_realloc(void *prevMemBlock,
unsigned int prevSize, unsigned int newSize);
int freeptr(void **ptrAddress);

/* builtins files */
int exitShell(ShellInfo *shellInfo);
int _cd(ShellInfo *shellInfo);
int _help(ShellInfo *shellInfo);
/* part 2*/
int _History(ShellInfo *shellInfo);
int unsetAlias(ShellInfo *shellInfo, char *aliasName);
int setAlias(ShellInfo *shellInfo, char *aliasName);
int printAlias(StringNumberList *aliasNode);
int handleAlias(ShellInfo *shellInfo);

/* getLine.c */
ssize_t bufferChainedCommands(ShellInfo *shellInfo,
			      char **cmdBuf, size_t *bufLength);
ssize_t getInputLine(ShellInfo *shellInfo);
ssize_t readBuffer(ShellInfo *shellInfo, char *buffer, size_t *size);
int getNextLine(ShellInfo *shellInfo, char **bufferPtr, size_t *bufLength);
void blockCtrlC(int signalNumber);

/* lists functions */
StringNumberList *prepend_node(StringNumberList **list_head,
			       const char *string, int number);
StringNumberList *append_node(StringNumberList **list_head,
			      const char *string, int number);
size_t display_list_data(const StringNumberList *node);
int remove_node_at_index(StringNumberList **list_head, unsigned int position);
void free_list(StringNumberList **list_head_ptr);
size_t list_length(const StringNumberList *node);
char **convert_list_to_strings(StringNumberList *first_node);
size_t display_list(const StringNumberList *node);
StringNumberList *find_node_with_prefix(StringNumberList *node,
					char *prefix, char c);
ssize_t find_node_position(StringNumberList *first_node,
			   StringNumberList *target_node);


/* vars.c */
int substitute_strings(char **old_string, char *new_string);
int is_cmd_chain(ShellInfo *shellInfo, char *buffer, size_t *position);
void eval_chain(ShellInfo *shellInfo, char *buffer, size_t *position,
		size_t start, size_t length);
int substitute_alias(ShellInfo *shellInfo);
int substitute_vars(ShellInfo *shellInfo);


/* environments.c */
char *get_environ(ShellInfo *shellInfo, const char *varName);
int _env(ShellInfo *shellInfo);
int init_environ(ShellInfo *shellInfo);
int uninit_environ(ShellInfo *shellInfo);
int populateEnvList(ShellInfo *shellInfo);

/* getenvronments.c */
char **get_env(ShellInfo *shellInfo);
int uninit_env(ShellInfo *shellInfo, char *varName);
int init_env(ShellInfo *shellInfo, char *varName, char *varVal);

/* History.c */
char *getHistoryFile(ShellInfo *shellInfo);
int writeHistory(ShellInfo *shellInfo);
int readHistory(ShellInfo *shellInfo);
int buildHistoryList(ShellInfo *shellInfo, char *buffer, int count);
int renumberHistory(ShellInfo *shellInfo);



#endif
