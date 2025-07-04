# analysis
# creating a soccer ball, with a grey shadow on it

# specifications
# thoroughly think which object needs to be on the bottom and which need to be on the top
# all the coordinates are pre-determined so there is no need of input from the user.
# careful use of the getX() and getY() methods so the polygons and the lines align

# design
# create the outer circle, then all the black pentagons. Use getX() and getY() to note the coordinates
# create the lines joining the pentagons. Use getX() and getY() to note the coordinates
# add a grey-filled circle beneath a white-filled circle to give the perception of shadow on the ball

import graphics as g


def main():

    # creating a window
    window = g.GraphWin("Soccer Ball - Taha", 400, 400)
    window.setCoords(0.0, 0.0, 400, 400)
    window.setBackground("white")

    # grey-filled circle beneath the white-filled circle to give the perception of a shadow
    Outline = g.Circle(g.Point(200, 200), 120)
    Outline.setFill("light grey")
    Outline.draw(window)
    Outline.setWidth(4)

    # white-filled circle over the grey-filled circle to give the perception of a shadow
    WhiteShade = g.Circle(g.Point(164, 261), 130)
    WhiteShade.setOutline("white")
    WhiteShade.setFill("white")
    WhiteShade.draw(window)

    # pentagons 1 through 6
    pentagon1 = g.Polygon(g.Point(155, 220), g.Point(140, 265), g.Point(185, 295), g.Point(230, 270), g.Point(210, 220))
    pentagon1.setFill("black")
    pentagon1.draw(window)

    pentagon2 = g.Polygon(g.Point(210, 125), g.Point(238, 173), g.Point(282, 174), g.Point(290, 130), g.Point(240, 100))
    pentagon2.setFill("black")
    pentagon2.draw(window)

    pentagon3 = g.Polygon(g.Point(100, 135), g.Point(95, 175), g.Point(130, 170), g.Point(160, 125), g.Point(140, 105))
    pentagon3.setFill("black")
    pentagon3.draw(window)

    pentagon4 = g.Polygon(g.Point(106, 271), g.Point(116, 260), g.Point(92, 223), g.Point(82, 223), g.Point(92, 253))
    pentagon4.setFill("black")
    pentagon4.draw(window)

    pentagon5 = g.Polygon(g.Point(174, 317), g.Point(192, 311), g.Point(214, 317))
    pentagon5.setFill("black")
    pentagon5.draw(window)

    pentagon6 = g.Polygon(g.Point(263, 300), g.Point(264, 273), g.Point(298, 227), g.Point(313, 239), g.Point(295, 272), g.Point(277, 291))
    pentagon6.setFill("black")
    pentagon6.draw(window)

    # lines 1 through 11
    line1 = g.Line(g.Point(191, 314), g.Point(185, 293))
    line1.draw(window)
    line1.setWidth(3)

    line2 = g.Line(g.Point(228, 269), g.Point(266, 272))
    line2.draw(window)
    line2.setWidth(3)

    line3 = g.Line(g.Point(297, 231), g.Point(280, 172))
    line3.draw(window)
    line3.setWidth(3)

    line4 = g.Line(g.Point(288, 131), g.Point(295, 129))
    line4.draw(window)
    line4.setWidth(3)

    line5 = g.Line(g.Point(240, 103), g.Point(234, 86))
    line5.draw(window)
    line5.setWidth(3)

    line6 = g.Line(g.Point(211, 126), g.Point(157, 126))
    line6.draw(window)
    line6.setWidth(3)

    line7 = g.Line(g.Point(140, 108), g.Point(147, 92))
    line7.draw(window)
    line7.setWidth(3)

    line8 = g.Line(g.Point(129, 168), g.Point(156, 221))
    line8.draw(window)
    line8.setWidth(3)

    line9 = g.Line(g.Point(141, 264), g.Point(115, 259))
    line9.draw(window)
    line9.setWidth(3)

    line10 = g.Line(g.Point(96, 173), g.Point(91, 224))
    line10.draw(window)
    line10.setWidth(3)

    line11 = g.Line(g.Point(208, 221), g.Point(238, 172))
    line11.draw(window)
    line11.setWidth(3)

    # reintroduce the black outline of the ball so that it is on top of all the other objects
    Outline = g.Circle(g.Point(200, 200), 120)
    Outline.draw(window)
    Outline.setWidth(4)

    # delay
    window.getMouse()
    window.close()


main()