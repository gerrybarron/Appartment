<?php
    include "connection.php";
    $json_string = "";
    $parsed_json = "";
    $hum = "";
    $temp = "";
    $gas = "";
    $lat = "";
    $long = "";
    $sel1 = $dbh->prepare("SELECT * FROM tbl_devices");
    $sel1->execute();
    $sel1->rowCount();

    $dataSet = '';
    $count=0;
    $dataArray = $sel1->fetchAll(PDO::FETCH_ASSOC);

    foreach ($dataArray as $deviceName) {
      $json_string.$count = file_get_contents("https://dweet.io:443/get/latest/dweet/for/".$deviceName["fld_devicename"]);
      $parsed_json = json_decode($json_string.$count);  
      foreach ($parsed_json->{'with'} as $item) {
        $hum = $item->content->Humidity;
        $temp = $item->content->Temperature;
        $gas = $item->content->Gas;
        $lat = $item->content->Latitude;
        $long = $item->content->Longitude;

        $dataSet .= '["'.$deviceName["fld_devicename"].'",'. $lat.', '.$long.', 0, '.$hum.', '.$temp.','.$gas.'],';
      }
      $count++;
    }
    $newDataSet = rtrim($dataSet, ',');

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
<!DOCTYPE html>
<html lang="en">
  <head>
    <title>Styled Map Types</title>
    <meta name="viewport" content="width=device-width,initial-scale=1.0, user-scalable=yes">
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <!-- Font Awesome -->
    <link rel="stylesheet" href="css/font-awesome.min.css">

    <!-- Bootstrap core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Material Design Bootstrap -->
    <link href="css/mdb.min.css" rel="stylesheet">

    <!-- Your custom styles (optional) -->
    <link href="css/style.css" rel="stylesheet">

    <style>
      /* Always set the map height explicitly to define the size of the div
       * element that contains the map. */
      #map {
        height: 100%;
        position: relative;
        width: 100%;
      }
      
      /* Optional: Makes the sample page fill the window. */
      html, body {
        height: 100%;
        margin: 0;
        padding: 0;
      }
    </style>
  </head>
  <body>

  <!--Navbar-->
  <nav class="navbar navbar-dark primary-color-dark">

    <!-- Collapse button-->
    <button class="navbar-toggler hidden-sm-up" type="button" data-toggle="collapse" data-target="#collapseEx">
        <i class="fa fa-bars"></i>
    </button>

    <div class="container">

        <!--Collapse content-->
        <div class="collapse navbar-toggleable-xs" id="collapseEx">
            <!--Navbar Brand-->
            <a class="navbar-brand" href="#">Navbar</a>
            <!--Links-->
            <ul class="nav navbar-nav">
                <li class="nav-item active">
                    <a class="nav-link" href="#">Home <span class="sr-only">(current)</span></a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="#">About</a>
                </li>
            </ul>
        </div>
        <!--/.Collapse content-->

    </div>

</nav>
<!--/.Navbar-->
<!-- Button trigger modal -->
<button type="button" class="btn btn-primary btn-lg" data-toggle="modal" data-target="#myModal" id="trigmode">
    Launch demo modal
</button>

<!-- Modal -->
<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
    <div class="modal-dialog" role="document">
        <!--Content-->
        <div class="modal-content">
            <!--Header-->
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                    <span aria-hidden="true">&times;</span>
                </button>
                <h4 class="modal-title" id="myModalLabel">Modal title</h4>
            </div>
            <!--Body-->
            <div class="modal-body">
              <div id="mapdal"></div>
            </div>
        </div>
        <!--/.Content-->
    </div>
