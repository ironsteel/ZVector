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
#include <QColor>

#include "GroupManager.hpp"
#include "Tools/ToolFactory.hpp"

class GLCanvas : public QGLWidget
{
	Q_OBJECT
public:
	explicit GLCanvas(QWidget *parent = 0);
	virtual ~GLCanvas()
	{
		//   delete m_program;
		delete m_groupManager;
	}
	void redrawSelectionBufer();
        void setZoomFactor(float zoom_factor);
	void collapseSelectedGroup();

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
        void wheelEvent(QWheelEvent *);

public slots:
	void changeTool( Tool* tool ) { m_currentTool = tool; }
        void rotateShapeByAngle(int angle);

        inline Shape* getCurrentShape();
        inline void flush();

        void groupSelectedShapes();

        void pushCurrentShapeBack();

        void popCurrentShapeFront();

        void saveSceneToFile(std::string filename);

        void restoreSceneFromFile(std::string filename);



private:
        void applyViewportTransform();
        struct { float x,y; } m_diff;

	QVector2D m_mousePos;
	GroupManager* m_groupManager;
	Tool* m_currentTool;
	ToolFactory* m_toolFactory;
        QGLShaderProgram* m_program;

        float m_zoom;
        float m_x;
        float m_y;
        int m_width;
        int m_height;

        bool leftButtonPressed;
        bool middleButtonPressed;
};

Shape* GLCanvas::getCurrentShape()
{
        return m_groupManager->getCurrentShape();
}

void GLCanvas::flush()
{
        updateGL();
        paintGL();
}

#endif // GLCANVAS_H
