#pragma once

//#include <Lsc/SQLiteSys/sqlite3.h> // Trying embedded sqlite3 source as part of this project. 
#include <Lsc/DBQuery/Lib.h>
#include <Lsc/Rem/Rem.h>
#include <Lsc/Rem/Object.h>
#include <chrono>
#include <stack>
#include <memory>

struct sqlite3;

namespace Lsc::Db
{

#pragma region SQL_SCHEMA

class DBQUERY_LIB SchemaItem : public Object
{
    String mName;

public:
    
    using List = std::vector<Object *>;
    
    SchemaItem() = default;
    SchemaItem(SchemaItem &&) noexcept = default;
    SchemaItem(const SchemaItem &) = default;
    ~SchemaItem() override;
    
    SchemaItem(Object *);
    
};





/*

    NULL. The value is a NULL value.
    INTEGER. The value is a signed integer, stored in 1, 2, 3, 4, 6, or 8 bytes depending on the magnitude of the value.
    REAL. The value is a floating point value, stored as an 8-byte IEEE floating point number.
    TEXT. The value is a text string, stored using the database encoding (UTF-8, UTF-16BE or UTF-16LE).
    BLOB. The value is a blob of data, stored exactly as it was input.
    
    2.2. Date and Time Datatype
    SQLite does not have a storage class set aside for storing dates and/or times. Instead, the built-in Date And Time Functions of SQLite are capable of storing dates and times as TEXT, REAL, or INTEGER values:

    TEXT as ISO8601 strings ("YYYY-MM-DD HH:MM:SS.SSS").
    REAL as Julian day numbers, the number of days since noon in Greenwich on November 24, 4714 B.C. according to the proleptic Gregorian calendar.
    INTEGER as Unix Time, the number of seconds since 1970-01-01 00:00:00 UTC.
    Applications can chose to store dates and times in any of these formats and freely convert between formats using the built-in date and time functions.
    
    --------------------
    
    1. Overview
SQLite supports five date and time functions as follows:

date(timestring, modifier, modifier, ...)
time(timestring, modifier, modifier, ...)
datetime(timestring, modifier, modifier, ...)
julianday(timestring, modifier, modifier, ...)
strftime(format, timestring, modifier, modifier, ...)
All five date and time functions take a time string as an argument. The time string is followed by zero or more modifiers. The strftime() function also takes a format string as its first argument.

The date and time functions use a subset of IS0-8601 date and time formats. The date() function returns the date in this format: YYYY-MM-DD. The time() function returns the time as HH:MM:SS. The datetime() function returns "YYYY-MM-DD HH:MM:SS". The julianday() function returns the Julian day - the number of days since noon in Greenwich on November 24, 4714 B.C. (Proleptic Gregorian calendar). The strftime() routine returns the date formatted according to the format string specified as the first argument. The format string supports the most common substitutions found in the strftime() function from the standard C library plus two new substitutions, %f and %J. The following is a complete list of valid strftime() substitutions:

%d		day of month: 00
%f		fractional seconds: SS.SSS
%H		hour: 00-24
%j		day of year: 001-366
%J		Julian day number
%m		month: 01-12
%M		minute: 00-59
%s		seconds since 1970-01-01
%S		seconds: 00-59
%w		day of week 0-6 with Sunday==0
%W		week of year: 00-53
%Y		year: 0000-9999
%%		%
Notice that all other date and time functions can be expressed in terms of strftime():

Function		Equivalent strftime()
date(...)		strftime('%Y-%m-%d', ...)
time(...)		strftime('%H:%M:%S', ...)
datetime(...)		strftime('%Y-%m-%d %H:%M:%S', ...)
julianday(...)		strftime('%J', ...)
The only reasons for providing functions other than strftime() is for convenience and for efficiency.

2. Time Strings
A time string can be in any of the following formats:

YYYY-MM-DD
YYYY-MM-DD HH:MM
YYYY-MM-DD HH:MM:SS
YYYY-MM-DD HH:MM:SS.SSS
YYYY-MM-DDTHH:MM
YYYY-MM-DDTHH:MM:SS
YYYY-MM-DDTHH:MM:SS.SSS
HH:MM
HH:MM:SS
HH:MM:SS.SSS
now
DDDDDDDDDD
In formats 5 through 7, the "T" is a literal character separating the date and the time, as required by ISO-8601. Formats 8 through 10 that specify only a time assume a date of 2000-01-01. Format 11, the string 'now', is converted into the current date and time as obtained from the xCurrentTime method of the sqlite3_vfs object in use. The 'now' argument to date and time functions always returns exactly the same value for multiple invocations within the same sqlite3_step() call. Universal Coordinated Time (UTC) is used. Format 12 is the Julian day number expressed as a floating point value.

Formats 2 through 10 may be optionally followed by a timezone indicator of the form "[+-]HH:MM" or just "Z". The date and time functions use UTC or "zulu" time internally, and so the "Z" suffix is a no-op. Any non-zero "HH:MM" suffix is subtracted from the indicated date and time in order to compute zulu time. For example, all of the following time strings are equivalent:

2013-10-07 08:23:19.120
2013-10-07T08:23:19.120Z
2013-10-07 04:23:19.120-04:00
2456572.84952685
In formats 4, 7, and 10, the fractional seconds value SS.SSS can have one or more digits following the decimal point. Exactly three digits are shown in the examples because only the first three digits are significant to the result, but the input string can have fewer or more than three digits and the date/time functions will still operate correctly. Similarly, format 12 is shown with 10 significant digits, but the date/time functions will really accept as many or as few digits as are necessary to represent the Julian day number.

3. Modifiers
The time string can be followed by zero or more modifiers that alter date and/or time. Each modifier is a transformation that is applied to the time value to its left. Modifiers are applied from left to right; order is important. The available modifiers are as follows.

NNN days
NNN hours
NNN minutes
NNN.NNNN seconds
NNN months
NNN years
start of month
start of year
start of day
weekday N
unixepoch
localtime
utc
The first six modifiers (1 through 6) simply add the specified amount of time to the date and time specified by the preceding timestring and modifiers. The 's' character at the end of the modifier names is optional. Note that "±NNN months" works by rendering the original date into the YYYY-MM-DD format, adding the ±NNN to the MM month value, then normalizing the result. Thus, for example, the data 2001-03-31 modified by '+1 month' initially yields 2001-04-31, but April only has 30 days so the date is normalized to 2001-05-01. A similar effect occurs when the original date is February 29 of a leapyear and the modifier is ±N years where N is not a multiple of four.

The "start of" modifiers (7 through 9) shift the date backwards to the beginning of the current month, year or day.

The "weekday" modifier advances the date forward, if necessary, to the next date where the weekday number is N. Sunday is 0, Monday is 1, and so forth. If the date is already on the desired weekday, the "weekday" modifier leaves the date unchanged.

The "unixepoch" modifier (11) only works if it immediately follows a timestring in the DDDDDDDDDD format. This modifier causes the DDDDDDDDDD to be interpreted not as a Julian day number as it normally would be, but as Unix Time - the number of seconds since 1970. If the "unixepoch" modifier does not follow a timestring of the form DDDDDDDDDD which expresses the number of seconds since 1970 or if other modifiers separate the "unixepoch" modifier from prior DDDDDDDDDD then the behavior is undefined. For SQLite versions before 3.16.0 (2017-01-02), the "unixepoch" modifier only works for dates between 0000-01-01 00:00:00 and 5352-11-01 10:52:47 (unix times of -62167219200 through 106751991167).

The "localtime" modifier (12) assumes the time string to its left is in Universal Coordinated Time (UTC) and adjusts the time string so that it displays localtime. If "localtime" follows a time that is not UTC, then the behavior is undefined. The "utc" modifier is the opposite of "localtime". "utc" assumes that the string to its left is in the local timezone and adjusts that string to be in UTC. If the prior string is not in localtime, then the result of "utc" is undefined.

4. Examples
Compute the current date.
SELECT date('now');

Compute the last day of the current month.
SELECT date('now','start of month','+1 month','-1 day');

Compute the date and time given a unix timestamp 1092941466.
SELECT datetime(1092941466, 'unixepoch');

Compute the date and time given a unix timestamp 1092941466, and compensate for your local timezone.
SELECT datetime(1092941466, 'unixepoch', 'localtime');

Compute the current unix timestamp.
SELECT strftime('%s','now');

Compute the number of days since the signing of the US Declaration of Independence.
SELECT julianday('now') - julianday('1776-07-04');

Compute the number of seconds since a particular moment in 2004:
SELECT strftime('%s','now') - strftime('%s','2004-01-01 02:34:56');

Compute the date of the first Tuesday in October for the current year.
SELECT date('now','start of year','+9 months','weekday 2');

Compute the time since the unix epoch in seconds (like strftime('%s','now') except includes fractional part):
SELECT (julianday('now') - 2440587.5)*86400.0;

5. Caveats And Bugs
The computation of local time depends heavily on the whim of politicians and is thus difficult to get correct for all locales. In this implementation, the standard C library function localtime_r() is used to assist in the calculation of local time. The localtime_r() C function normally only works for years between 1970 and 2037. For dates outside this range, SQLite attempts to map the year into an equivalent year within this range, do the calculation, then map the year back.

These functions only work for dates between 0000-01-01 00:00:00 and 9999-12-31 23:59:59 (julian day numbers 1721059.5 through 5373484.5). For dates outside that range, the results of these functions are undefined.

Non-Vista Windows platforms only support one set of DST rules. Vista only supports two. Therefore, on these platforms, historical DST calculations will be incorrect. For example, in the US, in 2007 the DST rules changed. Non-Vista Windows platforms apply the new 2007 DST rules to all previous years as well. Vista does somewhat better getting results correct back to 1986, when the rules were also changed.

All internal computations assume the Gregorian calendar system. It is also assumed that every day is exactly 86400 seconds in duration.
 
*/
class DBQUERY_LIB Field : public SchemaItem
{
    String mName;

public:
    enum class Type : uint8_t
    {
        NUL = 0,
        INT,
        REAL,
        TEXT,
        BLOB
    };
    
