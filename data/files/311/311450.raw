module TestFuncs

using Base.Test
using MariaDB

# This means we could use a different database, that had the same interface as MariaDB
const DB = MariaDB

function connect_to_database(user::AbstractString,
                             password::AbstractString,
                             dbname::AbstractString)
    db = DB.init()
    @test db.ptr != C_NULL

    connect_flags = DB.CLIENT_MULTI_RESULTS | DB.CLIENT_MULTI_STATEMENTS
    db = DB.real_connect(db, "localhost", user,
                              passwd=password, dbname=dbname, flags=connect_flags)
    @test db.ptr != C_NULL

    db
end

function create_test_database()
    db = connect_to_database("root", "", "")
    cmd = """create database db_test;
             alter database db_test DEFAULT CHARACTER SET = utf8mb4;
             alter database db_test DEFAULT COLLATE = utf8mb4_unicode_ci;
             create user 'maarten'@'localhost' identified by 'pwd_maarten';
             grant ALL on db_test.* to 'maarten'@'localhost';
             create user 'michael'@'localhost' identified by 'pwd_michael';
	     grant SELECT on db_test.* to 'michael'@'localhost';"""
    rc = DB.real_query(db, cmd)
    rc != DB_OK && println(DB.last_error(db))
    @test rc == DB_OK
    DB.close(db)
end

function drop_test_database()
    db = connect_to_database("root", "", "")

    command = """drop user 'maarten'@'localhost';
		 drop user 'michael'@'localhost';
    		 drop database db_test;"""
    rc = DB.real_query(db, command)
    rc != DB_OK && println(DB.last_error(db))
    @test rc == DB_OK

    DB.close(db)
end

function prepare_database()
    db = connect_to_database("root", "", "")
    # Check to see if we already have a database 'db_test'
    command = "show databases like 'db_test';"
    println("got here 1!")
    rc = DB.real_query(db, command)
    println("got here 2!")
    rc != DB_OK && println(DB.last_error(db))
    @test rc == DB_OK
    fc = DB.field_count(db)
    println("got here 3!")
    @test fc == 1
    reshndl = DB.use_result(db)
    println("got here 4!")
    @test reshndl.ptr != C_NULL
    rowCount = 0
    println("result type\n")
    dump(reshndl)
    println()
    while length(DB.fetch_row(reshndl)) != 0
        rowCount += 1
        println("got here 5! $rowCount")
    end

    println("got here 6!")
    DB.free_result(reshndl)
    println("got here 7!")

    DB.close(db)
    println("got here 8!")
    if rowCount > 0
        println("Database 'db_test' found")
        println("\tRecreating...")
        drop_test_database()
    else
        println("Database 'db_test' not found")
        println("\tCreating...")
    end
    create_test_database()
end

