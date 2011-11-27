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

#include "Group.hpp"
#include <limits>

void Group::deleteShapes()
{
	while( !m_shapes.empty() )
	{
		delete m_shapes.back();
		m_shapes.pop_back();
	}
}

void Group::addShape(Shape * shape)
{
	m_shapes.push_back(shape);
}

void Group::getBoundingBox4dv( double* bounds )
{
        bounds[0] = std::numeric_limits<double>::max();
        bounds[1] = bounds[0];
        bounds[2] = std::numeric_limits<double>::min();
        bounds[3] = bounds[2];

        QLinkedList<Shape*>::iterator it = m_shapes.begin();
        while(it != m_shapes.end()) {
                double shapeBounds[4];
                (*it)->getBoundingBox4dv(shapeBounds);

                if(shapeBounds[0] < bounds[0]) {
                        bounds[0] = shapeBounds[0];
                }
                if(shapeBounds[1] < bounds[1]) {
                        bounds[1] = shapeBounds[1];
                }

                if(shapeBounds[2] > bounds[2]) {
                        bounds[2] = shapeBounds[2];
                }
                if(shapeBounds[3] > bounds[3]) {
                        bounds[3] = shapeBounds[3];
                }
                ++it;
        }
}

void Group::draw(bool skipColor = false)
{
        glPushMatrix();
        glMultMatrixd(m_mat.constData());
        if(m_shapes.size())
        {
                QLinkedList<Shape*>::iterator sit = m_shapes.begin();
                while( sit != m_shapes.end())
                {
                        (*sit)->draw(skipColor);
                        sit++;
                }
                double boundingBox[4];
                getBoundingBox4dv(boundingBox);
                drawBoundingBox(boundingBox);
        }
        glPopMatrix();

}

void Group::setFillColorOpacity(double alpha)
{
        Shape::setFillColorOpacity(alpha);
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->setFillColorOpacity(alpha);
                sit++;
        }
}

void Group::setContourColorOpacity(double alpha)
{
        Shape::setContourColorOpacity(alpha);
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->setContourColorOpacity(alpha);
                sit++;
        }
}

void Group::setFillColor(const QColor &color)
{
        Shape::setFillColor(color);
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->setFillColor(color);
                sit++;
        }
}

void Group::setContourColor(const QColor &color)
{
        Shape::setContourColor(color);
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->setContourColor(color);
                sit++;
        }
}

void Group::setContourWidth(double width)
{
        Shape::setContourWidth(width);
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->setContourWidth(width);
                sit++;
        }
}

void Group::resize(double x, double y)
{
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->resize(x, y);
                sit++;
        }
}


