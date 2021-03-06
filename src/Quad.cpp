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

#include "Quad.hpp"
#include <GL/gl.h>
#include <sstream>
#include <math.h>

Quad::Quad( double origin_x, double origin_y )
{
	double* m = m_mat.data();
        m[12] = origin_x;
        m[13] = origin_y;
	m_normals.push_back(QVector2D( -EIGEN_1_1_0, -EIGEN_1_1_0 ));
	m_normals.push_back(QVector2D( -EIGEN_1_1_0,  EIGEN_1_1_0 ));
	m_normals.push_back(QVector2D(  EIGEN_1_1_0,  EIGEN_1_1_0 ));
	m_normals.push_back(QVector2D(  EIGEN_1_1_0, -EIGEN_1_1_0 ));
	m_vertices.push_back(QVector2D());
	m_vertices.push_back(QVector2D());
	m_vertices.push_back(QVector2D());
	m_vertices.push_back(QVector2D());
}

void Quad::resize(double x, double y)
{
        m_vertices[1].setY( m_vertices[1].y() + y);
        m_vertices[2].setX( m_vertices[2].x() + x);
        m_vertices[2].setY( m_vertices[2].y() + y);
        m_vertices[3].setX( m_vertices[3].x() + x);

        m_bounds[0].setX(m_vertices[0].x());
        m_bounds[0].setY(m_vertices[0].y());
        m_bounds[1].setX(m_vertices[2].x());
        m_bounds[1].setY(m_vertices[2].y());

        //        if(m_vertices[0].x() < m_vertices[2].x())
        //        {
        //                m_vertices[2].setX( m_vertices[2].x() + x);
        //                m_vertices[3].setX( m_vertices[3].x() + x);
        //        }
        //        else
        //        {
        //                m_vertices[0].setX( m_vertices[0].x() + x);
        //                m_vertices[3].setX( m_vertices[1].x() + x);
        //        }

        //        if(m_vertices[0].y() < m_vertices[2].y())
        //        {
        //                m_vertices[2].setY( m_vertices[2].y() + y);
        //                m_vertices[1].setY( m_vertices[1].y() + y);
        //        }
        //        else
        //        {
        //                m_vertices[0].setY( m_vertices[0].y() + y);
        //                m_vertices[1].setY( m_vertices[3].y() + y);
        //        }

        //        m_bounds[0] = m_vertices[0].x();
        //        m_bounds[1] = m_vertices[0].y();
        //        m_bounds[2] = m_vertices[2].x();
        //        m_bounds[3] = m_vertices[2].y();
}

std::string Quad::toString()
{
        std::stringstream serialized;

        serialized << QUAD << " " << Shape::toString() << "\n";

	return serialized.str();
}

QVector2D Quad::getCenter()
{
	QVector3D bb[2];
	getBoundingBox4dv(bb);
	QVector2D center;
	double* m_mat_data = m_mat.data();
	
	center.setX((bb[1].x() - bb[0].x())/2 + m_mat_data[12]);
        center.setY((bb[1].y() - bb[0].y())/2 + m_mat_data[13]);
	
	return center;
}

void Quad::rotate(double angle)
{
      rotateAround(angle, getCenter());
}
