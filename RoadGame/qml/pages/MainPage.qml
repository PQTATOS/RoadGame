/*******************************************************************************
**
** Copyright (C) 2022 ru.auroraos
**
** This file is part of the Моё приложение для ОС Аврора project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

import QtQuick 2.0
import QtPositioning 5.3
import Sailfish.Silica 1.0
import src 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    Item {
        id: mainArea
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: controllsArea.top

        Rectangle{
            id: debug_1
            anchors.fill: parent
            color: "Gray"

           Rectangle {
                id: playableArea
                anchors.fill: parent
                anchors.margins: 30
                color: "black"
                 GScene{
                     id: scene
                     anchors.fill: parent
                     width: parent.width
                     height: parent.height

                     Component.onCompleted: {
                         loadGame();
                         loadLevel(1);
                     }
                 }
                Timer {
                     id: render_timer
                     interval: 32
                     running: true
                     repeat: true
                     onTriggered: {
                          scene.requestPaint()
                     }
                 }
                 Timer {
                     id: sim_timer
                     interval: 16
                     running: true
                     repeat: true
                     onTriggered: {
                         scene.requestSimUpdate()
                     }
                 }

                 MouseArea {
                     id: ct_area
                     anchors.fill: parent

                     onPressed:{
                         scene.startAddingPath();
                         scene.addPathPoint(mouseX, mouseY);
                     }
                     onReleased: {
                         console.debug("stoped")
                         scene.stopAddingPath()
                     }

                     onPositionChanged:{
                         scene.addPathPoint(mouseX, mouseY);
                     }
                 }
            }
        }
    }

    Item {
        id: controllsArea
        width: parent.width
        height: 200
        anchors.bottom: parent.bottom

        Rectangle{
            id: debug_2
            anchors.fill: parent
            width: parent.width
            height: parent.height

            color: "black"
            border.color: "yellow"
            border.width: 4

            Row {
                anchors.fill: parent
                anchors.margins: 17
                width: parent.width
                height: parent.height

                spacing: 30

                Button{
                    id: menuBtn
                    width: 150
                    height: 150
                    icon.source: "qrc:/src/img/menu_btn.png"
                    icon.color: "white"
                    icon.width: 150
                    icon.height: 150
                    icon.cache: true
                    anchors.verticalCenter: parent.verticalCenter

                    onClicked: {
                        mapBtn.visible = !mapBtn.visible
                        clearBtn.visible = !clearBtn.visible
                        simBtn.visible = !simBtn.visible
                        downBtn.visible = !downBtn.visible
                        upBtn.visible = !upBtn.visible

                    }
                }
                Button{
                    id: mapBtn
                    width: 150
                    height: 150
                    icon.source: "qrc:/src/img/map_btn.png"
                    icon.color: "white"
                    icon.width: 150
                    icon.height: 150
                    icon.cache: true
                    anchors.verticalCenter: parent.verticalCenter
                    visible: false

                    onClicked: {pageStack.replace(Qt.resolvedUrl("LevelSelectPage.qml"))}
                }
                Button{
                    id: clearBtn
                    width: 150
                    height: 150
                    icon.source: "qrc:/src/img/clear_btn.png"
                    icon.color: "white"
                    icon.width: 150
                    icon.height: 150
                    icon.cache: true
                    anchors.verticalCenter: parent.verticalCenter
                    visible: false

                    onClicked: {scene.restartLevel()}
                }
                Button{
                    id: simBtn
                    width: 150
                    height: 150
                    icon.source: "qrc:/src/img/sim_btn.png"
                    icon.color: "white"
                    icon.width: 150
                    icon.height: 150
                    icon.cache: true
                    anchors.verticalCenter: parent.verticalCenter

                    onClicked: {console.debug("Sim button")}
                }

                Button{
                    id: downBtn
                    width: 150
                    height: 150
                    icon.source: "qrc:/src/img/down_btn.png"
                    icon.color: "white"
                    icon.width: 150
                    icon.height: 150
                    icon.cache: true
                    anchors.verticalCenter: parent.verticalCenter

                    onClicked: {console.debug("down button")}
                }
                Button{
                    id: upBtn
                    width: 150
                    height: 150
                    icon.source: "qrc:/src/img/up_btn.png"
                    icon.color: "white"
                    icon.width: 150
                    icon.height: 150
                    icon.cache: true
                    anchors.verticalCenter: parent.verticalCenter

                    onClicked: {console.debug("Up button")}
                }
            }
        }
    }
}

