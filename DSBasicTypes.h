#ifndef _DSBASICTYPES_H_
#define _DSBASICTYPES_H_

#include <stdlib.h>
#include <assert.h>

/*************************************************************************
 * Grundlegenden Datentypen fuer das (Q)SDL-Depository
 *************************************************************************/

#define DS_VERSION               "1.6.1"
#define DS_DATE                  "$Date: 1998/01/13 12:48:22 $"

#define DS_CREATE_ENV 1
#define DS_NAME_ENV               "env"
#define DS_NAME_ENV_BLOCK         "env"
#define DS_NAME_ENV_PROCESS       "env"
#define DS_NAME_ENV_SIGNAL_ROUTE  "env"
#define DS_NAME_ENV_STATE_ACTIVE  "produce"
#define DS_NAME_ENV_STATE_PASSIVE "consume"
#define DS_NAME_ENV_STATE         "produce_and_consume"

#define DS_NAME_EXTERNAL         "external"

#define DS_DEFAULT_RETURN_PARAM_NAME "return_value"
#define DS_GENERATOR_NAME_STRING   "string"
#define DS_GENERATOR_NAME_ARRAY    "array"
#define DS_GENERATOR_NAME_POWERSET "powerset"

#define DS_SORT_NAME_NATURAL    "natural"
#define DS_SORT_NAME_INTEGER    "integer"
  #define DS_SORT_OPERATOR_NAME_FLOAT     "float"
  #define DS_SORT_OPERATOR_NAME_FIX       "fix"
#define DS_SORT_NAME_REAL       "real"
#define DS_SORT_NAME_TIME       "time"
  #define DS_SORT_OPERATOR_NAME_TIME      "time"
  #define DS_SORT_OPERATOR_NAME_NOW       "now"
#define DS_SORT_NAME_DURATION   "duration"
  #define DS_SORT_OPERATOR_NAME_DURATION  "duration"
#define DS_SORT_NAME_BOOLEAN    "boolean"
  #define DS_SORT_LITERAL_NAME_TRUE       "true"
  #define DS_SORT_LITERAL_NAME_FALSE      "false"
#define DS_SORT_NAME_PID        "pid"
  #define DS_SORT_LITERAL_NAME_NULL       "null"
  #define DS_SORT_OPERATOR_NAME_PARENT    "parent"
  #define DS_SORT_OPERATOR_NAME_SELF      "self"
                                          /* Prozess-Instanz */
  #define DS_SORT_OPERATOR_NAME_THIS      "this"
                                          /* Prozess-Typ */
  #define DS_SORT_OPERATOR_NAME_SENDER    "sender"
  #define DS_SORT_OPERATOR_NAME_OFFSPRING "offspring"
#define DS_SORT_NAME_CHARACTER  "character"
  #define DS_SORT_OPERATOR_NAME_NUM       "num"
  #define DS_SORT_OPERATOR_NAME_CHR       "chr"
#define DS_SORT_NAME_CHARSTRING "charstring"
  #define DS_SORT_LITERAL_NAME_EMPTYSTRING "''"
  #define DS_SORT_LITERAL_NAME_EMPTYSTRING2 "emptystring"
  #define DS_SORT_OPERATOR_NAME_MKSTRING   "mkstring"
  #define DS_SORT_OPERATOR_NAME_LENGTH     "length"
  #define DS_SORT_OPERATOR_NAME_FIRST      "first"
  #define DS_SORT_OPERATOR_NAME_LAST       "last"
  #define DS_SORT_OPERATOR_NAME_CONCAT     "//"
  #define DS_SORT_OPERATOR_NAME_EXTRACT    "extract"
  #define DS_SORT_OPERATOR_NAME_MODIFY     "modify"
  #define DS_SORT_OPERATOR_NAME_SUBSTRING  "substring"
#define DS_SORT_NAME_BYTE       "byte"
  #define DS_SORT_OPERATOR_NAME_BAND       "band"
  #define DS_SORT_OPERATOR_NAME_BOR        "bor"
  #define DS_SORT_OPERATOR_NAME_BXOR       "bxor"
  #define DS_SORT_OPERATOR_NAME_BNOT       "bnot"
  #define DS_SORT_OPERATOR_NAME_BSHL       "bshl"
  #define DS_SORT_OPERATOR_NAME_BSHR       "bshr"
  #define DS_SORT_OPERATOR_NAME_BPLUS      "bplus"
  #define DS_SORT_OPERATOR_NAME_BSUB       "bsub"
  #define DS_SORT_OPERATOR_NAME_BMUL       "bmul"
  #define DS_SORT_OPERATOR_NAME_BDIV       "bdiv"
  #define DS_SORT_OPERATOR_NAME_BMOD       "bmod"
  #define DS_SORT_OPERATOR_NAME_I2B        "i2b"
  #define DS_SORT_OPERATOR_NAME_B2I        "b2i"
  #define DS_SORT_OPERATOR_NAME_C2B        "c2b"
  #define DS_SORT_OPERATOR_NAME_B2C        "b2c"
