<?php
if($_SERVER["REQUEST_METHOD"] == "POST"){
    session_start();
    session_unset();
    session_destroy();
    header("Location: /C2WebServer/login/html/");
}
else
    header("Location: /C2WebServer/index.php");
?>