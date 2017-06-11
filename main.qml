import QtQuick 2.6
import QtQuick.Window 2.2
import QtLocation 5.5
import QtPositioning 5.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(55, 45)
        zoomLevel: 5

//        MapItemView {
//            model: photoPointer
            MapQuickItem{
                coordinate {
                    latitude: 55
                    longitude: 45
                }
                anchorPoint.x: dronePointer.width / 2;
                anchorPoint.y: dronePointer.height / 2;
                sourceItem:
                    Column{
                        Image {id: dronePointer; source: "qrc:/plane.png"}
                    }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        photoPointer.addPointer(1, 55, 45)
                        console.log("Готово!")
                        //console.log("setPointer: " + "id: " + track_id + "lat: " + lat + "lon: " + lon )
                    }
                }
            }
        }

    }
//}
