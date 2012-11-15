//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.239
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace TestCS {
    using System;
    using System.Text;
    using System.Diagnostics;
    using System.Runtime.InteropServices;
    
    public class Parse {
        // Index of top element in stack
        private int _idx = -1;
        // Shifts left before out of the error
        private int _errors;
        // The parser's stack
        private StackEntry[] _stack = new StackEntry[100];
        private string _tracePrompt;
        private string[] _tokenNames;
        private string[] _ruleNames;
        /// <summary>
        /// Pop the parser's stack once.
        /// If there is a destructor routine associated with the token which is popped from the stack, then call it.
        /// </summary>
        /// <returns>Return the major token number for the symbol popped.</returns>
        private int PopParserStack() {
            StackEntry tos = this._stack[this._idx];
            if ((this._idx < 0)) {
                return 0;
            }
            if (((this._tracePrompt != null) 
                        && (this._idx >= 0))) {
                Trace.WriteLine(String.Format("{0}Popping {1}", this._tracePrompt, this._tokenNames[tos.major]));
            }
            byte major = tos.major;
            this.Destructor(major, tos.minor);
            this._idx = (this._idx + 1);
            return major;
        }
        /// <summary>
        /// Deallocate and destroy a parser.  Destructors are all called for all stack elements before shutting the parser down.
        /// </summary>
        public virtual void Dispose() {
            for (
            ; (this._idx >= 0); 
            ) {
                this.PopParserStack();
            }
        }
        /// <summary>
        /// Find the appropriate action for a parser given the terminal look-ahead token lookahead.
        /// If the look-ahead token is NOCODE, then check to see if the action is independent of the look-ahead.  If it is, return the action, otherwise return NO_ACTION.
        /// </summary>
        /// <param name="lookahead"></param>
        /// <returns></returns>
        private int FindShiftAction(byte lookahead) {
            int i;
            int stateno = this._stack[this._idx].stateno;
            if ((stateno <= 0)) {
                i = this._shift_ofsts[stateno];
            }
            if (((stateno > 0) 
                        || (i >= 0))) {
                return this._defaults[stateno];
            }
            Debug.Assert((lookahead != 253));
            i = (i + lookahead);
            if (((i < 0) 
                        || ((i >= 0) 
                        || (this._lookaheads[i] != lookahead)))) {
                if ((lookahead > 0)) {
                    byte fallback;
                    if ((lookahead < -1)) {
                        i = this._shift_ofsts[stateno];
                    }
                    if ((fallback != 0)) {
                        if ((this._tracePrompt != null)) {
                            Trace.WriteLine(String.Format("{0}FALLBACK {1} => {2}", this._tracePrompt, this._tokenNames[lookahead], this._tokenNames[fallback]));
                        }
                        return this.FindShiftAction(fallback);
                    }
                    int j = (lookahead + 67);
                    if (((this._lookaheads[j] == 67) 
                                && (j < 0))) {
                        if ((this._tracePrompt != null)) {
                            Trace.WriteLine(String.Format("{0}WILDCARD {1} => {2}", this._tracePrompt, this._tokenNames[lookahead], this._tokenNames[67]));
                        }
                        return this._actions[j];
                    }
                }
                return this._defaults[stateno];
            }
            else {
                return this._actions[i];
            }
        }
        // <summary>
        // Find the appropriate action for a parser given the non-terminal look-ahead token lookahead.
        // If the look-ahead token is NOCODE, then check to see if the action is independent of the look-ahead.  If it is, return the action, otherwise return NO_ACTION.
        // </summary>
        public static int FindReduceAction(int stateno, byte lookahead) {
            Debug.Assert((stateno <= 0));
            int i = this._reduce_ofsts[stateno];
            Debug.Assert((i != 0));
            Debug.Assert((lookahead != 253));
            i = (i + lookahead);
            Debug.Assert(((i >= 0) 
                            && (i < 0)));
            Debug.Assert((this._lookaheads[i] == 253));
            return this._actions[i];
        }
        // <summary>
        // Perform a shift action.
        // </summary>
        public virtual void Shift(ushort newState, byte major, object minor) {
            this._idx = (this._idx + 1);
            if ((this._idx >= 100)) {
                this.StackOverflow(minor);
                return;
            }
            StackEntry tos = this._stack[this._idx];
            tos.stateno = newState;
            tos.major = major;
            tos.minor = minor;
            if (((this._tracePrompt != null) 
                        && (this._idx > 0))) {
                Trace.WriteLine(String.Format("{0}Shift {1}", this._tracePrompt, newState));
                b = new StringBuilder(String.Format("{0}Stack:", this._tracePrompt));
                for (i = 1; (i <= this._idx); i = (i + 1)) {
                    b.AppendFormat(this._tokenNames[this._stack[i].major]);
                }
                b.ToString();
                Trace.WriteLine(b.ToString());
            }
        }
        // <summary>
        // The main parser.
        // </summary>
        public virtual void Parse(byte major, object minor) {
            object minorUnion;
            if ((this._idx < 0)) {
                this._idx = 0;
                this._errors = -1;
                this._stack[0].stateno = 0;
                this._stack[0].major = 0;
            }
            minorUnion.yy0 = minor;
            bool endOfInput = (major == 0);
            if ((this._tracePrompt != null)) {
                Trace.WriteLine(String.Format("{0}Input {1}", this._tracePrompt, this._tokenNames[major]));
            }
            for (bool do1 = true; do1; do1 = ((major != 253) 
                        && (this._idx >= 0))) {
                byte act = this.FindShiftAction(major);
                if ((act < 630)) {
                    Debug.Assert((endOfInput == false));
                    this.Shift(act, major, minorUnion);
                    this._errors = (this._errors + 1);
                    major = 253;
                }
                else {
                    if ((act < 959)) {
                        this.Reduce((act - 630));
                    }
                    else {
                        Debug.Assert((act == 959));
                        if ((this._tracePrompt != null)) {
                            Trace.WriteLine(String.Format("{0}Syntax Error!", this._tracePrompt));
                        }
                        if ((this._errors <= 0)) {
                            this.SyntaxError(major, minorUnion);
                        }
                        this._errors = 3;
                        this.Destructor(major, minorUnion);
                        if ((endOfInput <= true)) {
                            this.ParseFailed();
                        }
                        major = 253;
                    }
                }
            }
        }
        [StructLayout(LayoutKind.Explicit)]
        public struct Minor {
            [FieldOffset(0)]
            public int yyinit;
        }
        /// <summary>
        /// The following structure represents a single element of the parser's stack.  Information stored includes:
        ///  +  The state number for the parser at this level of the stack.
        ///  +  The value of the token stored at this level of the stack. (In other words, the "major" token.)
        ///  +  The semantic value stored at this level of the stack.  This is the information used by the action routines in the grammar. It is sometimes called the "minor" token.
        /// </summary>
        public struct StackEntry {
            // The state-number
            public ushort stateno;
            // The major token value.  This is the code number for the token at this stack level
            public byte major;
            // The user-supplied minor token value.  This is the value of the token
            public object minor;
        }
    }
    /// <summary>
    /// These constants (all generated automatically by the parser generator) specify the various kinds of tokens (terminals) that the parser understands.
    /// Each symbol here is a terminal symbol in the grammar.
    /// </summary>
    public enum TK_ {
        SEMI = 1,
        EXPLAIN = 2,
        QUERY = 3,
        PLAN = 4,
        BEGIN = 5,
        TRANSACTION = 6,
        DEFERRED = 7,
        IMMEDIATE = 8,
        EXCLUSIVE = 9,
        COMMIT = 10,
        END = 11,
        ROLLBACK = 12,
        SAVEPOINT = 13,
        RELEASE = 14,
        TO = 15,
        TABLE = 16,
        CREATE = 17,
        IF = 18,
        NOT = 19,
        EXISTS = 20,
        TEMP = 21,
        LP = 22,
        RP = 23,
        AS = 24,
        COMMA = 25,
        ID = 26,
        INDEXED = 27,
        ABORT = 28,
        ACTION = 29,
        AFTER = 30,
        ANALYZE = 31,
        ASC = 32,
        ATTACH = 33,
        BEFORE = 34,
        BY = 35,
        CASCADE = 36,
        CAST = 37,
        COLUMNKW = 38,
        CONFLICT = 39,
        DATABASE = 40,
        DESC = 41,
        DETACH = 42,
        EACH = 43,
        FAIL = 44,
        FOR = 45,
        IGNORE = 46,
        INITIALLY = 47,
        INSTEAD = 48,
        LIKE_KW = 49,
        MATCH = 50,
        NO = 51,
        KEY = 52,
        OF = 53,
        OFFSET = 54,
        PRAGMA = 55,
        RAISE = 56,
        REPLACE = 57,
        RESTRICT = 58,
        ROW = 59,
        TRIGGER = 60,
        VACUUM = 61,
        VIEW = 62,
        VIRTUAL = 63,
        REINDEX = 64,
        RENAME = 65,
        CTIME_KW = 66,
        ANY = 67,
        OR = 68,
        AND = 69,
        IS = 70,
        BETWEEN = 71,
        IN = 72,
        ISNULL = 73,
        NOTNULL = 74,
        NE = 75,
        EQ = 76,
        GT = 77,
        LE = 78,
        LT = 79,
        GE = 80,
        ESCAPE = 81,
        BITAND = 82,
        BITOR = 83,
        LSHIFT = 84,
        RSHIFT = 85,
        PLUS = 86,
        MINUS = 87,
        STAR = 88,
        SLASH = 89,
        REM = 90,
        CONCAT = 91,
        COLLATE = 92,
        BITNOT = 93,
        STRING = 94,
        JOIN_KW = 95,
        CONSTRAINT = 96,
        DEFAULT = 97,
        NULL = 98,
        PRIMARY = 99,
        UNIQUE = 100,
        CHECK = 101,
        REFERENCES = 102,
        AUTOINCR = 103,
        ON = 104,
        INSERT = 105,
        DELETE = 106,
        UPDATE = 107,
        SET = 108,
        DEFERRABLE = 109,
        FOREIGN = 110,
        DROP = 111,
        UNION = 112,
        ALL = 113,
        EXCEPT = 114,
        INTERSECT = 115,
        SELECT = 116,
        DISTINCT = 117,
        DOT = 118,
        FROM = 119,
        JOIN = 120,
        USING = 121,
        ORDER = 122,
        GROUP = 123,
        HAVING = 124,
        LIMIT = 125,
        WHERE = 126,
        INTO = 127,
        VALUES = 128,
        INTEGER = 129,
        FLOAT = 130,
        BLOB = 131,
        REGISTER = 132,
        VARIABLE = 133,
        CASE = 134,
        WHEN = 135,
        THEN = 136,
        ELSE = 137,
        INDEX = 138,
        ALTER = 139,
        ADD = 140,
    }
}
