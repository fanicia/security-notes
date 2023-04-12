# SQL Injection

When logging into an application, you might see errors from the underlying databases.
This can be a sign of potential for SQL injection.
A good starting point to check for that would be:

```
admin' OR 1=1 -- //
```

This is good against queries such as `SELECT * from users where user=$user and pw=$pw`.
The early `' OR 1=1 -- //` is an attempt at ending the query early by outcommenting the `and...` statement and instead evaluating `1=1`

