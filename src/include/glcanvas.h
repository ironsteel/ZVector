/*  ZVector - cross platform vector drawing program using Qt and OpenGL
 *  (University project)
 *  Copyright (C) 2011  Rangel Ivanov & Nayden Dochev
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contacts:
 *  Nayden Dochev: nayyden <at> google <dot> com
 *  Rangel Ivanov: iron_steel_88 <at> abv <dot> bg
 */

#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QLinkedList>
#include <QGLShaderProgram>
#include <QString>

#include "Shape.hpp"
#include "Group.hpp"

#include "Tools/Tool.hpp"
#include "Tools/ToolFactory.hpp"

class Group;

enum QDRAW_TOOL{
    QDRAW_TOOL_CREATE,
    QDRAW_TOOL_TRANSLATE,
    QDRAW_TOOL_RESIZE
};

class GLCanvas : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLCanvas(QWidget *parent = 0);
    virtual ~GLCanvas()
    {
        delete m_group->getMaster();
        delete m_program;
    }
    void redrawSelectionBufer();

signals:
    void sendFrameBuffer(QImage buffer);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *e);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event );
    void mouseMoveEvent(QMouseEvent * event );

public slots:
    void chageTool( Tool* tool ) { m_currentTool = tool; }

private:
    struct point
    {
        double x;
        double y;
    };

    QList<point> vertexList;
    QVector2D m_mousePos;

    Group* m_group;

    Tool* m_currentTool;
    ToolFactory* m_toolFactory;
    QGLShaderProgram* m_program;

    friend class Tool;
};

#endif // GLCANVAS_H
