﻿// Driver template for the LEMON parser generator. The author disclaims copyright to this source code.
// First off, code is included that follows the "include" declaration in the input grammar file.
#include <stdio.h>
%%
// Next is all token values, in a form suitable for use by makeheaders. This section will be null unless lemon is run with the -m switch.
// These constants (all generated automatically by the parser generator) specify the various kinds of tokens (terminals) that the parser understands. 
// Each symbol here is a terminal symbol in the grammar.
%%
// Make sure the INTERFACE macro is defined.
#ifndef INTERFACE
#define INTERFACE 1
#endif
// The next thing included is series of defines which control various aspects of the generated parser.
//    YYCODETYPE         is the data type used for storing terminal and nonterminal numbers.  "unsigned char" is
//                       used if there are fewer than 250 terminals and nonterminals.  "int" is used otherwise.
//    YYNOCODE           is a number of type YYCODETYPE which corresponds to no legal terminal or nonterminal number.  This
//                       number is used to fill in empty slots of the hash table.
//    YYFALLBACK         If defined, this indicates that one or more tokens have fall-back values which should be used if the
//                       original value of the token will not parse.
//    YYACTIONTYPE       is the data type used for storing terminal and nonterminal numbers.  "unsigned char" is
//                       used if there are fewer than 250 rules and states combined.  "int" is used otherwise.
//    ParseTOKENTYPE     is the data type used for minor tokens given directly to the parser from the tokenizer.
//    YYMINORTYPE        is the data type used for all minor tokens. This is typically a union of many types, one of
//                       which is ParseTOKENTYPE.  The entry in the union for base tokens is called "yy0".
//    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If zero the stack is dynamically sized using realloc()
//    ParseARG_SDECL     A static variable declaration for the %extra_argument
//    ParseARG_PDECL     A parameter declaration for the %extra_argument
//    ParseARG_STORE     Code to store %extra_argument into yyparser
//    ParseARG_FETCH     Code to extract %extra_argument from yyparser
//    YYNSTATE           the combined number of states.
//    YYNRULE            the number of rules in the grammar
//    YYERRORSYMBOL      is the code number of the error symbol.  If not defined, then do no error processing.
%%
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

// The yyzerominor constant is used to initialize instances of YYMINORTYPE objects to zero.
__device__ static const YYMINORTYPE yyzerominor = { 0 };

// Define the yytestcase() macro to be a no-op if is not already defined otherwise.
//
// Applications can choose to define yytestcase() in the %include section to a macro that can assist in verifying code coverage.  For production
// code the yytestcase() macro should be turned off.  But it is useful for testing.
#ifndef yyASSERTCOVERAGE
#define yyASSERTCOVERAGE(X)
#endif

// Next are the tables used to determine what action to take based on the current state and lookahead token.  These tables are used to implement
// functions that take a state number and lookahead value and return an action integer.  
//
// Suppose the action integer is N.  Then the action is determined as follows
//
//   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead token onto the stack and goto state N.
//   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
//   N == YYNSTATE+YYNRULE              A syntax error has occurred.
//   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
//   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused slots in the yy_action[] table.
//
// The action table is constructed as a single large table named yy_action[]. Given state S and lookahead X, the action is computed as
//
//      yy_action[ yy_shift_ofst[S] + X ]
//
// If the index value yy_shift_ofst[S]+X is out of range or if the value yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
// is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table and that yy_default[S] should be used instead.  
//
// The formula above is for computing the action when the lookahead is a terminal symbol.  If the lookahead is a non-terminal (as occurs after
// a reduce action) then the yy_reduce_ofst[] array is used in place of the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of YY_SHIFT_USE_DFLT.
//
// The following are the tables generated in this section:
//
//  yy_action[]        A single table containing all actions.
//  yy_lookahead[]     A table containing the lookahead for each entry in yy_action.  Used to detect hash collisions.
//  yy_shift_ofst[]    For each state, the offset into yy_action for shifting terminals.
//  yy_reduce_ofst[]   For each state, the offset into yy_action for shifting non-terminals after a reduce.
//  yy_default[]       Default action for each state.
%%

// The next table maps tokens into fallback tokens.  If a construct like the following:
// 
//      %fallback ID X Y Z.
//
// appears in the grammar, then ID becomes a fallback token for X, Y, and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
// but it does not parse, the type of the token is changed to ID and the parse is retried before an error is thrown.
#ifdef YYFALLBACK
__constant__ static const YYCODETYPE yyFallback[] = {
%%
};
#endif