    struct Flag
    {
        uint8_t PK: 1;
        uint8_t NUL: 1;
        uint8_t Uniq : 1;
    };
    
    enum class Date : uint8_t
    {
        TIME = 0,
        STAMP,
        DATETIME
    };
    
    using List = std::vector<Field *>;
    Field() = default;
    Field(Field &&) noexcept = default;
    Field(const Field &) = default;
    ~Field() override;
};




class DBQUERY_LIB Table : public SchemaItem
{
    Field::List mFields;
public:
    
    using List = std::vector<Table *>;
    
    Table() = default;
    Table(Table &&) noexcept = default;
    Table(const Table &) = default;
    
    ~Table() override;
    
};

class DBQUERY_LIB Schema : public SchemaItem
{
    Table::List mTables;

public:
    
    Schema() = default;
    Schema(Schema &&) noexcept = default;
    Schema(const Schema &) = default;
    
    ~Schema() override;
    
    static Expect<Schema *> Load(std::string DbName_);
    
};

#pragma endregion SQL_SCHEMA



class DBQUERY_LIB QueryItem : public Object
{
    String      mText;
    QueryItem* mParent = nullptr;
public:
    using List = std::vector<QueryItem*>;
    
    QueryItem() = default;
    QueryItem(const QueryItem&) = default;
    QueryItem(QueryItem&&) = default;

    QueryItem(QueryItem& Parent_);


    ~QueryItem() override;
private:
    QueryItem::List* mChildren = nullptr;

};


class DBQUERY_LIB Query
{
    String                  mText;
    std::stack<std::string> mStack;
    
public:
    Query() = default;
    Query(Query &&) noexcept = default;
    Query(const Query &) = default;
    ~Query();
    
    Query &operator<<(std::string Obj_);
    template<typename T> Query &operator<<(T Arg_)
    {
        mText << Arg_;
        return *this;
    }
    
    #pragma region SQL_COMMANDS
    Query &Select(Query &Q_);
    Query &Delete(Query &Q_);
    Query &Update(Query &Q_);
    Query &Insert(Query &Q_);
    #pragma endregion SQL_COMMANDS
    std::string Text();
};




class DBQUERY_LIB Database
{
    sqlite3     *mHandle = nullptr;
    std::string mDbName;
public:
    
    using Return = Expect<sqlite3 *>;
    
    Database() = default;
    Database(Database &&) = default;
    Database(const Database&) = default;
    
    Database(std::string DbName_);
    
    ~Database() = default;

    std::string Filename();
    void SetName(std::string Name_);
    Return Open();
    Return Close();
    Return Create();
    
};
}


