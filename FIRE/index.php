<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta http-equiv="x-ua-compatible" content="ie=edge">

    <title>Find, Inform, Response and Enhance</title>

    <!-- Font Awesome -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.6.0/css/font-awesome.min.css">

    <!-- Bootstrap core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Material Design Bootstrap -->
    <link href="css/mdb.min.css" rel="stylesheet">

    <!-- Your custom styles (optional) -->
    <link href="css/style.css" rel="stylesheet">

</head>

<body>
	<?php
    $json_string = file_get_contents("https://dweet.io:443/get/latest/dweet/for/gerrybarrontest1");
    $parsed_json = json_decode($json_string);
    foreach ($parsed_json->{'with'} as $item) {
 	 	$hum = $item->content->Humidity;
 	 	$temp = $item->content->Temperature;
 	 	$gas = $item->content->Gas;
 	 	$lat = $item->content->Latitude;
 	 	$long = $item->content->Longitude;
		}
	
  	?>

    <!-- -->

    <h1 class="animated fadeIn"><?php echo $hum; ?></h1>
    <h2 class="animated fadeIn"><?php echo $temp; ?></h2>
    <h3 class="animated fadeIn"><?php echo $gas; ?></h3>
    <h3 class="animated fadeIn"><?php echo $lat; ?></h3>
	<h3 class="animated fadeIn"><?php echo $long; ?></h3>

	<div id="googleMap" style="width:100%;height:380px;"></div>
    <!--/-->


    <!-- SCRIPTS -->
    
   
    <!-- JQuery -->
    <script type="text/javascript" src="js/jquery-3.1.1.min.js"></script>

    <!-- Bootstrap tooltips -->
    <script type="text/javascript" src="js/tether.min.js"></script>

    <!-- Bootstrap core JavaScript -->
    <script type="text/javascript" src="js/bootstrap.min.js"></script>

    <!-- MDB core JavaScript -->
    <script type="text/javascript" src="js/mdb.min.js"></script>


</body>

</html>