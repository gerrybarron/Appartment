var vLat=0, vLong=0, map;
var arrayDevice=[], aryHum=[], aryTemp=[], aryGas=[], aryLat=[], aryLong=[], markers=[];
var marker, i, vicon;

$(document).ready(function()
{
    vLat =14.821251; vLong =120.287235;
    document.getElementById('mapcanvas').style.width="100%";
    document.getElementById('mapcanvas').style.height="100%"; //scrheight + "px";

    getDevices(); //use to get Devices from API
    getDeviceStatus(); //use to get Status of devices from dweet.io
    
    google.maps.event.addDomListener(window, 'load',initialize(vLat, vLong, 12));   
    //startRefresh();
});
//function startRefresh(){
  //getDevices();
  //getDeviceStatus();
  //userMarkers();
//}
//setInterval(function(){startRefresh()}, 10000);

//Get available devices
function getDeviceStatus(){
    var ndevice = arrayDevice.length;
    for(var i=0; i<=arrayDevice.length-1; i++){
      $.ajax({
        type: "GET",
        url: "https://dweet.io:443/get/latest/dweet/for/"+arrayDevice[i],
        async: false,
        success: function(myData){
          console.log(myData);
          aryHum.push(myData.with[0].content.Humidity);
          aryTemp.push(myData.with[0].content.Temperature);
          aryGas.push(myData.with[0].content.Gas);
          aryLat.push(myData.with[0].content.Latitude);
          aryLong.push(myData.with[0].content.Longitude);
        }
      }); //end of ajax function  
    }//end of for loop
}

//Get status of devices
function getDevices(){
      $.ajax({
      type: "GET",
      url: "http://localhost/fire3/apitest.php",
      async: false,
      success: function(deviceData){
          console.log(deviceData);
          for(var i=0; i<=deviceData.length-1; i++){
          dvcId = deviceData[i].deviceid;
          arrayDevice.push(deviceData[i].devicename);
          }

      }
    }); //end of ajax function
}

function initialize(vLat, vLong, vZoom)
{
  var firedept = {lat: 14.821251, lng: 120.287235};
  //var myMapStyle = setMyMapStyle();
  //var mapReference = new google.maps.StyledMapType(myMapStyle, {name: "Styled Map"});
  var mapOptions = 
    {
      zoom: vZoom,
      center: new google.maps.LatLng(vLat, vLong),
      mapTypeId: google.maps.MapTypeId.ROADMAP,
      disableDefaultUI: true,
      mapTypeControlOptions: {
            mapTypeIds: [google.maps.MapTypeId.ROADMAP, "map_style"]}
    };
  
  map = new google.maps.Map(document.getElementById("mapcanvas"), mapOptions);
  //map.mapTypes.set("map_style", mapReference);
  //map.setMapTypeId("map_style");

  /*marker = new google.maps.Marker({
        position: new google.maps.LatLng(14.821251, 120.287235),
        map:map,
        icon: "img/fs-small-size.png"
  });*/
  //userMarkers();
  addMarkerFD(firedept);
  addMarkers();
}

function addMarkerFD(location){
  var markerFD = new google.maps.Marker({
    position:  location,
    map: map,
    icon: "img/fs-small-size.png"
  });
  markers.push(marker);
}

function addMarkers(){
  for(i=0; i<arrayDevice.length; i++){
    if (aryHum[i]>=60 && aryTemp[i]<=30 && aryGas[i]<=50) {
      vicon = "img/normal-small-size.png";
    }
    else if(aryHum[i]<=60 && aryTemp[i]<=30 && aryGas[i]<=50){
      vicon = "img/alert-small-size.png";
    }
    else if(aryHum[i]<=60 && aryTemp[i]>=30 && aryGas[i]<=50){
      vicon = "img/danger-small-size.png";
    }
    marker = new google.maps.Marker({
      position: new google.maps.LatLng(aryLat[i], aryLong[i]),
        map:map,
        icon:vicon
    }); 
    markers.push(marker);
  }
}

//function setMapOnAll(mapcanvas) {
  //for (var i = 0; i < markers.length; i++) {
    //markers[i].setMap(mapcanvas);
  //}
//}

//function showMarkers() {
  //setMapOnAll(mapcanvas);
//}

//Mark all devices in the map
function userMarkers() {
  for(i=0; i<arrayDevice.length; i++) {
    console.log(aryTemp[i]);
    if(aryHum[i]>=60 && aryTemp[i]<=30 && aryGas[i]<=50){
      vicon = "img/normal-small-size.png";
    }
    else if(aryHum[i]<=60 && aryTemp[i]<=30 && aryGas[i]<=50){
      vicon = "img/alert-small-size.png";
    }
    else if(aryHum[i]<=60 && aryTemp[i]>=30 && aryGas[i]<=50){
      vicon = "img/danger-small-size.png";
    }
    console.log(vicon)
    console.log(aryLat[i]);
    marker = new google.maps.Marker({
      position: new google.maps.LatLng(aryLat[i], aryLong[i]),
      map:map,
      icon: vicon
    });
  }
}