#define DS_SORT_NAME_DISCIPLINE    "discipline"
  #define DS_SORT_LITERAL_NAME_PS      "ps"
  #define DS_SORT_LITERAL_NAME_IS      "is"
  #define DS_SORT_LITERAL_NAME_FCFS    "fcfs"
  #define DS_SORT_LITERAL_NAME_LCFSPP  "lcfspp"
  #define DS_SORT_LITERAL_NAME_RANDOM  "random"
  #define DS_SORT_LITERAL_NAME_FCFSPP  "fcfspp"
  #define DS_SORT_LITERAL_NAME_FCFSPNP "fcfspnp"
#define DS_SORT_NAME_DETERMINISTIC "deterministic"
#define DS_SORT_NAME_EMPIRICAL     "empirical"
#define DS_SORT_NAME_ERLANG        "erlang"
#define DS_SORT_NAME_NEGEXP        "negexp"
#define DS_SORT_NAME_NORMAL        "normal"
#define DS_SORT_NAME_UNIFORM       "uniform"
#define DS_SORT_NAME_BERNOULLI     "bernoulli"
#define DS_SORT_NAME_POISSON       "poisson"
#define DS_SORT_NAME_RANDINT       "randint"

#define DS_SORT_OPERATOR_NAME_INIT      "init"
#define DS_SORT_OPERATOR_NAME_SAMPLE    "sample"

/* Basissorten fuer die QSDL-Sensoren: */

#define DS_SORT_NAME_COUNTER                "counter"
  #define DS_SORT_OPERATOR_NAME_SUM         "sum"
  #define DS_SORT_OPERATOR_NAME_SUMINT      "sumint"
  #define DS_SORT_OPERATOR_NAME_SUMTIME     "sumtime"
  #define DS_SORT_OPERATOR_NAME_SUMTIMEINT  "sumtimeint"
#define DS_SORT_NAME_FREQUENCY              "frequency"
  #define DS_SORT_OPERATOR_NAME_SUM         "sum"
  #define DS_SORT_OPERATOR_NAME_ABSFREQ     "absfreq"
  #define DS_SORT_OPERATOR_NAME_RELFREQ     "relfreq"
  #define DS_SORT_OPERATOR_NAME_LASTVALUE   "lastvalue"
  #define DS_SORT_OPERATOR_NAME_CURRENTVALUE "currentvalue"
  #define DS_SORT_OPERATOR_NAME_LASTSAMPLE "lastsample"
#define DS_SORT_NAME_TALLY                 "tally"
  #define DS_SORT_OPERATOR_NAME_NUM        "num"
  #define DS_SORT_OPERATOR_NAME_NUMINT     "numint"
  #define DS_SORT_OPERATOR_NAME_MINIMUM    "minimum"
  #define DS_SORT_OPERATOR_NAME_MAXIMUM    "maximum"
  #define DS_SORT_OPERATOR_NAME_SUM        "sum"
  #define DS_SORT_OPERATOR_NAME_SUMINT     "sumint"
  #define DS_SORT_OPERATOR_NAME_SUMSQUARE  "sumsquare"
  #define DS_SORT_OPERATOR_NAME_AVERAGE    "average"
  #define DS_SORT_OPERATOR_NAME_AVERAGEINT "averageint"
  #define DS_SORT_OPERATOR_NAME_VARIANCE   "variance"
  #define DS_SORT_OPERATOR_NAME_STDDEV     "stddev"
  #define DS_SORT_OPERATOR_NAME_VARCOEFF   "varcoeff"

#define DS_SORT_NEUTRAL_INTEGER    "0"
#define DS_SORT_NEUTRAL_NATURAL    "0"
#define DS_SORT_NEUTRAL_BOOLEAN    "false"
#define DS_SORT_NEUTRAL_REAL       "0.0"
#define DS_SORT_NEUTRAL_CHAR       "'\\0'"
#define DS_SORT_NEUTRAL_CHARSTRING "\"\""
#define DS_SORT_NEUTRAL_DURATION   "0.0"
#define DS_SORT_NEUTRAL_TIME       "0.0"
#define DS_SORT_NEUTRAL_PID        "0L"

