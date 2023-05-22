<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // db connection sqlite
    $db = new PDO('sqlite:/var/www/html/C2WebServer/botnet.db');
    // get data from form
    $username = $_POST["username"];
    $password = $_POST["password"];
    
    // check username and password from db using prepared statement
    $stmt = $db->prepare("SELECT * FROM users WHERE user = ? AND password = ?");
    $stmt->execute([$username, $password]);
    $row = $stmt->fetch(PDO::FETCH_ASSOC);
    if($row){
        session_start();
        $_SESSION["username"] = $username;
        $_SESSION["password"] = $password;
        echo "Login success";
        header("Location: /C2WebServer/index.php");
    } else {
        header("Location: /C2WebServer/login/html");

    }
}
?>
    