// The following structure represents a single element of the parser's stack.  Information stored includes:
//
//   +  The state number for the parser at this level of the stack.
//
//   +  The value of the token stored at this level of the stack. (In other words, the "major" token.)
//
//   +  The semantic value stored at this level of the stack.  This is the information used by the action routines in the grammar.
//      It is sometimes called the "minor" token.
typedef struct YYSTACKENTRY
{
	YYACTIONTYPE stateno;  // The state-number
	YYCODETYPE major;      // The major token value.  This is the code number for the token at this stack level
	YYMINORTYPE minor;     // The user-supplied minor token value.  This is the value of the token
} YYSTACKENTRY;

// The state of the parser is completely contained in an instance of the following structure
typedef struct YYPARSER
{
	int yyidx;                    // Index of top element in stack
#ifdef YYTRACKMAXSTACKDEPTH
	int yyidxMax;                 // Maximum value of yyidx
#endif
	int yyerrcnt;                 // Shifts left before out of the error
	ParseARG_SDECL                // A place to hold %extra_argument
#if YYSTACKDEPTH<=0
	int yystksz;                  // Current side of the stack
	YYSTACKENTRY *yystack;        // The parser's stack
#else
	YYSTACKENTRY yystack[YYSTACKDEPTH];  // The parser's stack
#endif
} YYPARSER;

#ifndef NDEBUG
#include <stdio.h>
__device__ static FILE *yyTraceFILE = nullptr;
__device__ static char *yyTracePrompt = nullptr;
#endif

#ifndef NDEBUG
// 
// Turn parser tracing on by giving a stream to which to write the trace and a prompt to preface each trace message.  Tracing is turned off
// by making either argument NULL 
//
// Inputs:
// <ul>
// <li> A FILE* to which trace output should be written. If NULL, then tracing is turned off.
// <li> A prefix string written at the beginning of every line of trace output.  If NULL, then tracing is turned off.
// </ul>
//
// Outputs:
// None.
extern "C" __device__ void ParseTrace(FILE *traceFILE, char *tracePrompt)
{
	yyTraceFILE = traceFILE;
	yyTracePrompt = tracePrompt;
	if (!yyTraceFILE) yyTracePrompt = nullptr;
	else if (!yyTracePrompt) yyTraceFILE = nullptr;
}
#endif

#ifndef NDEBUG
// For tracing shifts, the names of all terminals and nonterminals are required.  The following table supplies these names
__constant__ static const char *const yyTokenName[] = {
%%
};
#endif

#ifndef NDEBUG
// For tracing reduce actions, the names of all rules are required.
__constant__ static const char *const yyRuleName[] = {
%%
};
#endif

#if YYSTACKDEPTH<=0
// Try to increase the size of the parser stack.
__device__ static void yyGrowStack(YYPARSER *p)
{
	YYSTACKENTRY *newEntry;
	int newSize = p->yystksz*2 + 100;
	newEntry = realloc(p->yystack, newSize*sizeof(newEntry[0]));
	if (newEntry)
	{
		p->yystack = newEntry;
		p->yystksz = newSize;
#ifndef NDEBUG
		if (yyTraceFILE)
			fprintf(yyTraceFILE, "%sStack grows to %d entries!\n", yyTracePrompt, p->yystksz);
#endif
	}
}
#endif

// This function allocates a new parser. The only argument is a pointer to a function which works like malloc.
//
// Inputs:
// A pointer to the function used to allocate memory.
//
// Outputs:
// A pointer to a parser.  This pointer is used in subsequent calls to Parse and ParseFree.
extern "C" __device__ void *ParseAlloc(void *(*allocProc)(size_t))
{
	YYPARSER *parser = (YYPARSER *)(*allocProc)((size_t)sizeof(YYPARSER));
	if (parser)
	{
		parser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
		parser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
		parser->yystack = NULL;
		parser->yystksz = 0;
		yyGrowStack(parser);
#endif
	}
	return parser;
}

// The following function deletes the value associated with a symbol.  The symbol can be either a terminal or nonterminal.
// "yymajor" is the symbol code, and "yypminor" is a pointer to the value.
__device__ static void yy_destructor(YYPARSER *yyparser, YYCODETYPE yymajor, YYMINORTYPE *yypminor)
{
	ParseARG_FETCH;
	switch (yymajor)
	{
		// Here is inserted the actions which take place when a terminal or non-terminal is destroyed.  This can happen
		// when the symbol is popped from the stack during a reduce or during error processing or when a parser is 
		// being destroyed before it is finished parsing.
		//
		// Note: during a reduce, the only symbols destroyed are those which appear on the RHS of the rule, but which are not used inside the C code.
%%
    default:  break; // If no destructor action specified: do nothing
	}
}

