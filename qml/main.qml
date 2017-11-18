import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Chess")
    visible: true
    width: 800
    height: 600
    
    property int squareSize: 70

    property var images: [
      {'imgPath' : "/images/white_pawn.svg"},
      {'imgPath' : "/images/black_pawn.svg"},
      {'imgPath' : "/images/white_rook.svg"},
      {'imgPath' : "/images/black_rook.svg"},
      {'imgPath' : "/images/white_knight.svg"},
      {'imgPath' : "/images/black_knight.svg"},
      {'imgPath' : "/images/white_bishop.svg"},
      {'imgPath' : "/images/black_bishop.svg"},
      {'imgPath' : "/images/white_queen.svg"},
      {'imgPath' : "/images/black_queen.svg"},
      {'imgPath' : "/images/white_king.svg"},
      {'imgPath' : "/images/black_king.svg"},
    ]

    Item {
      id: gameBoard
      x: 0
      y: 0
      width : logic.boardSize * squareSize
      height: logic.boardSize * squareSize
      
      Image {
        source: "/images/chess_board.jpg"
        height: gameBoard.height
        width: gameBoard.width
      }
      
      Repeater {
        model: logic

        Image {
            id:h
          height: squareSize
          width : squareSize

          x: squareSize * positionX
          y: squareSize * positionY

          source: images[type].imgPath
          
          MouseArea {
            anchors.fill: parent
            drag.target: parent
            visible:logic.mouse
            property int startX: 0
            property int startY: 0

            onPressed: {
              startX = parent.x;
              startY = parent.y;
            }

            onReleased: {
              var fromX = startX / squareSize;
              var fromY = startY / squareSize;
              var toX   = (parent.x + mouseX) / squareSize;
              var toY   = (parent.y + mouseY) / squareSize;

              if (!logic.move(fromX, fromY, toX, toY)) {
                parent.x = startX;
                parent.y = startY;
              }
            }
          }
        }
      }
    }

    Item{
        height: 240
        anchors.left: gameBoard.right
              anchors.right: parent.right
              anchors.leftMargin: 10
              anchors.rightMargin: 10

        ColumnLayout{
            Button {
              id: startButton
              visible: logic.startButton
              text: "Start"
              onClicked: {
                logic.start();
              }
            }

            Button {
              id: loadButton
              text: "Load"
              visible: logic.loadButton
              onClicked: {
                logic.load();
                  }
            }

            Button {
              id: stopButton
              visible: logic.stopButton
              text: "Stop"
              onClicked: {
                logic.stop();
                }
            }

            Button {
               id: saveButton
               visible: logic.saveButton
               text: "Save"
               onClicked: {
                 logic.save();
                }
            }

            Button {
                id: prevButton
                text: "Prev"
                visible: logic.prevButton
                onClicked: {
                    logic.prev();
                 }
            }

            Button {
               id: nextButton
               text: "Next"
               visible: logic.nextButton
               onClicked: {
                   logic.next();
                 }
            }

            Button {
              id: continueButton
              text: "Continue"
              visible: logic.continueButton
              onClicked: {
                 logic.cont();
              }
            }

            Text {
            text: "Game over "
            visible: logic.game_overText
            }

        }
    }
}
