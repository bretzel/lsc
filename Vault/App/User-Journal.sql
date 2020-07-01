PRAGMA foreign_keys = '1';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
PRAGMA encoding
PRAGMA foreign_keys
PRAGMA foreign_keys = '0';
PRAGMA foreign_keys
ALTER TABLE "main"."User" ADD COLUMN 	"Field4"	INTEGER
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
CREATE TABLE "sqlb_temp_table_1" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER
);
INSERT INTO "main"."sqlb_temp_table_1" SELECT "ID","UserName","Birth","Field4" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_1" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_2" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2
);
INSERT INTO "main"."sqlb_temp_table_2" SELECT "ID","UserName","Birth","A" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_2" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
ALTER TABLE "main"."User" ADD COLUMN 	"Field5"	INTEGER
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_3" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	INTEGER
);
INSERT INTO "main"."sqlb_temp_table_3" SELECT "ID","UserName","Birth","A","Field5" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_3" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_4" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	INTEGER
);
INSERT INTO "main"."sqlb_temp_table_4" SELECT "ID","UserName","Birth","A","Name" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_4" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_5" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	INTEGER
);
INSERT INTO "main"."sqlb_temp_table_5" SELECT "ID","UserName","Birth","A","Name" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_5" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_6" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT
);
INSERT INTO "main"."sqlb_temp_table_6" SELECT "ID","UserName","Birth","A","Name" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_6" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_7" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT
);
INSERT INTO "main"."sqlb_temp_table_7" SELECT "ID","UserName","Birth","A","Name" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_7" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
SELECT COUNT(*) FROM (SELECT COUNT("_rowid_") FROM "main"."User" WHERE "Name" IS NULL);
SELECT COUNT("_rowid_") FROM "main"."User" WHERE "Name" IS NULL LIMIT 0, 49999;
CREATE TABLE "sqlb_temp_table_8" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT
);
INSERT INTO "main"."sqlb_temp_table_8" SELECT "ID","UserName","Birth","A","Name" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_8" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
SELECT COUNT(*) FROM (SELECT COUNT("_rowid_") FROM "main"."User" WHERE "Name" IS NULL);
SELECT COUNT("_rowid_") FROM "main"."User" WHERE "Name" IS NULL LIMIT 0, 49999;
CREATE TABLE "sqlb_temp_table_9" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT
);
INSERT INTO "main"."sqlb_temp_table_9" SELECT "ID","UserName","Birth","A","Name" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_9" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
SELECT COUNT(*) FROM (SELECT COUNT("_rowid_") FROM "main"."User" WHERE "A" IS NULL);
SELECT COUNT("_rowid_") FROM "main"."User" WHERE "A" IS NULL LIMIT 0, 49999;
CREATE TABLE "sqlb_temp_table_10" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT
);
INSERT INTO "main"."sqlb_temp_table_10" SELECT "ID","UserName","Birth","A","Name" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_10" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
ALTER TABLE "main"."User" ADD COLUMN 	"Field6"	INTEGER
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_11" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT,
	"Created"	INTEGER
);
INSERT INTO "main"."sqlb_temp_table_11" SELECT "ID","UserName","Birth","A","Name","Field6" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_11" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_12" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT,
	"Created"	INTEGER
);
INSERT INTO "main"."sqlb_temp_table_12" SELECT "ID","UserName","Birth","A","Name","Created" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_12" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_13" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT,
	"Created"	INTEGER
);
INSERT INTO "main"."sqlb_temp_table_13" SELECT "ID","UserName","Birth","A","Name","Created" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_13" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_14" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT,
	"Created"	TEXT
);
INSERT INTO "main"."sqlb_temp_table_14" SELECT "ID","UserName","Birth","A","Name","Created" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_14" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_15" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT,
	"Created"	TEXT
);
INSERT INTO "main"."sqlb_temp_table_15" SELECT "ID","UserName","Birth","A","Name","Created" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_15" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_16" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT,
	"Created"	TEXT
);
INSERT INTO "main"."sqlb_temp_table_16" SELECT "ID","UserName","Birth","A","Name","Created" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_16" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_17" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	INTEGER,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT,
	"Created"	TEXT
);
INSERT INTO "main"."sqlb_temp_table_17" SELECT "ID","UserName","Birth","A","Name","Created" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_17" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_18" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	TEXT,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT,
	"Created"	TEXT
);
INSERT INTO "main"."sqlb_temp_table_18" SELECT "ID","UserName","Birth","A","Name","Created" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_18" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_19" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	TEXT,
	"A"	INTEGER DEFAULT 2,
	"Name"	TEXT,
	"Created"	TEXT
);
INSERT INTO "main"."sqlb_temp_table_19" SELECT "ID","UserName","Birth","A","Name","Created" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_19" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
CREATE TABLE "sqlb_temp_table_20" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"UserName"	TEXT NOT NULL UNIQUE,
	"Birth"	TEXT,
	"A"	INTEGER DEFAULT 255,
	"Name"	TEXT,
	"Created"	TEXT
);
INSERT INTO "main"."sqlb_temp_table_20" SELECT "ID","UserName","Birth","A","Name","Created" FROM "main"."User";
PRAGMA defer_foreign_keys
PRAGMA defer_foreign_keys = '1';
DROP TABLE "main"."User";
ALTER TABLE "main"."sqlb_temp_table_20" RENAME TO "User"
PRAGMA defer_foreign_keys = '0';
PRAGMA database_list;
SELECT type,name,sql,tbl_name FROM "main".sqlite_master;
SELECT type,name,sql,tbl_name FROM sqlite_temp_master;
PRAGMA "main".foreign_key_check
PRAGMA foreign_keys = '1';
 