// Pop the parser's stack once.
//
// If there is a destructor routine associated with the token which is popped from the stack, then call it.
//
// Return the major token number for the symbol popped.
__device__ static int yy_pop_parser_stack(YYPARSER *parser)
{
	YYSTACKENTRY *yytos = &parser->yystack[parser->yyidx];

	if (parser->yyidx < 0) return 0;
#ifndef NDEBUG
	if (yyTraceFILE && parser->yyidx >= 0)
		fprintf(yyTraceFILE, "%sPopping %s\n", yyTracePrompt, yyTokenName[yytos->major]);
#endif
	YYCODETYPE yymajor = yytos->major;
	yy_destructor(parser, yymajor, &yytos->minor);
	parser->yyidx--;
	return yymajor;
}

// Deallocate and destroy a parser.  Destructors are all called for all stack elements before shutting the parser down.
//
// Inputs:
// <ul>
// <li>  A pointer to the parser.  This should be a pointer obtained from ParseAlloc.
// <li>  A pointer to a function used to reclaim memory obtained from malloc.
// </ul>
extern "C" __device__ void ParseFree(void *p, void (*freeProc)(void*))
{
	YYPARSER *parser = (YYPARSER *)p;
	if (!parser) return;
	while (parser->yyidx >= 0) yy_pop_parser_stack(parser);
#if YYSTACKDEPTH<=0
	free(parser->yystack);
#endif
	(*freeProc)((void*)parser);
}

// Return the peak depth of the stack for a parser.
#ifdef YYTRACKMAXSTACKDEPTH
extern "C" __device__ int ParseStackPeak(void *p)
{
	YYPARSER *parser = (YYPARSER *)p;
	return parser->yyidxMax;
}
#endif

// Find the appropriate action for a parser given the terminal look-ahead token lookAhead.
//
// If the look-ahead token is YYNOCODE, then check to see if the action is independent of the look-ahead.  If it is, return the action, otherwise
// return YY_NO_ACTION.
__device__ static int yy_find_shift_action(YYPARSER *parser, YYCODETYPE lookAhead)
{
	int stateno = parser->yystack[parser->yyidx].stateno;
 
	int i;
	if (stateno > YY_SHIFT_COUNT || (i = yy_shift_ofst[stateno]) == YY_SHIFT_USE_DFLT)
		return yy_default[stateno];
	_assert(lookAhead != YYNOCODE);
	i += lookAhead;
	if (i < 0 || i >= YY_ACTTAB_COUNT || yy_lookahead[i] != lookAhead)
	{
		if (lookAhead > 0)
		{
#ifdef YYFALLBACK
			YYCODETYPE fallback; // Fallback token
			if (lookAhead < sizeof(yyFallback) / sizeof(yyFallback[0]) && (fallback = yyFallback[lookAhead]) != 0)
			{
#ifndef NDEBUG
				if (yyTraceFILE)
					fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n", yyTracePrompt, yyTokenName[lookAhead], yyTokenName[fallback]);
#endif
				return yy_find_shift_action(parser, fallback);
			}
#endif
#ifdef YYWILDCARD
			{
				int j = i - lookAhead + YYWILDCARD;
				if (
#if YY_SHIFT_MIN+YYWILDCARD<0
				j >= 0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
				j < YY_ACTTAB_COUNT &&
#endif
				yy_lookahead[j] == YYWILDCARD)
				{
#ifndef NDEBUG
					if (yyTraceFILE)
						fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n", yyTracePrompt, yyTokenName[lookAhead], yyTokenName[YYWILDCARD]);
#endif
					return yy_action[j];
				}
			}
#endif
		}
		return yy_default[stateno];
	}
	else
		return yy_action[i];
}

