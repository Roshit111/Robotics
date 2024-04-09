<?php

function OpenCon()
{
    $server = "localhost";
    $name = "root";
    $pwd = "";
    $dbName = "pond_management_system";

    $db = mysqli_connect($server, $name, $pwd, $dbName);

    if (!$db) {
        die("Connection failed: " . mysqli_connect_error());
    }

    echo "Connected successfully";

    return $db;
}

function CloseConn($db)
{
    mysqli_close($db);
}