function create_tables()
    println("\tCreating tables ...")
    db = connect_to_database("maarten", "pwd_maarten", "db_test")
    @test db.ptr != C_NULL

    command = "create table Persons (
        ID INT NOT NULL AUTO_INCREMENT,
        FirstName VARCHAR(64),
        LastName VARCHAR(64),
        PRIMARY KEY pk_persons(ID)
    );"
    command = string(command, "insert into Persons (FirstName, LastName) values
        ('Michael', 'Brands'),
        ('Florian', 'Lechner'),
        ('Maarten', 'Heremans'),
        ('Diederik', 'Herbert'),
        ('Ulf', 'Nystrom'),
        ('Roy', 'Williams'),
        ('Enzo', 'Brands'),
        ('Scott', 'Jones'),
        ('Joby', 'Chacko'),
        ('Junia', 'Antony'),
        ('Thara', 'H'),
        ('Jayakrishnan', 'Nair'),
        ('Kiran', 'P'),
        ('Andrew', 'Joy')
    ;")

    rc = DB.real_query(db, command)
    if rc != DB_OK
        println(DB.last_error(db))
    end
    @test rc == DB_OK

    # Loop over results and clear out
    rc = DB.next_result(db)
    while rc == DB_OK
        if DB.field_count(db) > 0
            reshndl = DB.store_result(db)
            DB.free_result(reshndl)
        end
        rc = DB.next_result(db)
    end
    if rc > DB_OK
        println(DB.last_error(db))
    end
    @test rc == DB.NO_MORE_RESULTS

    command = "create table Skills (
        ID INT NOT NULL AUTO_INCREMENT,
        Skill VARCHAR(64),
        PRIMARY KEY pk_skills(ID)
    );"
    command = string(command, "insert into Skills (Skill) values
        ('Management'),
        ('Programming'),
        ('Housekeeping'),
        ('Testing'),
        ('Eating'),
        ('PITA'),
        ('Design'),
        ('Crazy Good Ideas'),
        ('Nkn'),
        ('Julia')
    ;")

    rc = DB.real_query(db, command)
    if rc != DB_OK
        println(DB.last_error(db))
    end
    @test rc == DB_OK

    # Loop over results and clear out
    rc = DB.next_result(db)
    while rc == DB_OK
        if DB.field_count(db) > 0
            reshndl = DB.store_result(db)
            DB.free_result(reshndl)
        end
        rc = DB.next_result(db)
    end
    if rc > DB_OK
        println(DB.last_error(db))
    end
    @test rc == DB.NO_MORE_RESULTS

    cmd1 = "create table PersonSkills (
        PersonID INT NOT NULL,
        SkillID INT NOT NULL,
        PRIMARY KEY pk_person_skils(PersonID, SkillID),
        CONSTRAINT fk_personskills_personid FOREIGN KEY (PersonID) references Persons(ID)
            ON UPDATE CASCADE ON DELETE CASCADE,
        CONSTRAINT fk_personskills_skillid FOREIGN KEY (SkillID) references Skills(ID)
            ON UPDATE CASCADE ON DELETE RESTRICT
    );"
    cmd2 = "insert into PersonSkills (PersonID, SkillID) values
        (1, 1), (1, 4), (1, 8),
        (2, 1), (2, 2), (2, 4),
        (3, 2), (3, 4), (3, 9), (3, 10),
        (4, 1), (4, 3),
        (5, 3),
        (6, 1), (6, 7),
        (7, 2), (7, 4), (7, 10),
        (8, 2), (8, 5), (8, 6), (8, 10),
        (9, 1), (9, 2), (9, 4),
        (10, 2), (10, 4), (10, 10),
        (11, 2), (11, 4),
        (12, 2), (12, 4), (12, 10),
        (13, 7),
        (14, 2), (14, 7)
    ;"

    rc = DB.real_query(db, string(cmd1, cmd2))
    if rc != DB_OK
        println(DB.last_error(db))
    end
    @test rc == DB_OK

    # Loop over results and clear out
    rc = DB.next_result(db)
    while rc == DB_OK
        if DB.field_count(db) > 0
            reshndl = DB.store_result(db)
            DB.free_result(reshndl)
        end
        rc = DB.next_result(db)
    end
    if rc > DB_OK
        println(DB.last_error(db))
    end
    @test rc == DB.NO_MORE_RESULTS

    DB.close(db)
end

function print_fields(fields::Vector{DB.DB_FIELD})
    for f in fields
        println("""
                Field: {
                    name:      $(f.name),
                    table:     $(f.table),
                    db:        $(f.db),
                    catalog:   $(f.catalog),
                    def:       $(f.def),
                    length:    $(f.length),
                    max_len:   $(f.max_length),
                    flags:     $(f.flags),
                    decimals:  $(f.decimals),
                    charsetnr: $(f.charsetnr),
                    field_type:$(f.field_type)
                }""")
        end
    end

function print_row(row::Vector{Any})
    for c in row
        print(c," | ")
    end
    println("")
end

function print_result(db::DB.DB)
    reshndl = DB.use_result(db)
    fields = DB.fetch_fields(reshndl)
    print_fields(fields)
    row = DB.fetch_row(reshndl)
    while length(row) != 0
        print_row(row)
        row = DB.fetch_row(reshndl)
    end
    DB.free_result(reshndl)
end

function query_tables()
    println("\tQuerying tables ...")
    db = connect_to_database("michael", "pwd_michael", "db_test")
    @test db != C_NULL

    command = "Select * from Persons;"
    command = string(command, "Select * from Skills;")
    rc = DB.real_query(db, command)
    if rc != DB_OK
        println(DB.last_error(db))
    end
    @test rc == DB_OK

    if DB.field_count(db) > 0
        print_result(db)
    end

    rc = DB.next_result(db)
    while rc == DB_OK
        if DB.field_count(db) > 0
            print_result(db)
        end
        rc = DB.next_result(db)
    end
    if rc > DB_OK
        println(DB.last_error(db))
    end
    @test rc == DB.NO_MORE_RESULTS

    command = "select p.FirstName, p.LastName, s.Skill from PersonSkills as ps inner join
    Persons as p on (ps.PersonID = p.ID) inner join Skills as s on (ps.SkillID = s.ID) order
    by p.FirstName, p.LastNAme, s.Skill;"

    rc = DB.real_query(db, command)
    if rc != DB_OK
        println(DB.last_error(db))
    end
    @test rc == DB_OK
    if DB.field_count(db) > 0
        print_result(db)
    end

    DB.close(db)
end

rc = DB.library_init()
@test rc == DB_OK

prepare_database()
create_tables()
query_tables()

DB.library_end()
end