// Find the appropriate action for a parser given the non-terminal look-ahead token lookAhead.
//
// If the look-ahead token is YYNOCODE, then check to see if the action is independent of the look-ahead.  If it is, return the action, otherwise return YY_NO_ACTION.
__device__ static int yy_find_reduce_action(int stateno, YYCODETYPE lookAhead)
{
#ifdef YYERRORSYMBOL
	if (stateno > YY_REDUCE_COUNT)
		return yy_default[stateno];
#else
	_assert(stateno <= YY_REDUCE_COUNT);
#endif
	int i = yy_reduce_ofst[stateno];
	_assert(i != YY_REDUCE_USE_DFLT);
	_assert(lookAhead != YYNOCODE);
	i += lookAhead;
#ifdef YYERRORSYMBOL
	if (i < 0 || i >= YY_ACTTAB_COUNT || yy_lookahead[i] != lookAhead)
		return yy_default[stateno];
#else
	_assert(i >= 0 && i < YY_ACTTAB_COUNT);
	_assert(yy_lookahead[i] == lookAhead);
#endif
	return yy_action[i];
}

// The following routine is called if the stack overflows.
__device__ static void yyStackOverflow(YYPARSER *yyparser, YYMINORTYPE *yypMinor)
{
	ParseARG_FETCH;
	yyparser->yyidx--;
#ifndef NDEBUG
	if (yyTraceFILE)
		fprintf(yyTraceFILE, "%sStack Overflow!\n", yyTracePrompt);
#endif
    while (yyparser->yyidx >= 0) yy_pop_parser_stack(yyparser);
	// Here code is inserted which will execute if the parser stack every overflows
%%
	ParseARG_STORE; // Suppress warning about unused %extra_argument var
}

// Perform a shift action.
__device__ static void yy_shift(YYPARSER *yyparser, int yyNewState, int yyMajor, YYMINORTYPE *yypMinor)
{
	YYSTACKENTRY *yytos;
	yyparser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
	if (yyparser->yyidx > yyparser->yyidxMax)
		yyparser->yyidxMax = yyparser->yyidx;
#endif
#if YYSTACKDEPTH>0 
	if (yyparser->yyidx >= YYSTACKDEPTH) //SKY: Error here if you remove the space
	{
		yyStackOverflow(yyparser, yypMinor);
		return;
	}
#else
	if (yyparser->yyidx >= yyparser->yystksz)
	{
		yyGrowStack(yyparser);
		if (yyparser->yyidx >= yyparser->yystksz)
		{
			yyStackOverflow(yyparser, yypMinor);
			return;
		}
	}
#endif
	yytos = &yyparser->yystack[yyparser->yyidx];
	yytos->stateno = (YYACTIONTYPE)yyNewState;
	yytos->major = (YYCODETYPE)yyMajor;
	yytos->minor = *yypMinor;
#ifndef NDEBUG
	if (yyTraceFILE && yyparser->yyidx > 0)
	{
		fprintf(yyTraceFILE, "%sShift %d\n", yyTracePrompt, yyNewState);
		fprintf(yyTraceFILE, "%sStack:", yyTracePrompt);
		for (int i = 1; i <= yyparser->yyidx; i++)
			fprintf(yyTraceFILE, " %s", yyTokenName[yyparser->yystack[i].major]);
		fprintf(yyTraceFILE, "\n");
	}
#endif
}

// The following table contains information about every rule that is used during the reduce.
__constant__ static const struct
{
	YYCODETYPE lhs; // Symbol on the left-hand side of the rule
	unsigned char nrhs; // Number of right-hand side symbols in the rule
} yyRuleInfo[] = {
%%
};

__device__ static void yy_accept(YYPARSER *);  // Forward Declaration

// Perform a reduce action and the shift that must immediately follow the reduce.
__device__ static void yy_reduce(YYPARSER *yyparser, int yyruleno)
{
	int yygoto;                     // The next state
	int yyact;                      // The next action
	YYMINORTYPE yygotominor;        // The LHS of the rule reduced
	int yysize;                     // Amount to pop the stack
	ParseARG_FETCH;
	YYSTACKENTRY *yymsp = &yyparser->yystack[yyparser->yyidx]; // The top of the parser's stack
#ifndef NDEBUG
	if (yyTraceFILE && yyruleno >= 0  && yyruleno < (int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])))
		fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt, yyRuleName[yyruleno]);
