<?php
  require_once("connectserv.php");
  echo $date = date("Y/m/d");
  echo $time = date("H:i:s");
  $a_id = mysqli_real_escape_string($conn,$_GET['alert_id']);
  $a_machine = mysqli_real_escape_string($conn,$_GET['machine_id']);
  $a_temp = mysqli_real_escape_string($conn,$_GET['alert_temp']);
  $a_humidity = mysqli_real_escape_string($conn,$_GET['alert_humidity']);
  $a_smoke = mysqli_real_escape_string($conn,$_GET['alert_smoke']);
  $a_machinen = "node00".$a_machine;

  $a_id2 = mysqli_real_escape_string($conn,$_GET['alert_id2']);
  $a_machine2 = mysqli_real_escape_string($conn,$_GET['machine_id2']);
  $a_temp2 = mysqli_real_escape_string($conn,$_GET['alert_temp2']);
  $a_humidity2 = mysqli_real_escape_string($conn,$_GET['alert_humidity2']);
  $a_smoke2 = mysqli_real_escape_string($conn,$_GET['alert_smoke2']);
  $a_machinen2 = "node00".$a_machine2;

  $a_id3 = mysqli_real_escape_string($conn,$_GET['alert_id3']);
  $a_machine3 = mysqli_real_escape_string($conn,$_GET['machine_id3']);
  $a_temp3 = mysqli_real_escape_string($conn,$_GET['alert_temp3']);
  $a_humidity3 = mysqli_real_escape_string($conn,$_GET['alert_humidity3']);
  $a_smoke3 = mysqli_real_escape_string($conn,$_GET['alert_smoke3']);
  $a_machinen3 = "node00".$a_machine3;

  if($a_machine==1){
    $sql = "UPDATE alert SET machine_name = '$a_machinen', alert_temp = '$a_temp',
    alert_humidity = '$a_humidity',alert_smoke = '$a_smoke', alert_date = '$date', alert_time = '$time' WHERE alert_id =$a_id";

  }
  if($a_machine2==2){
    $sql = "UPDATE alert SET machine_name = '$a_machinen2', alert_temp = '$a_temp2',
    alert_humidity = '$a_humidity2',alert_smoke = '$a_smoke2', alert_date = '$date', alert_time = '$time' WHERE alert_id =$a_id2";
  }
  if($a_machine3==3){
    $sql = "UPDATE alert SET machine_name = '$a_machinen3', alert_temp = '$a_temp3',
    alert_humidity = '$a_humidity3',alert_smoke = '$a_smoke3', alert_date = '$date', alert_time = '$time' WHERE alert_id =$a_id3";
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