enum DSBoolean
{
  DS_FALSE = 0,
  DS_TRUE
};

typedef unsigned int DSCardinal;
typedef long int     DSInteger;
typedef double       DSDouble;

typedef enum
{
  DS_SORT_NATURAL = 0,
  DS_SORT_INTEGER,
  DS_SORT_REAL,
  DS_SORT_TIME,
  DS_SORT_DURATION,
  DS_SORT_BOOLEAN,
  DS_SORT_ILLEGAL
} DSOperatorIndex;

enum DSType
{
  DS_NONE = 0,
  DS_ACTION,
  DS_ACTUALPARAM,
  DS_ATOM,
  DS_BLOCK,
  DS_BLOCKSUBSTRUCTURE,
  DS_CHANNEL,
  DS_CHANNEL2CHANNELCONNECTION,
  DS_CHANNEL2ROUTECONNECTION,
  DS_EXPRESSION,
  DS_FORMALPARAM,
  DS_INPUT,
  DS_INPUTSIGNAL,
  DS_INPUTTIMERSIGNAL,
  DS_LINK,
  DS_MACHINE,
  DS_MACHINESERVICE,
  DS_MACHINESERVICESPEED,
  DS_NAMESORT,
  DS_OPERAND,
  DS_OPERATOR,
  DS_PIPE,
  DS_PIPE2LINKBINDING,
  DS_PIPE2PIPEBINDING,
  DS_PROCEDURE,
  DS_PROCESS,
  DS_PROCESSACCESS,
  DS_RANGE,
  DS_SAVE,
  DS_SENSOR,
  DS_SIGNAL,
  DS_SIGNALITEMLIST,
  DS_SIGNALLIST,
  DS_SIGNALROUTE,
  DS_SORT,
  DS_STATE,
  DS_STRING,
  DS_SYSTEM,
  DS_TIMER,
  DS_TRANSITION,
  DS_VARIABLE,
  DS_VARIABLEACCESS,
  DS_VARIABLEACCESSELEM,
  DS_ALL,
  DS_TYPE_MAX
};

enum DSSortTag
{
  DS_SORT_BASIC = 0,
  DS_SORT_EXTENDED,
  DS_SORT_GENERATOR,
  DS_SORT_STRUCT,
  DS_SORT_SYNONYM,
  DS_SORT_SYNTYPE,
  DS_SORT_MAX
};

enum DSActionTag
{
  DS_CALL = 0,
  DS_CREATE,
  DS_DECISION,
  DS_JOIN,
  DS_NEXTSTATE,
  DS_OUTPUT,
  DS_REQUEST,
  DS_RESET,
  DS_SET,
  DS_TASK,
  DS_RETURN,
  DS_STOP,
  DS_CLEAR,
  DS_UPDATE,
  DS_ASSERT,
  DS_ACTION_MAX
};

enum DSVariableAccessTag
{
  DS_ACCESS_FIELD = 0,
  DS_ACCESS_INDEX,
  DS_ACCESS_MAX
};

enum DSResult
{
  DS_ERROR = 0,
  DS_OK,
  DS_OUT_OF_MEMORY,
  DS_FATAL_ERROR,
  DS_READ_ERROR,
  DS_WRITE_ERROR,
  DS_RESULT_MAX
};

enum DSExpressionOperandTag
{
  DS_OPN_CONSTANT = 0,
  DS_OPN_VARIABLE_ACCESS,
  DS_OPN_SYNONYM,
  DS_OPN_EXPRESSION,
  DS_OPN_LITERAL,
  DS_OPN_OPERATOR,
  DS_OPN_PROCEDURE_CALL,
  DS_OPN_SENSOR,             /* for sensor access in atoms only */
  DS_OPN_SIGNAL,             /* for sensor access in atoms only */
  DS_OPN_STATE,              /* for sensor access in atoms only */
  DS_OPN_MACHINE_SERVICE,    /* for sensor access in atoms only */
  DS_OPN_PROCESS_ACCESS,     /* for atom + sensor access only */
  DS_OPN_MAX
};

enum DSExpressionOperator
{
  DS_OPT_NONE = 0,
  DS_OPT_OR,
  DS_OPT_XOR,
  DS_OPT_AND,
  DS_OPT_EQUAL,
  DS_OPT_NOT_EQUAL,
  DS_OPT_GREATER,
  DS_OPT_GREATER_EQUAL,
  DS_OPT_LESS,
  DS_OPT_LESS_EQUAL,
  DS_OPT_IN,
  DS_OPT_ADDITION,
  DS_OPT_SUBTRACTION,
  DS_OPT_CONCATENATION,
  DS_OPT_MULTIPLICATION,
  DS_OPT_DIVISION,
  DS_OPT_MOD,
  DS_OPT_REM,
  DS_OPT_MINUS,
  DS_OPT_NOT,
  DS_OPT_THICKARROW,
  DS_OPT_MAX
};