#endif

	// Silence complaints from purify about yygotominor being uninitialized in some cases when it is copied into the stack after the following
	// switch.  yygotominor is uninitialized when a rule reduces that does not set the value of its left-hand side nonterminal.  Leaving the
	// value of the nonterminal uninitialized is utterly harmless as long as the value is never used.  So really the only thing this code
	// accomplishes is to quieten purify.  
	//
	// 2007-01-16:  The wireshark project (www.wireshark.org) reports that without this code, their parser segfaults.  I'm not sure what there
	// parser is doing to make this happen.  This is the second bug report from wireshark this week.  Clearly they are stressing Lemon in ways
	// that it has not been previously stressed...  (SQLite ticket #2172)
	//: memset(&yygotominor, 0, sizeof(yygotominor));
	yygotominor = yyzerominor;

	switch (yyruleno)
	{
  // Beginning here are the reduction cases.  A typical example follows:
  //   case 0:
  //  #line <lineno> <grammarfile>
  //     { ... }           // User supplied code
  //  #line <lineno> <thisfile>
  //     break;
%%
	};
	yygoto = yyRuleInfo[yyruleno].lhs;
	yysize = yyRuleInfo[yyruleno].nrhs;
	yyparser->yyidx -= yysize;
	yyact = yy_find_reduce_action(yymsp[-yysize].stateno, (YYCODETYPE)yygoto);
	if (yyact < YYNSTATE)
	{
#ifdef NDEBUG
		// If we are not debugging and the reduce action popped at least one element off the stack, then we can push the new element back
		// onto the stack here, and skip the stack overflow test in yy_shift(). That gives a significant speed improvement.
		if (yysize)
		{
			yyparser->yyidx++;
			yymsp -= yysize-1;
			yymsp->stateno = (YYACTIONTYPE)yyact;
			yymsp->major = (YYCODETYPE)yygoto;
			yymsp->minor = yygotominor;
		}
		else
#endif
		{
			yy_shift(yyparser, yyact, yygoto, &yygotominor);
		}
	}
	else
	{
		_assert( yyact == YYNSTATE + YYNRULE + 1 );
		yy_accept(yyparser);
	}
}

// The following code executes when the parse fails
#ifndef YYNOERRORRECOVERY
__device__ static void yy_parse_failed(YYPARSER *yyparser)
{
	ParseARG_FETCH;
#ifndef NDEBUG
	if (yyTraceFILE)
		fprintf(yyTraceFILE, "%sFail!\n", yyTracePrompt);
#endif
	while (yyparser->yyidx >= 0) yy_pop_parser_stack(yyparser);
	// Here code is inserted which will be executed whenever the parser fails
%%
	ParseARG_STORE; // Suppress warning about unused %extra_argument variable
}
#endif

// The following code executes when a syntax error first occurs.
__device__ static void yy_syntax_error(YYPARSER *yyparser, int yymajor, YYMINORTYPE yyminor)
{
	ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
%%
	ParseARG_STORE; // Suppress warning about unused %extra_argument variable
}

// The following is executed when the parser accepts
__device__ static void yy_accept(YYPARSER *yyparser)
{
	ParseARG_FETCH;
#ifndef NDEBUG
	if (yyTraceFILE)
		fprintf(yyTraceFILE, "%sAccept!\n", yyTracePrompt);
#endif
	while (yyparser->yyidx >= 0) yy_pop_parser_stack(yyparser);
	// Here code is inserted which will be executed whenever the parser accepts
%%
	ParseARG_STORE; // Suppress warning about unused %extra_argument variable
}

