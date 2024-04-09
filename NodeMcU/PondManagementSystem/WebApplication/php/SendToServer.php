<?php
require_once 'dbConfig.php';

$Db = OpenCon();

$pondId = $_GET["Pond_Id"];
$phValue = $_GET["Ph_level"];
$Salinity = $_GET["Salinity_level"];
$temp = $_GET["Temp_level"];
$Level = $_GET["Water_level"];

$query = "INSERT INTO `readings`(`pondId`, `phValue`, `salinity`, `temp`, `level`) 
        VALUES ('$pondId','$phValue','$temp','$Level','$Salinity')";
$validate = mysqli_query($Db, $query);

if($validate){
    echo "Done";
}