<?php
  require_once("connectserv.php");
  echo $date = date("Y/m/d");
  echo $time = date("H:i:s");
  $machine = mysqli_real_escape_string($conn,$_GET['machine']);
  $id = mysqli_real_escape_string($conn,$_GET['n001_id']);
  $humidity = mysqli_real_escape_string($conn,$_GET['n001_humidity']);
  $temp = mysqli_real_escape_string($conn,$_GET['n001_temp']);
  $smoke = mysqli_real_escape_string($conn,$_GET['n001_smoke']);

  $machine2 = mysqli_real_escape_string($conn,$_GET['machine2']);
  $id2 = mysqli_real_escape_string($conn,$_GET['n002_id']);
  $humidity2 = mysqli_real_escape_string($conn,$_GET['n002_humidity']);
  $temp2 = mysqli_real_escape_string($conn,$_GET['n002_temp']);
  $smoke2 = mysqli_real_escape_string($conn,$_GET['n002_smoke']);

  $machine3 = mysqli_real_escape_string($conn,$_GET['machine3']);
  $id3 = mysqli_real_escape_string($conn,$_GET['n003_id']);
  $humidity3 = mysqli_real_escape_string($conn,$_GET['n003_humidity']);
  $temp3 = mysqli_real_escape_string($conn,$_GET['n003_temp']);
  $smoke3 = mysqli_real_escape_string($conn,$_GET['n003_smoke']);

  if($machine==1){
    $sql = "UPDATE node001 SET temperature = '$temp', humid = '$humidity',smoke = '$smoke',
    dates = '$date', times = '$time' WHERE tempid =$id";

  }
  if($machine2==2){
    $sql = "UPDATE node002 SET temperature = '$temp2', humid = '$humidity2',smoke = '$smoke2',
    dates = '$date', times = '$time'  WHERE tempid =$id2";
  }
  if($machine3==3){
    $sql = "UPDATE node003 SET temperature = '$temp3', humid = '$humidity3',smoke = '$smoke3',
    dates = '$date', times = '$time'  WHERE tempid =$id3";
  }

  $sql_query = mysqli_query($conn,$sql);
  if ($sql_query)
  {
    echo "Complete";
  }
  else
  {
    echo "Error";
  }
  mysqli_close($conn);
?>
