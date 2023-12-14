<html>
<head>
<h3>Cities Search</h3>
</head>
<body>
<form action="search.php">
Search for: <input type="text" name="searchFor" value="<?php echo $_REQUEST["searchFor"]; ?>">
<input type="submit" value="Go!">
<br><br>
<?php
if ($_REQUEST["searchFor"]) {
  try {
    $conn = mysqli_connect("MYDB", "root", "av", "world");
    $query = "SELECT countries.name, cities.name, cities.latitude, cities.longitude ".
      "FROM cities JOIN countries ON cities.country=countries.id ".
      "WHERE cities.name LIKE ? ORDER BY 1,2";
    $stmt = $conn->prepare($query);

    $searchFor = "%".$_REQUEST["searchFor"]."%";
    $stmt->bind_param("s", $searchFor);
    $stmt->execute();
    $result = $stmt->get_result();

    echo "<table><tr><td>Country</td><td>City</td><td>Lat</td>
 <td>Long</td></tr>";
    foreach ($result->fetch_all(MYSQLI_NUM) as $row) {
      echo "<tr>";
      foreach($row as $data) {
        echo "<td>".$data."</td>";
      }
      echo "</tr>";
    }
    echo "</table>";

  } catch (Exception $e) {
    echo "Exception " . $e->getMessage();
  }
}
?>
</form>
</body>
</html>	