</div>
<!-- /.Live preview-->
    <div id="map"></div>
    <script>
      var map;
      var start = '14.817915, 120.283194';
      var trueDevices = [
        //['gerrybarron', <?php echo $lat; ?>, <?php echo $long;?>, 0, <?php echo $hum;?>, <?php echo $temp;?>, <?php echo $gas;?>]
        <?php echo $newDataSet; ?>
      ];
      var firestation = [
          ['Fire Station',14.817915, 120.283194,9]
      ];
      
      var end="";
      var request;
      var directionsDisplay;
      var directionsService;
      
      function initMap() {

        function setMarkers(map) {
        // Adds markers to the map.

        // Marker sizes are expressed as a Size of X,Y where the origin of the image
        // (0,0) is located in the top left of the image.

        // Origins, anchor positions and coordinates of the marker increase in the X
        // direction to the right and in the Y direction down.
        var image = {
          url: 'https://raw.githubusercontent.com/gerrybarron/Barron/master/normal.png',
          // This marker is 20 pixels wide by 32 pixels high.
          size: new google.maps.Size(50, 50),
          // The origin for this image is (0, 0).
          origin: new google.maps.Point(0, 0),
          // The anchor for this image is the base of the flagpole at (0, 32).
          anchor: new google.maps.Point(0, 0)
        };
        var alrt_image = {
          url: 'https://raw.githubusercontent.com/gerrybarron/Barron/master/alert.png',
          // This marker is 20 pixels wide by 32 pixels high.
          size: new google.maps.Size(50, 50),
          // The origin for this image is (0, 0).
          origin: new google.maps.Point(0, 0),
          // The anchor for this image is the base of the flagpole at (0, 32).
          anchor: new google.maps.Point(0, 32)
        };
        var danger_image = {
          url: 'https://raw.githubusercontent.com/gerrybarron/Barron/master/danger.png',
          // This marker is 20 pixels wide by 32 pixels high.
          size: new google.maps.Size(50, 50),
          // The origin for this image is (0, 0).
          origin: new google.maps.Point(0, 0),
          // The anchor for this image is the base of the flagpole at (0, 32).
         anchor: new google.maps.Point(25, 25)
        };
        var firestation_image = {
          url: 'https://raw.githubusercontent.com/gerrybarron/Barron/master/firestation2.png',
          // This marker is 20 pixels wide by 32 pixels high.
          size: new google.maps.Size(50, 50),
          // The origin for this image is (0, 0).
          origin: new google.maps.Point(0, 0),
          // The anchor for this image is the base of the flagpole at (0, 32).
          anchor: new google.maps.Point(25, 25)
        };
        // Shapes define the clickable region of the icon. The type defines an HTML
        // <area> element 'poly' which traces out a polygon as a series of X,Y points.
        // The final coordinate closes the poly by connecting to the first coordinate.
        var shape = {
          coords: [1, 1, 1, 20, 18, 20, 18, 1],
          type: 'poly'
        };

        for (var i = 0; i < trueDevices.length; i++) {
            var trueDevice = trueDevices[i];
            if (trueDevice[4] >= 60 && trueDevice[5] <= 30 && trueDevice[6]<=60) {
              var marker = new google.maps.Marker({
                position: {lat: trueDevice[1], lng: trueDevice[2]},
                map: map,
                icon: image,
                shape: shape,
                title: trueDevice[0],
                zIndex: trueDevice[3]
              }); 
            }
            else if (trueDevice[4] <= 60 && trueDevice[5] <= 30 && trueDevice[6]<=60){
              var marker = new google.maps.Marker({
                position: {lat: trueDevice[1], lng: trueDevice[2]},
                map: map,
                icon: alrt_image,
                shape: shape,
                title: trueDevice[0],
                zIndex: trueDevice[3]
              }); 
            }
            else if (trueDevice[4] >= 60 && trueDevice[5] >= 30 && trueDevice[6]<=60){
              var marker = new google.maps.Marker({
                position: {lat: trueDevice[1], lng: trueDevice[2]},
                map: map,
                icon: alrt_image,
                shape: shape,
                title: trueDevice[0],
                zIndex: trueDevice[3]
              }); 
            }
            else if (trueDevice[4] >= 60 && trueDevice[5] <= 30 && trueDevice[6]>=60){
              var marker = new google.maps.Marker({
                position: {lat: trueDevice[1], lng: trueDevice[2]},
                map: map,
                icon: alrt_image,
                shape: shape,
                title: trueDevice[0],
                zIndex: trueDevice[3]
              }); 
            }
            else if (trueDevice[4] <= 60 && trueDevice[5] >= 30 && trueDevice[6]<=60){
              var marker = new google.maps.Marker({
                position: {lat: trueDevice[1], lng: trueDevice[2]},
                map: map,
                icon: danger_image,
                shape: shape,
                title: trueDevice[0],
                zIndex: trueDevice[3]
              }); 
              end = String(trueDevices[0][1]+", "+trueDevices[0][2]);
              directionsDisplay.setMap(map);
              
                $("#trigmode").trigger("click");

                  var startModal = '14.817915, 120.283194';
                  var endModal = trueDevices[0][1]+", "+trueDevices[0][2];

                  var directionsServiceser = new google.maps.DirectionsService();
                  var directionsDisplayplay = new google.maps.DirectionsRenderer();

                  var mapModal = new google.maps.Map(document.getElementById('mapdal'), {
                    zoom:7,
                    mapTypeId: google.maps.MapTypeId.ROADMAP
                  });
                  
                  directionsDisplayplay.setMap(mapModal);         

                  var request = {
                    origin: startModal, 
                    destination: endModal,
                    travelMode: google.maps.DirectionsTravelMode.DRIVING
                  };

                  directionsServiceser.route(request, function(response, status) {
                    if (status == google.maps.DirectionsStatus.OK) {
                      directionsDisplayplay.setDirections(response);
                    }
                  });  
            }
            else if (trueDevice[4] <= 60 && trueDevice[5] >= 30 && trueDevice[6]>=60){
              var marker = new google.maps.Marker({
                position: {lat: trueDevice[1], lng: trueDevice[2]},
                map: map,
                icon: danger_image,
                shape: shape,
                title: trueDevice[0],
                zIndex: trueDevice[3]
              }); 
              end = String(trueDevices[0][1]+", "+trueDevices[0][2]);
              directionsDisplay.setMap(map);
            }
            else if (trueDevice[4] >= 60 && trueDevice[5] >= 30 && trueDevice[6]>=60){
              var marker = new google.maps.Marker({
                position: {lat: trueDevice[1], lng: trueDevice[2]},
                map: map,
                icon: danger_image,
                shape: shape,
                title: trueDevice[0],
                zIndex: trueDevice[3]
              }); 
              end = String(trueDevices[0][1]+", "+trueDevices[0][2]);
              directionsDisplay.setMap(map);
            }
        }
        
        for (var i = 0; i < firestation.length; i++) {
          var firestat = firestation[i];
          var marker2 = new google.maps.Marker({
            position: {lat: firestat[1], lng: firestat[2]},
            map: map,
            icon: firestation_image,
            shape: shape,
            title: firestat[0],
            zIndex: firestat[3]
          });
        }
      }
        // Create a new StyledMapType object, passing it an array of styles,
        // and the name to be displayed on the map type control.
        var styledMapType = new google.maps.StyledMapType(
            [
          {elementType: 'geometry', stylers: [{color: '#ebe3cd'}]},
          {elementType: 'labels.text.fill', stylers: [{color: '#523735'}]},
          {elementType: 'labels.text.stroke', stylers: [{color: '#f5f1e6'}]},
          {
            featureType: 'administrative',
            elementType: 'geometry.stroke',
            stylers: [{color: '#c9b2a6'}]
          },
          {
            featureType: 'administrative.land_parcel',
            elementType: 'geometry.stroke',
            stylers: [{color: '#dcd2be'}]
          },
          {
            featureType: 'administrative.land_parcel',
            elementType: 'labels.text.fill',
            stylers: [{color: '#ae9e90'}]
          },
          {
            featureType: 'landscape.natural',
            elementType: 'geometry',
            stylers: [{color: '#dfd2ae'}]
          },
          {
            featureType: 'poi',
            elementType: 'geometry',
            stylers: [{color: '#dfd2ae'}]
          },
          {
            featureType: 'poi',
            elementType: 'labels.text.fill',
            stylers: [{color: '#93817c'}]
          },
          {
            featureType: 'poi.park',
            elementType: 'geometry.fill',
            stylers: [{color: '#a5b076'}]
          },
          {
            featureType: 'poi.park',
            elementType: 'labels.text.fill',
            stylers: [{color: '#447530'}]
          },
          {
            featureType: 'road',
            elementType: 'geometry',
            stylers: [{color: '#f5f1e6'}]
          },
          {
            featureType: 'road.arterial',
            elementType: 'geometry',
            stylers: [{color: '#fdfcf8'}]
          },
          {
            featureType: 'road.highway',
            elementType: 'geometry',
            stylers: [{color: '#f8c967'}]
          },
          {
            featureType: 'road.highway',
            elementType: 'geometry.stroke',
            stylers: [{color: '#e9bc62'}]
          },
          {
            featureType: 'road.highway.controlled_access',
            elementType: 'geometry',
            stylers: [{color: '#e98d58'}]
          },
          {
            featureType: 'road.highway.controlled_access',
            elementType: 'geometry.stroke',
            stylers: [{color: '#db8555'}]
          },
          {
            featureType: 'road.local',
            elementType: 'labels.text.fill',
            stylers: [{color: '#806b63'}]
          },
          {
            featureType: 'transit.line',
            elementType: 'geometry',
            stylers: [{color: '#dfd2ae'}]
          },
          {
            featureType: 'transit.line',
            elementType: 'labels.text.fill',
            stylers: [{color: '#8f7d77'}]
          },
          {
            featureType: 'transit.line',
            elementType: 'labels.text.stroke',
            stylers: [{color: '#ebe3cd'}]
          },
          {
            featureType: 'transit.station',
            elementType: 'geometry',
            stylers: [{color: '#dfd2ae'}]
          },
          {
            featureType: 'water',
            elementType: 'geometry.fill',
            stylers: [{color: '#b9d3c2'}]
          },
          {
            featureType: 'water',
            elementType: 'labels.text.fill',
            stylers: [{color: '#92998d'}]
          }
        ],
            {name: 'Styled Map'});

        // Create a map object, and include the MapTypeId to add
        // to the map type control.
        map = new google.maps.Map(document.getElementById('map'), {
          center: {lat: 14.821251, lng: 120.287235},
          zoom: 15,
          mapTypeControlOptions: {
            mapTypeIds: ['roadmap', 'satellite', 'hybrid', 'terrain',
                    'styled_map']
          }

        });
        directionsDisplay = new google.maps.DirectionsRenderer();
        directionsService = new google.maps.DirectionsService();
        
        setMarkers(map);
       
        request = {
          origin: start, 
          destination: end,
          travelMode: google.maps.DirectionsTravelMode.DRIVING
        };
        
        directionsService.route(request, function(response, status) {
          if (status == google.maps.DirectionsStatus.OK) {
            directionsDisplay.setDirections(response);
          }
        });
        //Associate the styled map with the MapTypeId and set it to display.
        map.mapTypes.set('styled_map', styledMapType);
        map.setMapTypeId('styled_map');
      }
    </script>
    <script async defer
    src="https://maps.googleapis.com/maps/api/js?key=AIzaSyAOSrVBmfLfJNg2hdGZ14PCaMSRt5jAqn4&callback=initMap">
    </script>
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