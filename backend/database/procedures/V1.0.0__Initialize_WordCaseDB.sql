/*******************************************************************************
** PROJECT:    Word Case Conversion Engine
** COMPONENT:  Database Schema & Metadata
** AUTHOR:     Nitish Singh
** VERSION:    1.0.0 (Initial Version)
** DESCRIPTION: 
** - Bootstrap: Ensures [WordCaseDB] exists on the instance.
** - Audit: Creates [SchemaVersionLog] to track environment state.
** - Schema: Creates [ConversionTypes] for metadata-driven conversion logic.
** - Sync: Deploys [usp_InitializeConversionTypes] to manage the 13 core enums.
*******************************************************************************/

-- 1. BOOTSTRAP: Ensure Database Exists
USE master;
GO

IF NOT EXISTS (SELECT name FROM sys.databases WHERE name = 'WordCaseDB')
BEGIN
    CREATE DATABASE WordCaseDB;
    PRINT 'SUCCESS: Database [WordCaseDB] created by Nitish Singh.';
END
GO

USE WordCaseDB;
GO

-- 2. AUDIT: Version History Log
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[SchemaVersionLog]') AND type in (N'U'))
BEGIN
    CREATE TABLE dbo.SchemaVersionLog (
        VersionID INT PRIMARY KEY IDENTITY(1,1),
        VersionNumber VARCHAR(20) NOT NULL,
        Author VARCHAR(50) NOT NULL,
        AppliedDate DATETIME DEFAULT GETDATE(),
        Description VARCHAR(255)
    );
END
GO

-- 3. SCHEMA: Create Table ConversionTypes
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[ConversionTypes]') AND type in (N'U'))
BEGIN
    CREATE TABLE dbo.ConversionTypes (
        Id INT PRIMARY KEY IDENTITY(1,1),
        CodeName VARCHAR(50) NOT NULL UNIQUE, 
        DisplayName VARCHAR(100) NOT NULL,    
        ConversionValue INT NOT NULL,         
        IsActive BIT DEFAULT 1,
        LastModified DATETIME DEFAULT GETDATE()
    );
    
    INSERT INTO dbo.SchemaVersionLog (VersionNumber, Author, Description) 
    VALUES ('1.0.0', 'Nitish Singh', 'Initial version: Schema creation and core metadata seeding.');
    
    PRINT 'SUCCESS: Table [ConversionTypes] created.';
END
ELSE
BEGIN
    PRINT 'INFO: Table [ConversionTypes] already exists.';
END
GO

-- 4. LOGIC: Create or Alter Synchronization Stored Procedure
IF OBJECT_ID('dbo.usp_InitializeConversionTypes', 'P') IS NOT NULL
    DROP PROCEDURE dbo.usp_InitializeConversionTypes;
GO

CREATE PROCEDURE dbo.usp_InitializeConversionTypes
AS
/*******************************************************************************
** Name: usp_InitializeConversionTypes
** Ver:  1.0.0
** Author: Nitish Singh
** Desc: Synchronizes the 13 hard-coded conversion enums with the database.
*******************************************************************************/
BEGIN
    SET NOCOUNT ON;

    MERGE INTO dbo.ConversionTypes AS Target
    USING (VALUES 
        ('Alternating', 'Alternating Case', 0),
        ('Capitalize', 'Capitalize', 1),
        ('Lower', 'Lower Case', 2),
        ('Upper', 'Upper Case', 3),
        ('Sentence', 'Sentence Case', 4),
        ('Toggle', 'Toggle Case', 5),
        ('Reverse', 'Reverse String', 6),
        ('RemoveVowels', 'Remove Vowels', 7),
        ('RemoveSpaces', 'Remove Spaces', 8),
        ('InvertWords', 'Invert Words', 9),
        ('SnakeCase', 'Snake Case', 10),
        ('KebabCase', 'Kebab Case', 11),
        ('LeetSpeak', 'Leet Speak', 12)
    ) AS Source (CodeName, DisplayName, ConversionValue)
    ON Target.CodeName = Source.CodeName
    
    -- Insert new types if they don't exist
    WHEN NOT MATCHED BY TARGET THEN
        INSERT (CodeName, DisplayName, ConversionValue, IsActive)
        VALUES (Source.CodeName, Source.DisplayName, Source.ConversionValue, 1)
        
    -- Update existing types if DisplayName or Value changed in script
    WHEN MATCHED THEN
        UPDATE SET 
            Target.DisplayName = Source.DisplayName,
            Target.ConversionValue = Source.ConversionValue,
            Target.LastModified = GETDATE();

    PRINT 'SUCCESS: ConversionTypes metadata synchronized.';
END
GO

-- 5. DEPLOYMENT EXECUTION
EXEC dbo.usp_InitializeConversionTypes;
GO

-- 6. FINAL VERIFICATION
SELECT * FROM dbo.SchemaVersionLog;
SELECT * FROM dbo.ConversionTypes;
GO