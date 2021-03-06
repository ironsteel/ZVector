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

#ifndef QDRAWMAINWINDOW_H
#define QDRAWMAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>

#include "glcanvas.h"
#include "GLDebugBufferWidget.h"

namespace Ui {
class QDrawMainWindow;
}

class QDrawMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit QDrawMainWindow(QWidget *parent = 0);
	~QDrawMainWindow();

private slots:

        void on_doTranslate_clicked();
        void on_popShapeFront_clicked();
        void on_pushShapeBack_clicked();
        void keyPressEvent(QKeyEvent *e);

        void on_rotateMinus90_clicked();

        void on_rotatePlus90_clicked();

        void on_angleSpinbox_valueChanged(int );

        void rotateCurrentShapeBy(int angle);

        void on_actionDraw_Ellipse_triggered();

        void redrawSelectBuffer();

	void on_actionSelect_triggered();

	void on_actionCreate_triggered();

	void on_actionNew_triggered();

	void on_actionMove_triggered();

	void on_actionDraw_Triangle_triggered();

        void on_actionGroup_triggered();

        void on_colorTriangle_colorChanged(const QColor &);

        void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);

        void on_opacity_valueChanged(int value);

        void updateWidgetsForSelectedShape(Shape* shape);

        void on_outline_width_valueChanged(int arg1);

        void on_actionReset_Zoom_triggered();

        void on_autoShapeDetails_valueChanged(int arg1);

        void on_actionSave_as_triggered();

        void on_actionOpen_triggered();

	void on_actionUngroup_triggered();
	
        void on_width_valueChanged(double arg1);

        void on_height_valueChanged(double arg1);

private:
        Ui::QDrawMainWindow *ui;

        GLCanvas* getActiveCanvas();

signals:
	void changeTool (Tool*);
};

#endif // QDRAWMAINWINDOW_H
