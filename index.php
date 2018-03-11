<html>
    <head>
        <title>Tutorial</title>
    </head>
    <body>
		<?php
		$servername = "mysql.cba.pl";
		$username = "smarthomeluna";
		$password = "haslo";
		$dbname = "piekos19";
		$conn = new mysqli($servername, $username, $password, $dbname);
		if ($conn->connect_error) {die("Connection failed: " . $conn->connect_error);}
		$sql = "SELECT id, dane1, dane2 FROM piekos199 ORDER BY id DESC LIMIT 100";
		$result = $conn->query($sql);
		if ($result->num_rows > 0) {
			echo '<table cellspacing="0" border="1" rules="rows" bordercolor="black">';
			echo '<tr>
					<td width="100px" bgcolor="silver" align="center">ID:</td>
					<td width="100px" bgcolor="gray" align="center">Dane1:</td>
					<td width="100px" bgcolor="silver" align="center">Dane2:</td>
				</tr>';
			while($row = $result->fetch_assoc()) {
				echo '<tr>
						<td bgcolor="silver" align="center">' . $row["id"]. '</td>
						<td bgcolor="gray" align="center">' . $row["dane1"].'</td>
						<td bgcolor="silver" align="center">' . $row["dane2"]. "</td>
					</tr>";
			}
			echo "</table>";
		} else {
			echo "0 results";
		}
		$conn->close();
		?>
    </body>
</html>