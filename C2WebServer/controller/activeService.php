<?php
$serviceAddress = $_GET["ip"];
$servicePort = 1212;
$url = "http://$serviceAddress:$servicePort/";
$response = file_get_contents($url);
Header("Location: ../index.php");
?>