// The main parser program.
// The first argument is a pointer to a structure obtained from "ParseAlloc" which describes the current state of the parser.
// The second argument is the major token number.  The third is the minor token.  The fourth optional argument is whatever the
// user wants (and specified in the grammar) and is available for use by the action routines.
//
// Inputs:
// <ul>
// <li> A pointer to the parser (an opaque structure.)
// <li> The major token number.
// <li> The minor token number.
// <li> An option argument of a grammar-specified type.
// </ul>
//
// Outputs:
// None.
extern "C" __device__ void Parse(void *yyp, int yymajor, ParseTOKENTYPE yyminor ParseARG_PDECL)
{
	YYMINORTYPE yyminorunion;
	int yyact;            // The parser action.
	int yyendofinput;     // True if we are at the end of input
#ifdef YYERRORSYMBOL
	int yyerrorhit = 0;   // True if yymajor has invoked an error
#endif
	YYPARSER *yyparser;  // The parser

	// (re)initialize the parser, if necessary
	yyparser = (YYPARSER *)yyp;
	if (yyparser->yyidx < 0)
	{
#if YYSTACKDEPTH<=0
		if (yyparser->yystksz <= 0)
		{
		//: memset(&yyminorunion, 0, sizeof(yyminorunion));
			yyminorunion = yyzerominor;
			yyStackOverflow(yyparser, &yyminorunion);
			return;
		}
#endif
		yyparser->yyidx = 0;
		yyparser->yyerrcnt = -1;
		yyparser->yystack[0].stateno = 0;
		yyparser->yystack[0].major = 0;
	}
	yyminorunion.yy0 = yyminor;
	yyendofinput = (yymajor==0);
	ParseARG_STORE;

#ifndef NDEBUG
	if (yyTraceFILE)
		fprintf(yyTraceFILE, "%sInput %s\n", yyTracePrompt, yyTokenName[yymajor]);
#endif

	do
	{
		yyact = yy_find_shift_action(yyparser,(YYCODETYPE)yymajor);
		if (yyact < YYNSTATE)
		{
			_assert(!yyendofinput); // Impossible to shift the $ token
			yy_shift(yyparser, yyact, yymajor, &yyminorunion);
			yyparser->yyerrcnt--;
			yymajor = YYNOCODE;
		}
		else if (yyact < YYNSTATE + YYNRULE)
			yy_reduce(yyparser,yyact-YYNSTATE);
		else
		{
			_assert(yyact == YY_ERROR_ACTION);
#ifndef NDEBUG
			if (yyTraceFILE)
				fprintf(yyTraceFILE, "%sSyntax Error!\n", yyTracePrompt);
#endif
#ifdef YYERRORSYMBOL
			// A syntax error has occurred. The response to an error depends upon whether or not the grammar defines an error token "ERROR".  
			//
			// This is what we do if the grammar does define ERROR:
			//  * Call the %syntax_error function.
			//  * Begin popping the stack until we enter a state where it is legal to shift the error symbol, then shift the error symbol.
			//  * Set the error count to three.
			//  * Begin accepting and shifting new tokens.  No new error processing will occur until three tokens have been shifted successfully.
			if (yyparser->yyerrcnt < 0)
				yy_syntax_error(yyparser, yymajor, yyminorunion);
			int yymx = yyparser->yystack[yyparser->yyidx].major;
			if (yymx == YYERRORSYMBOL || yyerrorhit)
			{
#ifndef NDEBUG
				if (yyTraceFILE)
					fprintf(yyTraceFILE,"%sDiscard input token %s\n", yyTracePrompt,yyTokenName[yymajor]);
#endif
				yy_destructor(yyparser, (YYCODETYPE)yymajor,&yyminorunion);
				yymajor = YYNOCODE;
			}
			else
			{
				while (yyparser->yyidx >= 0 && yymx != YYERRORSYMBOL && (yyact = yy_find_reduce_action(yyparser->yystack[yyparser->yyidx].stateno, YYERRORSYMBOL)) >= YYNSTATE)
					yy_pop_parser_stack(yyparser);
				if (yyparser->yyidx < 0 || yymajor == 0)
				{
					yy_destructor(yyparser,(YYCODETYPE)yymajor,&yyminorunion);
					yy_parse_failed(yyparser);
					yymajor = YYNOCODE;
				}
				else if (yymx != YYERRORSYMBOL)
				{
					YYMINORTYPE u2;
					u2.YYERRSYMDT = 0;
					yy_shift(yyparser,yyact,YYERRORSYMBOL,&u2);
				}
			}
			yyparser->yyerrcnt = 3;
			yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
			// If the YYNOERRORRECOVERY macro is defined, then do not attempt to do any kind of error recovery.  Instead, simply invoke the syntax
			// error routine and continue going as if nothing had happened.
			//
			// Applications can set this macro (for example inside %include) if they intend to abandon the parse upon the first syntax error seen.
			yy_syntax_error(yyparser,yymajor,yyminorunion);
			yy_destructor(yyparser,(YYCODETYPE)yymajor,&yyminorunion);
			yymajor = YYNOCODE;
      
#else  // YYERRORSYMBOL is not defined
			// This is what we do if the grammar does not define ERROR:
			//  * Report an error message, and throw away the input token.
			//  * If the input token is $, then fail the parse.
			//
			// As before, subsequent error messages are suppressed until three input tokens have been successfully shifted.
			if (yyparser->yyerrcnt <= 0)
				yy_syntax_error(yyparser, yymajor, yyminorunion);
			yyparser->yyerrcnt = 3;
			yy_destructor(yyparser, (YYCODETYPE)yymajor, &yyminorunion);
			if (yyendofinput)
				yy_parse_failed(yyparser);
			yymajor = YYNOCODE;
#endif
		}
	}
	while (yymajor != YYNOCODE && yyparser->yyidx >= 0);
	return;
}