enum DSRangeOperator
{
  DS_RANGE_OPT_NONE = 0,
  DS_RANGE_OPT_EQUAL,
  DS_RANGE_OPT_NOT_EQUAL,
  DS_RANGE_OPT_GREATER,
  DS_RANGE_OPT_GREATER_EQUAL,
  DS_RANGE_OPT_LESS,
  DS_RANGE_OPT_LESS_EQUAL,
  DS_RANGE_OPT_MAX
};

/************************************************/
/* Konstanten fuer die verschiedene SAVE-Arten: */
/************************************************/

enum DSSaveType
{
  DS_SAVE_NONE = 0,
  DS_SAVE_SIGNALS = 1,
  DS_SAVE_ALL = 2
};

typedef enum
{
  DS_SENSOR_ILLEGAL = 0,                            /* Default value. */

  DS_SENSOR_COUNTER,                                /* User defined sensors */
  DS_SENSOR_FREQUENCY,
  DS_SENSOR_TALLY,
    
  DS_SENSOR_PCS_FREQ_SIGNAL_RECEIVE,                   /* Process sensor types. */
  DS_SENSOR_PCS_FREQ_SIGNAL_DROP,
  DS_SENSOR_PCS_FREQ_SIGNAL_CONSUME,
  DS_SENSOR_PCS_FREQ_SIGNAL_SAVE,
  DS_SENSOR_PCS_FREQ_SIGNAL_LOSE,
  DS_SENSOR_PCS_FREQ_SIGNAL_SEND,
  DS_SENSOR_PCS_FREQ_REQUEST,
  DS_SENSOR_PCS_FREQ_STATE,
  DS_SENSOR_PCS_COUNT_SIGNAL_RECEIVE,
  DS_SENSOR_PCS_COUNT_SIGNAL_DROP,
  DS_SENSOR_PCS_COUNT_SIGNAL_CONSUME,
  DS_SENSOR_PCS_COUNT_SIGNAL_SAVE,
  DS_SENSOR_PCS_COUNT_SIGNAL_LOSE,
  DS_SENSOR_PCS_COUNT_SIGNAL_SEND,
  DS_SENSOR_PCS_COUNT_REQUEST,
  DS_SENSOR_PCS_COUNT_STATE,
  DS_SENSOR_PCS_QUEUE_LENGTH,
  DS_SENSOR_PCS_QUEUE_CONTENT,
  DS_SENSOR_PCS_WAITTIME_SIGNAL,
  DS_SENSOR_PCS_WAITTIME_STATE,
  DS_SENSOR_PCS_RESPONSETIME_REQUEST,
  DS_SENSOR_PCS_TRANSMISSIONTIME_SIGNAL,
  DS_SENSOR_PCS_FREQ_TRANSITION,
  DS_SENSOR_PCS_COUNT_TRANSITION,
  
  DS_SENSOR_MACH_FREQ_REQUEST,                      /* Machine sensor types. */
  DS_SENSOR_MACH_COUNT_REQUEST,
  DS_SENSOR_MACH_QUEUE_LENGTH,
  DS_SENSOR_MACH_QUEUE_CONTENT,
  DS_SENSOR_MACH_UTILIZATION,
  DS_SENSOR_MACH_WAITTIME_REQUEST,
  DS_SENSOR_MACH_THROUGHPUT,
  DS_SENSOR_MACH_SERVICETIME_REQUEST,
  
  DS_SENSOR_SYS_FREQ_SIGNAL,                           /* System sensor types. */
  DS_SENSOR_SYS_FREQ_REQUEST,
  DS_SENSOR_SYS_FREQ_PROCESS_CREATE,
  DS_SENSOR_SYS_FREQ_PROCESS_STOP,
  DS_SENSOR_SYS_COUNT_SIGNAL,
  DS_SENSOR_SYS_COUNT_REQUEST,
  DS_SENSOR_SYS_COUNT_PROCESS_CREATE,
  DS_SENSOR_SYS_COUNT_PROCESS_STOP,
  DS_SENSOR_SYS_LIFETIME_PROCESS,
  
  
  DS_SENSOR_MAX_ID                                  /* Use to verify validity of ID. */
} DSSensorType;

#endif 
