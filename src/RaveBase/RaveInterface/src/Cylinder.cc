#include "DataFormats/GeometrySurface/interface/Plane.h"
#include "DataFormats/GeometrySurface/interface/TangentPlane.h"
#include "DataFormats/GeometrySurface/interface/GeomExceptions.h"

#include "rave/Cylinder.h"
#include <cfloat>

namespace ravesurf {

Cylinder::Cylinder ( const rave::Point3D & pos, const rave::Point3D & normal, float radius ):
		pos_ ( pos ),
		norm_ ( normal ),
		radius_ (radius),
		Surface(RaveToCmsObjects().convert(pos), TkRotation<float>()),
		theRadius(radius) //
		{}

// intinalisieren
// Scalar theRadius;
// Surface( const PositionType& pos, const RotationType& rot) :
// Base( pos, rot), theMediumProperties(0.,0.), m_mpSet(false) {}

rave::Point3D Cylinder::positionRave() const
{
  return pos_;
}

rave::Vector3D Cylinder::axisRave() const
{
  return norm_;
}

float Cylinder::radiusRave() const
{
  return radius_;
}


// cms
Surface::Side Cylinder::side( const LocalPoint& p, Scalar toler) const
{
  Scalar lz = p.perp() - radius();
  return (fabs(lz)<toler ? SurfaceOrientation::onSurface :
	  (lz>0 ? SurfaceOrientation::positiveSide : SurfaceOrientation::negativeSide));
}

ReferenceCountingPointer<TangentPlane>
Cylinder::tangentPlane (const LocalPoint& aPoint) const
{
  return tangentPlane(toGlobal(aPoint));
}

ReferenceCountingPointer<TangentPlane>
Cylinder::tangentPlane (const GlobalPoint& aPoint) const
{
  //
  // Tangent plane at specified point. In order to avoid
  // possible numerical problems currently no attempt is made
  // to verify, if the point is actually on the cylinder.
  //
  // local y parallel to axis
  GlobalVector yPlane(toGlobal(LocalVector(0.,0.,1.)));
  // local x normal to y and a vector linking the specified
  // point with the axis
  GlobalVector xPlane(yPlane.cross(aPoint-position()));
  Scalar size = xPlane.mag();
  if ( size<FLT_MIN )
    throw GeometryError("Attempt to construct TangentPlane on cylinder axis");
  xPlane /= size;
//   // local z defined by x and y (should point outwards from axis)
//   GlobalVector zPlane(xPlane.cross(yPlane));

  return ReferenceCountingPointer<TangentPlane>(new TangentPlane(aPoint,
								 RotationType(xPlane,
									      yPlane),
								 this));
}
} // ravesurf
